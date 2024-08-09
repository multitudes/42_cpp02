/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:36:23 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/09 12:26:08 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath>
#include <iostream>
#include <iomanip>
#include <limits>
#include "debug.h"

/**
 * @brief Fixed::fraction needs to be initialized outside the class.
 */
const int Fixed::fraction = 8;

/**
 * @brief operator << overload
 * 
 * @param os 
 * @param fixed 
 * @return std::ostream& 
 * 
 * I cannot overload the operator << inside the class because it defined
 * in the std namespace. So I overload it outside the class.	
 * My precision is set to 8 decimal places because the smallest unit is 1/256
 * or 0.00390625. So if I have the right most 8 bits to zero I can convert
 * the fixed point number to an integer and dont loose any information.
 * converting to float is sometimes to be avoided if possible because of the
 * precision loss.
 */
std::ostream& operator<<(std::ostream& os, const Fixed& fixed) {
	// check if I have the last fraction N bits to zero and then convert to int
	if ((fixed.getRawBits() % 256) == 0) // 256 is 2 ^ to my fraction bits 
		os << fixed.toInt();
	else // here I set the precision to 8 decimal places which is good for this ex but wuld need to be expanded
		os << std::fixed << std::setprecision(8) << fixed.toFloat();
	return os;
}

/**
 * @brief Fixed::Fixed default constructor
 */
Fixed::Fixed( void ) : number(0) {
	debug("Default constructor called");
}

/**
 * @brief Fixed::Fixed constructor with int
 * 
 * @param n 
 */
Fixed::Fixed( int const n ) {
	debug("Int constructor called");
	// check for underflow and overflow
	if (n > (std::numeric_limits<int>::max() >> Fixed::fraction))
		std::cerr << "Overflow in int initializer" << std::endl;
	else if (n < (std::numeric_limits<int>::min() >> Fixed::fraction))
		std::cerr << "Underflow in int initializer" << std::endl;
	else 
		this->number = n << Fixed::fraction;
}

/**
 * @brief myRound
 * 
 * @param value
 * I need to emulate the std::round function because it is not available in the
 * cpp 98 standard. I use the floor and ceil functions to round the number.
 */
static double myRound(double value) {
    return (value >= 0.0) ? floor(value + 0.5) : ceil(value - 0.5);
}

/**
 * @brief Fixed::Fixed constructor with float
 * 
 * @param f 
 * 
 * It takes a float and converts it to a fixed-point number.
 * `roundf(f * (1 << Fixed::fraction)` scales the floating
 * point number  by 256 (1 << Fixed::fraction) and rounds it.
 * because the number is stored as an integer there is an implicit
 * casting here. the float has a different memory mapping than the int
 * but because of the casting the float is converted to an int rounded and
 * displaced of n fraction bits (rawbit mapping).
 * EX 1.5: 1.5 * 256 = 384.0 -> 384 which in bits 
 * 00000001 10000000. considering the 8 fraction bits i have 1.5
 */
Fixed::Fixed( float const f ) {
	debug("Float constructor called");
	// make dure the number fits in the fixed point number
	double d = f * (1 << Fixed::fraction);
	if (d > std::numeric_limits<int>::max()) {
        std::cerr << "Overflow in float initializer" << std::endl;
		number = std::numeric_limits<int>::max();
    } else if (d < std::numeric_limits<int>::min()) {
        std::cerr << "underflow in float initializer" << std::endl;
		number = std::numeric_limits<int>::min();
    } else {
        number = static_cast<int>(myRound(d));
    }
}

/**
 * @brief Fixed::Fixed copy constructor
 * 
 * @param copy 
 */
Fixed::Fixed(const Fixed& copy) : number(copy.getRawBits()) {
	debug("Copy constructor called");
}

/**
 * @brief Fixed::operator=
 * 
 * @param assignment operator 
 * @return Fixed& 
 */
Fixed& Fixed::operator=(const Fixed& assign) {
	debug("Assignment operator called");
	// handle when the object is assigned to itself
	if (this != &assign)
		this->number = assign.getRawBits();
	return *this;
}

/**
 * @brief Fixed::toFloat
 * 
 * @return float
 * 
 * It converts the fixed-point number to a floating point number.
 * Again the casting changes the bit mapping here.
 * In memory the float mapping is different from the int mapping
 * but in this case the raw bit int value is converted to a float and then
 * divided by 256 (1 << Fixed::fraction) to get the float value.
 */
