/** *******************************************************************************
|								                  |
|	A C++ realisation of vectors' class and its basic functions.              |                              
|										  |
|	@file Vector.cpp							  |
|	@date March 20, 2014						          |
|	@author Kirill Korolev <kirill.korolef@gmail.com>	                  |
|	@version 1.0 (March 20, 2014)						  |
|						                                  |
|	@note The program has been created for learning basic features of the C++ | 
|         language.		                                                  |
|                                                                                 |
|	@note Ver. 1.1 (April 23, 2014):                                          |
|		- A view of "#include" file has beeb changed                      |
|		- "main" function has been added for testing                      |
|		- "=" operator has been modified                                  |
|		- Assertion for "&" elements has been corrected                   |
|     @note Ver. 1.2 (May 03, 2014):                                              |
|           - A tab shift has been fixed                                          |
|           - Assert for links has been removed                                   |
|           - "=" operator has been modified                                      |
|           - A pause has been removed from main func.                            |
|				                                                  |	
**********************************************************************************/

#include <cstdio>
#include <cstdlib>

#define NDEBUG 

#ifndef NDEBUG		
	#define ASSERT( cond, messege )                          \ /**< Checking of correctness of data */
        if ( ! ( cond ) )                                        \
		{                                                \
			printf("Fatal error: %s,     "           \
				   "file: %s, line: %d \n",      \
				   #messege, __FILE__, __LINE__);\
			abort();                                 \
		}
#else
	#define ASSERT( cond, messege )
#endif

/** *******************************************************************************
|				                                                  |
|	Vector_t - a class which consists of coordinates	                  |
|	       data and basic math functions fo vectors.                          |
|	                                                                          |
**********************************************************************************/

class Vector_t
{
	public:
		double x, y;			            /**< The coordinates */
 	private:
		Vector_t();				    /**< A basic constractor */	
	public:	
		Vector_t(const Vector_t & v);               /**< v1 = v2; v1(v2); Vector_t v */
		Vector_t(double xx, double yy);	            /**< Vector_t(3, 4); v = Vector_t(3, 4); v(3, 4) */
		explicit Vector_t(double a);	    	    /**< Vector_t(5)  */
		~Vector_t();                                /**< A basic distructor */
		Vector_t operator+ (const Vector_t & v);    /**< v1 + v2; v1 + v2 + v3 */
		Vector_t operator- (const Vector_t & v);    /**< v1 - v2; v1 - v2 - v3 */
		Vector_t operator/ (double num);            /**< v1 / a */
		Vector_t & operator= (const Vector_t & v);  /**< v1 = v2; v1 = v2 = v3 */
};

/** *******************************************************************************
|									          |
|	operator* - an operator for			                          |
|	multiplication of a vector and a number.                                  |
|	                                                                          |
|	@param num - a number for the multiplication                              |
|		   v   - a vector                                                 |
|		                                                                  |
|	@return Vector_t class element - a vector                                 |
|			which is a result of the multiplication.                  |
|	                                                                          |
|	@note The two vertions of the operator are for different orders of        |
|            parametres.                                                          |
|	                                                                          |
**********************************************************************************/

Vector_t operator* (double num, const Vector_t & v);    /**< a * v */
Vector_t operator* (const Vector_t & v, double num);    /**< v * a; v * a * b */

Vector_t::Vector_t():
	x(0),
	y(0)
{
	printf("[C] A (0, 0) vector has been created [C]\n");
}

/** *******************************************************************************
|								                  |
|	A constructor for a Vector_t class.				          |
|					                                          |
|	@param v - a vector	  					          |
|									          |
|	@note The constructor creates a copy of vector "v" with same coordinates  |
|               and print a messege about creation.				  |
|										  |
**********************************************************************************/

Vector_t::Vector_t(const Vector_t & v)
{
	//ASSERT(* v != NULL, "Cons.: Vector v has a NULL address.");
	x = v.x;
	y = v.y;
	printf("[C] A (%lg, %lg) vector has been created [C]\n", x, y);
}

Vector_t::~Vector_t()
{
	printf("[D] A (%lg, %lg) vector has been destroyed [D]\n", x, y);
	x = 0;
	y = 0;
}

/** *******************************************************************************
|							   	                  |
|	A constructor for a Vector_t class.				          |
|									          |
|	@param xx, yy - coordinates		  		   	          |
|								                  |
|	@note The constructor creates a vector with different coordinates x and y |
|           and print a messege about creation.				          |
|									          |
**********************************************************************************/

Vector_t::Vector_t(double xx, double yy):
	x(xx),
	y(yy)
{
	printf("[C] A (%lg, %lg) vector has been created [C]\n", x, y);
}

/** *******************************************************************************
|										  |
|	A constructor for a Vector_t class.					  |
|										  |
|	@param a - a coordinate							  |
|										  |
|	@note The constructor creates a vector with same coordinates x and y and  |
|		  print a messege about creation.				  | 
|										  |
**********************************************************************************/

Vector_t::Vector_t(double a):
	x(a),
	y(a)
{
	printf("[C] A (%lg, %lg) vector has been created [C]\n", a, a);
}

/** *******************************************************************************
|									          |
|	operator+ - an operator for						  |
|	addition of a vector and a number (class function).                       |
|	                                                                          |
|	@param num  - a number for the multiplication                             |
|		   this - a current vector                                        |
|		                                                                  |
|	@return Vector_t class element - a vector                                 |
|			which is a result of the division.                        |
|	                                                                          |
**********************************************************************************/

Vector_t Vector_t::operator+ (const Vector_t & v)
{
	//ASSERT(* v != NULL, "Op.+: The Vector v has a NULL address.");
	return (Vector_t(v.x + x, v.y + y));
}

/** *******************************************************************************
|									          |
|	operator- - an operator for					          |
|	subtruction of 2 vectors (class function).                                |
|	                                                                          |
|	@param v    - a vector for the subtraction                                |
|		   this - a current vector                                        |
|		                                                                  |
|	@return Vector_t class element - a vector                                 |
|			which is a result of the subtraction.                     |
|	                                                                          |
**********************************************************************************/

Vector_t Vector_t::operator- (const Vector_t & v)
{
	//ASSERT(* v != NULL, "Op.-: The Vector v has a NULL address.");
	return (Vector_t(x - v.x, y - v.y));
}

/** *******************************************************************************
|								                  |
|	operator/ - an operator for					          |
|	division of a vector and a number (class function).                       |
|	                                                                          |
|	@param num  - a number for the division                                   |
|		   this - a current vector                                        |
|		                                                                  |
|	@return Vector_t class element - a vector                                 |
|			which is a result of the division.                        |
|	                                                                          |
**********************************************************************************/

Vector_t Vector_t::operator/ (double num)
{
	ASSERT(num != 0, "Op./: Division by zero.");
	return(Vector_t(x / num, y / num));
}

Vector_t operator* (const Vector_t & v, double num)
{
	//ASSERT(* v != NULL, "Op.*: Vector v has a NULL address.");
	return (Vector_t(v.x * num, v.y * num));
}

Vector_t operator* (double num, const Vector_t & v)
{
	//ASSERT(* v != NULL, "Op.*: Vector v has a NULL address.");
	return (Vector_t(v.x * num, v.y * num));
}

/** *******************************************************************************
|					                                          |
|	operator= - an operator for					          |
|	assignment of a vector (class function).                                  |
|	                                                                          |
|	@param v    - a vector for an assignment                                  |
|		   this - a current vector                                        |
|		                                                                  |
|	@return Vector_t class element - a vector                                 |
|			which is a result of the assignment.                      |
|	                                                                          |
**********************************************************************************/

Vector_t & Vector_t::operator= (const Vector_t & v)
{
	//ASSERT(* v != NULL, "Op.=: Vector v has a NULL address.");
	if (this != &v)
	{
		x = v.x;
		y = v.y;
	}
	return(* this);
}

int main()
{
	Vector_t v1(5, 4);
	Vector_t v2(7, 4);
	Vector_t v3 = v1 + 4 * v2;
	printf("%lf %lf", v3.x, v3.y);

	//system("PAUSE");
	return 0;
}