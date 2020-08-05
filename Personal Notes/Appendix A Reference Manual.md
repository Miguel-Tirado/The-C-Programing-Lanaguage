# Appendix A: Reference Manual 

**A1. Introduction**

This manual goes over the C language specified by the draft submitted to ANSI for approval as American National Standard for Information Systems. Note that I will try to add my own interpretations of the C manual on the C programing language book. 

**A2. Lexical Conventions**

A program contains one or more translation units stored in files. It is translated in several phases which are described in A12. The first phases low level lexical transformations, carry out directives introduced by lines beginning with the # characters, and preform macro definitions and expansion. Now when the preprocessing of A12 is completed, the program has been reduced into a sequence of tokens. 

**A2.1 Tokens**

A token is the smallest element of a program that is meaningful to the compiler. There are 6 classes of tokens which include the following:

- Keywords
- Identifiers 
- Constants 
- Strings
- Special Symbols
- Operators 

Blanks, horizontal and vertical tabs, newlines, formfeeds, and comments as described below (collectively known as "white space") are ignored except as they separate tokens. Some white space is needed or else the adjacent identifiers, keywords, and constant would not be distinguishable to the compiler. 

If the input stream has been separated into tokens up to a given character, the next token is the longest string if characters that could constitute a token. 

**A2.2 Comments**

The characters /* introduce a comment, which ends with the character */. Note that comments do no nest, and they do not occur within a string or character literals . Also another way to place comments is to use //, however this is just a comment for one line at a time, therefore another // would be required when you reach the new line. 

```c
/*    This is a comment 
		in C                       */

//this is another comment in c
```

**A2.4 Keywords**

The following identifiers are reserved for use as keywords, and may not be used otherwise:

```c
auto         double      int        struct
break        else        long       switch
case         enum        register   typedef
char         extern      return     union
const        float       short      unsigned
continue     for         signed     void
default      goto        sizeof     volatile
do           if          static     while
```

Note some implantations reserve the words fortran and asm.

**A2.5 Constants**

A constant is a variable or value that cannot be modified once they are defined. They are fixed values in a program. There are several kinds of constants. Each has a data type such as integer, float, octal, hexadecimal, character constant and more. The most basic types are the following:

```
constant:
	integer-constant
	character-constant
	floating-constant 
	enumeration-constant
```

Note that every constant has some range, the integers that are too big to fit in a int will be taken as a long. There are various ranges that differ form unsigned to signed bits. 

Defining constants:

In c we can define constants in two ways as shown below:

1. Using #define preprocessor directive
2. Using a const keyword

Literals: the values assigned to each constant variable are referred to as the literals. Generally both terms, constants and literals are used interchangeably. For example `const int = 5` is a constant expression and the value 5 is referred to as constant integer literal 

**Integer Constants**

A integer constant with a sequence of digits is an octal if it begins with 0 (digit zero), decimal otherwise. Octal constants do not contain the digits 8 or 9 because octal is based 8 so the number of valid digit is 0-7, note zero indexing. A sequence of digits preceded by 0x or 0X (digit zero) is a hexadecimal integer. The hexadecimal digits include a or A through f or F with values 10 through 15. Therefore the number list for hexadecimal is the following

```c
0x0;	0x5;	0xa; /* 10 */	0xf; // 15
0x1;	0x6;	0xb; /* 11 */
0x2;	0x7;	0xc; /* 12 */
0x3;	0x8;	0xd; /* 13 */	
0x4;	0x9;	0xe; /* 14 */
```

An integer constant may be suffixed by the letter u or U, to specify that it is unsigned. It may also be suffixed with l or L to indicate that it is long.

The type of an integer constant depends on its form, value and suffix. If it is unsuffixed, octal or hexadecimal, it has the first possible of these types: int, unsigned, unsigned int, long int, unsigned long int. If it is suffixed by u our U, then unsigned int, unsigned long int. If it is suffixed by l or L, then long int, unsigned long int.  If an integer constant is suffixed by UL, it is unsigned long. 

**A 2.5.2 Character Constants**

A character constant is a sequence of one or more characters enclosed in single quotes as in 'x'. The value of a character constant with only one character is the numeric value of the character in the machines character set at execution time. The value of a multi-character constant is implementation defined. 

Note that character constant do not contain ' character or newlines; in order to represent them, and certain other characters, the following escape sequences may be used:

```
newline		   NL(LF)	\n				backslash	\	    \\
horizontal tab 	HT	     \t				question mark ?      \?
vertical tab    VT		 \V				single quote  '      \'
backspace       BS		 \b				double quote  "		 \"
carriage return CR		 \r				octal number  000    \000
formfeed	    FF       \f				hex number    hh     \xhh
audible alert   BEL       \a
```

The escape \000 consists of the backslash followed by 1, 2, or 3 octal digits, which are taken to specify the value of the desired character. A common example of this construction is \0 (not followed by a digit), which specifies the character NUL. The escape \xhh consists of the backslash, followed by x, followed by hexadecimal digits, which are taken to specify the value of the desired character. There is no limit on the number of digits, but the behavior is undefined if the resulting character value exceeds that of the largest character. For either octal or hexadecimal escape characters, if the implementation treats the char type as signed, the value is signed-extended as if cast to char type. If the character following the \ is not one of those specified, the behavior is undefined.  

In some implementations, there is an extended set of characters that cannot be represented in the char type. A constant in this extended set is written with a preceding L, for example, 'x', and is called a wide character constant. Such a constant has type wchar_t and integral type defined in the standard header <stddef.h>. as ordinary character constant, octals or hexadecimal escapes may be used; the effect is undefined if the specified value exceeds that representable with wchar_t. 

**A2.5.3**

A floating constant consist of an integer part, a decimal point, a fraction part, and e or E, an optional signed integer exponent and an optional type suffix, one of f,F,l, or L. The integer and fraction parts both consist of a sequence of digits, either the integer part or the fraction part (not both) may be missing; either the decimal point or the e and the exponent (not both) may be missing. The type is determined by the suffix; F or f makes it float, L or l make it long double; otherwise it is double. 

**A2.5.4 Enumeration Constants**

Identifiers declared as enumerators are constant of type int. 

**A2.6 String Literals**

A string literal, also called a string constant, is a sequence of characters surrounded double quotes, as in ". . .". A string has type "array of characters" and storage class static and initialized with the given characters. Whether identical string literals are distinct is implementation defined, and the behavior of a program that attempts to alter a string literal is undefined. 

Adjacent string literals are concatenated into a single string. After any concatenation, a null byte \0 is appended to the string so that programs that scan the string can find its end. String literals do not contain newline or double quotes characters; in order to represent them , the same escape sequences as for character constant are available. 

As with character constants, string literals in an extended character set are written with a preceding L, as in L ". . .". Wide character string literals have type array of wchar_t. Concatenation of ordinary and wide string literals is undefined. 

**A4. Meaning of Identifiers **

- identifiers or names, refer to a variety of things: functions; tags of structures, unions, and enumerations; members of structures or unions; enumerations constants; typedef names; and objects. 

- An object, sometimes called a variable, is a location in storage, and its interpretation depends on two main attributes: its storage class and its type. 

- The storage class determines the lifetime of the storage associated with identified field object; the type determines the meaning of the values found in the identified object. 

- A name also has scope, which is the region of the program in which it is known, and a linkage, which determines whether the same name in another scope refers to the same object or function. 

**A4.1 Storage class **

There are two main types of storage classes which are automatic and static. <u>Several keywords, together with the context of an object's declaration, specify its storage class.</u> Automatic objects are local to a block, and are discarded after exiting the block.  Declarations within a block create automatic objects if no <u>storage class specification</u> is mentioned, or if the auto specifier is used. Objects declared register are automatic, and are (if possible) stored in fast registers of the machine. 

Static objects may be local to block or external to all blocks, but in either case retain their values across exit from and reentry to functions to functions and blocks. Within a block, including a block that provides the code for a function, static objects are declared with the keyword `static`. The objects declared outside all blocks, at the same level as a function definitions, are always static. They may be made local to a particular translation unit by use of static keyword; this gives them internal linkage. They become global to an entire program by omitting an explicit storage class, or by using the keyword extern; this gives them external linkage. 

**A8.1 Storage Class Specifiers**

The storage class specifiers are :

```
Storage-class-specifier:
	auto
	register
	static
	extern
	typedef
```

The auto and register specifiers give the declared objects automatic storage class, and may be used only within functions. Such declarations also serve as definitions and cause storage to be reserved. A register declaration is equivalent to an auto declaration, but hints that the declared object will only certain types are eligible; the restrictions are implementation-dependent. However if an object is declared register, the unary operator may not be applied to it, explicitly or implicitly. 

Storage class Characteristics: 

- The static specifier gives the declared object static storage class and may be used either or outside a function. Inside a function, this specifier causes storage to be allocated, and serves as a definition.
- A declaration with extern, used inside a function, specifies that the storage for the declared objects is defined elsewhere; for its effect outside a function. 
- The typedef specifier does not reserve storage and is called a storage class specifier only for syntactic convenience

At most one storage class specifier may be given a declaration. if none is given, these rules are used: objects declared inside a function are taken to be auto ; functions declared within a function are taken to be extern; objects and functions declared outside a function are taken to be static, with external linkage. 

**A4.2 Basic Types**

There are several fundamental types. Objects declared as characters (char) are large enough to store any member of the execution character set. If a genuine character character from that set is stored in a char object, its value is equivalent to the integer code for the character, and is non-negative. Other quantities may be stored into char variables, but the available range of values, especially whether the value is signed, is implementation-dependent.  

Unsigned characters declared unsigned char consume the same amount of space as plain characters, but always appear non-negative; explicitly signed characters declared signed char likewise take the same space as plain characters. 

besides the char types, up to three sizes of integer, declared short int, int, and long int are available. Plain int objects have the natural size suggested by the host machine architecture; the other sizes are provides to meet special needs. Longer integers provide at least as much storage as shorter ones, but the implementation may make plain integers equivalent to either short integers, or long integers. The int types all represent signed values unless specified otherwise. 

Unsigned integers declared with the keyword unsigned, obey the law of arithmetic modulo 2^n where n is the number of bits in the representation, and thus arithmetic on unsigned quantities can never overflow. The set if non-negative values that can be stored in a signed object is a subset of the values that can be stored in the corresponding unsigned object, and the representation for the overlapping values is the same. 

Enumerations are unique types that have integral values; associated with each enumeration is a set of named constants. Enumerations behave like integers but it is common for a compiler to issue a warning when an object of a particular enumeration type is assigned something ether one of its constants, or an expression of its type. 

