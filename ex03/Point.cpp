/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:33:54 by lbrusa            #+#    #+#             */
/*   Updated: 2024/09/18 16:36:13 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include <utility> 
#include "debug.h"

/**
 * @brief Point::Point default constructor
 */
Point::Point( void ) : x(0), y(0) {
	debug("Default constructor called");
}

/**
 * @brief Point::Point constructor with two float values
 * 
 * @param x
 * @param y
 * 
 * Initializes the x and y values with the given float values.
 */
Point::Point(float const x, float const y) : x(Fixed(x)), y(Fixed(y)) {
	debug("Float constructor called");
}

/**
 * @brief Point::Point destructor
 */
Point::~Point( void ) {
	debug("Destructor called");
}

/**
 * @brief Point::Point copy constructor
 * 
 * @param copy 
 */
Point::Point(const Point& copy): x(copy.x), y(copy.y) {
	debug("Copy constructor called");
}

/**
 * @brief Point::operator= assignment operator
 * 
 * Since the x and y values are const, 
 * the assignment operator will only return the current object.
 * Cannot change the x and y values.
 */
Point &Point::operator=(const Point& assign) {
	debug("Assignment operator called");
	if (this != &assign)
		return *this;
	return *this;
}

/**
 * @brief Point::getX getter
 * 
 * @return Fixed 
 */
Fixed Point::getX( void ) const {
	return this->x;
}

/**
 * @brief Point::getY getter
 * 
 * @return Fixed 
 */
Fixed Point::getY( void ) const {
	return this->y;
}

