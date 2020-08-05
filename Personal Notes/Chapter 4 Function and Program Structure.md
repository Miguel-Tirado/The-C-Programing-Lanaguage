# Chapter 4: Function and Program Structure 

Summary:

Functions break large computing tasks into smaller ones, and enable people to build on what others have done instead of starting over from scratch. Appropriate functions hide details of operation from parts of the program that don't need to know about them, thus clarifying the whole, and easing the pain of making changes. 

A program may reside in one or more source files. Source files may be compiled separately and loaded together, along with previously compiled functions from libraries. In c it is possible to declare the type of arguments when a function is declared . The syntax of a function also changes, so that declarations and definitions match.

The standard clarifies rules on the scope of names; in particular, it requires that there be only one definition of each external object. initialization is more general: automatic arrays and structures may now be initialized.

**4.1 Basics of Functions**

Were going to write a program that prints each line of its input that contains a particular "pattern" or string characters. This is very similar to the grep command in Unix systems. For example the pattern could be "ould" in the set of lines.

```
Ah Love! could you and i with Fate conspire.
To grasp this sorry Scheme of Things entire,
Would not we shatter it to bite -- and then 
Re-mould it nearer to the Heart's Desire!
```

and the result will be:

```
Ah Love! could you and i with Fate conspire.
Would not we shatter it to bite -- and then 
Re-mould it nearer to the Heart's Desire!
```

The job can be broken down to the following pseudocode :

```pseudocode
while (there's another line) {
	if(the line contains the pattern) {
		print it
	}
}
```

Note 3 small pieces are easier to deal with than one big one, because irrelevant details can be buried in the functions, and the chance of unwanted interactions is minimized. We need to write a routine to decide whether the line contains an occurrence of the pattern. to solve this will write a function `strindex(s,t)` that returns the positions or index in the string s where the string t begins, or -1 if s doesn't contain t. Because C array begin at position zero, indexes will be zero or positive, and so the negative value like -1 is convenient for signaling failure. 

```c
#include <stdio.h>
#define MAXLINE 1000 

int getline(char s[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould"; // pattern to serch for 

int main(void) {
	char line[MAXLINE];
	int found = 0;
	
	while(getline(line, MAXLINE) > 0) {
		if(strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	}
	return found;
}

int getline(char s[], int lim) {
	int i,c;
	
	i = 0;
	while(--lim > 0  && (c = getchar()) != EOF && c != '\n') {
		s[i++] = c;
	}
	if(c == '\n') {
		s[i++] = c;
	}
	s[i] = '\0';
	return i;
}

int strindex(char s[], char t[]) {
	int i,j,k;
	
	for(i = 0; s[i] != '\0'; i++) {
		for(j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++) 
			;
		if(k > 0 && t[k] == '\0') {
			return i;
		}
	}
	return -1;
}
```

A function structure follows:

```pseudocode
return-type function-name(argument declarations) {
	declarations and statements
}
```

A most bare bones function declarations is :

`dummy() {}`

This function does nothing and returns nothing. A do-nothing function like this is helpful as a place holder during program development. 

A program is just a set of declarations of variables and functions. Communications between the functions is by arguments and values returned by the function, and through external variables. The functions can occur in any order in the source file, and source program can be split into multiple files so long as no function is split.

The return statement is the mechanism for returning a value from the called function to its caller. Any expression can follow return:

```pseudocode
return expression;
```

The *expression* will be converted to the return type of the function if necessary. Parenthesis are often used around the expression. but they are optional. Note it is not illegal but probably a sign of trouble, if a function returns a value from one place and no value from another. In any case , if a function fails to return a value, its "value" is certain to be garbage. 

The mechanics of how to compile and load a C program that resides on multiple source files vary from one system to the next. On a Unix system, for example, the cc command does the job. Suppose that the three functions are stored in three files  called main.c, getline.c, and strindex.c. The command: 

`cc main.c getline.c strindex.c`

compiles the 3 files, placing the resulting object code in files main.o, getline,o and strindex.o, then loads all of them into an executable file called a.out. If there was an error in main.c, that file can be recompiled by itself and the result loaded with the previous objects with the command. 

`cc main.c getline.c strindex.c`

