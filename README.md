# 42_cpp02

This is a project for learning C++ at 42 Berlin.  
The main topics are:
 - foating point arithmetic vs fixed point arithmetic
 - Ad-hoc polymorphism
 - Operator overloading
 - Canonical classes

## what is a canonical form?

Defines the essential members for proper object management:

- Default Constructor: Creates an object in a valid state.
- Destructor: Cleans up resources when the object is destroyed.
- Copy Constructor: Creates a new object as a copy of an existing one.
- Copy Assignment Operator: Assigns the contents of one object to another.

If you don't explicitly define a copy constructor or assignment operator for your class, the compiler will generate default versions for you.

The compiler-generated copy constructor and assignment operator performs a shallow copy by copying the members of the source object to the new object. This can lead to issues if the class contains pointers or other dynamically allocated resources, because we will have two classes pointing to the same resource ex a dynamically allocated array with even risks of double freeing the same memory! 

The takeaway is :
- When your class contains pointers or other dynamically allocated resources, you must define your own copy constructor and assignment operator to perform deep copies.
- If you need to control the copying process, you can define your own copy constructor and assignment operator.

## When are the copy constructors and assignment operators called?
Also a common source of confusion: When are the copy constructors and assignment operators called?

The copy constructor is a constructor so it doesnt return anything. The definition is:
```cpp
// in the header
Fixed(const Fixed& copy);

// in the .cpp file
Fixed::Fixed(const Fixed& copy) {
	debug("Copy constructor called");
	*this = copy;
}

// or also shorter
Fixed(const Fixed& copy) : number(copy.number) {
	debug("Copy constructor called");
}
```
Since we do not have dynamically allocated memory the shallow copy is perfectly fine and we would not even need to declare/define the copy constructor.

So when does it gets called?

- An object is initialized from another object of the same type:

```cpp
Fixed n1;
Fixed n2 = n1; // Copy constructor called
```

- An object is returned by value from a function:
```cpp
Fixed myFunction() {
    Fixed obj;
    // ...
    return obj; // Copy constructor called for the return value
}
```
But I invite you t try it... 
in main():
```cpp
Fixed myFunction() {
	Fixed a;
	return a;
}

int main() {
	Fixed c = myFunction();
}
```
Nothing gets printed. Why is the copy constructor not being called?
This behavior is due to a compiler optimization known as copy elision. The compiler is allowed to optimize away unnecessary copy operations, and in this case, it's optimizing away the creation of a temporary object and the subsequent copy constructor call.  
If you want to explicitly force the copy constructor to be called, you can disable these optimizations using the `-fno-elide-constructors` flags for clang and GCC.
Recompiling I would get again lots of messages. First the def constr is called, then the copy constructor is called for the return value of the function, and then the copy constructor is called for the assignment of the return value to the variable c. then the destructor is called for the object we had created in the function! I would get:
```cpp
Default constructor called
Copy constructor called
Destructor called
Copy constructor called
Destructor called
... 
(use c)
...
(then again after main exiting I get another destructor call)
```

(Note: Disabling these optimizations can negatively impact performance)

- An object is passed by value to a function:
```cpp
void myFunction(Fixed obj) {
    // Copy constructor called for the function parameter
}
```
Here testing this 
```cpp
void myFunction(Fixed a) {
	std::cout << a.getRawBits() << std::endl;
}
int main(void)
{
	Fixed a;
	test2(a);
}
```

I get :
```cpp
Fixed.cpp:37: Default constructor called
Fixed.cpp:58: Copy constructor called
0
Fixed.cpp:44: Destructor called
Fixed.cpp:44: Destructor called
```
To highlight the difference from the above. When does the assignment operator get called?
The assignment operator is called when:

- An existing Fixed object is assigned the value of another Fixed object using the = operator.

```cpp
Fixed n1;
Fixed n2;
n2 = n1; // Assignment operator called
```

- An object is returned by value from a function and assigned to another existing object. Which is the same as the above mostly.

```cpp
Fixed n1;
n1 = myFunction(); // Assignment operator called
```



## About the fixed point arithmetic
We are practicing writing canonical form with a Fixed number class.  
Long time ago when computers did not have floating point units, fixed point arithmetic was used.  
There is not much on the internet today about this topic.  I found something on wiki ( see below for links)   
The idea is to take an int and decide how many bits for the fractional part we will need.  
For example, if we have a 32 bit int and we decide to use 8 bits for the decimal part, we can represent numbers from -2^23 to 2^23-1 with a precision of 1/256. Since the int has 32 bits:  
`00000000 00000000 00000000.00000000`
we pass a raw value of 256 to our Fixed class we get 1 in decimal:
`00000000 00000000 00000001.00000000`
or :
`00000000 00000000 00000000.11111111`
will be a raw value of 255 which is 0.99609375 converted to float. The reason for this is that our 8 bit precision is 1/256 or 0.00390625. And 255 * 0.00390625 = 0.99609375. In our toFloat however we will get a float value of 0.996094. It is somewhat disappointing but we lose precision when converting to float.  A single-precision float (IEEE 754) has approximately 7 decimal digits of precision but this decreases for large numbers.  
There are many articles about this topic and how to handle the loss of precision.  I recommend to start with the blog post by fabien sanglard (link below) about how float numbers are represented in memory. 

Anyway, in our exercise we create a class to represent fixed point numbers with 8 bit fractional part that will have a raw value called number and property for the number of bits assigned to the fraction (in our case 8).  

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
For this exercise we just write the class in the header file and a .cpp file with the implementation of the class.  We will just test the constructors printing a message when each is caled. See the discussion above about why the copy constructor is not being called when i am in a function... :)

## ex01
We implement our setter and getters for the rawbits number property which will be the value of the underlying int containing our fixed point number in memory. And also start the conversion to int and to float and falling into the rabbit hole of the floating point numbers...
## ex02
Here we create function overloading all math operators, min max and comparison operators..

## ex03
A practical application of our class to tell wether a point falls inside a triangle or not.


## links
https://www.cprogramming.com/tutorial/floating_point/understanding_floating_point.html  
https://en.wikipedia.org/wiki/Fixed-point_arithmetic  
https://fabiensanglard.net/floating_point_visually_explained/  

