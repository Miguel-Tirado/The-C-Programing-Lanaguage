# Chapter 2: Types, Operators, and Expressions

Variables and constants are the basic data objects manipulated in a program. Declarations list variables to be used, and state what type they have and perhaps what their initial values. The type of an object determines the set of values it can have and what operations can be preformed on it. 

There are now `signed` and `unsigned` forms of all integer types, and notations for unsigned constants and hexadecimal character constants. Floating-point operations may be done in single precision; there is also a `long double` type for extended precision. String constants may be concatenated at compile time. Enumerations have become part of the language, formalizing a feature of long standing. Objects may be declared constant, which prevents them from being changed. 

**2.1 Variable Names** 

Names are made up of letters and digits; the first character must be a letter. Useful tip is to use the "_" since it counts as a letter for improving readability of long variable names. However don't begin variable names with underscore  because library routines often use names starting with underscore. C is case sensitive so "A" is not the same as "a"; Therefore traditional C practice is to use lower case for variable names, and upper case for symbolic constants. 

At least the first 31 characters of an internal name are significant. For function names external variables, the number may be less than 31, because external variables names may be used by assemblers and loaders over which language has no control.

Its wise to choose variable names that are related to the purpose of the variable, and that are unlikely to get mixed up typographically. We tend to use short names for local variables, especially loop indices, and longer names for external variables.

**2.2 Data Types and sizes**

The few basic data types in C are:  

- char:     a single byte (8bits), capable of holding one character in the local character set.
- Int:        an integer, typically reflecting the natural size of integers on the host machine. 
               typically 32 bits or 4 bytes.
- float:     single-precision floating point, typically 4 bytes or 32 bits
- double: double precision floating point, typically 8 bytes long or 64 buts

For more details a table of integer types will be provided down below:

| Type           | Storage size | Value range                                          |
| -------------- | ------------ | ---------------------------------------------------- |
| char           | 1 byte       | -128 to 127 or 0 to 255                              |
| unsigned char  | 1 byte       | 0 to 255                                             |
| signed char    | 1 byte       | -128 to 127                                          |
| int            | 2 or 4 bytes | -32,768 to 32,767 or -2,147,483,648 to 2,147,483,647 |
| unsigned int   | 2 or 4 bytes | 0 to 65,535 or 0 to 4,294,967,295                    |
| short          | 2 bytes      | -32,768 to 32,767                                    |
| unsigned short | 2 bytes      | 0 to 65,535                                          |
| long           | 8 bytes      | -9223372036854775808 to 9223372036854775807          |
| unsigned long  | 8 bytes      | 0 to 18446744073709551615                            |

For more detail on floating types a table is provide below:

| Type        | Storage size | Value range            | Precision         |
| ----------- | ------------ | ---------------------- | ----------------- |
| float       | 4 byte       | 1.2E-38 to 3.4E+38     | 6 decimal places  |
| double      | 8 bytes      | 2.3E-308 to 1.7E+308   | 15 decimal places |
| long double | 10 bytes     | 3.4E-4932 to 1.1E+4932 | 19 decimal places |

In addition, there are a number of qulaifiers that can be applied to these basic type. short and long apply to integers:

```c
short int sh;
long int counter;
```

The intent of short and long should provide different lengths of integers where practical. short is often 16 bits, long 32 bits, and int is either 16 or 32 bits. Each compiler is free to choose appropriate sizes for its own hardware, subject only to the restriction that short is no longer than int, which is no longer than long.

The qualifier signed and unsigned may be applied to char or any integer. unsigned char number are always positive or zero and obey the laws of arithmetic modulo 2^n, where n is the number of bits in a type. For example if chars is 8 bits, unsigned char variables have values between 0 and 255, while signed chars have values between -128 and 127.

The types long double specifies extended precision floating point. As with integers, the sizes of floating point objects are implementation defined; float, double and long double could represent one, two or three distinct sizes, along with other properties of the machine and compiler. 

**2.3 Constants**

An integer constant like 1234 is an int. A long constant is written with a terminal 1 (ell) or L as in 123456789L; an integer too big to fit into an int will also be taken as long.  Unsigned constants are written with a terminal u or U, and the suffix ul or UL indicates unsigned long. 

The value of an integer can be specified in octal or hexadecimal instead of decimal. A leading 0 (zero) on an integer constant  means octal; a leading 0x or 0X means hexadecimal. Octal and hexadecimal constants may also be followed by L to make them long and U to make them unsigned: 0XFUL is an unsigned long constants with value 15 decimal. 

