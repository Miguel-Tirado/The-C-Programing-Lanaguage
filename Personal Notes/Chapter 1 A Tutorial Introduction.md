# Chapter 1: A Tutorial Introduction 

Basic Structure of a C program:

There are several ways to set up basic structure in C. The first one being the following:

```c
#include <stdio.h>

int main() {
    printf("hello world\n");
    return 0;
}
```

Notice that are main function was declared as a `int` and that we are returning 0. We return 0 to indicate an exit status for the operating system. The exit status is basically the number which tells whether a process exited correctly, or errors were encountered. Generally an exit status of 0 tells us that the process exited without any error, each process requires an exit status.

The second way of declaring a function in C is as follows:

```c
#include <stdio.h>

int main(void) {
    printf("hello world\n");
}
```

Notice here that we are not returning anything inside the main function because we are passing the void keyword inside main which indicates that the main function would return nothing.

`'\n'` indicates a newline character

`'\t'` indicate a tab character 

`'\0'` Indicate end of character string 

`'\b'` Indicates backspace character 

`//` Indicate a comment 

`/*  */` Indicate comment as well 

In C all variables must be declared before they are used, usually at the beginning of the function before and executable statements. 

1.2 Variables and Arithmetic Expressions 

```c
#include <stdio.h> 

int main() {
    int fahr,celsius;
    int lower,upper,step;
    
    lower = 0;
    upper = 300;
    step = 20;
    
    fahr = lower;
    while (fahr <= upper) {
        celsius = 5 * (fahr-32) /9;
        printf("%d\t%d\n",fahr,celsius);
        fahr = fahr + step;
    }
}
```

This program here using variables is used to calculate the temperature in Celsius and Fahrenheit staring from 0 and ending at 200 while incrementing 20 degree each step.

`"%d",fahr` Indicates a integer value to be printed by passing the values into the print statement 

char => character - is a single byte(8bits)

short => short integer 

long => long integer 

double => double precision floating point 

printf specifiers 

`"%d"` print as a decimal integer 

`"%6d"` print as decimal integer, at least 6 characters wide 

`"%f"` print as floating point 

`"%.2"` print as floating point, 2 characters after decimal point 

`"%6.2"` print as floating point, at least 6 wide and 2 after decimal point 

Format Specifiers for print statements:

| Format Specifier |                  Description                   |              Supported Data types              |
| :--------------: | :--------------------------------------------: | :--------------------------------------------: |
|        %c        |                   Character                    |              char, unsigned char               |
|        %d        |                 signed integer                 |        short, unsigned short, int, long        |
|     %e or %E     |      scientific notation of float values       |                 float, double                  |
|        %f        |                 floating point                 |                     float                      |
|     %g or %G     |              similar as %e or %E               |                 float, double                  |
|       %hi        |             signed integer(short)              |                     short                      |
|       %hu        |            unsigned integer(short)             |                 unsigned short                 |
|        %i        |                 signed Integer                 |        short, unsigned short, int, long        |
| %l or %ld or %li |                 signed integer                 |                      long                      |
|       %lf        |                 floating point                 |                     double                     |
|       %Lf        |                 floating point                 |                  long double                   |
|       %lu        |                unsigned integer                |          unsigned int, unsigned long           |
|    %lli, %lld    |                 signed integer                 |               unsigned long long               |
|        %o        |         octal representation of intger         | short, unsigned short, int, unsigned int, long |
|        %p        |        Address of pointer to void coid*        |                     void *                     |
|        %s        |                     string                     |                     char *                     |
|        %u        |                unsigned integer                |          unsigned int, unsigned long           |
|     %x or %X     | Hexadecimal representation of Unsigned Integer | short, unsigned short, int, unsigned int, long |
|        %n        |                 print nothing                  |                                                |
|        %%        |               prints % character               |                                                |

1.3 For Statement 

```c
#include <stdio.h>

/* print Fahrenheit-Celsius table */
int main () {
    int fahr;
    
    for(fahr = 0; fahr <= 300; fahr = fahr + 20) {
        printf("%3d %6.1f\n",fahr,(5.0/9.0)*(fahr-32));
        return 0;
    }
}
```

