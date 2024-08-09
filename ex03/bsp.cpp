/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 14:58:04 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/06 12:43:07 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Point.hpp"
#include "Fixed.hpp"
#include <iostream>

/**
 * @brief sign
 * 
 * @param point
 * @param a
 * @param b
 * @return Fixed 
 * 
 * formula to calculate the determinant of the three points 
 * for a triangle with vertices a, b, c and a point p 
 * I take a b and p for the first determinant
 * ex p = (2,5)
 * a = (1,2)
 * b = (4,1)
 * v1 is ap and v2 is ab
 * | p.x - a.x  b.x - a.x |
 * | p.y - a.y  b.y - a.y |
 * 
 * ex |1  3|
 * |3 -1|
 * determinant 1*(-1) - 3*3 = -1 - 9 = -10
 * https://youtu.be/eu6i7WJeinw?si=TcEWe282Rl0yB1WG
*/
Fixed sign(Point point, Point a, Point b)
{
    return (point.getX() - b.getX()) * (a.getY() - b.getY()) - (a.getX() - b.getX()) * (point.getY() - b.getY());
}

/**
 * @brief bsp
 * 
 * @param a
 * @param b
 * @param c
 * @param point
 * @return true if the point is inside the triangle
 * 
 * This solution used vectors and determinants. 
 * For each edge, it splits the plane into two by the line formed by the two vertices
 * and adding the position of the point to check, 
 * I calculate the sign of the determinant of the three points.
 * If the sign is the same for all the edges, the point is inside the triangle.
 * if one of the determinants is zero, the point is on the edge of the triangle and therefore not inside.
*/
bool bsp( Point const a, Point const b, Point const c, Point const point) {
	// i use determinants to calculate the area of the triangle 
	// formed by the point and the three vertices
	Fixed d1, d2, d3;
	bool hasNeg, hasPos, hasZero;
	
	d1 = sign(point, a, b);
	d2 = sign(point, b, c);
	d3 = sign(point, c, a);
	
	// if the determinant is zero it means that the point is on the edge of the triangle
	//std::cout << "determinants : " << d1 << " " << d2 << " " << d3 << std::endl;
	hasZero = (d1 == 0) || (d2 == 0) || (d3 == 0);
	if (hasZero)
		return false;
		
	// here if either all determinants are negative or all determinants are positive
	// the point is inside the triangle
    hasNeg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    hasPos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(hasNeg && hasPos);
}

