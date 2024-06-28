/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: handle_dir.cpp                                                 */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/06/12 16:56:16                                            */
/*   Updated:  2024/06/27 19:14:40                                            */
/*                                                                            */
/* ************************************************************************** */

#include "engine.hpp"
#include <dirent.h>
#include <fcntl.h>
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic warning "-Weverything"
#pragma GCC diagnostic ignored "-Wempty-translation-unit"
#pragma GCC diagnostic ignored "-Wunused-macros"
#pragma GCC diagnostic ignored "-Wextra-semi"
#pragma GCC diagnostic ignored "-Wunsafe-buffer-usage"
#pragma GCC diagnostic ignored "-Wc++98-compat"
#pragma GCC diagnostic ignored "-Wwritable-strings"
#pragma GCC diagnostic ignored "-Wlanguage-extension-token"
#pragma GCC diagnostic ignored "-Wpre-c++20-compat-pedantic"
#pragma GCC diagnostic ignored "-Wc++20-designator"
#pragma GCC diagnostic ignored "-Wc++98-compat-extra-semi"
;

static std::string get_relative_directory_name(std::string const &absolute, std::string const &base)
{
	return (absolute.substr(base.size() - 1, absolute.size() - base.size() - 1));
}

static std::vector<std::string> get_directory_entries(DIR *dirp)
{
	struct dirent           *ent;
	std::vector<std::string> directory_entries;

	ent = readdir(dirp); // NOLINT, note: I did not find a better syscall for this
	while (ent != nullptr)
	{
		directory_entries.push_back(ent->d_name);
		ent = readdir(dirp); // NOLINT
	}
	return (directory_entries);
}

static std::string compile_body(std::string const &dir_name, std::vector<std::string> const &directory_entries)
{
	std::string res;

	res += "<html>\r\n<head><title>" + dir_name + "</title></head>\r\n<body>\r\n<h1>" + dir_name + "</h1><hr><pre>\r\n";
	for (std::string const &entry : directory_entries)
	{
		res += "<a href=\"" + entry + "\">";
		res += entry + "</a>\r\n";
	}
	res += "</pre><hr></body>\r\n</html>\r\n";
	return (res);
}

static ReturnType handle_dir_internal(std::string const &headers, std::string const &body,
									  t_c_individual_server_config const &config)
{
	int const memfd = memfd_create("", 0);

	if (memfd == -1)
	{
		return (handle_error(500, config));
	}
	if (ftruncate(memfd, static_cast<ssize_t>(body.size())) == -1)
	{
		close(memfd);
		return (handle_error(500, config));
	}
	if (write(memfd, body.c_str(), body.size()) !=
		static_cast<ssize_t>(
			body.size())) // due to the trunc the previus trunc the condition will only fail if the syscall
						  // is interrupted by a signal or enocounters a error (non should happen)
	{
		close(memfd);
		return (handle_error(500, config));
	}
	return (ReturnType(memfd, headers, NO_CHILD));
}

ReturnType handle_dir(std::string &resource, t_c_route const &route, t_c_individual_server_config const &config,
					  struct stat statbuf)
{
	DIR                     *dirp = opendir(resource.c_str());
	std::string const        relative_directory_name = get_relative_directory_name(resource, route.get_path());
	std::vector<std::string> directory_entries;
	std::string              body;
	std::string const        current_time = get_current_time_as_string();
	std::string              headers;

	if (((statbuf.st_mode & S_IRUSR) == 0) && ((statbuf.st_mode & S_IRGRP) == 0))
	{
		return (handle_error(403, config)); // forbidden
	}
	if (route.get_resource().get_direcory_listing() == false)
	{
		return (handle_error_internal_internal(route.get_resource().get_file_is_a_directory_page(),
											   "HTTP/1.1 403 Forbidden\r\n"));
	}
	if (dirp == nullptr || current_time.empty() == true)
	{
		return (handle_error(500, config)); // internal server error
	}
	directory_entries = get_directory_entries(dirp);
	body = compile_body(relative_directory_name, directory_entries);
	headers = std::string("HTTP/1.1 200 OK\r\n") + "Server: webserv/0.1\r\n" + "Date: " + +"\r\n" +
			  "Content-Type: text/html\r\n" + "Content-Length: " + std::to_string(body.size()) + "\r\n" +
			  "Connection: close" + "\r\n\r\n";
	closedir(dirp);
	return (handle_dir_internal(headers, body, config));
}

#pragma GCC diagnostic pop