float Fixed::toFloat( void ) const {
	return static_cast<float>(number) / (1 << Fixed::fraction);
}

/**
 * @brief Fixed::toInt
 * 
 * @return int 
 * 
 * It converts the fixed-point number to an integer.
 * The raw bit value is shifted to the right by Fixed::fraction bits.
 * This is equivalent to dividing the number by 256 (1 << Fixed::fraction).
 */
int Fixed::toInt( void ) const {
	 if (number < 0) {
        int absInt = (-number) >> Fixed::fraction;
        // Invert the result to get the correct negative integer
        return -absInt;
    }
	return this->number >> Fixed::fraction;
}

/**
 * @brief Fixed::~Fixed
 * 
 * Destructor
 */
Fixed::~Fixed( void ) {
	debug("Destructor called");
}

/**
 * @brief Fixed::getRawBits
 * 
 * @return int
 * 
 * The raw binary representation of the fixed-point number.
 * When I have for ex 1 as fixed point number 
 * in binary it is 00000000 00000000 00000001 00000000 because
 * of the 8 fraction bits.
 */
int Fixed::getRawBits( void ) const {
	return this->number;
}

/**
 * @brief Fixed::setRawBits
 * 
 * @param raw 
 * 
 * It sets the raw value of the fixed-point number.
 * The raw value is the integer representation of the number.
 * It defaults to zero. If I want to set the number to 1 I pass 256.
 * because the raw bit value is shifted to the left by Fixed::fraction bits.
 * This is equivalent to multiplying the number by 256 (1 << Fixed::fraction).
 * and the raw bits will look like 00000000 00000000 00000001 00000000 
 */
void Fixed::setRawBits( int const raw ) {
	this->number = raw;
}

/**
 * @brief Fixed::operator> comparison operator overload
 * 
 * @param rhs
 * @return true if this->number is greater than rhs.number
 */
bool Fixed::operator>(const Fixed& rhs) const {
	return getRawBits() > rhs.getRawBits();
}

/**
 * @brief Fixed::operator< comparison operator overload
 * 
 * @param rhs
 * @return true if this->number is less than rhs.number
 */
bool Fixed::operator<(const Fixed& rhs) const {
	return getRawBits() < rhs.getRawBits();
}

/**
 * @brief Fixed::operator>= comparison operator overload
 * 
 * @param rhs
 * @return true if this->number is greater or equal than rhs.number
 */
bool Fixed::operator>=(const Fixed& rhs) const {
	return getRawBits() >= rhs.getRawBits();
}

/**
 * @brief Fixed::operator<= comparison operator overload
 * 
 * @param rhs
 * @return true if this->number is less or equal than rhs.number
 */
bool Fixed::operator<=(const Fixed& rhs) const {
	return getRawBits() <= rhs.getRawBits();
}

/**
 * @brief Fixed::operator== comparison operator overload
 * 
 * @param rhs
 * @return true if this->number is equal to rhs.number
 */
bool Fixed::operator==(const Fixed& rhs) const {
	return getRawBits() == rhs.getRawBits();
}

/**
 * @brief Fixed::operator!= comparison operator overload
 * 
 * @param rhs
 * @return true if this->number is different than rhs.number
 */
bool Fixed::operator!=(const Fixed& rhs) const {
	return getRawBits() != rhs.getRawBits();
}

/**
 * @brief Fixed::operator+ arithmetic operator overload
 * 
 * @param rhs
 * @return Fixed 
 * 
 * Assuming that the fractional parts are same for both numbers
 */
Fixed Fixed::operator+(const Fixed& rhs) const {
	long result = static_cast<long long>(number) + static_cast<long long>(rhs.getRawBits());
    // Handle potential overflow and underflow
    if (result > std::numeric_limits<int>::max()) {
		std::cerr << "Overflow in Fixed addition\n" << std::endl;
		return Fixed(0);
	} else if (result < std::numeric_limits<int>::min()) {
        std::cerr << "Underflow in Fixed addition\n" << std::endl;
        return Fixed(0);
    }
    return Fixed(static_cast<int>(result));
}

/**
 * @brief Fixed::operator- arithmetic operator overload
 * 
 * @param rhs
 * @return Fixed 
 * 
 * Assuming that the fractional parts are same for both numbers
 */
Fixed Fixed::operator-(const Fixed& rhs) const {
	int result = number - rhs.getRawBits();
	return Fixed(result);
}