A *character constant* is an integer, written as one character within single quotes quotes such as 'x'. The value of a character constant is the numeric value of the character in the machine character set. For example, in the ASCII character set the character constant '0' has the value of 48, which is unrelated to the numeric value 0. If we write '0' instead of a numeric value of 48 that depends on character set, the program is independent of the particular value and easier to read. 

Certain characters can be represented in character and string constant by escape sequences like \n (new line); these sequences look like two characters, but represent only one.

An arbitrary byte sized bit pattern can be specified `\ooo` where ooo is one to three octal digits (0...7). Or by `'\xhh'` where hh is one or more hexadecimal digits (0...9, a...f,A...F). so  me we might write:

```c
#define VTAB '\013'
#define BELL '\007'
```

or in hexadecimal 

```c
#define VTAB '\xb'
#define BELL '\x7'
```

Complete set of escape sequences 

- \a alert (bell) character                                \\\   backslash
- \b backspace                                               \?  question mark
- \f formfeed                                                   \\' single quote 
- \n newline                                                    \\" double quote 
- \r carriage return                                          \ooo octal number
- \t horizontal tab                                            \xhh hexadecimal 
- \v vertical tab

The character constant '\0' represents the character with value zero, the null character. A *constant expression* is an expression that involves only constants. such expressions may be evaluated during compilation rather than run time, and accordingly may be used in any place that a constant can occur:

```c
#define MAXLINE 1000
char line[MAXLINE+1];
//or  
#define LEAP 1
int days[31+28+LEAP+31+20];
```

A *string constant* or *string literal*, is a sequence of zero or more characters surrounded by double quotes as in

```c
"i am a string"
//or 
"" /* the empty string */
```

The standard library function strlen(s) returns the length of its character string s, excluding the terminal '\0'. Here is our version of it:

```c
/* strlen: return length of s */
int strlen(char s[]) {
    int i;
    i = 0;
    while( s[i] != '\0') {
        ++i;
    }
    return i;
}
```

strlen and other string functions are declared in the standard header <string.h>. Be careful to distinguish between a character constant and a string that contains a single character: 'x' is not the same as "x". 

*Enumeration* is a list of constant integer values; as in.

`enum boolean { NO, YES};`

where NO has the value of 0 while YES has the value of 1. Another example of enumerations is :

```c
enum escapes {BELL = '\a', BACKSPACE = '\b', TAB = '\t', NEWLINE = '\n', VTAB = '\v', RETURN = '\r'};

enum months {JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, NOV, DEC} 
// FEB = 2, MAR = 3 ....
```

Enumerations allow us associate constant values with names, offer alternative to #define with the advantage that the values can be generated for you. Although variables of enum type may be declared, compilers need not check that what you store in such a variable is a valid value for the numeration. Nevertheless, enumeration variables offer the chance of checking and so are often better than #defines. 

Summary of Constants

constant in c are variables or values that cannot be modified once they are defined in the program. There can be any types of constants such as integer, float, octal, hexadecimal and character constants.  Constant can be defined in two ways 1st using #define preprocessor directive and the 2nd using a *const* keyword. 

**2.4 Declarations**

All variables must be declared before use, although certain declarations can be made implicitly by context.  A declaration specifies a type, and contains a list of one or more variables of that type as in:

```c
int lower, upper, step;
char c, line[100];
```

Variables can be distributed among declarations in any fashion; the lists above could equally well be written as:

```c
int lower;
int upper;
int step;
char c;
char line[1000];
```

A variable may also be initialized in its declaration. if the name is followed by an equals sign and an expression, the expression serves as an initializer as in:

```c
char esc = '\\';
int i = 0;
int limit = MAXLINE - 1;
float eps = 1.0e-5;
```

Note that initializing is setting a variable with a value. External and static variables are initialized to zero by default. Automatic variables for which there is no explicit initializer have undefined values (garbage values). 

The qualifier *const* can be applied to the declaration of any variables to, specify that its value will not be changed. Note for an array the *const* qualifier says that the elements will not be altered.

```c
const double e = 2.71828182845905;
const char msg[] = "warning:";
```

The constant declarations can also be used with array arguments, to indicate that the function does not change that array. 

`const strlen(const char[]);`

**2.5 Arithmetic Operations **

The binary arithmetic operations are +,-,*,/ and the modules operator %. Integer division truncates any fractional part. The expression `x % y` produces the remainder when x is divided by y, and thus is zero  when y divides x exactly. 

