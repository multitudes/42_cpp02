/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:31:11 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/08 17:09:22 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

/**
 * @brief Fixed class
 */
class Fixed {
	public:
		Fixed( void );
		Fixed( int const n );
		Fixed( float const f );
		~Fixed( void );
		Fixed(const Fixed& copy);
		Fixed& operator=(const Fixed& assign);
		
		// getter and setter for the fraction
		int getRawBits( void ) const;
		void setRawBits( int const raw );
		
		// methods
		float toFloat( void ) const;
		int toInt( void ) const;
		
		static const int fraction;
	
	private:
		int number;
};

/**
 * @brief operator << overload
 * 
 * Forward declaration of the operator << overload
 */
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif  // FIXED_HPP_