Because objects of these types can be interpreted as numbers, they will be referred to as arithmetic types. Types char and int of all sizes, each with or without sign and also enumeration types, will collectively be called integral types. The types float double and long double will be called floating types.

The void type specifies an empty set of values. It is used as the type returned, by functions that generate no value. 

**A.4.3 Derived Types**

Besides the basic types, conceptually there is an infinite amount of derived types constructed from the fundamental types in the following ways:

```
	arrays of objects of a given type;
	functions of objects of a given type;
	pionters to objects of a given type;
	structures containing a sequence of objects of various types
	unions capable of containing any one several objects of barous types
```

In general these methods of constructing objects can be applied recursively. 

**A4.4 Type Qualifiers**

Type Qualifiers: The keywords which are used to modify the properties of a variable 

There are two types of qualifiers which are:

1. const
2. volatile

An object's type may have additional qualifiers. Declaring an object const announces that its value will not be changed; declaring it volatile announces that it has several properties relevant to optimization. Neither qualifier affects  the range of values or arithmetic properties of the object. 

Const keyword:

- They refer to fixed values and also called literals.
- they may be belonging to any data type

Volatile keyword:

- When a variable is defined as volatile, the program may not change the value of the variable explicitly.
- But these variables values might keep changing without any explicit assignment by the program.

**A5 Objects and Lvalues**

<u>An *object* is a named region of storage; and *lvalue* is an expression referring to an object.</u> An example of an ivalue expression is an identifier with suitable type and storage class. There are operators that yield ivalues: for example, if E is an expression of pointer type, then *E is an lvalue expression referring to the object that E points to. The name "lvalue" comes from the assignment E1 = E2 in which the left operand E1 must be an lvalue expression. The discussion of each operator specifies whether it expects lvalue operands and whether it yeilds an lvalue. 

**A6 Conversions**

Some operators (+ - * / %) may, depending on their operands(x,y,z), cause conversions of the value of an operand from one type to another. Note that A6.5 summarizes the conversions demanded by most ordinary operators.

**A6.1 Integral Promotion**

A character, a short integer, or an integer bit-field, all either signed or not signed, or an object of enumeration type may be used in an expression wherever an integer may be used. If an int can represent all the values of the original type, then the value is converted to int; otherwise the value is converted to unsigned int. This is integral promotion.

**A6.2 Integer Conversions**

Note that when a value of floating type is converted to integral type, the fractional part is discarded; if the resulting value cannot be represented in integral type, the behavior is undefined. To be precise the result of converting to a signed type, the value if the unsigned type is wider. 

When any integer is converted to a signed type, the value is unchanged if it can be represented in the new type and is implementation define otherwise. 

**A6.3 Integer and Floating **

When a value of floating type is converted to integral type, the fractional part is discarded; if the resulting value cannot be represented in the integral type, the behavior is undefined. In particular, the result of converting negative floating values to unsigned integral type is not specified. 

When a value of integral type is converted to floating, and the value is in the representable range but is not exactly representable, then the result may be either the next higher or next lower representable value. If the result is out of range, the behavior in undefined. 

**A6.4 Floating Types**

When a less practice floating value is converted to an equally or more precise floating type, the value is unchanged. When a more precise floating value is converted to a less precise floating value is converted to be a less precise floating type, and the value is within representable value. If the result is out of range, the behavior is undefined. 

**A6.5 Arithmetic Conversions**

Many operators cause conversions and yield result types in a similar way. The effect is to bring operands into a common type, which is also the type of the result. This pattern is called the usual arithmetic conversions. 

First, if either operand is long double, the other is converted to long double.
· Otherwise, if either operand is double, the other is converted to double.
· Otherwise, if either operand is float, the other is converted to float.
· Otherwise, the integral promotions are performed on both operands; then, if either
operand is unsigned long int, the other is converted to unsigned long int.
160
· Otherwise, if one operand is long int and the other is unsigned int, the effect
depends on whether a long int can represent all values of an unsigned int; if so,
the unsigned int operand is converted to long int; if not, both are converted to
unsigned long int.
· Otherwise, if one operand is long int, the other is converted to long int.
· Otherwise, if either operand is unsigned int, the other is converted to unsigned
int.
· Otherwise, both operands have type int.

**A6.6  Pointers and Integers**

An expression of integral type may be added to or subtracted from a pointer; in such a case the
integral expression is converted as specified in the discussion of the addition operator
(Par.A.7.7).

Two pointers to objects of the same type, in the same array, may be subtracted; the result is
converted to an integer as specified in the discussion of the subtraction operator (Par.A.7.7).

An integral constant expression with value 0, or such an expression cast to type void *, may
be converted, by a cast, by assignment, or by comparison, to a pointer of any type. This
produces a null pointer that is equal to another null pointer of the same type, but unequal to
any pointer to a function or object.

Certain other conversions involving pointers are permitted, but have implementation-defined
aspects. They must be specified by an explicit type-conversion operator, or cast (Pars.A.7.5
and A.8.8).

A pointer may be converted to an integral type large enough to hold it; the required size is
implementation-dependent. The mapping function is also implementation-dependent.
A pointer to one type may be converted to a pointer to another type. The resulting pointer may
cause addressing exceptions if the subject pointer does not refer to an object suitably aligned in
storage. It is guaranteed that a pointer to an object may be converted to a pointer to an object
whose type requires less or equally strict storage alignment and back again without change; the
notion of ``alignment'' is implementation-dependent, but objects of the char types have least
strict alignment requirements. As described in Par.A.6.8, a pointer may also be converted to
type void * and back again without change.

A pointer may be converted to another pointer whose type is the same except for the addition
or removal of qualifiers (Pars.A.4.4, A.8.2) of the object type to which the pointer refers. If
qualifiers are added, the new pointer is equivalent to the old except for restrictions implied by
the new qualifiers. If qualifiers are removed, operations on the underlying object remain subject
to the qualifiers in its actual declaration.

Finally, a pointer to a function may be converted to a pointer to another function type. Calling
the function specified by the converted pointer is implementation-dependent; however, if the
converted pointer is reconverted to its original type, the result is identical to the original
pointer.

**A6.7 Void**

The non existent value of a void may not be used in any way, and neither explicit nor implicit conversion to any non-void type may be applied. Because a void expression denotes a non existent value, such an expression statement or as the left operand of a comma operator. 

An expression may be converted to type void cast. For example a void cast documents the discarding of the value of a function call used as an expression statement. 

**A6.8 Pointers to void**

Any pointer to an object may be converted to type void * without loss of information. If the result is converted back to the original pointer type, the original pointer is recovered. Unlike the pointer to pointer conversions discussed in A6.6, which generally require an explicit cast. Pointers may be assigned to and from pointer of type void * and may be compared with them. 

A void pointer is a pointer that has no associated data type with it. A void pointer can hold address of any type an can be type casted to any type. 

```c
int a = 10; 
char b = 'x'; 
  
void *p = &a;  // void pointer holds address of int 'a' 
p = &b; // void pointer holds address of char 'b' 

```

**A7. Expressions**

Expression: is a combination of operators, constants and variables. An expression may consist of one or more operands, and zero or more operators to produce a value. 

![](D:\Downloads\expression.PNG)

Expression may fall in the following types:

![](D:\Downloads\typeExpressions.PNG)

**A7.1 Pointer generation**

If the type of expression or subexpression is "array of T", for some type T, then the value of the expression is a pointer to the first object in the array, and the type of the expression is altered to "pointer to T". Note that this means that arrays are  basically pointer since that's what they are converted into in C; therefore we can interchange between array and pointers use properties such as [] and *. This conversion does not take place if the expression is the operand of the unary & operator, or of ++, --,  sizeof, or as the left operand of an assignment or the "." operator. Similarly, an expression of type "function returning T" except when used as the operand of the & operator, is converted to "pointer to function returning T". 

**A7.2 Primary Expressions**

Primary expressions are identifiers, constants, strings, or expressions in parentheses. 

```c
primary-expressions: 
	identifier
    constant
    string
    (expression)
```

Identifier: are names for entities in a program that include variables, functions, structures, unions and labels. 

An identifier is a primary expressions, provided is has been suitably declared as discussed below. Its type is specified by its declaration. An identifier is an ivalue if it refers to an object and if its type is arithmetic, structure, union, or pointer.

A constant is a primary expression. Its type depends on its form as discussed in A2.5. A string literal is a primary expression. A parenthesized expression is a primary expression whose type and value are identical to those of the unadorned expression. The presence of parenthesis does not affect whether the expression is an lvalue. 

**A7.3 Postfix Expressions**

The operators in postfix expressions group left to right:

```
postfix-expression:
primary-expression
postfix-expression[expression]
postfix-expression(argument-expression-listopt)
postfix-expression.identifier
postfix-expression->identifier
postfix-expression++
postfix-expression--
argument-expression-list:
assignment-expression
assignment-expression-list , assignment-expression
```

**A7.3.1 Array References**

A postfix expression followed by an expression in square brackets is a postfix expression denoting a subscripted array reference. One of the two expressions must have type "pointer to T" where T is some type, and other must have integral type; the type of the subscript T. The expression E1[E2] is identical by definition to *((E1) +(E2)).

**A7.3.2 Function Calls**

A function call is a postfix expression, called the function designator, followed by parenthesis containing a possibly empty , comma-separated list of arguments expressions, which constitute the argument to the function. If the postfix expression  consists of an identifier for which no declarations exits in the current scope, the identifier is implicitly declared as if the declaration

```
extern int identifier();
```

Had been given in the innermost block containing the function call. 

- The term argument is used for an expression passed by a function call; An **argument** is referred to the values that are passed within a function when the function is called.
- The term parameter is used for an input object (or its identifier) received by a function definition, or described in a function declaration; The parameter is referred to as the variables that are defined during a function declaration or definition.

```c
// C code to illustrate Arguments 
  
#include <stdio.h> 
  
// sum: Function defintion 
int sum(int a, int b) 
{ 
    // returning the addition 
    return a + b; 
} 
  
// Driver code 
int main() 
{ 
    int num1 = 10, num2 = 20, res; 
  
    // sum() is called with 
    // num1 & num2 as ARGUMENTS. 
    res = sum(num1, num2); 
  
    // Displaying the result 
    printf("The summation is %d", res); 
    return 0; 
} 

```

```c
// C code to illustrate Parameters 
  
#include <stdio.h> 
  
// Mult: Function defintion 
// a and b are the PARAMETERS 
int Mult(int a, int b) 
{ 
    // returning the multiplication 
    return a * b; 
} 
  
// Driver code 
int main() 
{ 
    int num1 = 10, num2 = 20, res; 
  
    // Mult() is called with 
    // num1 & num2 as ARGUMENTS. 
    res = Mult(num1, num2); 
  
    // Displaying the result 
    printf("The multiplication is %d", res); 
    return 0; 
} 

```