Note this example of a for loop produces the same output as the variable example. In this case `fahr` is initialized and set to 0 while the condition is to exit the loop when `fahr` is greater than 300, while incrementing `fahr` by 20 each iteration.

There are several other ways to declare a for loop but they all follow the following general format.

```pseudocode
for(init; condition; increment/decrement) {
	statements;
}
```

There are also other forms of for loops for instance:

```c
int i;
for(i = 2; i <= 12; ++i) 
    ;
```

This version of a for loop sole purpose is just to iterate to test the condition until it may be false. Note that these types of for loops tend to have more complex conditional statements inside. 

1.4 Symbolic Constants 

The `#define` directives allows the definition of macros within your source code. These macro definitions allow constant values to be declared for use throughout your code. Macro definitions are not variables and cannot be changed by your program code like variables. You generally use this syntax when creating constants that represent numbers, string or expressions. 

`#define CNAME value`

`#define CNAME (expression)`

A #define line defines a symbolic name or symbolic constant to be particular string of characters: `#define name replacement text` 

Thereafter, any occurrence of name (not in quotes and not part of another name) will be replaced by the corresponding replacement text. The name has the same form as a variable name: a sequence of letters and digits that begins with a letter. The replacement text can be any sequence of characters;it is not limited to numbers. 

```c
#include <stdio.h>

#define LOWERR 0  /* lower limit of table */
#define UPPER 300 /* upper limit */
#define STEP 20   /* step aside */

/* print Fahrenheit-Celsius table */
int main(void) {
    int fahr;
    
    for(fahr = LOWER;fahr <= UPPER;fahr = fahr + STEP) {
        printf("%3d %6.1f\n",fahr,(5.0/9.0)*(fahr-32));
    }
}
```

Notice no semicolon at the end of #define line 

1.5 Character Input and Output 

The standard library provides several functions for reading and writing one character at a time, of which getchar and putchar are the simplest. Each time is called, getchar reads the next input character from a text stream and returns that as its value. That is after:

`c = getchar()`

The variable c contains the next character of input. The characters normally come from the keyboard.

`putchar(c)` 

The function putchar prints a character each time it is called. prints the contents if the integer variable c as a character, usually on the screen. Calls to putchar and printf may be interleaved; the output will appear in the order in which the calls are made.

1.5.1 File Copying 

With the use of getchar and putchar we can write some useful programs without knowing alot about the input or output. The pseudocode is as follow below:

```pseudocode
read a character 
while(character is not end-of-file indicator)
	output the character just read
	read a character 
```

The simplest form of getting user input is as follows:

```c
#include <stdio.h>

/* copy input to output */
int main (void) {
    int c;
    while((c = getchar()) != EOF) {
        putchar(c);
    }
}
```

Notice that c is declared as type `int` instead of `char` this is because the getchar function returns a distinctive value when there is no more input, a value that cannot be confused with any real character. This value is called the `EOF` for (end of file). we must have c to be a type big enough to hold any value that getchar returns. Therefore we cant use `char` type because c must be big enough to hold EOF in addition to any possible char. recall that the size of a `char` is a byte which is only 8 bits while the size of a `int` is 4 bytes or 32 bits.

Notice that the parenthesis around the assignment within the condition `(c = getchar())` are necessary. the precedence of `!=` is higher than `=`, which means that in the absence of parenthesis the relational test `!=` would be done before the assignment `=`. so the statement. 

`c = getchar() != EOF`

is the same as 

`c =(getchar() != EOF)`

we do no want this to happen since this would set the value of c to 0 or 1. 

Relational operators in C

Relation operators are used to compare values of two expressions. Relational operators are binary operators because they require two operands to operate. if the relation is true then the result of the relational expression is 1, if the relation is false then the result of the relational expression is 0.