The cc command uses the ".c" versus ".o" naming convention to distinguish source files from objects. 

Note the main difference between and Unix and Linux is that Linux was derived from Unix and its an open source operating system free to use. While Unix is operating system that is not free to use and is not open source.

Linux developed by Linus Torvalds in 1991

Unix developed by Ken Thompson in 1969  from AT&T Bell labs 

**4.2 Functions Returning Non-Integers**

Functions are capable of return more than just integer and void types, for instance many math function like sqrt, sin, and cos return double. To illustrate how to deal with non-integer functions, let us write and use the function atof(s), which converts the string s to its double-precision floating point equivalent. It handles an optional sign and decimal point, and the presence or absence  of either integer part or fractional part. Our version is not a high-quality input conversion routine; that would take more space than we care to use. 

First atof itself must declare the type  of value it returns, since it is not int. the type name precedes the function name. 

```c
#include <ctype.h>  
/* atof:  convert string s to double */   
double atof(char s[])   {       
    double val, power;       
    int i, sign;      
    for (i = 0; isspace(s[i]); i++)  /* skip white space */
        ;      
    sign = (s[i] == '-') ? -1 : 1;      
    if (s[i] == '+' || s[i] == '-')          
        i++;      
    for (val = 0.0; isdigit(s[i]); i++)         
        val = 10.0 * val + (s[i] - '0');      
    if (s[i] == '.')       
        i++;    
    for (power = 1.0; isdigit(s[i]); i++) {     
        val = 10.0 * val + (s[i] - '0');        
        power *= 10;   
    }     
    return sign * val / power;  
}
```

Second and just as important, the calling routine must know that atof returns a non-int value. The declaration is shown in this primitive calculator, which reads one number per line, optionally preceded by a sign, and adds them up, printing the running sum after each input:

```c
#include <stdio.h>   #define MAXLINE 100   
/* rudimentary calculator */   
int main(void)   {     
    double sum, atof(char []);       
    char line[MAXLINE];   
    int getline(char line[], int max);      
    sum = 0;      
    while (getline(line, MAXLINE) > 0)        
        printf("\t%g\n", sum += atof(line));    
    return 0; 
}
```

The declaration `double sum, atof(char [])` says that sum is a double variable, and that atof is a function that takes one char argument and returns a double. 

The function atof must be declared and defined constantly. If atof itself and the call to it in main have inconsistent  types in the same source files, the error will be detected by the compiler. But if (as is more likely) atof were compiled separately, the mismatch would not be declared, atof would return a double that main would treat as an int, and meaningless answers would result. 

The reason a mismatch can happen is that if there is no function prototype, a function is implicitly declared by its first appearance in an expression as `sum += atof(line)` 

if a name that has been previously declared occurs in an expression and is followed by a left parenthesis, it is declared by the context to be a function name, the function is assumed to return an int, and nothing is assumed about its arguments. 

Note if a function comes with no arguments such as 

```c
double atof();
```

that too is taken that nothing is to be assumed about the arguments of atof; all parameter checking is turned off. This special meaning of the empty argument list is intended to permit older C programs to compile with new compilers. But its a bad idea to use it with new programs, If the function takes arguments, declare them ; if it takes no arguments use void. 

Now that we have atof we can make atoi 

```c
/* atoi: convert string s to integer using atof */
int atoi(char s[]) {
    double atof(char s[]);
    return (int) atof(s);
}
```

expression is converted to the type of the function before return is taken. Therefore, the value of atof, a double, is converted automatically to int when it appears in this return, since the converted atoi returns an int.  The cast states explicitly that the operation is intended and suppresses any warning. 

**4.3 External Variables

A c program consists of a set of external objects, which are either variables or functions.  External variables are define outside any function,and thus potentially available to many functions. Functions themselves are always external since C does not allow functions to be defined inside other functions. By default, external variables and functions have the property that all references to them by the same name, even from functions compiled separately, are references to the same thing.  (the standard calls this property *external linkage*)

Properties of external variables:

Because external variables are globally accessible, they provide an alternative to function arguments and return values for communicating data between functions. any function may access an external variable by referring to it by name, if the name has been declared somehow. 

If a large number of variables must be shared among function, external variables are among the more convenient and efficient than long argument lists. 