In preparing for the call to a function, a copy is made of each argument; all argument-passing is stricly by value. A function may change the values of its parameter objects, which are copies of the argument expressions, but these changes cannot affect the values of the arguments. For example if I have int x = 2 and int y = 4 and I passing them into a function named swap that swaps x and y swap(a, b) then only copies of x and y are sent to the function. Therefore the swap wont affect the values of x and y. Note that it is possible to pass a pointer on the understanding that the functions may change the value of the object to which the pointer points too. 

There are two styles to which functions may be declared. in the new style, the types of parameters are explicit and are part of the type of the function: such a declaration is also called a function prototype. In the old style, parameter types are not specified. Function declaration is discussed.

If the definition is new style, the promoted type of the argument must be that of the parameter itself, without promotion. If the function declaration in scope for call is new style, then the arguments are converted, as if by assignment, to the types of the corresponding parameters of the function prototype. The number of arguments must be the same as the number of explicitly described parameters, unless the declaration's parameters list ends with the ellipsis notation (, ...). In that case the number of arguments must be equal or exceed the number of parameters; trailing arguments beyond explicitly typed parameters suffer default argument promotion as described in the preceding paragraph. 

The order of evaluation of arguments is unspecified; take note that various compilers differ.

**A7.3.3 Structure References**

A postfix expression followed by a dot '.' followed by an identifier is a postfix expression. The first operand must be a structure or a union, and the identifier must name a member of the structure or union. The value is the name member of the structure or union, and its type is the type of the member. the expression is an lvalue if the fist expression is an lvalue, and if the type of the second expression is not an array type. 

A postfix expression followed by an arrow (built from - and >) followed by an identifier is a postfix expression. The first operand expression must be a pointer to a structure or a union, and the identifier must name a member of the structure or union. The result refers to the named member of the structure or union to which the pointer expressions points, and the type is the type of the member; the result is an lvalue if the type is not an array type. 

Thus the expression E1 ->MOS is the same as (*E1).mos.

**A7.3.4 Postfix Incrementation**

A postfix expression followed by a ++ and -- operator is a postfix expression. The value of the expression is the value of the operand. After the value is noted the operand is incremented (++) or decremented(--) by 1 . The operand must be an lvalue. 

**A7.4 Unary Operators**

Expressions with unary operators group left to right.

```
unary-expression:
postfix expression
++unary expression
--unary expression
unary-operator cast-expression
sizeof unary-expression
sizeof(type-name)

unary operator: one of
& * + - ~ !
```

**A7.4.1 Prefix  Incrementation Operators**

A unary expression preceded by a ++ or -- operator is a unary expression. The operand is incremented (++) or decremented (--) by 1. The value of the expression is the value after the incrementation/decrementation. This means the value is first incremented or decremented and then used inside the expression. 

**A7.4.2 Address Operator**

The unary & operator takes the address of its operand. The operand must be an lvalue referring neither to a bit-field nor to an object declared as register, or must be of function type. The result is a pointer to the object or function referred to by the lvalue. If the the type of operand is T, then the type of the result is "pointer to T".

The "Address Of" operator denoted by the ampersand character `&` is a unary operator, which returns the address of a variable. After declaration of a pointer variable, we need to initialize the pointer with the valid memory address; to get the memory address of a variable Address Of & operator is used.

```c
#include <stdio.h>
int main()
{
	int x=10;	//integer variable
	int *ptrX;	//integer pointer declaration
	ptrX=&x;	//pointer initialization with the address of x
	
	printf("Value of x: %d\n",*ptrX);
	return 0;
}
```

Output:

```
Value of x: 10
```

**A7.4.3 Indirection Operator**

The unary operator * operator denotes indirection, and returns the object or function to which its operand points to. It is an lvalue if the operand is a pointer to an object of arithmetic, structure, union or pointer type. Of the type of the expression is a "pointer to T" the type of the result is T. 

The "Dereference Operator" or "indirection Operator" denoted by asterisk character `*`, is a unary operator which preforms two operations with the pointer (which is used for two purposes with the pointers). 

- To declare a pointer
- To access the stored value of the memory (location) pointed by the pointer. 

To declare a pointer 

Syntax:

```c
data_type *pointer_variable_name;
```

To access the stored value of the memory (loaction) pointed by the pointer

```c
*pointer_variable_name;
```

**A7.4.4 Unary Plus Operator**

The operand  of the unary + operator must have arithmetic type, and the result is the value of the operand. An integral operand undergoes integral promotion. The type of the result is the the type of the promoted operand. 

**A7.4.5 Unary minus Operator**

The operand of the unary - operator must have the arithmetic type and the result is the negative of its operand. An integral operand undergoes integral promotion. The negative of an unsigned quantity is compared by subtracting the promoted value from the largest value of the promoted type and adding one; but negative zero is zero. The type of the result is the type of the promoted operand. 

**A7.4.6 Ones Compliment Operator**

The operand of the `~` operator must have integral type, and the result is the one's complement of its operand. The integral promotions are preformed. If the operand is unsigned, the result is computed by subtracting the value from the largest value of the promoted type. If the operand is signed, the result is computed by converting the promoted operand to the corresponding unsigned type, applying -, and converting back to the sign type. The type of the result is the type of the promoted operand. 

**A7.4.7 Logical Negation Operator**

The operand of the ! operator must have arithmetic type or be a pointer, and the result is 1 if the value of its operand compares equal to 0 and 0 otherwise. The type of the result is int.

**A7.4.8 Sizeof Operator**

The sizeof operator yields the number of bytes (8bits) required to store an object of the type of its operand. The operand is either an expression, which is not evaluated, or a parenthesized type name. When sizeof is applied to a char, the result is 1; when applied to an array, the result is the number of bytes in the array. When applied to a structure or union, the result is the number of bytes in the object, including any padding required to make the object tile an array: the size of an array of n elements in n times the size of one element. The operator may not be applied to an operand of function type, or of incomplete type, or to a bit-field. 

```c
#include <stdio.h> 
int main() 
{ 
    printf("%lu\n", sizeof(char)); 
    printf("%lu\n", sizeof(int)); 
    printf("%lu\n", sizeof(float)); 
    printf("%lu", sizeof(double)); 
    return 0; 
} 
```

Output:

```
1
4
4
8
```

another example 

```c
#include <stdio.h> 
int main() 
{ 
    int a = 0; 
    double d = 10.21; 
    printf("%lu", sizeof(a + d)); 
    return 0; 
} 
```

Output:

```
8
```

**A7.5 Casts**

A unary expression preceded by the parenthesized name of a type causes conversion of the value of the expression to the named type.

```
cast-expression:
	unary-expression
	(type-name) cast-expression
```

This construction is called a cast. Type names are described at A8.8.

A cast: converting one datatype into another is known as type casting. 

```
(type-name) expression
```

example 

```c
#include <stdio.h>

main() {

   int sum = 17, count = 5;
   double mean;

   mean = (double) sum / count;
   printf("Value of mean : %f\n", mean );
}
```

**A7.6 Multiplicative Operators**

The multiplicative operator *, / and % group left to right. If the operands have arithmetic type, the usual arithmetic conversion are performed. There are some additional type possibilities for operator.

```
multiplicative-expression:
multiplicative-expression * cast-expression
multiplicative-expression / cast-expression
multiplicative-expression % cast-expression
```

The operands of * and / must have arithmetic type; the operands of % must have integral type. The usual arithmetic conversions are performed on the operands and predict the type of the result. 

The binary * operator denotes multiplication.

The binary / operator yields the quotient, and the % operator the remainder, of the division of the first operand by the second if the second operand is 0, the result is undefined. Otherwise, it is always true that (a/b) * b + a % b is equal to a. if both operands are non negative then the remainder is non negative and smaller than divisor, if not it is guaranteed only that the absolute value of the remainder is smaller than the absolute value of the divisor.

**A7.7 Additive Operators**

The additive opertors + and - group left to right . if the operands have arithmetic type, the usual arithmetic conversions are performed. There are some additional type possibilities for each operator. 

```
additive-expression:
multiplicative-expression
additive-expression + multiplicative-expression
additive-expression - multiplicative-expression
```

The result of the + operator is the sum of the operands. A pointer to an object in an array and a
value of any integral type may be added. The latter is converted to an address offset by
multiplying it by the size of the object to which the pointer points. The sum is a pointer of the
same type as the original pointer, and points to another object in the same array, appropriately
offset from the original object. Thus if P is a pointer to an object in an array, the expression
P+1 is a pointer to the next object in the array. If the sum pointer points outside the bounds of
the array, except at the first location beyond the high end, the result is undefined.  

The result of the - operator is the difference of operands. A value of any integral type may be subtracted from a pointer, and then the same conversions and conditions as for addition apply. 

If two pointers to objects of the same type are subtracted, the result is a signed integral value representing the displacement between the pointed-to objects; pointers to successive objects differ by 1. The type of the result depends on the implementation, but is defined as ptrdiff_t in the standard header <stddef.h>. The value is undefined unless the pointers point to objects with the same array; however if p points to the last member of an array, then (P+1)-p has value 1.

**A7.8 Shift Operators**

The shift operators << and >> group left-to-right. For both operators, each operand must be integral, and is subject to the integral promotions. The type of the result is that of the promoted left operand. The result is undefined if the right operand is negative, or greater than or equal to the number of bits in the left expression's type.

```c
shift-expression:
additive-expression
shift-expression << additive-expression
shift-expression >> additive-expression
```

The value of E1 << E2 (interpreted as a bit pattern) left shifted E2 bits; in the absence of overflow, this is equivalent to multiplication by 2^E2. The value of E1 >> E2 is E1 right shifted E2 bit positions. The right shift is equivalent to division by 2^E2 if E1 is unsigned or if it has a non-negative value; otherwise the result is implementation defined.   

```c
/* C++ Program to demonstrate use of left shift  
   operator */
#include<stdio.h> 
int main() 
{ 
    // a = 5(00000101), b = 9(00001001) 
    unsigned char a = 5, b = 9;  
  
    // The result is 00001010  
    printf("a<<1 = %d\n", a<<1); 
    
    // The result is 00010010  
    printf("b<<1 = %d\n", b<<1);   
    return 0; 
} 
```

Output:

```
a<<1 = 10
b<<1 = 18
```

**A7.9 Relational Operators**

The relational operators group left to right, but this fact is not useful; a<b<c is parsed (a<b) <c and a<b evaluates to either 0 or 1.

