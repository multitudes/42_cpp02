/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:36:23 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/09 12:24:42 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <cmath> 
#include <iomanip>
#include <limits>
#include <math.h>
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
	if ((fixed.getRawBits() % 256) == 0)
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
 * @brief Fixed::~Fixed
 * 
 * Destructor
 */
Fixed::~Fixed( void ) {
	debug("Destructor called");
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
 * The raw value of a fixed-point number is the integer representation 
 * of the number. In a fixed-point number system, a number is 
 * represented as an integer, and a certain number of bits are interpreted 
 * as the fractional part of the number.
 * 
 * For example, if you have a 16-bit fixed-point number with 8 fractional bits, 
 * the number 0001001100110011 would represent the number 00010011.00110011 
 * in binary, or 19.199 in decimal.
 * 
 * In your Fixed class, the number property holds the raw value of the 
 * fixed-point number. The getRawBits method returns this raw value, 
 * and the setRawBits method sets a new raw value.
 * 
 */
