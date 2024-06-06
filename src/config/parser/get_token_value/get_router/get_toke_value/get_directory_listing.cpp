/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_directory_listing.cpp                                      */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/06/04 12:11:29                                            */
/*   Updated:  2024/06/04 12:16:00                                            */
/*                                                                            */
/* ************************************************************************** */

#include "../get_router.hpp"
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

static bool get_on_or_off(std::vector<t_c_token> &tokens, size_t &i, char const *config_file)
{
	if (tokens[i].get_token() == "on")
	{
		return (true);
	}
	if (tokens[i].get_token() == "off")
	{
		return (false);
	}
	throw(std::invalid_argument(std::string(config_file) + ":" + tokens[i].get_position().to_string() +
								": error expected on or off, but found: " + tokens[i].get_token() + '\n'));
}

void get_direcory_listing(t_c_resource_constructor_params &params, std::vector<t_c_token> &tokens, size_t &i,
						  char const *config_file)
{
	t_c_position const position = tokens[i].get_position();

	if (params.directory_listing_position.is_valid() == true)
	{
		throw(std::invalid_argument(std::string(config_file) + ": " + position.to_string() +
									" : error: redefinition of directory_listing attribute previusly defined at: " +
									params.directory_listing_position.to_string() + '\n'));
	}
	i++;
	if (i == tokens.size())
	{
		throw(std::invalid_argument(std::string(config_file) +
									": error, expected a value for directory_listing atribute at " +
									position.to_string() + ", but found end of file\n"));
	}
	params.directory_listing = get_on_or_off(tokens, i, config_file);
	params.directory_listing_position = position;
	i++;
	if (i == tokens.size())
	{
		throw(std::invalid_argument(std::string(config_file) +
									": error, expected a semicolon, to end the directory_listing"
									" attribute at " +
									position.to_string() + ", but found end of file\n"));
	}
	if (tokens[i].get_token()[0] != ';')
	{
		throw(std::invalid_argument(std::string(config_file) + tokens[i].get_position().to_string() +
									": error, expected a semicolon, to end the directory_listing attribute at " +
									position.to_string() + ", but found: " + tokens[i].get_token() + '\n'));
	}
}

#pragma GCC diagnostic pop