For example, a year is a leap year if it is devisable by 4 but not by 100, except that years divisible by 400  are leap years. Therefore:

```c
if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
	printf("%d is a leap year\n",year);
} else {
	printf("%d is not a leap year \n", year)
}
```

Note that the % (modulus) operator cannot be applied to float or double. The direction of truncation for / and the sign of the result for % are machine dependent for negative operands as is the action taken on overflow or underflow.

The binary + and - operators have the same precedence, which is lower than the precedence of *,/ and % which is in turn lower than unary + and - arithmetic operators associate left from right. 

 Unary Operators 

Basically, for a operation to occur, you need two operand/variables and a operator (+,-,$,/) But, unary operators work on a single operand. The 3 most common types of unary operators are:

- Increment and Decrement operators: `++i` and `--i`
- single plus or minus: `+` and `-`
- Not operator: `!`

**2.6 Relational and logical Operators**

The following table below represent all the relational and quality operators:

| Operator | Description              | Example  | Result |
| -------- | ------------------------ | -------- | ------ |
| `>`      | greater than             | 1 > 2    | 0      |
| `>=`     | greater than or equal to | 3 >= 2   | 1      |
| `<`      | smaller than             | 10 < 5   | 0      |
| `<=`     | smaller than or equal to | 6 <= 7   | 1      |
| `==`     | equal to                 | 98 == 98 | 1      |
| `!=`     | not equal to             | 10 != 9  | 1      |

Note that the relational operators `>   >=   <    <=`  all have the same precedence. However just below them are the equality operators `==   !=` 

relational operators have lower precedence than arithmetic operators so an expression like i < lim -1 is taken as i < (lim - 1).

The logical operators include the `&&    ||` which expressions connected by && or || are evaluated left to right, and evaluation stops as soon as the truth or falsehood of the result is known. 

Example 

```c
for(i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i) {
    s[i] = c;
}
```

The Unary negation operator ! converts a non zero operand into 0, and a zero operand into 1. A common use of !. A common use of ! is in construction like 

`if (!valid)`

rather than 

`if (valid == 0)`

Note both of these statements are the same 

**2.7 Type Conversions**

When an operator has operands of different types they are converted to a common type according to small number of rules. The general rule for automatic conversions is those that convert narrower operands into a wider wider one without losing information.

We cant use a float as a subscript.

expressions that might loose information like assigning a longer integer type to a shorter, or a floating point type to an integer, may draw a warning, but they are not illegal. 

Note: subscript is an integer type constant or variable name whose value ranges from 0 to size where size is the total number of elements in the array.

```c
char country[] = "india";

int stud[] = {1,2,3,4,5};
```

A `char` is just a small integer, so chars may be freely used in athematic expressions. An example of this is the function `atoi` which converts a string of digits into a numeric equivalent.

```c
/* atoi: convert s to integer */
int atoi(char s[]) {
    int i,n;
    
    n = 0;
    for(i = 0; s[i] >= '0' && s[i] <= '9';++i) {
        n = 10 * n + (s[i] - '0');
    }
    return n;

}
```

note:

`s[i] - '0'`

gives the numeric value of the character stored in s[i] , because the values of '0', '1' etc .

An example of char to int conversion is the function lower, which maps a single character to lower case for the ASCII character set. 

```c
/* lower: convert c to lower case: ASCII only */
int lower(int c) {
    if(c >= 'A' && c <= 'Z') {
        return c + 'a' - 'A';
    } else {
        return c;
    }
}
```

Note that the standard header `<ctype.h>` described in appendix B, defines a family of functions that provide tests and conversions that are independent of character set. For example we can replace this expression `c >= '0' && c <= 9` with `isdigit(c)` from the ctype library.

Question: when a char is converted to an int, can it ever produce a negative integer? The answer varies from machine to machine, reflecting difference in architecture. 

The definition of C guaranties that any character in the machine standard printing character set will never be negative; so these characters will always be positive quantities in expression. But arbitrary bit patterns stored in character variables may appear to be negative on some machines, yet positive on others. <u>For portability, specify signed or unsigned if noncharacter data is to be stored in char variables.</u>  

Implicit arithmetic conversions work much as expected. In general if an operator like + or * that takes two operands (a binary operator) has operands of different types, the "lower" type is promoted to the higher type before the operation proceeds. The result is of the higher type. `c = int a + float b` therefore c will have to be a float value to store the result. 

