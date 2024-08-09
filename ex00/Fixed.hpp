/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:31:11 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/07 11:01:54 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

/**
 * @brief Fixed class
 * 
 * The goal is to create a class that represents a fixed-point number.
 */
class Fixed {
	public:
		Fixed( void );
		~Fixed( void );
		Fixed(const Fixed& copy);
		Fixed &operator=(const Fixed& assign);
		
		// getter and setter 
		// the raw is the binary representation of the fixed-point number
		int getRawBits( void ) const;
		void setRawBits( int const raw );

	private:
		static const int fraction;
		int number;
};

#endif  // FIXED_HPP_
