/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_cpp.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 13:06:34 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/07 16:20:45 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

#include <iostream>
#include <sstream>

#define COLOR  "\033[1;92m"
#define RESET "\033[0m"

#ifdef NDEBUG
#define debug(...)
#else
#define debug(msg) \
    std::cerr << COLOR << __FILE__ << ":" << __LINE__ << ": " << msg << RESET << std::endl;
#endif

#endif //DEBUG_H