If there are no unsigned operands, the following informal set of rules will suffice:

1. if either operand is long double, convert the other to long double.
2. Otherwise, if either operand is double, convert the other to double.
3. Otherwise, if either operand is float, convert the other to float.
4. Otherwise, convert char and short to int.
5. Then, if either operand is long, convert the other to long.

Note that floats in a expression are not automatically converted to double; the main reason for using float is to save storage in large arrays, or, less often, to save time on machines where double precision arithmetic is particularly expensive. 

conversion rules are more complicated when unsigned operands are involved. The problem is that comparisons between signed and unsigned values are machine dependent, because they depend on the sizes of the various integer types. 

Conversions take place across assignments; the value of the right is converted to the type of the left, which is the type of the result. A character is converted to an integer, either by sign extension or not, as described above.

Since an argument of a function call is an expression, type conversions also take place when arguments are passed to functions. In the absence of a function prototype, char and short become int, and float becomes double. 

Finally, explicit type conversions can be forced ("coerced") in any expression, with a unary operator called a cast. In the construction

```pseudocode
(type-name) expression 
```

The expression is converted to the name type by the conversion rules above. The precise meaning of is as if the expression were assigned to a variable of the specified type, which is then  used in place of the whole construction. For instance, the library routine `sqrt` expects a double argument and will produce nonsense if inadvertently handed something else. so id n is a integer then: `sqrt((double) n)` to convert the value of n to double before passing it to sqrt. Note that the cast produces the value of n in the proper type; n itself is not altered. The cast operator has the same high precedence as other unary operators. 

If arguments are declared by a function prototype, as they normally should be, the declaration causes automatic coercion of any arguments when the function is called. thus given a function prototype for sqrt:

```c
double sqrt(double n);
//the call 
root2 = sqrt(2);
```

**2.8 Increment and Decrement Operators**

The increment operator ++ adds 1 to its operand, while the decrements operator -- subtracts 1. an example of this is:

```c
if(c == '\n') {
    ++nl;
}
```

One unique ability that the increment and decrement have is that they can be used as prefix operators: ++i, --i or postfix operators: i++, i--. their goals are the same to increment i. But the expression for ++i increments before its value is used, while i++ increments i after its value has been used. Here is an example of the use of postfix and prefix:

```c
//if n = 5, then 
x = n++; 
//sets the value of x to be 5, while
x = ++n;
//sets the value of x to be 6
```

Note: the increment and decrement operators can only be applied to variables; an expressions like (i + j)++ is invalid. another example of the use of postfix and prefix is:

```c
/* squeeze: delete all c from s */
void squeeze(char s[], int c) {
    int i, j;
    for(i = j = 0; s[i] != '\0'; i++) {
        if(s[i] != c) {
            s[j++] = s[i];
        }
    }
    s[j] = '\0';
}
```

Each time a non-c occurs, it is copied into the current j position and only then is j incremented to be ready for the next character. This is exactly the same as:

```c
if(s[i] != c) {
    s[j] = s[i];
    j++;
}
```

As a third example, consider the standard function strcat(s,t), which concatenates the string t to the end of the string s.

```c
/* strcat: concatenates t to the end of s; s must be big enough */
void strcat(char s[], char t[]) {
    int i, j;
    
    i = j = 0;
    while(s[i] != '\0') { //find end of s
        i++;
    }
    while((s[i++] = t[j++]) != '\0')
        ;
}
```

**2.9 Bitwise Operators**

C provides six operators  for bit manipulation; these may only be applied to integral operands, that is, char, short, int, and long, whether signed or unsigned.

| Operand | Definition               |
| ------- | ------------------------ |
| &       | bitwise AND              |
| \|      | bitwise OR               |
| ^       | bitwise exclusive OR     |
| <<      | left shift               |
| >>      | right shift              |
| ~       | ones compliment  (unary) |

Masking is the act of applying a mask to a value. This is accomplished by doing:

- Bitwise ANDing '&' in order to extract a subset of the bits in the value
- Bitwise ORing in order to set a subset of the bits in the value
- Bitwise XORing in order to toggle a subset of the bits in the value 

The shift operators << and >> perform left and right shifts of their left operand by the number of bit positions given by the right operand, which must be positive. Thus x << 2 shifts the value of x left by 2 position, filling vacated bits with zero; this is equivalent to multiplication by 4.  

