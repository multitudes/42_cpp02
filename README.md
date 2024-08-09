# 42_cpp02

This is a project for learning C++ at 42 Berlin.  
The main topics are:
 - foating point arithmetic vs fixed point arithmetic
 - Ad-hoc polymorphism
 - Operator overloading
 - Canonical classes

## ex01
We are practicing writing canonical form with a Fixed number class.  
long time ago when computers did not have floating point units, fixed point arithmetic was used.  There is not much on the internet today about this topic.  I found something on wiki and stack overflow.( see below for links)   
We take an int and we decide how many digit for the decimal part we will need.  
For example, if we have a 32 bit int and we decide to use 8 bits for the decimal part, we can represent numbers from -2^23 to 2^23-1 with a precision of 1/256. Since the int has 32 bits:  
`00000000 00000000 00000000.00000000`
we pass a raw value of 256 and we get 1 in decimal:
`00000000 00000000 00000001.00000000`
or :
`00000000 00000000 00000000.11111111`
will be a raw value of 255 which is 0.996 converted to float.

To handle these numbers we create a class that will have a raw value and a fixed point value.  

The number of bits used to represent the fractional part is fixed.  This is a way to do floating point arithmetic without a floating point unit.  The class we are writing is a simple version of this concept. 

Using the anonical form we will include a constructor, a copy constructor, an assignment operator, and a destructor:

```cpp
class Fixed {
	public:
		Fixed( void );
		~Fixed( void );
		Fixed(const Fixed& copy);
		Fixed &operator=(const Fixed& assign);
		
		// getter and setter 
		// the raw is the binary representation of the fixed-point number
		int getRawBits( void ) const;
		void setRawBits( int const raw );

		
	private:
		static const int fraction;
		int number;
};
``` 


## ex00
For this exercise we just write the class in the header file and a .cpp file with the implementation of the class.

## ex01

## ex02

## ex03

## links

https://en.wikipedia.org/wiki/Fixed-point_arithmetic  
https://fabiensanglard.net/floating_point_visually_explained/  