! Caution: for it can have a bad effect on a program structure and lead to programs with too many data connections between functions. 

- External variables have greater scope and lifetime. 
- Automatic variables are internal to a function;  they come into existence when the function is entered and disappear when it is left. 
- External variables are permanent, so they retain vales from one function invocation to the next. 

Therefore is much more convenient to use external variables when 2 functions must share data, yet neither calls the other, it is often most convenient if the shared data is kept in external variables rather than passed in and out via arguments. 

For our example were are going to create a polish calculator, the notation is as follows:

```
(1-2) * (4 + 5)
is entered as
1 2 - 4 5 + * 
```

Parenthesis are not needed; the notation is unambiguous as long as we know how many operands each operator expects.

How the program will work: Each operand is pushed into a stack; when an operator (+,-,*,/) arrives, the proper number of operands (two for binary operators) is popped, the operator is applied to them, and the result is pushed back into the stack.  in the example above 1 and 2 are pushed, then they are subtracted to get -1. Next 4 and 5 are pushed and then replaced by their sum 9. The product of -1 and 9 which is -9, replaces them on the stack. The value on the top of the stack is popped and printed when the end of the input line is encountered.

```pseudocode
while (next operator or operand is not end of file indicator) 
	if(number)
		push it
	else if (operator)
		pop operands
		do operation
		push result
	else if (newline)
		pop and print top of stack
	else 
		error 
```

We decided to store the stack and is associated information in external variables accessible to the push and pop functions but not to main. 

```c
#include es
#define es

// function declarations for main 
main() {...}

//external variables for push and pop

void push(double f) {...}
double pop(void) {...}

int gettop(char s[]) {...}

//routines called by gettop
```

The main code look likes:

```c
#include <stdio.h>
#include <stdlib.h> // for atof

#define MAXOP 100  // max size of operand or operator 
#define NUMBER '0' // signal that a number was found

int getop(char []);
void push(double);
double pop(void);

// reverse polish calculator 
int main(void) {
	int type;
	double op2;
	char s[MAXOP];
	
	while((type = getop(s)) != EOF) {
		switch(type) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*': 
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/': 
				op2 = pop();
				if(op2 != 0.0) {
					push(pop() / op2);
				} else {
					printf("error: zero diversion\n");
				}
				break;
			case '\n': 
				printf("\t%.8g\n",pop());
				break;
			default:
				printf("error: unkown command %s\n",s);
				break;
		}
	}
}
```

Note: for - and / the left and right operands must be distinguished. In 

```c
push(pop() - pop()); // wrong gor - and /
// ex 2 - 4 = -2 while 4 - 2 = 2 
```

 <u>To guarantee the right order, it is necessary to pop the first value into temporary variable as we did in main.</u> 

```c
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f) {
    if(sp < MAXVAL)
        val[sp++]=f;
    else
        printf("error:stack full, cant push %g\n",f);
}

double pop(void) {
    if(sp>0)
        return val[--sp];
    else
    {
        printf("error: stack empty\n");
        return 0.0;
    }
}
```

A variable is external if it is defined outside any function. Thus the stack (double val[MAXVAL]) and stack index (int sp) that must be shared by push and pop are defined outside of these function. 

Let us now turn to the implementation of getop, the function that fetches the next operator or operand. The tasks are; skip blanks and tabs. if the next character is not a digit or decimal, return it. otherwise, collect a string of digits and return a NUMBER, the signal that a number has been collected. 

```c
#include<ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[])
{
    int i,c;

    while((s[0] = c = getch()) == ' ' || c =='\t')
        ;
    s[1] = '\0';
    
    i = 0;
    if(!isdigit(c) && c!='.' && c!='-')
        return c;

    if(c=='-')
        if(isdigit(c=getch()) || c == '.')
            s[++i]=c;
        else
        {
            if(c!=EOF)
                ungetch(c);
            return '-';
        }
    
    if(isdigit(c))
        while(isdigit(s[++i] =c =getch()))
            ;

    if(c=='.')
        while(isdigit(s[++i] = c=getch()))
            ;
    
    s[i] = '\0';
    if(c!=EOF)
        ungetch(c);
    return NUMBER;
}
```