Right shifting an unsigned quantity always fills vacated bits with zero. Right shifting a signed quantity will fill with sign bits (arithmetic shift) on some machines and with 0-bits (logical shift) on others.

The unary operator ~ yields the ones compliment of an integer; that is it converts each 1 bit into a 0 bit and vice versa. 

**2.10 Assignment Operators and Expressions **

Expressions are in which the variable on the left hand side is repeated immediately on the right, can be written in the compressed form:

```c
//regular expression
i = i + 2;
//Alternate expression
i += 2;
```

 The operator `+=` is called an *assignment operator*. Most binary operators (operators like + that have a left and right operand) have a corresponding assignment operator op =, where op is one of +   -  *   /    %   <<   >>   &    ^    |

Case: if expr1 and expr2 are expressions, then 

```pseudocode
expr1 op= expr2
// is equivilant to 
expr1 = (expr1)op(expr2)
a += 3;
a = a + 3;
// except that expr1 is computed only once. Notice the paranthesis around expr2:
x *= y + 1; //means
x = x * (y+1) 
//rather than 
x = x * y + 1
```

An example, the function bitcount counts the number of 1 bits in its integer argument.

```c
// bitcount: count 1 bits in x
int bitcount(unsigned x) {
    int b;
    
    for(b = 0; x != 0;x >> 1) {
        if(x & 01){
            b++;
        }
    }
    return b;
}
```

Declaring the argument x to be unsigned ensures that when it is right shifted, vacated bits will be filled with zeros, not sign bits, regardless of the machine the program runs on. Assignment operators have the advantage that they correspond better to the way people think. We say "add 2 to i" or "increment i by 2". Thus the expression i += 2 is preferable to i = i + 2. 

 The assignment operator makes the code easier to understand since the reader doesn't have to check painstakingly that two long expressions are indeed the same or to wonder why there not. 

```c
yyval[yypv[p3+p2] + yypv[p1+p2]] += 2;
```

In all such expressions, the type of an assignment expression is the type of its left operand and the value is the value after the assignment. 

**2.11 Conditional Expressions**

```c
// The statements
if(a > b) {
    z = a;
} else {
    z = b;
}
```

The conditional expression, written with the ternary operator "?:", provides an alternative way to write this and similar constructions. In the expression

`expr1 ? expr2 : expr3`

the expression expr1 is evaluated first. if it is non zero(true) then expr2 is evaluated, and that is the value of the conditional expression. Otherwise expr3 is evaluated, and that is the value. only one of expr2 and expr3 is evaluated. Therefore to set Z to the maximum of a and b:

```c
z = (a > b) ? a : b;
```

 Note that the conditional expressions is indeed an expression, and it can be used wherever any other expression can be. If expr2 and expr3 are of different types, the type of the result is determined by the conversion rules discussed earlier. 

```c
(n > 0) ? f : n;
```

For example this loop prints n elements of an array, 10 per line, with each column seperated by one blank, and with each line (including the last) terminated by a newline.

```c
for(i = 0; i < n; i++) {
    printf("%6d%c",a[i], (i%10 == 9 || i == n-1) ? '\n' : ' ');
}
```

**2.12 Precedence and Order of Evaluation**

Table summarizes the rules for precedence and associativity of all operators, including those that we have not yet discussed. Operators on the same line have the same precedence; rows are in order of decreasing precedence, so for example, *,/, and % all have the same precedence , which is higher than that of binary + and -. The "Operator" () refers to function calls. The operators -> and . are used to access members of structures.

Note that the precedence of the bitwise operators &, ^, and | falls below == !=. This implies that bit testing expressions like 

```c
if((x & MASK) == 0) ...
```

Precedence Table:

![](D:\Pictures\C_Precedence.png)

Note: Unary +,-, and * have higher precedence than the binary forms. 

Similarly , the order in which function arguments are evaluated is not specified so the statement.

```c
printf("%d %d\n", ++n, power(2,n));  //Wrong
```

this can produce different results with different compilers, depending on whether n is incremented before power is called. The solution of course is to write

```c
++n;
printf("%d %d\n", n, power(2,n));  //right 
```

Function calls, nested assignment statements, and increment and decrement operators cause "side effects" --some variable is changed as a by product of the evaluation of an expression. in any expression involving side effects, there can be subtle dependencies on the order in which variables taking part in the expression are updated. 

The standard intentionally leaves most such within an expression is left to the discretion of the compiler, since the best order depends strongly on machine architecture. 

The moral is that writing code that depends on order of evaluation is a bad programing practice in any language. 