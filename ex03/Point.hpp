/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Point.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:34:29 by lbrusa            #+#    #+#             */
/*   Updated: 2024/09/18 16:35:34 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"
#include <iostream>

/**
 * @brief Point class
 * 
 * A Point class that has two Fixed values for x and y.
 * The class has a default constructor, a constructor with two float values, a copy constructor, and an assignation operator overload.
 * The class has two getter functions for the x and y values.
 */
class Point {
	public:
		Point( void );
		Point(float const x, float const y);
		~Point( void );
		Point(const Point& copy);
		Point &operator=(const Point& assign);

		// getter and setter for the x and y
		Fixed getX( void ) const;
		Fixed getY( void ) const;
			
	private:
		Fixed const x;
		Fixed const y;
};

#endif  // POINT_HPP_