```
relational-expression:
shift-expression
relational-expression < shift-expression
relational-expression > shift-expression
relational-expression <= shift-expression
relational-expression >= shift-expression
```

The operators < (less), > (greater), <= (less or equal), >= (greater or equal) all yield 0 if the specified relation is false and 1 if it is true. The type of the result is int. Note that pointers to objects of the same type may be compared; the result depends on the relative locations in the address space of the pointed to objects. 

Pointer comparison is defined only for parts of the
same object; if two pointers point to the same simple object, they compare equal; if the
pointers are to members of the same structure, pointers to objects declared later in the
structure compare higher; if the pointers refer to members of an array, the comparison is
equivalent to comparison of the the corresponding subscripts. If P points to the last member of
an array, then P+1 compares higher than P, even though P+1 points outside the array.
Otherwise, pointer comparison is undefined.  

**A7.10 Equality Operators**

```
equality-expression:
relational-expression
equality-expression == relational-expression
equality-expression != relational-expression
```

The == (equal to) and the != (not equal to) operators are analogous to the relational operators except for their lower precedence. (Thus a < b == c<d is 1 whenever a < b and c<d have the same truth-value.)

The equalitty operators follow the same rules as the relational operators, but permit additional possibilities: a pointer may be compared to a constant integral expression with value 0 or to a pointer to void. 

**A7.11 Bitwise AND Operator**

```
AND-expression:
equality-expression
AND-expression & equality-expression
```

The usual arithmetic conversions are preformed; the result is the bitwise AND function of the operands. The operator applies only to integral operands. 

```
12 = 00001100 (In Binary)
25 = 00011001 (In Binary)

Bit Operation of 12 and 25
  00001100
& 00011001
  ________
  00001000  = 8 (In decimal)
```

Example:

```c
#include <stdio.h>
int main()
{
    int a = 12, b = 25;
    printf("Output = %d", a&b);
    return 0;
}

//Output = 8
```

**A.7.12 Bitwise Exclusive or Operator**

```
exclusive-OR-expression:
AND-expression
exclusive-OR-expression ^ AND-expression
```

The usual arithmetic conversions are performed; the result is the bitwise exclusive OR function of the operands. The operator applies only to integral operands. 

```
12 = 00001100 (In Binary)
25 = 00011001 (In Binary)

Bitwise XOR Operation of 12 and 25
  00001100
^ 00011001
  ________
  00010101  = 21 (In decimal)
```

Example:

```c
#include <stdio.h>
int main()
{
    int a = 12, b = 25;
    printf("Output = %d", a^b);
    return 0;
}

//output = 21
```

**A7.13 Bitwise Inclusive or Operator**

```c
inclusive-OR-expression:
exclusive-OR-expression
inclusive-OR-expression | exclusive-OR-expression
```

The usual arithmetic conversions are performed; the result is the bitwise inclusive OR function of it operands. The Operator applies only to integral operands.

```
12 = 00001100 (In Binary)
25 = 00011001 (In Binary)

Bitwise OR Operation of 12 and 25
  00001100
| 00011001
  ________
  00011101  = 29 (In decimal)
```

Example

```c
#include <stdio.h>
int main()
{
    int a = 12, b = 25;
    printf("Output = %d", a|b);
    return 0;
}

//output 29
```

**A7.14 Logical AND operator**

```
logical-AND-expression:
inclusive-OR-expression
logical-AND-expression && inclusive-OR-expression
```

The && operator groups left to right. It returns 1 if both its operands compare unequal to zero, 0 otherwise. Unlike &, && guarantees left to right evaluation: the first operand is evaluated, including all side effects, if it is equal to 0, the value of the expression is 0. Otherwise, the right operand is evaluated, and if it is equal to 0, the expression value is 0 otherwise 1.

The operand need not have the same type, but each must have arithmetic type or be a pointer. 

**A7.15 Logical OR Operator**

```
logical-OR-expression:
logical-AND-expression
logical-OR-expression || logical-AND-expression
```

The || operator groups left to right. It returns 1 if either of its operands are true, and other wise. The operands need not to have the same type but each must have arithmetic type or be a pointer. The result is int. 

**7.16 Conditional Operator**

```
conditional-expression:
logical-OR-expression
logical-OR-expression ? expression : conditional-expression
```

Also known as the ternary operator is another form of making a if else block of code without having to take up so many lines of code. Conditional operators return one value if the condition is true and returns another value if the condition is false.

Example:

```c
#include <stdio.h>
 
int main()
{
   int x=1, y ;
   y = ( x ==1 ? 2 : 0 ) ;
   printf("x value is %d\n", x);
   printf("y value is %d", y);
}

/* -----Output------
   x value is 1
   y value is 2     */
```

**7.17 Assignment Expressions **

There are several assignment operators; all group right to left. 

```
assignment-expression:
conditional-expression
unary-expression assignment-operator assignment-expression
assignment-operator: one of
= *= /= %= += -= <<= >>= &= ^= |=
```

All require an lvalue as left operand, and the lvalue must be modifiable: it must be an array, and must not have incomplete type or be a function. It also cant be an const variable. 

**A7.18 Comma Operator**

```
expression:
assignment-expression
expression , assignment-expression
```

A pair of expressions separated by a comma is evaluated left to right, and the value of the left expression is discarded. The type and value of the result are the type and value of the right operand. All side effects from the evaluation of the left operand are completed before beginning evaluation of the right operand. 

**A7.19 Constant Expressions** 

Syntactically, A constant expression is an expression restricted to a subset of operators:

```
constant-expression:
conditional-expression
```

Expressions that evaluate to a constant are required in several contexts: after case, as array
bounds and bit-field lengths, as the value of an enumeration constant, in initializers, and in
certain preprocessor expressions.

Constant expressions may not contain assignments, increment or decrement operators, function
calls, or comma operators; except in an operand of sizeof. If the constant expression is
required to be integral, its operands must consist of integer, enumeration, character, and
floating constants; casts must specify an integral type, and any floating constants must be cast
to integer. This necessarily rules out arrays, indirection, address-of, and structure member
operations. (However, any operand is permitted for sizeof.)

More latitude is permitted for the constant expressions of initializers; the operands may be any
type of constant, and the unary & operator may be applied to external or static objects, and to
external and static arrays subscripted with a constant expression. The unary & operator can
also be applied implicitly by appearance of unsubscripted arrays and functions. Initializers must
evaluate either to a constant or to the address of a previously declared external or static object
plus or minus a constant  

A constant expression can be evaluated at compile time.  That means it has no variables in it.  For example:

```c
5 + 7 / 3
```

is a constant expression.  Something like:

```c
5 + someNumber / 3
```