| Operator | Description              | Example  | Result |
| -------- | ------------------------ | -------- | ------ |
| `>`      | greater than             | 1 > 2    | 0      |
| `>=`     | greater than or equal to | 3 >= 2   | 1      |
| `<`      | smaller than             | 10 < 5   | 0      |
| `<=`     | smaller than or equal to | 6 <= 7   | 1      |
| `==`     | equal to                 | 98 == 98 | 1      |
| `!=`     | not equal to             | 10 != 9  | 1      |

1.5.2 Character Counting

The next program will count characters. 

```c
#include <stdio.h>

/* count characters in input; 1st version */
int main(void) {
    long nc;
    
    nc = 0;
    while(getchar() != EOF) {
        ++nc;
    }
    printf("%1d\n",nc);
}
```

The following should count the amount of character the user types by incrementing the `long` variable `nc` every time the user types. Notice the use of `++nc` this is used to increment by one, an alternate version is `--nc` which is used to decrement by one. 

1.5.3 Line counting 

The next program counts input lines. where the standard library ensures that an input text stream appears as a sequence of lines, each terminated by a newline. 

```c
#include <stdio.h>

/* count lines in input */
int main (void) {
    int c,nl;
    nl = 0;
    while ((c = getchar()) != EOF) {
        if(c == '\n') {
            ++nl;
        }
    }
    printf("%d\n", nl);
}
```

every time the user presses the enter key the `nl` variable will be incremented by one. therefore we are counting the number of input lines used. Notice the difference between `==` which means 'equals to' while `=` means assigning a value to a variable.

A character written between single quotes represents an integer value equal to the numerical value of the character in the machine character set. this is called a character constant; although it is just another way to write a small integer. For instance, 'A' is a character constant; in the ASCII character set its value to 65, the internal representation of the character A.

1.5.4 Word Counting 

The fourth program is used to count the number of words the user types. 

```c
#include <stdio.h>
//Defining my constants or macros 
#define IN 1  /* insdie a word */
#define OUT 0 /* outside a word */

int main() {
	int c,nl,nw,nc, state;
	//nc = new characters, nl = new line, nw = new word 
	nl = nw = nc =0;
    state = OUT;
	while((c = getchar()) != EOF) {
		++nc;
		if(c == '\n') {
			++nl;
		}
		if (c == ' ' || c == '\t' || c == '\n') {
			state = OUT;
		} else if (state == OUT) {
			nw++;
		}
	}
	printf("\nNew Characters: %d, New Line: %d, New Word: %d", nc,nl,nw);
	return 0;
}
```

The variable state record whether  the program is currently in a word or not; initially it is not in a word which is assigned `OUT`. We use symbolic constant IN and OUT to the literal values 1 and 0 because they make the program more readable. Notice the 3 variables being assigned the value of 0.

`nl = nw = nc = 0;`

this means that all 3 values are initialized to have the value of 0; 

This example also used the `else`, which specifies an alternative action if the condition  part of an if statement is false.

```pseudocode
if(expression) {
	statement 1
} else {
	statement 2
}
```

1.6 Arrays 

let us write a program to count the number of occurrences of each digit, of white space characters(blank, tab,newline), and of all other characters.

```c
#include <stdio.h> 
// exmaple input: 222 => digits: 003000000, input: 44 => digits: 0000200000 

int main (void) {
	int c,i,nwhite,nother;
	int ndigit[10];
	
	nwhite = nother = 0;
	for (i = 0; i < 10; i++) {
		ndigit[i] = 0;
	}
	
	while ((c = getchar()) !=  EOF) {
		if(c >= '0' && c <= '9') {
			++ndigit[c-'0'];
		} else if (c == ' ' || c == '\n' || c == '\t'){
			++nwhite;
		} else {
			++nother;
		}
	}
	
	printf("digits: ");
	for (i = 0; i < 10; i++) {
		printf("%d",ndigit[i]);
	}
	printf(", white space = %d, other = %d\n",nwhite,nother);
}
```