getch delivers the next input character to be considered; ungetch remembers the characters put back on the input, so that subsequent calls to getch will return them before reading a new input. 

How they work together is simple. ungetch puts the pushed back characters into a shared buffer a character array.  getch reads from the buffer if there is anything else, and calls getchar if the buffer is empty. there must also be an index variables that records the position of the character in the buffer. 

```c
char buf[BUFSIZE]; //buffer for ungetch 
int bufp = 0;      // nect free position in buf

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if(bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}
```

**4.4 Scope Rules**

The source text of a program may be kept in several files, and previously compiled routines may be loaded from libraries.

The *scope* of name is the part of the program within which the name can be used. For an automatic variable declared at the beginning of a function, the scope is the function in which the name is declared. local variables of the same name in different functions are unrelated. the same us true of the parameters of a function, which are in effect  local variables. 

The scope of an external variable or a function lasts from the point at which it is declared to the end of the file being compiled.  For example if main sp, val, push, and pop are defined in one file, in order shown above, that is 

```c
int main() {...}

int sp = 0;
double val[MAXVAL];

void push(double f) {...}

double pop(void) {...}
```

Then the variables sp an val may be used in push and pop simply by naming them; no further declarations are needed. But these names are not visible in main nor are push and pop themselves. If an external variables is to be referred to before it is defined, or if it is defined in a different source file from the one where it is being used then an extern declaration is mandatory. 

A declaration announced the properties of a variable primarily its type; a definition also causes storage to be set aside.  if the line 

```c
// Definition of external variables 
int sp;
double val[MAXVAL];
```

appear outside of any function, they define the external variables cause storage to be set aside, and also serve as the declaration for the rest of that source file. on the other hand, the lines:

```c
// Declaration of external variables 
extern int sp;
extern double val[];
```

declare for the rest of the source file that sp is an int and that val is a double array , but they do not create the variables or reserve storage for them. 

Note the extern keyword is used to receive the external variables from another files that it was declared from.  <u>The extern keyword extends the visibility of the c Variables and C functions. There must be only one *definition* of an external variable:</u>

```c
//these are external variables that are outside any function 
int sp;
double val[MAXVAL];

int main(void) {...}
```

 <u>among all the files that make up the source program; other file may contain extern declarations to access it.</u> There may also be extern declarations in the file containing the definition. Array sizes must be specified with the definition, but are optional with an extern declaration. 

Initialization of an external variable goes only with the definition. Although it is not likely organization for this program, the functions push and pop could be defined in one file, and the variables val and sp defined and initialized in another. Then these definitions and declarations would be necessary to tie them together:

```pseudocode
In file1:
	extern int sp;
	extern double val[];
	
	void push(double f) {...}
	double pop(void) {...}
In file2:
	int sp = 0;
	double val[MAXVAL];
	
	int main(void) {...}
```

Because the extern declarations in *file1* lie ahead of and outside the function definitions, they apply to all functions; one set of declarations suffices for all of *file1*. This same organization would also be needed if the definitions of sp and val followed their use in one file. 

**4.5 Header files**

let us consider dividing the calculator program into several source files, as it might be if each of the components were substantially  bigger. The main function would go into a second file, stack.c; getop goes into a third. getop.c. finally getch and ungetch go into a fourth file, getch.c. We separate them from others because they would come from a separately compiled library in a realistic program.

![C_fileStructure](C:\Users\Miguel Tirado\OneDrive\School\C_Review\The C Programing Language\C_fileStructure.PNG)

There is a tradeoff between the desire that each file have access only to the information it needs for its job and the practical reality that it is harder to maintain more header files. It probably best to have one header file that contains everything that is to be shared between any two parts of the program; that is to be shared between any two parts of the program; that is to be shared between any two parts of the program; that is the decision we made here. For a much larger program more organization and more header would be needed. 

**4.6 Static Variables**

The variables sp and val in stacl.c, and buf and bufp in getch.c, are for the private use of the functions in their respective source files, and are not meant to be accessed by anything else. <u>The static declaration, applied to an external variable or function, limits the scope of that object to the rest of the source file being compiled.</u>  External static thus provides a way to hide names like buf and bufp in the getch-ungetch combination, which must be external so they can be shared, yet which should not be usable to users of getch and ungetch. 

