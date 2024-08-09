/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbrusa <lbrusa@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 17:03:12 by lbrusa            #+#    #+#             */
/*   Updated: 2024/08/09 11:48:40 by lbrusa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Fixed.hpp"


Fixed test() {
	Fixed a;
	return a;
}

void test2(Fixed a) {
	std::cout << a.getRawBits() << std::endl;
}

/**
 * @brief main
 * 
 * @return int
 * Test the Fixed class with default constructor,
 * copy constructor and assignation operator.
 */
int main(void)
{
	// Fixed a;
	// Fixed b;
	Fixed a = test();
	// test2(a);
	// Fixed b = a;
	// // Fixed b( a );
	// // Fixed c;
	// Fixed c = test();
	
	// std::cout << a.getRawBits() << std::endl;
	// std::cout << b.getRawBits() << std::endl;
	// std::cout << c.getRawBits() << std::endl;
	
	return 0;
}