Array subscripts always start a 0 in C. A subscript can be any integer expression, which include integer variables like i and integer constant. The expression `if(c >= '0' && c <= '9')` determines whether the character in c is a digit. If it is, the numeric value of that digit is `c-'0'`. Note that this only works if '0','1',..., '9' have consecutive increasing values. luckily they do.

by definition chars are just small integers, so char variables and constants are identical to ints in arithmetic expressions. notice that `c-'0'` is an integer expression with a value between 0 and 9 corresponding to the character '0' to '9' stored in `c`, and thus a valid subscript for the array ndigit. 

Note the use of `else if` which is used in programs to express multiway decisions. The conditions are evaluated from top to bottom. Here is an example of else if:

```pseudocode
else if (condition) {
	statement
}
```

1.7 Functions

In C a function is equivalent to a subroutine. A function provides a convenient way to encapsulate some computation, which can then be used without worrying about its implementation. With properly designed functions it is possible to ignore how a job is done; knowing what is done is sufficient enough. 

The general format of a function is as follows:

```pseudocode
return-type function-name(parameter declarations,if any) {
	declarations
	statements
	return 
}
```

example of a program using function is as follows:

```c
#include <stdio.h> 

/* test power function */
int power(int m, int n);

int main(void) { 
	int i; 
	
	for(i = 0; i < 10; ++i) {
		printf("i value: %d, power1: %d, power2: %d\n",i,power(2,i),power(3,i));
	}
}

/* power: raise base to n-th power: n>= 0 */
int power(int base, int n) {
	int i, p;
	p = 1;
	for(i = 1; i <= n; ++i) {
		p = p * base; 
	}
	return p;
}
```

function definitions can appear in any order, and in one source file or several, although no function can be split between files. Notice the this line of code inside the main function:

`printf("i value: %d, power1: %d, power2: %d\n",i,power(2,i),power(3,i));`

each call passes two arguments to power, which each time returns an integer to be formatted and printed. now the first line of power itself:

`int power (int base, int n)`

declares the parameter types and names, and the type of the result that the function returns . The names used by power for its parameters are local to power, and are not visible to any other function: other routines can use the same names without conflict. The value that power computes is returned to main by the return statement.

The declaration:

`int power (int m, int n);` 

just before main says that power is a function that expects two int arguments and returns an int. this declaration, which is called a function prototype, has to agree with the definition and uses of power. It is an error if the definition of a function or any used of it do not agree with its prototype. Note parameter names need not to agree. Indeed parameter names are optional in a function prototype, so for the prototype we could have written:

`int power(int, int);`

1.8 Arguments--Call by Value 

In C all functions arguments are passed "by value". This means that the called function is given the values of its arguments in temporary variables rather than the originals. The main distinction is that in C the called function cannot directly alter a variable in the calling function; it can only alter its private, temporary copy. Call by value is an asset, however not a liability. It usually leads to more compact programs with fewer extraneous variables, because parameters can be treated as conveniently initialized local variables in the called routine. Note whatever is done to n inside power had no effect on the argument that power was originally called with.

```c
/* power: raise base to N-th power; n >= 0;  */
int power(int base, int n) {
    int p;
    for (p = 1; n > 0; --n) {
        p = p * base;
        return p;
    }
}
```

<u>Note when the name of an array is used as an argument, the value passed to the function is the location or address of the beginning of the array- there is no copying of array elements.</u> 

1.9 Character Arrays

The most common type of array in C is the array of characters. To illustrate the use of character arrays and functions to manipulate them lets write a program that reads a set of text lines and prints the longest. 