static storage is specified by prefixing the normal declaration with the word static. If the two routines and the two variables are compiled in one file, as in 

```c
static char buf[BUFSIZE];             //buffer for ungetch 
static int bufp = 0;                  //next free position in buf

int getch(void) {...}
void ungetch(int c) {...}
```

then no other routine will be able to access buf and bufp, and those names will not conflict with the same name in other files of the same program. The external static declaration is most often used for variables, but it can be applied to function as well. Normally, function name are global, visible to any part to any part of the entire program. If a function is declared static, however its name is invisible outside of the file in which it is declared. 

The static declaration can also be applied to internal variables. <u>Internal static variables are local to a particular function just as automatic variables are, but unlike automatics, they remain in existence rather than coming and going each time the function is activated . This means that internal static variables provide private, permanent storage within a single function.</u>

Add more about internal and external static variables. 

A static variable may be internal or external depending on the place of declaration. static variables are stored in initialized data segments. 

Internal static Variables: are defined as those having static variables which are declared inside a function and extends up to the end of the particular function. Note that the difference between a internal static variable and a local variable is that the duration or lifetime is different. 

External Static Variables: are those which are declared outside a function and set globally for the entire file/program. 

**4.7 Register Variables**

A register declarations advises the compiler that the variable in question will be heavily used. The idea is that register variables are to be placed in machine registers, which may result in smaller and faster programs. A register declaration looks like the following:

```c
register int x;
register char c;
```

The register declaration can only be applied to automatic variables and to the formal parameters of a function. In the latter case it looks like:

```c
f(register unsigned m, register long n) {
    register int i;
    ...
}
```

Only a few variables in each function may be kept in registers and only certain types are allowed. Excess register declarations are harmless, however, since the word *register* is ignored for excess or disallowed declarations. And it is not possible to take the address of a register variable. regardless of whether the variables is actually placed in a register. The specific restrictions on number and types of register variables vary from machine to machine. 

**4.8 Block Structure**

Note C is no a block structured language. Variables can be defined in a block-structured fashion within a function. Declarations of variables (including initializations) may follow the left brace that introduces any compound statement, not just the one that begin a function. variables declared in this way hide any identically named variables in outer blocks, and remain in existence until the matching right brace. For example:

```c
if(n > 0) {
    int i; // delcare a new i
    
    for(i = 0; i < n; i++) {
        ...
    }
}
```

<u>The scope of the variable i is the "true" branch of the if; this i is unrelated to any i outside the block. An automatic variable declared and initialized in a block is initialized each time the block is entered. A static variable is initialized only the first time the block is entered.</u> 

Automatic variables including formal parameters, also hide external variables and functions of the same name. Now given the declarations:

```c
int x;
int y;

f(double x) {
    double y;
    ...
}
```

then within the function f, occurrences of x refer to the parameter, which is a double; outside of f, they refer to the external int. The same is true of the variable y.

<u>! As a matter of style, its best to avoid variable names that conceal name in an outer scope; the potential for confusion and error is too great.</u>

**4.9 Initialization**

In the absence of explicit initialization, external and static variables are guaranteed to be initialized to zero; automatic and register variables have undefined (garbage) initial values. Scalar variables may be initialized when they are defined, by following the name with an equals sign and an expression. 

```c
int x = 1;
char squote = '\'';
long day = 1000L * 60L * 60L * 24L; // miliseconds/day
```

For external and static variables, the initializer must be a constant expression; the initialization is done once, conceptually before the program begins execution. For automatic and register variables, it is done each time the function or block is entered. 

For automatic and register variables, the initializer is not restricted to being a constant: it may be any expression involving previously defined values, even function calls. For example, the initialization of the binary search program in sec 3.3 could be written as: 

```c
int binsearch(int x, int v[], int n) {
	int low = 0;
    int high = n - 1;
    int mid;
    ...
} // instead of 

int binsearch(int x, int v[], int n) {
    int low,high,mid;

	low = 0;
	high = n - 1;
}

```

In effect, initialization of automatic variables are just shorthand for assignment statements. We have generally used explicit assignments, because initializer in declaration are harder to see and further away from point of use.

