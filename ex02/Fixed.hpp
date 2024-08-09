/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:31:11 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/07 11:02:09 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

/**
 * @brief Fixed class
 * 
 * The Fixed class will have an integer attribute that will store the fixed-point value.
 * The number of fractional bits will be defined as a constant with the value 8.
 * 
 * About `Fixed &operator=(const Fixed& assign);`
 * The reason for returning a reference is to allow for chaining of assignment 
 * operations. For example, if you have three Fixed objects a, b, and c, 
 * you might want to do something like a = b = c;. 
 * This sets both a and b to the value of c
 * The const Fixed& assign in the parameter list is indeed taking the argument by 
 * reference  to avoid unnecessary copying of objects
 * 
 * About the 6 comparison operators:
 * it is common to define comparison operators as member functions
 * you write a > b, this is equivalent to a.operator>(b).
 * The operator overloading function is a member function of the class
 * 
 * About the 4 arithmetic operators:
 * `Fixed operator+(const Fixed& rhs) const;` vs `Fixed& operator+(const Fixed& rhs) const;`
 * The first one returns a new object, the second one returns a reference to the object
 * but the first is the correct one because allows for chaining of operations
 * like a = b + c + d; where each operation returns a new object.
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
		
		bool operator>(const Fixed& rhs) const;
		bool operator<(const Fixed& rhs) const;
		bool operator>=(const Fixed& rhs) const;
		bool operator<=(const Fixed& rhs) const;
		bool operator==(const Fixed& rhs) const;
		bool operator!=(const Fixed& rhs) const;

		// the 4 arithmetic operators
		Fixed operator+(const Fixed& rhs) const;
		Fixed operator-(const Fixed& rhs) const;
		Fixed operator*(const Fixed& rhs) const;
		Fixed operator/(const Fixed& rhs) const;

		// the 4 increment operators
		// The pre-increment operator (++x) increments the value of x 
		// and then returns x. So it returns a reference to the incremented object
		Fixed& operator++();
		// The post-increment operator (x++), on the other hand, increments the value of x, 
		// but returns the original value of x before the increment. 
		// To do this, it needs to create a copy of x before incrementing it, 
		// and then return that copy. That's why the return type is Fixed, not Fixed&
		Fixed operator++(int);
		// same here for the decrement operators
		Fixed& operator--();
		Fixed operator--(int);
		
		// A static member function min/max that takes as parameters two 
		// references on fixed-point numbers, and returns a reference 
		static Fixed& min(Fixed& a, Fixed& b);
		static Fixed& max(Fixed& a, Fixed& b);
		
		// A static member function min/max that takes as parameters two
		// references on constant fixed-point numbers, and returns a reference
		static const Fixed& min(const Fixed& a, const Fixed& b);
		static const Fixed& max(const Fixed& a, const Fixed& b);
		
	private:
		int number;
		// initialized in Fixed.cpp
		static const int fraction;
};

// Forward declaration of the operator << overload
std::ostream& operator<<(std::ostream& os, const Fixed& fixed);

#endif  // FIXED_HPP_