```c
#include <stdio.h>
#define MAXLINE 1000               /* maximum input line size */

int getline(char line[], int maxline);
void copy(char to[], char from[]);

// print logest input
int main(void) {
	int len;                   // current line length 
	int max;                   // maximum length seen so far 
	char line[MAXLINE];        // current input line 
	char longest[MAXLINE];     // logest line saved here
	
	max = 0;
	while((len = getline(line, MAXLINE)) > 0) {
		if(len > max) {
			max = len;
			copy(longest, line);
		}
	}
	// there was a line, below 
	if (max > 0) {
		printf("%s",longest);
	}
}

// getline: read a line into s, return length 
int getline(char s[], int lim) {
	int c, i;
	for(i = 0; i < lim-1 && (c = getchar()) != EOF && c !='\n'; ++i) {
		s[i] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	// The \0 indicated the the end of the char array 
	// example: h e l l o \n \0 
	s[i] = '\0';
	return i;
}

// copy: copy 'from' into 'to'; assume  to is beg enouph 
void copy(char to[], char from[]) {
	int i;
	
	i = 0;
	while ((to[i] = from[i]) != '\0') {
		++i;
	}
}
```

In getline the arguments are declared by the line `int getline(int s[], int lim)` which specifies that the first argument, s is an array and the second, lim is an integer. The purpose of supplying the size of an array in a declaration is to set aside storage.

The return type of copy is void, which indicates that no value is returned. getline puts characters `'\0'` (the null character, whose value is zero)  at the end of the arrary it is creating, to mark the end of the string of characters.This convention is also used by the C language: when a string constant like 

"hello\n"

appears in a c program, it is stored as an array of characters containing the characters of the string and terminated with a '\0' to mark the end.

| h    | e    | l    | l    | o    | \n   | \0   |
| ---- | ---- | ---- | ---- | ---- | ---- | ---- |
| 0    | 1    | 2    | 3    | 4    | 5    | 6    |

The %s format specification in printf expects the corresponding arguments to be a string represented in this form. copy also relies on the fact that it input argument is terminated by '\0' and it copies this character into the output argument. 

1.10 External variables and Scope 

The variables in main, such as line, longest, etc., are private or local to main. because they are declared with main, no other function can have direct access to them. Each local variable in a function comes into existence only when the function is called, and disappears when the function is exited. This is why such variables are usually known as automatic variables. 

Because automatic variables come and go with function invocation, they do not retain their values from one call to the next, and must be explicitly set upon each entry. if they are not set, they will contain garbage. 

As an alternative to automatic variables, it is possible to define variables  that are external to all functions, that is, variables that can be accessed by name by any function.

An external variable must be defined, exactly once, outside of any function; this sets aside storage for it. The variable must also be declared in each function that wants to access it; this states the type of the variable. The declaration may be an explicit extern statement or may be implicit from context. 

```c
#include <stdio.h>

#define MAXLINE 1000

int max;
char line [MAXLINE];
char longest[MAXLINE];

int getline(void);
void copy(void);

int main(void) {
    int len;
    extern int max; 
    extern char longest[];
    
    max = 0;
    while((len = getline()) > 0) {
        if(len > max) {
            max = len;
            copy();
        }
    }
    if (max > 0) {
        printf("%s",longest)
    }
}

int getline(void) {
    int c,i;
    extern char line[];
    
    for(i=0;i < MAXLINE-1 && (c = getchar()) != EOF && c != '\n'; ++i) {
        line[i] = c;
    }
    if (c == '\n') {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

void copy(void) {
    int i;
    extern char line[], longest[];
    
    i = 0;
    while((longest[i] = line[i]) != '\0') {
        ++i
    }
}
```

The external variables in main getline, and copy are defined by the first lines of the example above, which state their type and cause storage to be allocated for them.  Before a function can use an external variable, the name of the variable must be made known to the function. one way to do this is to write an extern declaration in the function; the declaration is the same as before except for the added keyword `extern`

In certain circumstances, the extern declaration can be omitted. if the definition of an external variable occurs in the source file before its use in a particular function, then there is no need for an extern declaration in the function. 

The usual practice is to collect extern declarations of variables and functions in a separate file, historically called a header, that is included by `#include` at the front of each source file. The suffix .h is conventional for header names. 

Definitions refers to the place where the variables is created or assigned storage; declarations refer to place where the nature of the variable is started but no storage is allocated.

Note: relying too heavily on external variables is fraught with peril since it leads to programs whose data connections are not at all obvious variables can be changed in unexpected and even inadvertent ways, and the program is hard to modify. 

  