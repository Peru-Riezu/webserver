/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_resource_is_a_directory_page.cpp                           */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/05/15 06:15:58                                            */
/*   Updated:  2024/05/15 06:32:13                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.hpp"
#include <stdexcept>

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

static void get_element(s_t_c_server_config_params &params, std::string &server_config, size_t &i, size_t &line,
						size_t &colum)
{
	if (is_double_quote(server_config, i) == false)
	{
		throw(std::invalid_argument(std::string("error: on line: ") + std::to_string(line) +
									", colum: " + std::to_string(colum) + ", expected '\"'"));
	}
	i++;
	colum++;
	std::string::iterator filename_end = find_double_quote(server_config, i);
	if (filename_end == server_config.end())
	{
		throw(std::invalid_argument(std::string("error: on line: ") + std::to_string(line) +
									", colum: " + std::to_string(colum - 1) + ", no matching '\"' found"));
	}
	std::string *filename =
		new std::string(server_config.begin() + static_cast<std::string::difference_type>(i), filename_end);
	resolve_scape_sequences(*filename, line, colum);
	delete params.resource_is_a_directory_page;
	params.resource_is_a_directory_page = filename;
}

void get_resource_is_a_directory_page(s_t_c_server_config_params &params, std::string &server_config, size_t &line,
									  size_t &colum, size_t &i)
{
	if (params.resource_is_a_directory_page_set == true)
	{
		throw(std::invalid_argument(std::string("error: on line: ") + std::to_string(line) +
									", colum: " + std::to_string(colum) +
									", redefinition of resource_is_a_directory_page attribute"));
	}
	params.resource_is_a_directory_page_set = true;
	i += std::string("directory_traversal").size();
	colum += std::string("directory_traversal").size();
	skip_spaces(server_config, i, line, colum);
	get_element(params, server_config, i, line, colum);
	skip_spaces(server_config, i, line, colum);
	if (server_config[i] != ';')
	{
		throw(std::invalid_argument(std::string("error: on line: ") + std::to_string(line) + ", colum: " +
									std::to_string(colum) + ", unexpected end of file while looking for ';'"));
	}
	i++;
	colum++;
}

#pragma GCC diagnostic pop