An array may be initialized by following its declaration with a list of initializers enclosed in braces and separated by commas. For example, to initialize an array days with the number of days in each month:

```c
int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
```

When the size of the array is omitted, the compiler will compute the length by counting the initializers, of which there are 12 in this case.

 If there are fewer initializers for an array than the number specified, the missing elements will be zero for external, static, and automatic variables. It is an error to have too many initializers. There is no way to specify repetition of an initializer, nor to initialize an element in the middle of an array without supplying all the preceding values as well. 

Character arrays are a special case of initialization; a string may be used instead of the braces and commas option:

```c
char pattern[] = "ould";
// its shorthand for the longer but equivilant 
char pattern[] = {'o','u','l','d','\0'}
```

In this case, the array size is five (four characters plus the terminating '\0')

**4.10 Recursion**

C functions may be used recursively;  that is, a function may call itself either directly or indirectly. Consider printing a number as a character string. As we , mentioned before, the digits are generated in the wrong order: low order digits are available before high order digits, but they have to be printed the other way around. 

There are 2 solutions; One is to store the digits in an array as they are generated, then print them in reverse order, as we did with itoa in sec 3.6. The alternative is a recursive solution, in which printd first calls itself to cope with any leading digits, then prints the trailing digit  again, this version can fail on the largest negative number. 

```c
#include <stdio.h>

//printd: print n in decimal 
void printd(int n) {
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    if (n/10) {
        printd(n/10);
    }
    putchar(n % 10 + '0');
} 
```

When a function calls itself recursively, each invocation gets a fresh set of all the automatic variables, independent of the pervious set. Thus in printd(123) the first printd receives the argument n = 123. It passes 12 to a second printd, which in turn passes 1 to a third. The third level printd prints 1, then returns to the second level. That printd prints 2, then returns to the first level. That one print 3 and terminates. 

Given an array, one element is chosen and the other are partitioned into two subsets-- those less than the partition element and those greater than or equal to it. The same process is then applied recursively to the two subsets. When a subset has fewer than two elements, it doesn't need any sorting; this stop the recursion.

```c
//qsort: sortv[left]... v[right] into increasing order
void qsort(int v[], int left, int right) {
    int i, last;
    void swap(int v[], int i, int j);
    
    if (left >= right) {   //do nothing if array contains
        return;            // fewer than two elements
    }
    swap(v, left, (left + right)/2); //move partition elements
    
    last = left;                   // to v[0]
    for (i = left+1; i <= right; i++) {
        if (v[i] < v[left]) {
            swap(v, ++last,i);
        }
    }
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last + 1, right);
       
    
}
```

void swap

```c
void swap(int v[], int i, int j) {
    int temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
```

Recursion may provide no saving in storage, since somewhere a stack of the values being processed must be maintained. Nor will it be faster. But recursive code is more compact, and often much easier to write and understand than the non recursive equivalent. 

**4.11 The C Preprocessor **

C provides certain language facilities by means of a preprocessor, which is conceptually a separate first step in compilation. The two most frequently used features are #include, to include the contents of a file during compilations and #define to replace a token by an arbitrary sequence of characters. 

**4.11.1 File Inclusion**

File inclusion makes it easy to handle collections of #defines and declarations (among other things). Any source line of the form

```c
#include "filename"
//or 
#include <filename>
```

is replaced by the contents of the *filename*. If the *filename* is quoted, searching for the file typically begins where the source program was found; if it is not found there, or if the name is enclosed in < and >, searching follows an implementation defined role. An included file may itself contain #include lines. 

There are often several #include line at the beginning of a source file, to include common #define statements and `extern` declarations, or to access the function prototype declarations for  library functions from headers like <stdio.h>.

#include is the preferred way to tie the declarations together for a large program. It guarantees that all the source files will be supplied with the same definitions and variable declarations, and thus eliminates a particularly nasty kind of bug. 

**4.11.2 Macro Substitution**

A definition has the form:

```c
#define name replacement text
```