is not, assuming `someNumber` is a variable (ie, not itself a compile-time constant

**A8 Declarations**

Declarations specify the interpretation given to each identifier; they do not necessarily reserve storage associated with the identifier. Declarations that reserve storage are called definitions. declarations have the form of:

```
declaration:
	declaration-specifiers int-declarator-list-opt;
```

The declarators in the init-declarator-list contain the identifiers being declared; the declaration specifiers consist of a sequence of type and storage class specifiers. 

```
declaration-specifiers:
    storage-class-specifier declaration-specifiersopt
    type-specifier declaration-specifiersopt
    type-qualifier declaration-specifiersopt
init-declarator-list:
    init-declarator
    init-declarator-list , init-declarator
init-declarator:
    declarator
    declarator = initializer
```

Note that declarators will be discussed later; they contain the names being declared. A declaration must have at least one character, or its type specifier must declare a structure tag a union tag, or the members of an enumeration; empty declarations are not permitted. 

**A8.1 Storage Class specifiers **

The storage class specifiers are:

```
storage-class specifier:
auto
register
static
extern
typedef
```

The auto and register specifiers give the declared objects automatic storage class, and may
be used only within functions. Such declarations also serve as definitions and cause storage to
be reserved. A register declaration is equivalent to an auto declaration, but hints that the
declared objects will be accessed frequently. Only a few objects are actually placed into
registers, and only certain types are eligible; the restrictions are implementation-dependent.
However, if an object is declared register, the unary & operator may not be applied to it,
explicitly or implicitly.  

The static specifier gives the declared objects static storage class, and may be used either
inside or outside functions. Inside a function, this specifier causes storage to be allocated, and
serves as a definition; for its effect outside a function, see Par.A.11.2.
A declaration with extern, used inside a function, specifies that the storage for the declared
objects is defined elsewhere; for its effects outside a function, see Par.A.11.2.
The typedef specifier does not reserve storage and is called a storage class specifier only for
syntactic convenience; it is discussed in Par.A.8.9.
At most one storage class specifier may be given in a declaration. If none is given, these rules
are used: objects declared inside a function are taken to be auto; functions declared within a
function are taken to be extern; objects and functions declared outside a function are taken to
be static, with external linkage. See Pars. A.10-A.11.  

**A8.2 Type Specifiers**

The type specifiers are :

```c
storage-class specifier:
auto
register
static
extern
typedef
```

We can pair the word `long` and `short` with `int`; the meaning is the same if int is not mentioned. Also the word long may be specified together with double. At most one of signed or unsigned may be specified together with int or any of its short or long varieties, or with char. The signed specifier is useful for forcing char objects to carry a sign; it is permissible but redundant with other integral types. 

Types may also be qualified, to indicate special properties of the objects being declared. 



```c
type-qualifier:
	const
	volatile
```

Type qualifiers may appear with any type specifiers. A const object may be initialized, but not thereafter assigned to. There are no implementation-independent semantics for volatile objects. 

**A8.3 Structure and Union Declarations**

A structure is an object consisting of a sequence of named members of various types. A union is an object that contains, at different times, any one of several members of various types. Structure and union specifiers have the same form.

```
struct-or-union-specifier:
struct-or-union identifieropt{ struct-declaration-list }
struct-or-union identifier
struct-or-union:
struct
union
```

A struct-declaration-list is a sequence of declaration for the members of the structure or union:

```
struct-declaration-list:
struct declaration
struct-declaration-list struct declaration
struct-declaration: specifier-qualifier-list struct-declarator-list;
specifier-qualifier-list:
type-specifier specifier-qualifier-listopt
type-qualifier specifier-qualifier-listopt
struct-declarator-list:
struct-declarator
struct-declarator-list , struct-declarator
```

Usually, a structure declarator is just a declarator for a member of a structure or union. A structure member may also consist of a specified number of bits. The member is called a bit field. 

```c
Struct-declarator:
	declarator
    declarator: constant-expression\
A type specifier of the form 
    struct-or-union identifier { struct-declaration-list}
```

Declares the identifier to be the tag of the structure or union specified by the list. 

struct-union identifier

If a specifier with a tag but without a list appears when the tag is not declared, an incomplete type is specified. Objects with an incomplete structure or union type may be mentioned in contexts where their size is not needed. 

A structure may not contain a member of incomplete type. Therefore, it is impossible to declare a structure or union containing an instance of itself. However, besides giving a name to the structure or union type, tags allow definition of self-referential structures; a structure or union may contain a pointer to an instance of itself, because pointers to incomplete types may be declared. 

```
struct-or-union identifier; 
```

That declare a structure or union, but have no declaration list and no declarators. 

A structure or union specifier with a list but no tag created a unique type; it can be referred to directly only in the declaration of which it is a part. The names of members and tags do not conflict with each other or with ordinary variables. A member name may not appear twice in the same structure or union, but the same member name may be used in different structures or unions. 

A non field member of a structure may have an object type. A field member which need not have a declarator and thus may be unnamed has type int, unsigned int, or signed int, and is interpreted as an object of integral type of the specified length in bits. Adjacent field member of a structure are packed into implementation-dependent storage units in an implementation dependent direction. when a field following another field will not fit into a partially storage unit, it may be split between units or the unit may be padded. 

The numbers of a structure have addresses increasing in the order of their declarations. A non-field member of a structure is aligned at an addressing boundary depending on its type, there may be unnamed holes in a structure. If a pointer to a structure is cast to the type of a pointer to its first  , 

A union may be though may be thought of as a structure al of whose members begin at offset 0 and whose size is sufficient to contain any member. 

Example :

```c
struct tnode {
    char tword[20];
    int count;
    struct tnode *right;
    
};
```

Which contains an array of 20 characters, an integer and two pointers to similar structures. Once the declaration has been given, the declaration

```c
struct tnode s, *sp;
```

declares s to be a structure of the given sort and sp to be a pointer to a structure of the given sort.  The given sort here is tnode. With these declarations, the expression 

```c
sp->count
```

refers to the count field of the structure to which sp points;

```c
s.left
```

refers to the left subtree pointer of the structure s; and 

```c
s.right->tword[0]
```

refers to the first character of the tword member of the right subtree of s.

In general, a member of a union may not be inspected unless the value of the union has been assigned using the same member. However, one special guarantee simplifies the use of unions: if a union contains several structures that share a common initial sequence, and if the union currently contains one of these structures. For instance, the following legal format:

```c
union {
    struct {
        int type;
    } n;
    struct {
        int type;
        int intnode;
    }ni;
    struct {
        int type;
        float floatnode;
    } nf;
} u;
...
u.nf.type = FLOAT;
u.nf.floatnode = 3.14;
...
if(u.n.type == FLOAT)
    ...sin(u.nf.floatnode)...
```

**A8.4 Enumerations**

Enumerations are unique types with values ranging over a set of named constants called enumerators. The form of an enumeration specifier borrows from that of structures and unions. 

```
enum-specifier:
enum identifieropt { enumerator-list }
enum identifier
enumerator-list:
enumerator
enumerator-list , enumerator
enumerator:
identifier
identifier = constant-expression
```

The identifiers in an enumerator list are declared as constants of type int, and may appear wherever constants are required. If no enumerations with = appear , then the values of the corresponding constants begin with 0 and increase by 1 as the declaration is read from left to right. An enumerator with = gives the associated identifier continue the progression from the assigned value. 

Enumerators names in the same scope must all be distinct from each other and from ordinary variable names, but the values need not be distinct.

The role of the identifier in the enum-specifier is analogous to that of the structure tag in a struct specifier; it names a particular enumeration.  

Example of enumerations 

```c
// An example program to demonstrate working 
// of enum in C 
#include<stdio.h> 
  
enum week{Mon, Tue, Wed, Thur, Fri, Sat, Sun}; 
// remember 0 index and that we count from left to right 0,1,2,3,4,5 
int main() 
{ 
    enum week day; 
    day = Wed; 
    printf("%d",day); 
    return 0; 
}  

//Output 
//2
```

**A8.5 Declarators **

Declarators have the syntax of: 

```
declarator:
    pointeropt direct-declarator
direct-declarator:
    identifier
    (declarator)
    direct-declarator [ constant-expressionopt ]
    direct-declarator ( parameter-type-list )
    direct-declarator ( identifier-listopt )
pointer:
    * type-qualifier-listopt
    * type-qualifier-listopt pointer
type-qualifier-list:
    type-qualifier
    type-qualifier-list type-qualifier
```

The structure of declarators resembles that of indirection, function, and array expressions; the group is the same.

**A8.6 Meaning of Declarators**

A list of declarators appears after a sequence of type and storage class specifiers. Each declarator declares a unique main identifier, the one appears as the first alternative of the production for direct-declarator. The storage class specifier apply directly to this identifier, but its type depends on the form of its declarator. A declarator is read as an assertion that when its identifier appears in an expression of the same form as the declarator, it yields an object of the specified type. 

A declaration has the form "T, D" where T is a type and D is a declarator. The type attributed to the identifier in the various forms of declarator is described inductively using the notation. 

In a declaration T D where D is an unadorned identifier, the type of the identifier is T.

in a declaration T D where D has the form

(  D1 )

then the type of the identifier in D1 is the same as that of D. The parentheses do not alter the type, but may change the binding of complex declarators. 

Example 

```
int i = 0;
```

The expression int i = 0; is a declaration while the i part is a declarator. 

**A8.6.1 Pointer Declarators**

In a declaration T D where D has the form:

```
* type-qualifier list-opt D1
```

and the type of the identifier in the declaration T D1 is "type-modifier T", the type of the identifier of D is "type-modifier type qualifier list pointer to T". Qualifiers following * apply to pointer itself, rather than to the object to which the pointer points. 

For example 

```c
int *ap[];
```

Here ap[] plays the role of D1; a declaration "int ap[]" below would give ap the type "array of int" the type qualifier list is empty, and the type modifier is "array of". Hence the actual declaration gives ap the type "array of pointers to int". 

another example:

```c
int i, *pi, *const cpi = &i;
const int ci = 3, *pci;
```

declare an integer i and pointer to an integer pi. the value of the constant pointer cpi may not be changed, it will always point to the same location, however the value to which it refers may be altered. This means that if we set int i = 2 then we change it to int i = 3; the value for cpi will change as well. The integer ci is a constant, and may not be changed (though it may may initialized, as here). The type of pci is "pointer to const int" and pci itself may be changed to point to another place, but the value to which it points may not be altered by assigning through pci. 

**A8.6.2 Array Declarators**

In a declaration T D where D has the form 

```
D1[constant-expression]
```

and the type of the identifier in the declaration T D1 is type-modifier T, the type of the identifier of D is type modifier array of T. If the constant expression is present, it must have integral type, and value greater than 0. If the constant expression specifying the bound missing, the array has an incomplete type. 

An array may be constructed from an arithmetic type, from a pointer, from a structure or
union, or from another array (to generate a multi-dimensional array). Any type from which an
array is constructed must be complete; it must not be an array of structure of incomplete type.
This implies that for a multi-dimensional array, only the first dimension may be missing.  

```c
float fa[17], *afp[17];
```

declares an array of float numbers and an array of pointer to float numbers, Also 

```c
static int x3d[3][5][7];
```

declares a static three-dimensional array of integers, with rank 3 X 5 X 7. In complete detail,
x3d is an array of three items: each item is an array of five arrays; each of the latter arrays is an
array of seven integers. Any of the expressions x3d, x3d[i], x3d[i][j], x3d[i][j][k] may
reasonably appear in an expression. The first three have type ``array,'', the last has type int.
More specifically, x3d[i][j] is an array of 7 integers, and x3d[i] is an array of 5 arrays of 7
integers.

The array subscripting operation is defined so that E1[E2] is identical to *(E1+E2). Therefore,
despite its asymmetric appearance, subscripting is a commutative operation. Because of the
conversion rules that apply to + and to arrays (Pars.A6.6, A.7.1, A.7.7), if E1 is an array and
E2 an integer, then E1[E2] refers to the E2-th member of E1.

In the example, x3d[i][j][k] is equivalent to *(x3d[i][j] + k). The first subexpression
x3d[i][j] is converted by Par.A.7.1 to type pointer to array of integers,'' by Par.A.7.7, the
addition involves multiplication by the size of an integer. It follows from the rules that arrays
are stored by rows (last subscript varies fastest) and that the first subscript in the declaration
helps determine the amount of storage consumed by an array, but plays no other part in
subscript calculations  

**A8.6.3 Function Declarators **

In a new-style function declaration T D where D has the form 

```
D1 (parameter-type-list)
int swap( int a, int b)
```

and the type of the identifier in the declaration T D1 is "type modifier T", the type of the identifier of D is "type-modifier" function with arguments *parameter-type-list* returning T.

```
parameter-type-list:
    parameter-list
    parameter-list , ...
parameter-list:
    parameter-declaration
    parameter-list , parameter-declaration
parameter-declaration:	
    declaration-specifiers declarator
    declaration-specifiers abstract-declaratoropt
```

In the new style declaration, the parameter list specifies the types of the parameters. As a special case, the declarator for a new style function with no parameter has a parameter type list consisting solely of the keyword void. If the parameter type list ends with an ellipses ",...", then the function may accept more arguments than the number of parameters explicitly described;

The types of parameter that are arrays or functions are altered to pointers, in accordance with the rules for parameter conversions. The only storage class specifier permitted in a parameter's declaration specifier is register, and this specifier is ignored unless the function declarator heads a function definition. Similarly, if the declarators in the parameter declarations contain identifiers and the function declarator does not head a function, the identifier go out of scope immediately. 

**A8.7 Initialization** 

When an object is declared, its init-declarator may specify an initial value for the identifier
being declared. The initializer is preceded by =, and is either an expression, or a list of
initializers nested in braces. A list may end with a comma, a nicety for neat formatting.

```
initializer:
assignment-expression
{ initializer-list }
{ initializer-list , }
initializer-list:
initializer
initializer-list , initializer
```

All the expressions in the initializer for a static object or array must be constant expressions as
described in Par.A.7.19. The expressions in the initializer for an auto or register object or
array must likewise be constant expressions if the initializer is a brace-enclosed list. However,
if the initializer for an automatic object is a single expression, it need not be a constant
expression, but must merely have appropriate type for assignment to the object.

The first edition did not countenance initialization of automatic structures, unions, or arrays. The
ANSI standard allows it, but only by constant constructions unless the initializer can be expressed by a
simple expression.

A static object not explicitly initialized is initialized as if it (or its members) were assigned the
constant 0. The initial value of an automatic object not explicitly intialized is undefined.
The initializer for a pointer or an object of arithmetic type is a single expression, perhaps in
braces. The expression is assigned to the object.

The initializer for a structure is either an expression of the same type, or a brace-enclosed list
of initializers for its members in order. Unnamed bit-field members are ignored, and are not
initialized. If there are fewer initializers in the list than members of the structure, the trailing
members are initialized with 0. There may not be more initializers than members. Unnamed bitfield members are ignored,and are not initialized.

The initializer for an array is a brace-enclosed list of initializers for its members. If the array has
unknown size, the number of initializers determines the size of the array, and its type becomes
complete. If the array has fixed size, the number of initializers may not exceed the number of
members of the array; if there are fewer, the trailing members are initialized with 0.

As a special case, a character array may be initialized by a string literal; successive characters
of the string initialize successive members of the array. Similarly, a wide character literal
(Par.A.2.6) may initialize an array of type wchar_t. If the array has unknown size, the number
of characters in the string, including the terminating null character, determines its size; if its
size is fixed, the number of characters in the string, not counting the terminating null character,
must not exceed the size of the array.

The initializer for a union is either a single expression of the same type, or a brace-enclosed
initializer for the first member of the union.

The first edition did not allow initialization of unions. The ``first-member'' rule is clumsy, but is hard
to generalize without new syntax. Besides allowing unions to be explicitly initialized in at least a
primitive way, this ANSI rule makes definite the semantics of static unions not explicitly initialized.
An aggregate is a structure or array. If an aggregate contains members of aggregate type, the
initialization rules apply recursively. Braces may be elided in the initialization as follows: if the
initializer for an aggregate's member that itself is an aggregate begins with a left brace, then the
succeding comma-separated list of initializers initializes the members of the subaggregate; it is
erroneous for there to be more initializers than members. If, however, the initializer for a

subaggregate does not begin with a left brace, then only enough elements from the list are
taken into account for the members of the subaggregate; any remaining members are left to
initialize the next member of the aggregate of which the subaggregate is a part.
For example,
int x[] = { 1, 3, 5 };
declares and initializes x as a 1-dimensional array with three members, since no size was
specified and there are three initializers.

```
float y[4][3] = {
{ 1, 3, 5 },
{ 2, 4, 6 },
{ 3, 5, 7 },
};
```

is a completely-bracketed initialization: 1, 3 and 5 initialize the first row of the array y[0],
namely y[0][0], y[0][1], and y[0][2]. Likewise the next two lines initialize y[1] and y[2].
The initializer ends early, and therefore the elements of y[3] are initialized with 0. Precisely
the same effect could have been achieved by

```
float y[4][3] = {
1, 3, 5, 2, 4, 6, 3, 5, 7
};
```

The initializer for y begins with a left brace, but that for y[0] does not; therefore three
elements from the list are used. Likewise the next three are taken successively for y[1] and for
y[2]. Also,

```
float y[4][3] = {
{ 1 }, { 2 }, { 3 }, { 4 }
};
```



initializes the first column of y (regarded as a two-dimensional array) and leaves the rest 0.
Finally,
char msg[] = "Syntax error on line %s\n";
shows a character array whose members are initialized with a string; its size includes the
terminating null character.  



All the expressions in the initializer for a static object or array must be constant expressions as
described in Par.A.7.19. The expressions in the initializer for an auto or register object or
array must likewise be constant expressions if the initializer is a brace-enclosed list. However,
if the initializer for an automatic object is a single expression, it need not be a constant
expression, but must merely have appropriate type for assignment to the object.
The first edition did not countenance initialization of automatic structures, unions, or arrays. The
ANSI standard allows it, but only by constant constructions unless the initializer can be expressed by a
simple expression.

A static object not explicitly initialized is initialized as if it (or its members) were assigned the
constant 0. The initial value of an automatic object not explicitly intialized is undefined.
The initializer for a pointer or an object of arithmetic type is a single expression, perhaps in
braces. The expression is assigned to the object.
The initializer for a structure is either an expression of the same type, or a brace-enclosed list
of initializers for its members in order. Unnamed bit-field members are ignored, and are not
initialized. If there are fewer initializers in the list than members of the structure, the trailing
members are initialized with 0. There may not be more initializers than members. Unnamed bitfield members are ignored,and are not initialized.

The initializer for an array is a brace-enclosed list of initializers for its members. If the array has
unknown size, the number of initializers determines the size of the array, and its type becomes
complete. If the array has fixed size, the number of initializers may not exceed the number of
members of the array; if there are fewer, the trailing members are initialized with 0.

As a special case, a character array may be initialized by a string literal; successive characters
of the string initialize successive members of the array. Similarly, a wide character literal
(Par.A.2.6) may initialize an array of type wchar_t. If the array has unknown size, the number
of characters in the string, including the terminating null character, determines its size; if its
size is fixed, the number of characters in the string, not counting the terminating null character,
must not exceed the size of the array.

The initializer for a union is either a single expression of the same type, or a brace-enclosed
initializer for the first member of the union.

An aggregate is a structure or array. If an aggregate contains members of aggregate type, the
initialization rules apply recursively. Braces may be elided in the initialization as follows: if the
initializer for an aggregate's member that itself is an aggregate begins with a left brace, then the
succeding comma-separated list of initializers initializes the members of the subaggregate; it is
erroneous for there to be more initializers than members. If, however, the initializer for a

subaggregate does not begin with a left brace, then only enough elements from the list are
taken into account for the members of the subaggregate; any remaining members are left to
initialize the next member of the aggregate of which the subaggregate is a part.
For example,
int x[] = { 1, 3, 5 };
declares and initializes x as a 1-dimensional array with three members, since no size was
specified and there are three initializers.

```
float y[4][3] = {
{ 1, 3, 5 },
{ 2, 4, 6 },
{ 3, 5, 7 },
};
```

is a completely-bracketed initialization: 1, 3 and 5 initialize the first row of the array y[0],
namely y[0][0], y[0][1], and y[0][2]. Likewise the next two lines initialize y[1] and y[2].
The initializer ends early, and therefore the elements of y[3] are initialized with 0. Precisely
the same effect could have been achieved by

```
float y[4][3] = {
1, 3, 5, 2, 4, 6, 3, 5, 7
};
```

The initializer for y begins with a left brace, but that for y[0] does not; therefore three
elements from the list are used. Likewise the next three are taken successively for y[1] and for
y[2]. Also,

```
float y[4][3] = {
{ 1 }, { 2 }, { 3 }, { 4 }
};
```

initializes the first column of y (regarded as a two-dimensional array) and leaves the rest 0.
Finally,
char msg[] = "Syntax error on line %s\n";
shows a character array whose members are initialized with a string; its size includes the
terminating null character.  

**A8.8 Type Names**

In several contexts (to specify type conversions explicitly with a cast to declare parameter types in function declarators, and as an argument of sizeof) it is necessary to supply the name of a data type. This is accomplished using a *type name* which is syntactically a declaration for an object of that type omitting the name of the object.

```
type-name:
    specifier-qualifier-list abstract-declaratoropt
abstract-declarator:
    pointer
    pointeropt direct-abstract-declarator
direct-abstract-declarator:
    ( abstract-declarator )
    direct-abstract-declaratoropt [constant-expressionopt]
    direct-abstract-declaratoropt (parameter-type-listopt)
```

It is possible to identify uniquely the location in the abstract-declarator where the identifier would appear if the construction were a declarator in declaration. The named is then the same as the type of the hypothetical identifier. For example

```c
int
int *
int *[3]
int (*)[]
int *()
int (*[])(void)
```

name respectively the types "integer", "pointer to integer", "array of 3 pointers to integers", "pointer to an array of an unspecified number of integers", "function of unspecified parameters returning to integer", " array of unspecified size , of pointers to functions with no parameters each returning an integer".

**A8.9 Typedef**

Declarations whose storage class specifiers is typedef do not declare objects; instead they define identifiers that name types. These identifiers are called typedef names.

```
typedef-name:
	identifier
```

a typedef declaration attributes a type to each name among its declarators in the usual way. Thereafter, each such typedef name is  syntactically equivalent to a type specifier keyword for the associated type. For example:

```c
typedef long Blockno, *Blockptr;
typedef struct { double r, theta; } Complex;
```

The constructions 

```
Blockno b;
extern Blockptr bp;
Complex z, *zp;
```

These are legal declarations. The type of b is long, that of bp is "pointer to long" and that of z is the specified structure; zp is a pointer to such structure. 

Note that typedef does not introduce new types, only synonyms for types that could be specified in another way. In the example, b has the same type as any other long object. 

Typedef names may be redeclared in an inner scope, but a non-empty set of type specifiers must be given. For example,

```
extern Blockno;
```

does not redeclare Blockno, but

```
extern int Blockno;
```

does. 

**A8.10 Type Equivalence **

Two type specifiers lists are equivalent if they contain the same set of type specifiers, taking into account that some specifiers can be implied by others (for example, long alone implies long int). Structures, unions, and enumerations with different tags are distinct, and a tagless union, structure, or enumeration specifies a unique type.

Two types are the same if their abstract declarators, after expanding any typedef types, and deleting any function parameter identifiers, are the same up to equivalence of type specifier lists. Array sizes and function parameter types are significant. 

**A9. Statements**

Except as described, statements are executed in sequence. Statements are executed for their effect, and do not have values. They fall into the following groups:

```
	Statements:
		labeled-statement
		expression-statement
		compound-statement
		selection-statement
		iteration-statement
		jump-statement
```

**A9.1 Labeled Statement**

Statements may carry labeled prefixes. 

```
labeled-statement:
	identifier : statement
	case constant-expression: statement
	default : statement 
```

A label consiting of an identifier declares the identifier. The only use of an identifier label is as a target of goto. The scope of the identifier is the current function. Because labels have their own name space, they do not interfere with other identifiers and cannot be redeclared.

Case labels and default are used with the switch statement. The constant expression of case must have integral type. 

**A9.2 Expression Statement**

Most statements are expression statements, which have the form 

```
expression-statement:
	expression-opt;
```

Most expression statements are assignment or function calls. All side effects from the expression are completed before the next statement is executed. If the expression is missing, the construction is called a null statement; it is often used to supply an empty body to an iteration statement or to place a label.

A expression represents a single data item--usually a member. The expression may consists if a single entity, such as a constant or variable, or it may consist of some combinations of such entities. 

Examples:

```
a + b
x = y
t = u + v
x <= y
++j
```

An expression causes the computer to carry out some definite action. Expressions Statement consists of expression followed by a semicolon. 

```
a = 6;
c = a + b;
++j;
```

**A9.3 Compound Statement **

So that several statements can be used where one is expected, the compound statement also called a block is provided. The body of a function definition is a compound statement.

```
compound-statement:
    { declaration-listopt statement-listopt }
declaration-list:
    declaration
    declaration-list declaration
statement-list:
    statement
    statement-list statement
```

If an identifier in the declaration-list was in scope outside the block. The outer declaration is suspended within the block, after which it resumes its force. An identifier may be declared only once in the same block. These rules apply to identifiers in the same name space; identifiers in different name spaces are treated as distinct. 

Initialization of automatic objects is performed each time the block is entered at the top, and proceeds in the order of the declarators. If a jump into the block is executed, these initializations are not preformed. Initializations of static objects are performed only once, before the program begin execution. 

example of compound statement

```c
if( i > 0) {
    line[i] = x;
    x++;
    i--;
}
```

**A9.4 Selection Statements**

Selection statements choose one of several flows of control. 

```
selection-statement:
    if (expression) statement
    if (expression) statement else statement
    switch (expression) statement
```

In both forms of the if statement, the expression, which must have arithmetic or pointer type,
is evaluated, including all side effects, and if it compares unequal to 0, the first substatement is
executed. In the second form, the second substatement is executed if the expression is 0. The
else ambiguity is resolved by connecting an else with the last encountered else-less if at
the same block nesting level.

The switch statement causes control to be transferred to one of several statements depending
on the value of an expression, which must have integral type. The substatement controlled by a
switch is typically compound. Any statement within the substatement may be labeled with one
or more case labels (Par.A.9.1). The controlling expression undergoes integral promotion
(Par.A.6.1), and the case constants are converted to the promoted type. No two of these case
constants associated with the same switch may have the same value after conversion. There
may also be at most one default label associated with a switch. Switches may be nested; a
case or default label is associated with the smallest switch that contains it.

When the switch statement is executed, its expression is evaluated, including all side effects,
and compared with each case constant. If one of the case constants is equal to the value of the
expression, control passes to the statement of the matched case label. If no case constant
matches the expression, and if there is a default label, control passes to the labeled statement.
If no case matches, and if there is no default, then none of the substatements of the swtich is
executed  

**Iteration Statements**

Iteration statements specify looping.

```
iteration-statement:
    while (expression) statement
    do statement while (expression);
    for (expressionopt; expressionopt; expressionopt) statement
```

In the while and do statements, the sub statement is executed repeatedly so long as the value of the expression remains unequal to 0; the expression must have arithmetic or pointer type. With while, the test, including all side effects from the expression, occurs before each execution of the statement; with do, the test follows each iteration.

In the for statement, the first expression is evaluated once, and thus specifies initialization for the loop. There is no restriction on its type. The second expression must have arithmetic or pointer type; it is evaluated before each iteration, and if it becomes equal to 0, for the terminated. The third expression is evaluated after each iteration, and thus specifies a re-initialization for the loop. There is no restriction on its type. Side effect from each expression are completed immediately after its evaluation. If the sub statement does not contain continue, a statement. 

```
for (expression1; expression2; expression3) statement

is equivalent to =>

expression1;
while (expression2) {
    statement
    expression3;
}
```

Any of the three expression may be dropped. A missing second expression makes the implied test equivalent to testing a non zero constant. 

**A9.6 Jump Statement **

Jump statements transfer control unconditionally.

```
jump-statement:
goto identifier;
continue;
break;
return expressionopt;
```

In the goto statement, the identifier must be a label (Par.A.9.1) located in the current function.
Control transfers to the labeled statement.
A continue statement may appear only within an iteration statement. It causes control to pass
to the loop-continuation portion of the smallest enclosing such statement. More precisely,
within each of the statements

```
while (...) {		 do { 				for (...) {
... 				 ... 			        ...
contin: ;			 contin: ; 				contin: ;
} 					} while (...); 	    }
```

a continue not contained in a smaller iteration statement is the same as goto contin.
A break statement may appear only in an iteration statement or a switch statement, and
terminates execution of the smallest enclosing such statement; control passes to the statement
following the terminated statement.
A function returns to its caller by the return statement. When return is followed by an
expression, the value is returned to the caller of the function. The expression is converted, as
by assignment, to the type returned by the function in which it appears.
Flowing off the end of a function is equivalent to a return with no expression. In either case,
the returned value is undefined.  

**A10. External Declarations**

The unit of input provided to the C compiler is called a translation unit; it consist of a sequence of external declarations, which are either declarations or function definitions. 

```
translation-unit:
    external-declaration
    translation-unit external-declaration
external-declaration:
    function-definition
    declaration
```

The scope of external declaration persists to end of the translation unit in which they are declared, just as the effect of declaration within blocks persists to the end of the block. The syntax of external declarations is the same as that of all declarations, except that only at this level may the code for functions be given. 

**A10.1 Function Definitions** 

Function definitions have the form:

```
function-definition:
    declaration-specifiersopt declarator declaration-listopt compound-statement
```

The only storage class specifiers allowed among the declaration specifiers are extern or static for the distinction between them. 

A function may return an arithmetic type, a structure, a union, a pointer of void, but not a function or an array. The declarator in a function declaration must specify explicitly that the declared identifier has function type; that is, it must contain one of the forms:

```
direct-declarator ( parameter-type-list )
direct-declarator ( identifier-listopt )
```

Where the direct declarator is an identifier or a parenthesized identifier. In particular, it must not achieve function type by means of typedef. 

In the first form the definition is a new style function, and its parameters, together with their types are declared in its parameter type list; the declaration list following the function declarator must be absent. Unless the parameter type list consist solely of void, showing that the function takes no parameters, each declarator in the parameter type list must contain an identifier. If the parameter type list ends with ", . . ." then the function may be called with more arguments than parameters; the va_arg macro mechanism defined in the standard header <stdarg.h> must be used to refer to the extra arguments.

In both styles of function definition, the parameters are understood to be declared just after the same beginning of the compound statement constituting the functions body, and thus the same identifiers must not be redeclared there (although they may, like other identifiers, be redeclared in inner blocks). If a pointer is declared to have type "array of type", the declaration is adjusted to read "pointer to type", similarly, if a parameter is declared to have type "function returning type" the declaration is adjusted to read "pointer to function returning type". During the call to a function, the arguments are converted as necessary and assigned  to the parameters.

A complete example of the new style: 

```c
int max(int a, int b, int c)
{
int m;
m = (a > b) ? a : b;
return (m > c) ? m : c;
}
```

Here int is a declaration specifier; max(int a, int b, int c) is the function's declarator, and {...} is the block giving the code for the function. the corresponding old style definition would be 

```c
int max(a, b, c)
int a, b, c;
{
/* ... */
}
```

Where now int max(a,b,c) is the declarator, and in a, b, c; is the declaration list for the parameters. 

**A10.2 External Declaration**

External declarations specify the characteristics of objects, functions and other identifiers. The
term ``external'' refers to their location outside functions, and is not directly connected with the
extern keyword; the storage class for an externally-declared object may be left empty, or it
may be specified as extern or static.

Several external declarations for the same identifier may exist within the same translation unit if
they agree in type and linkage, and if there is at most one definition for the identifier.
Two declarations for an object or function are deemed to agree in type under the rule
discussed in Par.A.8.10. In addition, if the declarations differ because one type is an incomplete
structure, union, or enumeration type (Par.A.8.3) and the other is the corresponding completed
type with the same tag, the types are taken to agree. Moreover, if one type is an incomplete
array type (Par.A.8.6.2) and the other is a completed array type, the types, if otherwise
identical, are also taken to agree. Finally, if one type specifies an old-style function, and the
other an otherwise identical new-style function, with parameter declarations, the types are
taken to agree.

If the first external declarator for a function or object includes the static specifier, the
identifier has internal linkage; otherwise it has external linkage. Linkage is discussed in
Par.11.2.

An external declaration for an object is a definition if it has an initializer. An external object
declaration that does not have an initializer, and does not contain the extern specifier, is a
tentative definition. If a definition for an object appears in a translation unit, any tentative
definitions are treated merely as redundant declarations. If no definition for the object appears
in the translation unit, all its tentative definitions become a single definition with initializer 0.

Each object must have exactly one definition. For objects with internal linkage, this rule applies
separately to each translation unit, because internally-linked objects are unique to a translation
unit. For objects with external linkage, it applies to the entire program  

**A.11 Scope and Linkage**

A program need not all be compiled at one time: the source text may be kept in several files containing translation units, and precompiled routines may be loaded from libraries. Communication among the functions of a program may be carried out both through calls and through manipulation of external data. 

Therefore there are two kinds of scope to consider first, the *lexical scope* of an identifier, which is the region of the program text within the identifiers characteristics are understood; and second associated with objects and functions with external linkage, which determines the connections between  identifier in separately compiled translation units. 

**A11.1 Lexical Scope**

Identifiers fall into several name spaces that do not interfere with one another; the same identifier may be used for different purposes, even in the same scope, if the uses are in different name spaces. These classes are; objects functions, typedef names, and enum constants; labels; tags of structures, unions and enumerations; and members of each structure or union individually. 

The lexical scope of an object or function identifier in an external declaration begins at the end of its declarator and persists to the end of the translation unit in which it appears. The scope of a parameter of a function definition begins at the block defining the function, and persists through the function; the scope of an identifier declared at the head of an block begins at the end of its declarator, and persists to the end of the block. The scope of a label is the whole of the function in which it appears. The scope of a structure, union, or enumeration tag, or an enumeration constant, begins at its appearance in a type specifier, and persist to the end of the translation unit (for declarations at the external level) or to the end of the block (for declarations within a function).

If an identifier is explicitly declared at the head of a block, including the block constituting a function, any declaration of the identifier outside the block is suspended until the end of the block. 

Note that this is also called static scoping! In this scoping a variable always refers to its top level environment. 

```c

// A C program to demonstrate static scoping. 
#include<stdio.h> 
int x = 10; 
  
// Called by g() 
int f() 
{ 
   return x; 
} 
  
// g() has its own variable 
// named as x and calls f() 
int g() 
{ 
   int x = 20; 
   return f(); 
} 
  
int main() 
{ 
  printf("%d", g()); 
  printf("\n"); 
  return 0; 
} 

//output is 10

```

**A11.2  Linkage** 

Within a translation unit, all declarations of the same object or function identifier with internal linkage refer to the same thing, and the object or function is unique to that translation unit. All declarations for the same object or function identifier with external linkage refer to the same thing, and the object or function is shared by the entire program. 

The first external declaration for an identifier gives the identifier internal linkage if the static specifier is used, external linkage otherwise. If a declaration for an identifier within a block does not include the extern specifier, then the identifier has no linkage and is unique to the function. If it does include extern, and an external declaration for the identifier is active in the scope surrounding the block, then the identifier has the same linkage as the external declaration, and refers to the same object or function; but if no external declaration is visible, its linkage is external. 

**A12 Preprocessing **

A preprocessor performs macro substitution, conditional compilation, and inclusion of named files. Lines beginning with #, perhaps preceded by white space, communicate with the preprocessor. The syntax of these lines is independent of the rest of the language; they may appear anywhere and have effect that lasts independent of scope until the end of the translation unit. Line boundaries are significant each line is analyzed individually. To the preprocessor, a token is any language token, or character sequence giving a file name as in the #include directive; in addition, any character not otherwise define is taken as a token. However, the effect of white spaces other than space and horizontal tab is undefined within preprocessor lines. 

Note that preprocessing itself takes places in several logically successive phases that may, in a particular implementation, be condensed.

1. First, trigraph sequences as described in Par.A.12.1 are replaced by their equivalents.
   Should the operating system environment require it, newline characters are introduced
   between the lines of the source file.

2. Each occurrence of a backslash character \ followed by a newline is deleted, this
   splicing lines (Par.A.12.2).

3. The program is split into tokens separated by white-space characters; comments are
   replaced by a single space. Then preprocessing directives are obeyed, and macros
   (Pars.A.12.3-A.12.10) are expanded.

4. Escape sequences in character constants and string literals (Pars. A.2.5.2, A.2.6) are
   replaced by their equivalents; then adjacent string literals are concatenated.

5. The result is translated, then linked together with other programs and libraries, by
   collecting the necessary programs and data, and connecting external functions and
   object references to their definitions  

**A12.1 Trigraph sequences**

The character set of C source programs is contained within a seven bit ASSCII, but is a superset of the ISO 646-1983 Invariant Code Set. In order to enable programs to be represented in the reduced set, all occurrences of the following trigraph sequences are replaced by the corresponding single character. This replacement occurs before any other processing.

```
??= # 	??( [ 	??< {
??/ \ 	??) ] 	??> }
??' ^ 	??! | 	??- ~
```

No other such replacement occur.

**A12.2 Line Spacing**

Lines that end with the backslash character \ are folded by deleting the backslash and the following newline character. This occurs before division into tokens.

**A12.3 Macro Definition and Expansion**

A control line of the form 

```
# define identifier token-sequence
```

Causes the preprocessor to replace subsequent instances of the identifier with the given sequence of tokens; leading and trailing white space around the token sequence is discarded. A second #define for the same identifier is erroneous unless the seond token sequence is identical to the first, where all white space separations are taken to be equivalent. 

A line of the form

```
#define identifier (identifier-list) token-sequence
```

where there is no space between the first identifier and the (, is a macro definition with
parameters given by the identifier list. As with the first form, leading and trailing white space
around the token sequence is discarded, and the macro may be redefined only with a definition
in which the number and spelling of parameters, and the token sequence, is identical.
A control line of the form

```
# undef identifier
```

causes the identifier's preprocessor definition to be forgotten. It is not erroneous to apply
\#undef to an unknown identifier.

When a macro has been defined in the second form, subsequent textual instances of the macro
identifier followed by optional white space, and then by (, a sequence of tokens separated by
commas, and a ) constitute a call of the macro. The arguments of the call are the commaseparated token sequences; commas that are quoted or protected by nested parentheses do not
separate arguments. During collection, arguments are not macro-expanded. The number of
arguments in the call must match the number of parameters in the definition. After the
arguments are isolated, leading and trailing white space is removed from them. Then the token
sequence resulting from each argument is substituted for each unquoted occurrence of the
corresponding parameter's identifier in the replacement token sequence of the macro. Unless
the parameter in the replacement sequence is preceded by #, or preceded or followed by ##,
the argument tokens are examined for macro calls, and expanded as necessary, just before
insertion.

Two special operators influence the replacement process. First, if an occurrence of a parameter
in the replacement token sequence is immediately preceded by #, string quotes (") are placed
around the corresponding parameter, and then both the # and the parameter identifier are
replaced by the quoted argument. A \ character is inserted before each " or \ character that
appears surrounding, or inside, a string literal or character constant in the argument.

Second, if the definition token sequence for either kind of macro contains a ## operator, then
just after replacement of the parameters, each ## is deleted, together with any white space on
either side, so as to concatenate the adjacent tokens and form a new token. The effect is
undefined if invalid tokens are produced, or if the result depends on the order of processing of
the ## operators. Also, ## may not appear at the beginning or end of a replacement token
sequence.

In both kinds of macro, the replacement token sequence is repeatedly rescanned for more
defined identifiers. However, once a given identifier has been replaced in a given expansion, it
is not replaced if it turns up again during rescanning; instead it is left unchanged.

Even if the final value of a macro expansion begins with with #, it is not taken to be a
preprocessing directive.
For example, this facility may be used for ``manifest-constants,'' as in

```c
#define TABSIZE 100
int table[TABSIZE];
//The definition
#define ABSDIFF(a, b) ((a)>(b) ? (a)-(b) : (b)-(a))
```

defines a macro to return the absolute value of the difference between its arguments. Unlike a
function to do the same thing, the arguments and returned value may have any arithmetic type
or even be pointers. Also, the arguments, which might have side effects, are evaluated twice,
once for the test and once to produce the value.

Given the definition

```
#define tempfile(dir) #dir "%s"
the macro call tempfile(/usr/tmp) yields
"/usr/tmp" "%s"
```

which will subsequently be catenated into a single string. After

```
#define cat(x, y) x ## y
```

the call cat(var, 123) yields var123. However, the call cat(cat(1,2),3) is undefined: the
presence of ## prevents the arguments of the outer call from being expanded. Thus it produces
the token string

cat ( 1 , 2 )3
and )3 (the catenation of the last token of the first argument with the first token of the second)
is not a legal token. If a second level of macro definition is introduced,
\#define xcat(x, y) cat(x,y)
things work more smoothly; xcat(xcat(1, 2), 3) does produce 123, because the expansion
of xcat itself does not involve the ## operator.
Likewise, ABSDIFF(ABSDIFF(a,b),c) produces the expected, fully-expanded result  

**A12.4 File inclusion **

A control line of the form 

```
# include <filename>
```

causes the replacement of that line by the entire contents of the file filename. The characters in the name filename must not include > or newline, and the effect is undefined if it contains any ", ', \, or /*. The named file is searched for in a sequence of implementation-dependent places. 

Similarly, a control line of the form

```
# include "filename"
```

searches first in association with  the original source file (a deliberately implementation dependent phrase, ) and if that search fails, then as if in the first form. The effect of using ', \, or /* in the file name remains undefined, but > is permitted.

Finally a directive of the form 

```
# include tonken-sequence
```

not matching one of the previous forms is interpreted by expanding the token sequence as for normal text; one of the forms with <..> or ".." must result, and it is then treated as previously described. 

#include files may be nested. 

**A12.5 Conditional complication**

Parts of a program may be compiled conditionally, according to the following syntax.

```
preprocessor-conditional:
    if-line text elif-parts else-partopt #endif
if-line:
    # if constant-expression
    # ifdef identifier
    # ifndef identifier
elif-parts:
    elif-line text
    elif-partsopt
elif-line:
    # elif constant-expression
else-part:
    else-line text
else-line:
    #else
```

Each of the directives (if-line, elif-line, else-line, and #endif) appears alone on a line. The
constant expressions in #if and subsequent #elif lines are evaluated in order until an
expression with a non-zero value is found; text following a line with a zero value is discarded.
The text following the successful directive line is treated normally. ``Text'' here refers to any
material, including preprocessor lines, that is not part of the conditional structure; it may be
empty. Once a successful #if or #elif line has been found and its text processed, succeeding
\#elif and #else lines, together with their text, are discarded. If all the expressions are zero,
and there is an #else, the text following the #else is treated normally. Text controlled by
inactive arms of the conditional is ignored except for checking the nesting of conditionals  

The constant expression in #if and #elif is subject to ordinary macro replacement. Moreover, any expression of the form

```
defined identifier 
//or
defined (identifier)
```

are replaces, before scanning for macros, by 1L if the identifier is defined in the preprocessor, and by 0L if not. Any identifier remaining after macro expansion are replaced by )l. Finally, each integer constant is considered to be suffixed with L, so that all arithmetic is taken to be long or unsigned long. 

The resulting constant expression is restricted; it must be integral, and may not contain sizeof, a cast, or an enumeration constant.

```
The control lines
    #ifdef identifier
    #ifndef identifier
are equivalent to
    # if defined identifier
    # if ! defined identifier
respectively
```

**A.12.6 Line Control**

For the benefit of other preprocessor that generate C program, a line in one of the forms

```
# line constant "filename"
# line constant
```

causes the preprocessor to believe, for purposes or error diagnostic, that the line number of the next source line is given by the decimal integer constant and the current input file is named by the identifier. If the quoted filename is absent, the remembered name does not change. Macros in the line are expanded before it is interpreted. 

**A.12.7 Error Generation**

A preprocessor line of the form

```
# error token-sequence-opt
```

causes the preprocessor to write a diagnostic message that includes the token sequence.

**A12.8 Pragmas**

A control line of the form 

```
# pragma token-sequence-opt
```

causes the preprocessor to preform an implementation-dependent action. An unrecognized pragma is ignored. 

**A12.9 Null directive**

A control line of the form

```
#
```

has no effect

**A12.10 Predefined Names**

Several identifier are predefined, and expand to produce special information. They, and also the preprocessor expansion operator defined, may not be undefined or redefined. 

```
__LINE__ A decimal constant containing the current source line number.
__FILE__ A string literal containing the name of the file being compiled.
__DATE__ A string literal containing the date of compilation, in the form "Mmmm dd yyyy"
__TIME__ A string literal containing the time of compilation, in the form "hh:mm:ss"
__STDC__ The constant 1. It is intended that this identifier be defined to be 1 only in standardconforming implementations
```

**A13 Grammar **

Below is a recapitulation of the grammar that was given throughout the earlier part of this
appendix. It has exactly the same content, but is in different order.
The grammar has undefined terminal symbols integer-constant, character-constant, floatingconstant, identifier, string, and enumeration-constant; the typewriter style words and
symbols are terminals given literally. This grammar can be transformed mechanically into input
acceptable for an automatic parser-generator. Besides adding whatever syntactic marking is
used to indicate alternatives in productions, it is necessary to expand the ``one of''
constructions, and (depending on the rules of the parser-generator) to duplicate each
production with an opt symbol, once with the symbol and once without. With one further
change, namely deleting the production typedef-name: identifier and making typedef-name a
terminal symbol, this grammar is acceptable to the YACC parser-generator. It has only one
conflict, generated by the if-else ambiguity.  

