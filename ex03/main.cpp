/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:46:19 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/08 18:31:07 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include "Point.hpp"

// I found this solution looking online for determinants and vectors
bool bsp( Point const a, Point const b, Point const c, Point const point);

int main( void )
{
	// triangle vertices
	Point a = Point(0, 0);
	Point b = Point(0, 4); 
	Point c = Point(4, 0);
	// point to check
	Point point = Point(1, 1);
	
	// check if the point is inside the triangle
	// if the point is inside the triangle, the function returns true
	bool isInside = bsp(a, b, c, point);	
	if (isInside)
		std::cout << "The point is inside the triangle" << std::endl;
	else
		std::cout << "The point is outside the triangle" << std::endl;

	
	point = Point(4, 0);
	isInside = bsp(a, b, c, point);
	if (isInside)
		std::cout << "The point is inside the triangle" << std::endl;
	else
		std::cout << "The point is outside the triangle" << std::endl;
	return 0;
}