It calls for a macro substitution of the simplest kind - subsequent occurrences of the token name will be replaced by the replacement text. The name in a #define has the same form as a variable name ; the replacement text is arbitrary. Normally the replacement text is the rest of the line, but a long definition may be continued onto several lines by placing a \ at the end of each line to be continued. The scope of a name defined with #define is from it point, of definition to the end of the source file being compiled. A definition may use previous definition.  Substitutions are made only for tokens and do not take place within quoted strings. For example if YES is a defined name, there would be no substitution in printf("YES") or YESMAN.

Any name may be defined with any replacement text. For example,

```c
#define forever for(;;) // infifinate loop
```

Defines a new word for infinite loop.

It is also possible to define macros with arguments so the replacement  text can be different calls of the macro. As an example define a macro called max:

```c
#define max(A,B) ((A) > (B) ? (A) : (B))
```

 Therefore  

```c
x = max(p + q, r + s);
// will be replaced by the line 
x = ((p+q) > (r+s) ? (p+q) : (r+s));
```

So long as the arguments are treated consistently, with this macro will serve for any data type; there is no need for different kinds of max for different data types as there would be with functions. 

If you examine the expansion of max, you will notice some pitfalls. The expressions are evaluated twice; This is bad if they involve side effects like increment operators or input and output. for instance:

```c
max(i++, j++) //wrong
```

will increment the larger value twice. Some care also has to be taken with parenthesis to make sure  the order of evaluation is preserved; consider what happens when the macro

```c
#define square(x) x * x //wrong 
```

Nonetheless macros are valuable. One practical example comes from <stdio.h>, in which getchar and putchar are often defined as macros to avoid the run time overhead of a function call per character processed. The functions in <ctype.h> are also usually implemented as macros. 

Names may be undefined with #undef, usually to ensure that a routine is really a function, not a mcro:

```c
#undef getchar 
int getchar(void) {...}
```

Formal parameters are not replaced within quoted strings. If, however a parameter name is preceded by a # in the replacement text, the combination will be expanded into a quoted string with the parameter replaced by the actual argument. This can be combined with a string concatenation to make, for example a debugging macro:

```c
#define dprint(expr) printf(#expr " = %g\n", expr)

//when this is invoked, as in
dprint(x/y);
//the macro is expanded into 
printf("x/y" " = %g\n", x/y);
//and the srings are concatinated, so the effect is 
printf("x/y = %g\n", x/y);
```

Within the actual argument, each " is replaced by \" and each \ by \\\, so the result is a legal string constant.

The preprocessor operator ## provides a way to concatenate actual arguments during macro expansion. if a parameter in the replacement text is adjacent to a ##, the parameter is replaced by the actual argument, the ## and surrounding white space are removed, and the result is re-scanned. For example the macro paste concatenates its two arguments:

```c
#define paste(front, back) front ##back
```

so paste(name, 1) creates the token name 1. 

!The riles for nested uses of ## are arcane further details may be found on appendix A. 

**4.11.3 Conditional Inclusion**

It is possible to control preprocessing itself with conditional statements that are evaluated during preprocessing. This provides a way to include code selectively depending on the value of conditions evaluated during compilation. 

The #if line evaluates a constant integer expression (which may not include sizeof, casts, or enum constants). If the expression is non-zero, subsequent lines until an #endif or #elif or #else are included. (the preprocessor statement #elif is like else if.) The expression defined(name) in a #if is 1 if the name has been defined and 0 otherwise. 

For example, to make sure that the contents of a file hdr.h are included only once, the contents of the file are surrounded with a conditional like this:

```c
#if !defined(HDR)
#define HDR

/* contents of hdr.h go her */

#endif
```

The first inclusion of hdr.h defines the name HDR; subsequent inclusions will find the name defined and skip down to the #endif. A similar style can be used to avoid including file multiple times. if this style is used consistently, then each header can itself include any other headers on which it depends, without the user of the header having to deal with interdependence.

```c
#if SYSTEM == SYSV
	#define HDR "sysv.h"
#elif SYSTEM == BSD
	#define HDR "bsd.g"
#elif SYSTEM == MSDOS
	#define HDR "msdos.h"
#else 
	#define HDR "default.h"
#endif
#include HDR
```

The #ifdef and #ifndef lines are specialized forms that test whether a name is defined. The first example of #if above could have been written:

```c
#ifndef HDR
#define HDR

/* contents of hdr.h go here */

#endif
```

