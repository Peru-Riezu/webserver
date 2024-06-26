/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   ReturnType.cpp                                     :+:      :+:    :+:   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/06/07 11:48:15                                            */
/*   Updated: 2024/06/12 18:48:13 by amorion-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdio>
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

#include "engine.hpp"

ReturnType::ReturnType(int fd_param, std::string const &headers_param, pid_t child_pid_param)
	: fd(fd_param), headers(headers_param), child_pid(child_pid_param)
{
}

ReturnType::ReturnType(ReturnType const &copy)
{
	fd = copy.get_fd();
	headers = copy.get_headers();
	child_pid = copy.get_child_pid();
}

ReturnType::~ReturnType()
{
}

ReturnType const &ReturnType::operator=(ReturnType const &copy)
{
	fd = copy.get_fd();
	headers = copy.get_headers();
	child_pid = copy.get_child_pid();
	return (*this);
}

bool ReturnType::operator==(ReturnType const &rhs) const
{
	if (fd == rhs.get_fd() && headers == rhs.get_headers() && child_pid == rhs.get_child_pid())
	{
		return (true);
	}
	return (false);
}

int ReturnType::get_fd(void) const
{
	return (fd);
}

std::string const &ReturnType::get_headers(void) const
{
	return (headers);
}

pid_t ReturnType::get_child_pid(void) const
{
	return (child_pid);
}

bool ReturnType::is_cgi(void) const
{
	return (child_pid != NO_CHILD);
}

bool ReturnType::has_unrecoverable_error(void) const
{
	return (fd == -1);
}

#pragma GCC diagnostic pop
