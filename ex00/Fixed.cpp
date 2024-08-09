/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Fixed.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 13:36:23 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/08 17:50:36 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "debug.h"

/**
 * Deep copy vs shallow copy. when I copy an object the default is a shallow copy
 * which in the case of a pointer will copy the address of the pointer and not the
 * value of the pointer. In this way this leads to the problem of eventually deleting
 * the same memory twice. Or that modifying the copy will modify the original...
 * To avoid this I need to create a deep copy which will create new memory for the
 * dynamically allocated properties of the object if possible but this is also 
 * an implementation detail.
 */

/**
 * @brief Fixed::fraction needs to be initialized outside the class.
 */
const int Fixed::fraction = 8;

/**
 * @brief Fixed::Fixed default constructor
 * 
 * Defaults the fixed-point number to 0.
 */
Fixed::Fixed( void ) : number(0) {
	debug("Default constructor called");
}

/**
 * @brief Fixed::Fixed destructor
 */
Fixed::~Fixed( void ) {
	debug("Destructor called");
}

/**
 * @brief Fixed::Fixed copy constructor
 * 
 * @param copy 
 * Important at this point to undeerstand exactly what is happening
 * The copy constructor is invoqued when a new object is created from
 * an existing object. The new object will be a copy of the existing object.
 * like Fixed a = b;
 * but if a is already created, then the assignment operator will be called as below
 */
Fixed::Fixed(const Fixed& copy) {
	debug("Copy constructor called");
	*this = copy;
}

/**
 * @brief Fixed::operator= assignment operator
 * 
 * @param assign
 * @return reference to Fixed&
 * 
 * As noted above I call the assignment operator when I have an existing object
 * and I want to assign another existing object to it.
 * Fixed a; Fixed b; a = b;
 * I need to return a reference to the object because I might want to chain 
 * the assignment like a = b = c;
 * if I create the object from another then it is the copy constructor that is called
 * Fixed a = b;
 */
Fixed& Fixed::operator=(const Fixed& assign) {
	debug("Assignment operator called");
	if (this != &assign)
		this->number = assign.getRawBits();
	return *this;
}

/**
 * @brief Fixed::getRawBits getter
 * 
 * @return int 
 * If we have the fraction as 8bits, then our number will have
 * 24 bits to represent the integer part of the fixed-point number.
 * When we ask for the raw bits, we will return the 4 bytes value
 * Ex 1 will have raw bits as 256 
 */
int Fixed::getRawBits( void ) const {
	return this->number;
}

/**
 * @brief Fixed::setRawBits setter
 * 
 * @param raw
 * passing 512 should get me 2.0000
 */
void Fixed::setRawBits( int const raw ) {
	this->number = raw;
}
