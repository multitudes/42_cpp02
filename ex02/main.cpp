/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:46:19 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/09 10:02:24 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"
#include <limits>


/**
 * @brief main function
 * 
 * Practicing the operators overloads for the Fixed class.
 * It is also good to know how floats work :)
 * https://fabiensanglard.net/floating_point_visually_explained/
 */

int main()
{

	Fixed a = Fixed(2.5f);
	Fixed b = Fixed(3.f);
	Fixed c = a * b;

	std::cout << c << std::endl;

}
int main1( void )
{

	Fixed max_value = Fixed(std::numeric_limits<int>::max() / (1 << 8));
	Fixed min_value = Fixed(std::numeric_limits<int>::min() / (1 << 8));

	std::cout << "max_value: " << max_value << std::endl;
	std::cout << "min_value: " << min_value << std::endl;
	
	Fixed a(0.0f); 
	Fixed b(1.0f); 
	Fixed c(-1.0f);
	Fixed d(std::numeric_limits<float>::max());
	Fixed e(std::numeric_limits<float>::min());
	Fixed f(std::numeric_limits<int>::max());
	Fixed g(std::numeric_limits<int>::min());
	std::cout << "a: " << a << std::endl;
	std::cout << "b: " << b << std::endl;
	std::cout << "c: " << c << std::endl;
	std::cout << "d: " << d << std::endl;
	std::cout << "e: " << e << std::endl;
	std::cout << "f: " << f << std::endl;
	std::cout << "g: " << g << std::endl;

	std::cout << "a + b: " << a + b << std::endl;
	std::cout << "a - b: " << a - b << std::endl;
	std::cout << "a * b: " << a * b << std::endl;
	std::cout << "a / b: " << a / b << std::endl;
	std::cout << "a + c: " << a + c << std::endl;
	std::cout << "a - c: " << a - c << std::endl;
	std::cout << "a * c: " << a * c << std::endl;
	std::cout << "a / c: " << a / c << std::endl;
	std::cout << "a + d: " << a + d << std::endl;
	std::cout << "a - d: " << a - d << std::endl;
	std::cout << "a * d: " << a * d << std::endl;
	std::cout << "a / d: " << a / d << std::endl;
	std::cout << "a + e: " << a + e << std::endl;
	std::cout << "a - e: " << a - e << std::endl;
	std::cout << "a * e: " << a * e << std::endl;
	std::cout << "a / e: " << a / e << std::endl;
	std::cout << "a + f: " << a + f << std::endl;
	std::cout << "a - f: " << a - f << std::endl;
	std::cout << "a * f: " << a * f << std::endl;

	std::cout << "a / f: " << a / f << std::endl;
	std::cout << "a + g: " << a + g << std::endl;
	std::cout << "a - g: " << a - g << std::endl;
	std::cout << "a * g: " << a * g << std::endl;
	std::cout << "a / g: " << a / g << std::endl;
	
	std::cout << "a > b: " << (a > b) << std::endl;
	std::cout << "a < b: " << (a < b) << std::endl;
	std::cout << "a >= b: " << (a >= b) << std::endl;
	std::cout << "a <= b: " << (a <= b) << std::endl;
	std::cout << "a == b: " << (a == b) << std::endl;
	std::cout << "a != b: " << (a != b) << std::endl;

	std::cout << "a > c: " << (a > c) << std::endl;
	std::cout << "a < c: " << (a < c) << std::endl;
	std::cout << "a >= c: " << (a >= c) << std::endl;
	std::cout << "a <= c: " << (a <= c) << std::endl;
	std::cout << "a == c: " << (a == c) << std::endl;
	std::cout << "a != c: " << (a != c) << std::endl;
	
	std::cout << "a > d: " << (a > d) << std::endl;
	std::cout << "a < d: " << (a < d) << std::endl;
	std::cout << "a >= d: " << (a >= d) << std::endl;
	std::cout << "a <= d: " << (a <= d) << std::endl;
	std::cout << "a == d: " << (a == d) << std::endl;
	std::cout << "a != d: " << (a != d) << std::endl;

	std::cout << "a > e: " << (a > e) << std::endl;
	std::cout << "a < e: " << (a < e) << std::endl;
	std::cout << "a >= e: " << (a >= e) << std::endl;
	std::cout << "a <= e: " << (a <= e) << std::endl;
	std::cout << "a == e: " << (a == e) << std::endl;
	std::cout << "a != e: " << (a != e) << std::endl;

	std::cout << "a > f: " << (a > f) << std::endl;
	std::cout << "a < f: " << (a < f) << std::endl;
	std::cout << "a >= f: " << (a >= f) << std::endl;
	std::cout << "a <= f: " << (a <= f) << std::endl;
	std::cout << "a == f: " << (a == f) << std::endl;
	std::cout << "a != f: " << (a != f) << std::endl;

	std::cout << "a > g: " << (a > g) << std::endl;
	std::cout << "a < g: " << (a < g) << std::endl;	
	std::cout << "a >= g: " << (a >= g) << std::endl;
	std::cout << "a <= g: " << (a <= g) << std::endl;
	std::cout << "a == g: " << (a == g) << std::endl;
	std::cout << "a != g: " << (a != g) << std::endl;
	
	std::cout << "max_value: " << max_value << std::endl;
	std::cout << "min_value: " << min_value << std::endl;

	// with min and max
	std::cout << "min(a, b): " << Fixed::min(a, b) << std::endl;
	std::cout << "max(a, b): " << Fixed::max(a, b) << std::endl;
	std::cout << "min(a, c): " << Fixed::min(a, c) << std::endl;
	std::cout << "max(a, c): " << Fixed::max(a, c) << std::endl;
	std::cout << "min(a, d): " << Fixed::min(a, d) << std::endl;
	std::cout << "max(a, d): " << Fixed::max(a, d) << std::endl;
	std::cout << "min(a, e): " << Fixed::min(a, e) << std::endl;
	std::cout << "max(a, e): " << Fixed::max(a, e) << std::endl;
	std::cout << "min(a, f): " << Fixed::min(a, f) << std::endl;
	std::cout << "max(a, f): " << Fixed::max(a, f) << std::endl;
	std::cout << "min(a, g): " << Fixed::min(a, g) << std::endl;
	std::cout << "max(a, g): " << Fixed::max(a, g) << std::endl;
	
	// decrement and increment
	std::cout << "a: " << a << std::endl;
	std::cout << "++a: " << ++a << std::endl;
	std::cout << "a: " << a << std::endl;
	std::cout << "a++: " << a++ << std::endl;
	std::cout << "a: " << a << std::endl;
	std::cout << "--a: " << --a << std::endl;
	std::cout << "a: " << a << std::endl;
	std::cout << "a--: " << a-- << std::endl;
	std::cout << "a: " << a << std::endl;

	
	return 0;
}