/**
 * @brief Fixed::operator* arithmetic operator overload
 * 
 * @param rhs
 * @return Fixed 
 * 
 * Assuming that the fractional parts are same for both numbers.
 * Following wikipedia: To multiply two fixed-point numbers, 
 * it suffices to multiply the two underlying integers, 
 * and assume that the scaling factor of the result is the product of their scaling factors. 
 * The result will be exact, with no rounding, provided that it does not overflow 
 * the receiving variable. 
 */
Fixed Fixed::operator*(const Fixed& rhs) const {
	long long rawbits = number * rhs.number;
    // Divide by the scaling factor to adjust for the doubled fractional bits
	// Each Fixed has 8 bits so mult produces 16 bits
	// but i return a Fixed with 8 bits so i need to divide by 2 ^ 8 only
    rawbits /= (1 << (Fixed::fraction));
    // Handle potential overflow and underflow
    if (rawbits > std::numeric_limits<int>::max()) {
		std::cerr << "Overflow in Fixed multiplication\n";
		return Fixed(0);
	}
	else if (rawbits < std::numeric_limits<int>::min()) {
        std::cerr << "Underflow in Fixed multiplication\n";
        return Fixed(0); 
    }
	Fixed result = Fixed();
	result.setRawBits(static_cast<int>(rawbits));
    return result;
}

/**
 * @brief Fixed::operator/ arithmetic operator overload
 * 
 * @param rhs
 * @return Fixed
 * 
 * Assuming that the fractional parts are same for both numbers.
 * Following wiki... To divide two fixed-point numbers, one takes the integer quotient 
 * of their underlying integers, and assumes that the scaling factor is the 
 * quotient of their scaling factors. 
 * In general, the first division requires rounding and therefore the result is not exact. 
 */
Fixed Fixed::operator/(const Fixed& rhs) const {
	int result = number / rhs.getRawBits();
	return Fixed(result);
}

/**
 * @brief Fixed::operator++ pre-increment operator overload
 * 
 * @return Fixed& 
 * 
 * The 4 increment operators:
 * In C++, the pre-increment (++variable) and post-increment (variable++) 
 * operators are used to increase the value of a variable by 1.
 * 
 * The difference between them is WHEN the increment happens relative 
 * to the rest of the expression:
 * 
 * The pre-increment operator (++variable) increases the value of the 
 * variable before the rest of the expression is evaluated. For example, 
 * in the statement int y = ++x;, x is incremented, and then its new value 
 * is assigned to y.
 * 
 * The post-increment operator (variable++) increases the value of the 
 * variable after the rest of the expression is evaluated. For example, 
 * in the statement int y = x++;, the current value of x is assigned to y, 
 * and then x is incremented.
 * 
 * When overloading these operators for a class in C++, the pre-increment 
 * operator is typically overloaded as a member function with no parameters, 
 * while the post-increment operator is overloaded as a member function with 
 * a single parameter of type int. The parameter is not used; it's only there 
 * to distinguish the post-increment operator from the pre-increment operator.
 */
Fixed& Fixed::operator++() {
	this->number += 1;
	return *this;
}

/**
 * @brief Fixed::operator++ post-increment operator overload
 * 
 * @param int
 * 
 * The post-increment operator creates a copy, increments the current object, 
 * and returns the copy, providing the original un-incremented value (b = a++).
*/
Fixed Fixed::operator++(int) {
	Fixed tmp(*this);
	operator++();
	return tmp;
}

/**
 * @brief Fixed::operator-- pre-decrement operator overload
 * 
 * @return Fixed& 
 */
Fixed& Fixed::operator--() {
	this->number -= 1;
	return *this;
}

/**
 * @brief Fixed::operator-- post-decrement operator overload
 * 
 * @param int
 * @return Fixed 
 */
Fixed Fixed::operator--(int) {
	Fixed tmp(*this);
	operator--();
	return tmp;
}

/**
 * @brief Fixed::min/max static member function
 * 
 * A static member function min/max that takes as parameters two references 
 * on fixed-point numbers, and returns a reference to the smallest one
*/
Fixed& Fixed::min(Fixed& a, Fixed& b) {
	return a.getRawBits() < b.getRawBits() ? a : b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
	return a.getRawBits() > b.getRawBits() ? a : b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
	return a.getRawBits() < b.getRawBits() ? a : b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
	return a.getRawBits() > b.getRawBits() ? a : b;
}
