/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: t_c_router.hpp                                                 */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2024/05/14 03:53:52                                            */
/*   Updated:  2024/05/18 02:59:30                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "../t_c_route/t_c_route.hpp"

#include <cstdint>
#include <string>
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

class t_c_router
{
	private:
		std::vector<t_c_route> routes;

	public:
		explicit t_c_router(std::vector<t_c_route> const &routes_param);
		t_c_router(t_c_router const &copy);
		~t_c_router(void);
		bool                          operator==(t_c_router const &comparator) const;

		std::vector<t_c_route> const &get_routes(void) const;
		std::string                   to_string(void) const;
};

#pragma GCC diagnostic pop