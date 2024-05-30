/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: t_c_resource.hpp                                               */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/05/14 03:52:48                                            */
/*   Updated:  2024/05/30 23:57:14                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

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

class t_c_resource
{
	private:
		std::string root; // path to the directory in the filesystem of the origin server considered to be the root of
						  // the path of the requested resource, it can also be a file case in wich it will always
						  // respond whit the same file regardless of the requested resource
		std::string redirect; // empty string for no redirect, if not empty it will not reply whit a file but whit a:
							  // 301 permanently moved to "redirect"
		std::string file_is_a_directory_page = "default_error_pages/403"; // 403 forbidden by default
		bool        directory_listing = false;
		bool        post_allowed = false;
		bool        delet_allowed = false;
		bool        get_allowed = true;
		bool        is_cgi = false;

	public:
		explicit t_c_resource(std::string const &root_param, std::string const &redirect_param,
							  std::string const &file_is_a_directory_page_param, bool directory_listing_param,
							  bool post_allowed_param, bool delet_allowed_param, bool get_allowed_param,
							  bool is_cgi_param);
		t_c_resource(t_c_resource const &copy);
		~t_c_resource(void);
		bool                operator==(t_c_resource const &comparator) const;
		t_c_resource const &operator=(t_c_resource const &copy);

		std::string const  &get_root(void) const;
		std::string const  &get_redirect(void) const; // empty string for no redirect
		std::string const  &get_file_is_a_directory_page(void) const;
		bool                get_direcory_listing(void) const;
		bool                get_post_allowed(void) const;
		bool                get_delet_allowed(void) const;
		bool                get_get_allowed(void) const;
		bool                get_is_cgi(void) const;

		std::string         to_string(void) const;
};

#pragma GCC diagnostic pop
