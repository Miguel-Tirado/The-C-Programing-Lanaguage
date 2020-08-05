# Chapter 5: Pointers and Arrays

A pointer is a variable that contains the address of a variable. Pointers and arrays are closely related. You must declare a pointer before using it to store any variable address. 

Note that pointers have been lumped with goto statements aw a way to make disorganized code that hard to read. This is true when pointers are used carelessly and its easy to create pointer that point to unexpected locations. With more knowledge you can however, pointers can also be used to achieve clarity and simplicity.

The main change from ANSI C is to make explicit! rules about how pointers can be manipulated. In addition the type void * (pointer to void) replaces char * as the proper type for generic pointer. Also pointers and arrays are closely related that they are interchangeable.

**5.1 Pointers and Addresses**

A normal machine has an array of consecutively numbered or addressed memory cells that may be changed individually or in contiguous groups (contiguous: sharing a common border; touching). 

Common Situations 

- any byte can be a char; 1 byte = 8 bits 
- a pair of one-byte cells can be treated as a short integer; (2 bytes = 16 bits) = short int = 16 bits
- four adjacent bytes form a long; 4 bytes = 32 bits = long int 

<u>A pointer is a group of cells often 2 or 4 that can hold an address.</u> So if c is a char and p is a pointer that points to it, we could represent the situation such as:

![image-20200612113935731](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200612113935731.png)

The unary operator `&` gives the address of an object, so the statement 

```c
p = &c // & is used for the address location of c
```

assigns the address of c to the variable p, and p is said to point to c. <u>Note that the & operator only applies to objects in memory : variables and array elements. It can not be applied to expressions, constants, or register variables.</u> 

The unary operator * is the indirection or dereferencing operator; when applied to a pointer, it accesses the object the pointer points to. (dereferencing: obtain from a pointer the address of a data held in another location). Example lets say x and y are integers and ip is a pointer to int. This example shows how to declare a pointer and how to use & and *.

```c
int x = 1, y = 2, z[10];
int *ip;      // ip is a pointer to int 

ip = &x;      // ip now points to x
y = *ip;      // y is now equal to 1
*ip = 0;      // x is now 0
ip = &z[0]    // ip now points to z[0]
```

The declaration of the pointer ip:

```c
int *ip;
```

is intended as a mnemonic; it says the the expression *ip is an int. Note the syntax of the declaration for a variable mimics the syntax of expressions in which the variable might appear. This applies to function declarations as well. 

```c
double *dp, atof(char *);
```

This example says that in an expression *dp and atof(s) have values of the type double, and the argument of atof is a pointer to char. 

Note that a pointer is limited to a particular kind of object: every pointer points to a specific data type. Except for a pointer to void is used to hold any type of pointer but cannot be dereferenced itself. 

if ip points to the integer x, then *ip can occur in any context where x could do 

```c
*ip = *ip + 10;
```

increments *ip by 10.

The unary operator * and & bind more tightly than arithmatic operations so the assignment

```c
y = *ip + 1;
```

takes whatever ip points at, adds 1, and assigns the result to y, while 

```c
*ip += 1
```

increments what ip points to, as do

```c
++*ip;
//and
(*ip)++
```

The parentheses are necessary in this last example; without them, the expression would increment ip instead of what it points to,  because unary operators like * and ++ associate right to left.

<u>Finally since pointer are variables, they can be used without dereferencing, for example if iq is another pointer to int.</u>

```c
iq = ip;
```

<u>copies the contents of ip into iq thus making iq point to whatever ip pointed to.</u>

**5.2 Pointers and Function Arguments**

C passes arguments to functions by value, there is no direct way for the calling function. For instance, a sorting routine might exchange two out of order elements with a function called swap. you may think this might work:

```c
swap(a, b);
// where the swap function is defined as
void swap(int x, int y) {
    int temp;
    
    temp = x;
    x = y;
    y = temp;
}
```

<u>Because of call by value, swap cant affect the arguments a and b in the routine that called it. The function above only swaps copies of a and b.</u> 

The way to obtain the desired effect is for the calling program to pass pointers to the values to be changed. 

```c
swap(&a, &b);
```

since the operator & produces the address of a variable, &a is a pointer to a. In swap itself, the parameters are declared to be pointers, and the operands are accessed indirectly through them. Basically if you want to swap the values for a and b in the main function, we have to pass the pointers to the values to be changed. Note that the address of a and the address of b are being sent to the swap function. 

```c
void swap(int *px, int *py) {  // interchange *px and *py 
    int temp;
    
    temp = *px;
    *px = *py;
    *py = temp;
}
```

A visual representation looks like this:

<img src="C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200612164941599.png" alt="image-20200612164941599" style="zoom:80%;" />

Note that we are passing the address of a and b in the main function but we are dereferencing a and b with the use of the * operator. <u>Pointer arguments enable a function to access an change objects in the function that called it.</u> For instance, consider a function `getint` that performs free-format input conversion by breaking a stream of characters into integer values, one integer per call. `getint` has to return the value it found and also signal end of file when there is no more input. These values have to be, passed back to separate paths, for no matter what value is used for EOF, that could also be the value of an input integer. 

One solution is to have `getint` return the end of file EOF status as its function value, while using a pointer argument to store the converted integer back in the calling function. This is the tactic used for scanf. The following loop fills an array with integers by calls to `getint`.

```c
int n, array[SIZE], getint(int *);

for(n = 0; n < SIZE && getint(&array[n]) != EOF; n++) 
    ;
// as n increases we call getint() each iteration 
```

Each call sets array[n] to the next integer found in the input and increments n. Notice that it is essential to pass the address of array[n] to `getint`. Otherwise there is no way for `getint` to communicate the converted integer back to the caller. 

Our version of getint return EOF for end of file, zero if the next input is not a number, and a positive value if the next input contains a valid number. 

```c
#include <ctype.h>

int getch(void);
void ungetch(int);

//getint: get next integer from input into *pn
int getint(int *pn) {
    int c, sign;
    
    while(isspace(c = getchar())) // skip white spaces
        ;
    if(!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);  // its not a number 
        return 0;
    }
    sign = (c == '-') ? -1:1;
    if(c == '+' || c == '-') {
        c = getch();
    }
    for(*pn = 0; isdigit(C); c = getch()) {
    	*pn = 10 * *pn + (c-'0'); // u can think of *pn as regular variable x for instance. 
    }
    *pn *= sign; // same as *pn = *pn * sign 
    if(c != EOF) {
        ungetch(c);
    }
    return c;
}
```

<u>Throughout getint, *pn is used as an ordinary int variable.</u> We have also used getch and ungetch so the extra character that must be read can be pushed back onto the input. 

**5.3 Pointers and Arrays **

In c, there is a strong relationship between  pointers and arrays, so much so they must talked together. Any operation that can be done with array subscripting can also be done with pointers. This means that we can use pointers instead of arrays and vice versa. The pointer version will in general be faster but, at least to be uninitiated, somewhat harder to understand. The declaration

```c
int a[10];
```

defines an array a of size 10, that is, a block of 10 consecutive objects named a[0], a[1], ..., a[9].

![image-20200613114929589](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200613114929589.png)

The notation a[i] refers to the i-th element of the array. IFf pa is a pointer to an integer, declared as 

```c
int *pa;
//then the assignment 
pa = &a[0];
```

<u>sets pa to point to element zero of a; that is, pa contains the address of a[0]; now the assignment</u> 

```c
x = *pa;
```

<u>will copy the content of a[0] into x.</u>

If  pa points to a particular element of an array, then by definition pa + 1 points to the next element, pa + i points i elements after pa, and pa - i points i elements before. Thus, if  pa points to a[0],

```c
*(pa + 1)  // same as the contents of a[1] 
```

<u>refers to the contents of a[1], *pa+i* is the address of a[i], and *(pa + 1) is the contents of a[i].</u> Remember about zero indexing in arrays, so pa+1 is the address of a[1], may be thought as pa starting as a[0] and were adding one to it. 

![image-20200613122909507](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200613122909507.png)

This holds true for all types or sizes of the variable in the array a. The meaning of adding one to a pointer and by extension, all pointer arithmetic, is that pa+1 points to the next object, and pa+i points to the i-th object beyond pa.

<u>By definition, the value of a variable or expression of type array is the address of element zero of the array.</u> Thus after the assignment 

```c
pa = &a[0]; //same as pa = a;
```

pa and a have identical values. since the name of an array is synonym for the location of the initial element, the assignment pa = &a[0] can also be written as 

```c
pa = a; // same as pa = &a[0]
```

Notice that a reference to a[i] can also be written as *(a+i). 

- In evaluating a[i], C converts it to *(a+i) immediately; the two forms are equivalent. a[i] is equal to *(a + i) in C.  

- applying the operator & to both parts of this equivalence, it follows that &a[i] and a + i are also also identical: a + i is the address of the i-th element beyond a. 

opposite side 

- if pa is a pointer, expressions may use it with a subscript; pa[i] is identical to *(pa+i) immediately; the two forms are equivalent. 

In short, an array and index expressions is equivalent to one written as a pointer and offset. 

There is one difference between and array name and a pointer that must be kept in mind. A pointer is a variable, so pa=a and pa++ are legal. <u>But an array name is not a variable; constructions like a = pa and a++ are illegal.</u> Note a is the array and pa is the pointer here. But an array name is not a variable containing an address . We can use this fact to rewrite another version for strlen, which finds the length of a string:

```c
//strlen: return length of string
int strlen(char *s) {
    // n is the counter here
    int n;
    
    for(n = 0; *s != '\0'; s++) {
        n++;
    }
    return n;
}
```

<u>Since s is a pointer, incrementing it is perfectly legal; s++ had no effect on the character string in the function that called strlen, but merely increments strlen's private copy of the pointer.</u> that means calls like

```c
strlen("hello, world");              //string constant
strlen(array);                       // char array[100]
strlen(ptr);					   // char *ptr
```

all work! As formal parameters in a function definition 

```c
char s[];
//and
char *s;
```

are equivalent; we prefer that latter because it says more explicitly that the parameter is a pointer. When an array name is passed to a function , the function can at its convenience believe that it has been handed either an array or a pointer and manipulate it accordingly. It can also use both notations if needed. 

It is possible to pass part of an array to a function, by passing a pointer to the beginning of the subarray. For example, if a is an array,

```c
f(&a[2]);
//and 
f(a+2)
```

both pass to the function f the address of the subarray that starts at a[2]. Within f, the parameter declaration can read 

```c
f(int arr[]) {...}
//or 
f(int *arr) {...}
```

So as far as f is concerned, the fact that the parameter refers to part of a larger array is no consequence. If one is sure that the elements, it is also possible to index backwards to in an array: p[-1], p[-2], and so on are syntactically legal. and refer to the elements that immediately proceed p[0]. of course it is ilegal  to refer to objects that are not witinin the array bounds.

**5.4 Address Arithmetic**

Simplest forms of pointer or address arithmetic:

- If p is a pointer to some element of an array, then p++ increments p to point to the next element
- p += i increments it to point i elements beyond where it currently does.

C integration of pointers, arrays, and address arithmetic is one of it strengths. Let us illustrate by writing a rudimentary storage allocator. There are two main routines we need to learn about: 

- alloc(n): returns a pointer p to n consecutive  character positions, which can be used by the caller of alloc for storing characters. 
- afree(p): releases storage thus acquired so it can be re-used later. 

The routines are necessary because the calls to afree must be made in opposite order to the calls made on alloc. Note the storage managed by alloc and afree is a stack which runs on the first in last out principle. The standard library provides analogous functions called malloc and free that have no such restrictions.

The easiest implementation is to have alloc hand out pieces of a large character array that we will call allocbuf. This array is private to alloc and afree. since they deal in pointers, not array indices, no other routines need to know the name of the array, which can be declared to static in the source file containing alloc and afree, and thus be invisible outside it. In practical implementations, the array may well not even have a name; it might instead be obtained by calling the malloc  or by asking the operating system for a pointer to some unnamed block of storage.

We also need to know how much of allocbuf has been used. We use a pointer called allocp, that points to the next free element. When alloc is asked for n characters, it checks to see if there is enouph room left in allocbuf. If so alloc returns the current value of allocp (the begining of the free block). then increments it by n to point to the next free area. if there is no room, alloc returns zero. afree(p) merely sets allocp to p if p p is inside allocbuf. 

![image-20200613164805923](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200613164805923.png)

```c
#define ALLOCSIZE 1000 // size of available space 

static char allocbuf[ALLOCSIZE];   // storage for alloc
static char *allocp = allocbuff;   // next free position

char *alloc(int n) {   //returns pointer to n characters
    if(allocbuf + ALLOCSIZE - allocp >= n) {   // it fits
        allocp += n;
        return allocp - n;  //old p
	} else {   //not enouph room 
    	return 0;
    }
}

void afree(char *p) {
    if(p >= allocbuf && p < allocbuf + ALLOCSIZE) {
        alloccp = p;
    }
} // free storage to by p
```

<u>In general a pointer can be initialized just as any other variable can, though normally the only meaningful values are zero or an expression involving the address of previously defined data type of appropriate type</u> . The declaration

```c
static char *allocp = allocbuf; // allocbuf = &allocbuf[0]
```

defines allocp to be a character pointer and initializes it to point to the beginning of allocbuf, which is the next free position when the program starts. this could also be written as

```c
static char *allocp = &allocbuf[0] // &allocbuf[0] = allocbuf
```

 since the array name is the zeroth element. The test

```c
 if(allocbuf + ALLOCSIZE - allocp >= n) {   // it fits
```

checks if there's enough room to satisfy a request for n characters. If there is, the new value of allocp would be at most one beyond the end of allocbuf. If the request can be satisfied, alloc returns a pointer to the beginning of a block of characters (notice the declaration of the function itself). <u>if not alloc must return some signal to notify that there is no space left. C guarantees that zero is never a valid address for data, so a return value of zero, can be used to signal an abnormal event, in this case, no space.</u>

Note that pointers and integers are not interchangeable. Zero is the sole exception: the constant zero may be assigned to a pointer and a pointer may be compared with the constant zero. The symbolic constant NULL is often used in place of zero, as a mnemonic to indicate more clearly that this is a special value for a pointer. NULL is defined in <stdio.h>, so now will be able to use NULL instead of zero.  Tests like:

```c
 if(allocbuf + ALLOCSIZE - allocp >= n) {   // it fits
 //and 
 if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
```

show several important facets of pointer arithmetic. First pointers may compared under certain circumstances. <u>If p and q point to members of the same array then relations like ==, !=, <, >=, etc work properly.</u> for example:

```c
p < q
```

<u>is true if p points to an earlier member of the array than q does.</u> <u>Any pointer can be meaningfully compared for equality or inequality with zero. But the behavior is undefined for arithmetic or comparisons with pointers that do not point to members of the same array.</u> (There is one exception: the address of the first element past the end of the array can be used in pointer arithmetic.)

We noted that a pointer and a integer may be added or subtracted with the following construction:

```c
p + n // p is the pointer and n is number 
char *c;
c + 1 // c[1]
c + 2 // c[2]
```

means the address of the n-th object beyond the one p currently points to. This is true for every kind of object p points to; n is scalled according to the size of the objects p points to, which is determined by the declaration of p. If an int is four bytes, for example, the int will be scaled by four. 

<u>Pointer subtraction is also valid: if p and 1 point to elements of the same array, and p < q, then q - p + 1 is the number of elements from p to q inclusive.</u> With this we can rewrite another version of strlen:

```c
//strlen: return length of string s
// remember a char is like a smaller int 
int strlen(char *s) {
    char *p = s;
    
    while (*p != '\0') {
        p++;
    }
    return p - s;
}
```

In the declaration of p we are initializing it to s  so that it will point to the first character of the string. In the while loop, each character in turn is examined until the '\0' at the end is seen. Because p points to characters, p++ advances p to the next character each time, and p - s gives us the number of characters advanced over, that is, the string length. Note that s remains at the original position and that p is used as the counter. (the number of characters in the string could be too large to store in an int. the header <stddef.h> defines a type ptrdiff t that is large enough to hold the signed difference of two pointer values)

Pointer arithmetic is consistent: if we had been dealing with floats, which occupy more storage than chars, and if p were a pointer to float, p++ would advance to the next float. Thus we could write another version of alloc that maintains floats instead of chars, merely by changing char to float throughout alloc and afree. all the pointer manipulations automatically take into account the size of the object pointed to. 

Valid pointer operations:

- assignment of pointers of the same array type
- adding or subtracting a pointer and an integer 
- subtracting or comparing two pointers to members of the same array
- assigning or comparing to zero

All other pointer arithmetic is illegal. Not legal :

- not legal to add two pointers
- not legal to multiply or divide or shift or mask them
- cant add float or double 
- cant  assign a pointer of one type to a pointer of another type without a cast unless its a void * (pointer). 

Example of pointer incrementing 

```c
#include <stdio.h>

const int MAX = 3;

int main () {

   int  var[] = {10, 100, 200};
   int  i, *ptr;

   /* let us have array address in pointer */
   ptr = var;  // same as ptr = &var[0]
   // when using var it asumes were stating at position 0
	
   for ( i = 0; i < MAX; i++) {

      printf("Address of var[%d] = %x\n", i, ptr );
      printf("Value of var[%d] = %d\n", i, *ptr );

      /* move to the next location */
      ptr++;
   }
	
   return 0;
}

//--------------------output----------------------------------------------
Address of var[0] = bf882b30
Value of var[0] = 10
Address of var[1] = bf882b34
Value of var[1] = 100
Address of var[2] = bf882b38
Value of var[2] = 200
```

Example of pointer decrementing 

```c
#include <stdio.h>

const int MAX = 3;

int main () {

   int  var[] = {10, 100, 200};
   int  i, *ptr;

   /* let us have array address in pointer */
   ptr = &var[MAX-1];
	
   for ( i = MAX; i > 0; i--) {

      printf("Address of var[%d] = %x\n", i-1, ptr );
      printf("Value of var[%d] = %d\n", i-1, *ptr );

      /* move to the previous location */
      ptr--;
   }
	
   return 0;
}

//-----------------------------output-----------------------------------
Address of var[2] = bfedbcd8
Value of var[2] = 200
Address of var[1] = bfedbcd4
Value of var[1] = 100
Address of var[0] = bfedbcd0
Value of var[0] = 10
```

Notice that the initial declaration for ptr is different between the one for incrementing and decrementing.

**5.5 Character Pointers and Functions**

A *string constant*, written as 

```c
"I am string"
char str[] = {'I',' ','a','m',' ','s','t','r','i','n','g','\0'}
```

is an array of characters. In the internal representation , the array is terminated with  the null character '\0' so that programs can find the end. The length in storage is thus one more than the number of characters between the double quotes. 

The most common occurrence of string constants is as arguments to functions as in:

```c
printf("hello, world.\n");
```

When a character string like this appears in a program, access to it is through a character pointer; printf receives a pointer to the beginning of the character array. That is a string constant is accessed by a pointer to its first element. String constants need not be function arguments. If pmessage is declared as 

```c
char *pmessage;
// then the statement
pmessage = "now is the time";
```

<u>assigns to pmessage a pointer to the character array. This is not a string copy; only pointers are involved. C does not provide any operators for processing an entire string of characters as a unit.</u> Note the important difference between these definitions:

```c
char amessage[] = "now is the time";  // and array
char *pmessage = "now is the time";   // a pointer 
```

amessage is an array, just big enough to hold the sequence of characters and '\0' that initializes it. Individual characters within the array may be changed but amessage will always refer to the same storage. On the other hand, pmessage is a pointer, initialized to point to a string constant; the pointer may subsequently be modified to point elsewhere, but the result is undefined, if you try to modify the string constants.

![image-20200614155832857](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200614155832857.png)

This means if you try to modify the the string constants for amessage the result would be undefined . 

The first function is strcpy(s,t), which copies the string t to the string s. We may think we could just declare s = t but this copies the pointer, not the characters.

The array version of strcpy() 

```c
// strcpy: copy t to s: array subscript version

void strcpy(char *s, char *t) {
    int i;
    while((s[i] = t[i]) != '\0') {
    	i++;
    }
}
```

for contrast here is a version of strcpy with pointers

```c
//strcpy: copy t to s; pointer version

void strcpy(char *s, char *t) {
    while((*s = *t) != '\0') {
        s++;
        t++;
	}
}
```

<u>Because arguments are passed by value, strcpy can use the parameter s and t in any way it pleases.</u> Here they are conveniently initialized pointers which are marched along the arrays a character at a time, until the '\0' that terminates t has been copied to s. The final version would look like this for experienced c programmers: 

```c
//strcpy: copy t to s; pointer version 2
void(char *s, char *t) {
    while ((*s++ = *t++) != '\0')
        ;
}
```

This moves the increment of s and t into the test part of the loop. the value of *t++ is the character that t pointed to before t was incremented; the postfix++ doesn't change t until after this character has been fetched. In the same way the character is stored into the old s position before s is incremented. This character is also the value that is compared against '\0' to control the loop. The net effect is that characters are copied from t to s up to and including the terminating '\0'. 

The final revised version of strcpy would be:

```c
strcpy(char *s, char *t) {
    while(*s++ = *t++)
        ;
}
```

although this may seem cryptic at first sight, the notational convenience is considerable, and the idiom should be mastered, because you will see frequently in c programing.

The second routine that we will examine is strcmp(s,t) which compares the character strings s and t and returns negative, zero or positive if s is lexicographically less than or greater than t. the value is obtained by subtracting the characters at the first position where s and t disagree. 

```c
// strcmp return  (neg) <0 if s<t, 0 if s == t, (pos) >0 if s > t 
int strcmp(char *s, char* t) {
    int i;
    
    for(i = 0; s[i] == t[i];i++) {
        if(s[i] == '\0') {
            return 0;
        }
    }
    return s[i] - t[i];
}
// the pointer version 
// strcmp return  (neg) <0 if s<t, 0 if s == t, (pos) >0 if s > t 
int strcmp(char *s, char *t) {
    for(; *s == *t; s++, t++) {
        if(*s == '\0') {
            return 0;
        }
    }     
    return *s - *t;
}
```

since ++ and -- are either prefix or postfix operators other combinations of * and ++ and -- occur, although less frequently. for example:

```c
*--p;
```

<u>decrements p before fetching the character that p points to. in fact the pair of expressions:</u>

```c
*p++ = val;   // push val into stack
val = *--pl   // pop top of stack into val
```

<u>are the standard idioms for pushing and popping a stack.</u>

**5.6 Pointer Array; Pointers to Pointers**

<u>Since pointers are variables themselves, they can be stored in arrays just as other variables can.</u> To show this in action let us write a program that will  sort a set of text lines into alphabetic order, a stripped-down version of the UNIX program sort. 

For this program we need to deal with lines of text, which are of different lengths, and which, unlike integers, cant be compared or moved in a single operation. We need a data representation that will cope efficiently and conveniently with variable-length text lines. 

Now this is where an array of pointers comes in handy. If the lines to be sorted are stored, end to end in one long character array, then each line can be accessed by a pointer to its first character. The pointers themselves can be stored in an array. two lines can be compared by passing their pointers to strcmp. when two out of order lines have to be exchanged, the pointers in the pointer array are exchanged, not the text lines them selves. 

![image-20200615105137571](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200615105137571.png)

This eliminates the twin problems of complicated storage management and high overhead that would go with moving the lines themselves. The sorting process has three steps:

```pseudocode
read all the lines of the input
sort them 
print them in order
```

As usual, it's best to divide the program into functions that match this natural division (divide and conquer), with the main routine controlling the other functions. let us defer the sorting step for a moment, and concentrate on the data structure and the input and output.

The input routine has to collect and save the characters of each line, and build an array of pointers to the lines. It will also have to count the number of input lines, since that information is needed for sorting and printing. Since the input function can only cope with a finite number of input lines, it can return some illegal line count like -1 if too much input is presented. 

The output routine only has to print the lines in the order in which they appear in the array of pointers. 

```c
/* program that will sort a set of text lines into alphabetic order 
   similer to unix sort */
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000  // max number of lines to be sorted 

char *lineptr[MAXLINES]; //pointers to texlines 

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

// sort input lines 
int main() {
	int nlines;      // number of input lines read 
	
	if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines );
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000    // max length of any input lines
int getline(char *, int); // need to make this function!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
char *alloc(int);

//readlines: read input-lines 
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;        // len is for length and nline is for number of lines
	char *p, line[MAXLEN];
	
	nlines = 0;
	while((len = getline(line,MAXLEN)) > 0) {
		if(nlines >= MAXLINES || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			line[len-1] = '\0'; // deletes newline
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

//writelines: write output lines 
void writelines(char *lineptr[], int nlines) {
	int i;
	
	for(i = 0; i < nlines;i++) {
		printf("%s\n",lineptr[i]);
	}
}
```

The function getline is from sec 1.9. The main new thing is declaration for lineptr: 

```c
char *lineptr[MAXLINES]
```

says that lineptr is an array of MAXLINES elements, each element of which is a pointer to a char. That is, lineptr[i] is a character pointer, and *lineptr[i] is the character it points to, the first character of the i-th saved text line. 

Since lineptr is itself the name of an array, it can be treated as a pointer in the same manner as in our earlier examples, and writelines can be written instead as

```c
//writelines: write output lines
void writelines(char *lineptr[], int nlines) {
    while(nlines-- > 0) {
        printf("%s\n", *lineptr++);
    }
}
```

<u>Initially *lineptr points to the first line; each increment advances it to the next line pointer while nline is counted down.</u>

The quicksort form ch 4 needs minor changes to acomidate for the pointers: the declarations have to be modified and the comparison operation must be done by calling strcmp. The algorithm still remains the same.

```c
// qsort: sort v[left]...v[right] into increasing order 
void qsort(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[],int i, int j);
	
	if(left >= right) {   // do nothing if array contains fewer than 2 elements 
		return;
	}
	swap(v,left, (left + right)/2);
	last = left;
	for(i = left+1; i <= right;i++) {
		if(strcmp(v[i], v[left]) < 0){
			swap(v,++last,i);
		}
		swap(v,left,last);
		qsort(v,left,last-1);
		qsort(v, last+1,right);
		
	}
}
// similarly, the swap routine needs only trvial changes: 
void swap(char *v[],int i,int j) {
	char *temp;  // must be a char pointer as well for v
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}
```

Note since any individual element of v (alias lineptr) is a character pointer, temp must be also, so one can be copied to the other. 

**5.7 Multidimensional Arrays**

C provides rectangular multi-dimensional arrays, although in practice they are much less used than arrays of pointers. Now consider the problem of date conversion, from day of the month to day of the year and vice versa. For example, March 1 is the 60th day of a non-leap year, and the 61st day of a leap year. Let us define two functions to do the conversions: day_of_year converts the month and day into the day of the month and day. Since this latter function computes two values, the month and day arguments will be pointers:

```c
month_day(1988, 60, &m, &d)
```

sets m to 2 and d to 29 (February 29th).

These functions both need the same information, a table of the number of days in each month ("thirty days hath September ..."). Since the number of days per month differs for leap years. its easier to separate them into two rows of a two-dimensional array than to keep track of what happens to February during computation. The array for functions for preforming the transformations are as follows:

```c
static char daytab[2][13]={
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};
int day_of_year(int year, int month, int day);
void month_day(int year, int yearday);

int main(void) {
	int day,mo,dat;
	
	day = day_of_year(1998,2,29);
	printf("%d\n",day);
	month_day(1988,60);
	return 0;
}

int day_of_year(int year, int month, int day) {
	int i,leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for(i = 1; i < month; i++) {
		printf("int i: %d and day: %d\n",i,day);
		day += daytab[leap][i];
		printf("int i: %d and day: %d\n",i,day);
	}
	return day;
}

void month_day(int year, int yearday) {
	int i, leap;
	
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	
	for(i = 1; yearday > daytab[leap][i];i++) {
		yearday -= daytab[leap][i];
	}
	printf("Month: %d, Day: %d",i,yearday);
}
```

Recall that the athematic value of a logical expression, such as the one for leap, is either zero (false), or one (true), so it can be used as a subscript of the array daytab. The array daytab has to be external to both day_of_year and month_day, so they can both use it. We made it char to illustrate a legitimate use of char for storing small non character integers. 

In C, a two dimensional array is really a one-dimensional array, each of whose elements is an array. Hence subscripts are written as

```c
daytab[i][j]  //[row][col]
//rather than 
daytab[i,j]   //wrong
```

Other than this notational distinction, a 2 dimensional array can be treated in much the same way as in other languages. Elements are stored by rows, so the rightmost subscript, or column, varies fastest as elements are accessed in storage order. 

An array is initialized by a list of initilaizers in braces; each array can be treated in much the same way as in other languages. We started the array daytab with a column of zero so that month numbers can run form the natural 1 to 12 instead of 0 to 11. Since space is not a premium here, this clearer than adjusting the indices. 

<u>If a two dimensional array is to be passed to a function, the parameter declaration in the function must include the number of columns; the number of rows is irrelevant, since what is passed is, as before, a pointer to an array of rows, where each row is an array of 13 ints.</u>  In this case, it is a pointer to objects that are arrays of 13 ints. thus if the array daytab is to be passed to a function f, the declaration of f would be

```c
f(int daytab[2][13]) {...}
//it could also be
f(int daytab[][13]) {...}
// since the number of rows is irrelevant or it could be
f(int (*daytab)[13]) {...}
```

Which says that parameter is a pointer to an array of 13 integers. the parentheses are necessary since brackets [] have higher precedence than *. <u>Without parentheses, the declaration</u>

```c
int *daytab[13]
```

<u>is an array of 13 pointers to integers.</u> 

**5.8 Initialization of Pointers Arrays**

Consider the problem of writing a function month name(n), which returns a pointer to a character string containing the name of the n-th month. This is an ideal application for an internal static array. Month_name contains a private array of characters strings, and returns a pointer to the proper one when called.  The syntax is similar to previous initializations:

```c
//month_name: return name of n-th month
char *month_name(int n) {
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };
    return (n < 1 || n > 12) ? name[0] : name[n];
}
```

The declaration of name, which is an array of character pointers, is the same as lineptr in the sorting example. The initializer is a list of character strings; each is assigned to the corresponding position in the array. The characters of the i-th string are placed somewhere, and a pointer to them is stored in name[i]. Since the size of the array name is not specified, the compiler counts the initializers and fills in the correct number. 

**Pointers vs Multidimensional Arrays**

C newbies are sometimes confused about the difference between a two dimensional array and an array of pointers. For example given the defintions:

```c
int a[10][20];
int *b[10];      // an array of 10 pointers 
```

Then a [3] [4] and b [3] [4] are both syntactically legal references to a single int. However;

- a is a true two dimensional array: 200 int-sized locations have been set aside and the conventional rectangular subscript calculation 20xrow+col is used to fined the element a [row] [col].
- b the definition only allocates 10 pointers and does not initialize them, initialization must be done explicitly either statically or with code.

Assuming that each element of b does point to a twenty element array, then there will be 200 ints set aside, plus ten cells for the pointers. <u>The important advantage of the pointer array is that the rows of the array may be different lengths. That is each element of b need not point to twenty-element vector; some may point to two elements, some to fifty, and some to none at all.</u>

The most common use of arrays of pointers is to store character strings of diverse lengths, as in the function month_name. A illustration  of this can be found down below. Note this is the visual representation of the array of pointers. 

![image-20200618111830845](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200618111830845.png)

Note this the representation of the two dimensional array. 

![image-20200618112022943](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200618112022943.png)

**5.10 Command-line Arguments**

There are ways to pass command-line arguments or parameters to a program when it begins executing. 

When main is called it is called with two arguments:

1. Conventionally called *argc* for *argument count* is the number of command line arguments the program was invoked with. Basically the amount of arguments you passing to the main function. i.e) $ hello.exe -nr
2. *argv* for *argument vector* is a pointer to an array of characters or string that contain the arguments, one per string

The most basic example of this is the program *echo*, which echoes its command line arguments on a single line, separated by blanks. 

```C
echo hello,world
//prints the output 
hello world 
```

<u>By convention argv[0] is the name by which the program was invoked, so argc is at least 1.</u> If argc is 1, there is no command line arguments after the program name. In the example above, argc is 3 and argv[0], argv[1], and argv[2] are "echo", "hello", and "world" respectively. The first optional argument is argv[1] and the last is argv[argc-1]; additionally the standard requires that argv[argc] be a null pointer.

![image-20200618115159381](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200618115159381.png)

The first version of echo treats argv as an array of pointers. 

```c
#include <stdio.h>

//echo command line arguments 1st version 
int main(int argc, char *argv[]) {
    int i;
    
    for(i = 1; i < argc; i++) {
        printf("%S%S", argv[i],(1 < argc-1) ? " ": "");
    }
    printf("\n");
    return 0;
}
```

Since argv is a pointer to an array of pointers, we can manipulate the pointer rather than index the array. This next variation is based on incrementing argv, which is pointer to pointer to char, while argc is counted down. 

```c
#include <stdio.h>

//echo command line arguments 2nd version
int main(int argc, char *argv[]) {
    while(--argc >0) {
    	printf ("%s%s", *++argv, (argc > 1) ? " " : "");
    }
    printf("\n");
    return 0;
}
```

Since argv is a pointer to the begining of the array of arguments strings, incrementing it by 1 (++argv) make it point at the original argv[1] instead of argv[0]. Each successive increment moves it along to the next argument; *argv is then the pointer that argument. At the same time argc is decremented; when it becomes zero, there are no arguments left to print.

The print statment can also be written as the follwing:

```c
printf((argc > 1) ? "%s " : "%s",*++argv);
```

Note that the format argument of printf can be an expression too. Now lets modify the old search pattern program that was similar to grep. let us change the program so that the pattern to be matched is specified by the first argument on the command line. 

```c
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char *line, int max);

int main(int argc, char *argv[]) {
    char line[MAXLINE];
    int found = 0;
    
    if(argc != 2) {
        printf("Usage: find pattern\n");
    } else {
        while(getline(line, MAXLINE) > 0) {
            if(strstr(line, argv[1]) != NULL) {
                printf("%s", line);
                found++;
            }
        }
    }
    return found;
}
```

<u>The standard library function strstr (s,t) returns a pointer to the first occurrence of the string t in the string s, or NULL if there is none.</u> 

The model can now be elaborated to illustrate further pointer constructions. Here's an exmaple lets say we want to allow 2 optional arguments. one says "print all lines except those that match the pattern;" the second says "precede each printed printed line by its line number."

<u>In UNIX systems a argument that begins with a minus sign introduces an optional flag or parameter.</u> If we choose -x (for "except") to signal the inversion, and -n("number") to request line numbering, then the command 

```pseudocode
find -x -n pattern
```

will print out each line that doesn't match the pattern, preceded by its line number. note optional arguments should be permitted in any order, and the rest of the program should be independent of the number of arguments that were present. Furthermore, it is convenient for users if option arguments can be combined as in 

```pseudocode
find -nx pattern //using two arguments combined 
```

Here is the program:

```c
#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getline(char *line, int max);
/* find: print lines that match pattern from 1st arg */

int main(int argc, char *argv[]){
	char line[MAXLINE];
	long lineno = 0;
	int c, except = 0, number = 0, found = 0;
	while (--argc > 0 && (*++argv)[0] == '-') {
		while (c = *++argv[0]) {
			switch (c) {
				case 'x':
					except = 1;
					break;
				case 'n':
					number = 1;
					break;
				default:
					printf("find: illegal option %c\n", c);
					argc = 0;
					found = -1;
					break;
			}
		}
		
	}
	if (argc != 1) {
		printf("Usage: find -x -n pattern\n");
	} else {
		while (getline(line, MAXLINE) > 0) {
			lineno++;
			if ((strstr(line, *argv) != NULL) != except) {
				if (number) {
				printf("%ld:", lineno);
				}
				printf("%s", line);
				found++;
			}
		}
		return found;
	}
}
```

argc is decremented and argv is incremented before each optional argument. At the end of the loop, if there are no errors, argc tells how many arguments remain unprocessed and argv points to the first of these. 

Therefore argc should be 1 and \*argv should point at the pattern. Notice that *\++argv is a pointer to an argument string, so (\*++argv)[0] is it first character, (an alternate valid form would be \*\*++argv). Becuase [] binds together than \* and ++, the a parenthesis are necessary; without them the expression would be taken as \*++(argv[0]). In fact, that is what we used in the inner loop, where the expression \*++argv[0] increments the pointer argv[0]! 

Notice that *\++argv is a pointer to an argument string, so (\*++argv)[0] is it first character. 

```c
*++argv => "apple"           /* while */       (*++argv)[0] => 'a'                  
```

**5.11 Pointers to  Functions**

<u>In c, a function itself is not a variable, but it is possible to define pointers to functions, which can be assigned, placed in arrays, passed to functions, returned by functions, and so on.</u> To show we will modify the sorting program so that if the optional argument -n is given, it will sort the input lines numerically instead of lexicographically.  

A sort often consists of three parts a comparison that determines the ordering of any pair of objects, an exchange that reverses their order, and a sorting algorithm that makes comparisons and exchange functions to it. we can arrange to sort by different criteria.

Lexicographically comparison of two lines is done by strcmp, as before; we will also need a routine numcmp that compares two lines on the basis of numeric value and returns the same kind of condition indication as strcmp does. These functions are declared ahead of main and pointer to the appropriate one is passed to qsort.

```c
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right,
int (*comp)(void *, void *));
int numcmp(char *, char *);

/* sort input lines */
main(int argc, char *argv[]){
    int nlines; /* number of input lines read */
    int numeric = 0; /* 1 if numeric sort */
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
    	numeric = 1;
    }
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        qsort((void**) lineptr, 0, nlines-1,(int (*)(void*,void*))(numeric ? numcmp : strcmp));
        writelines(lineptr, nlines);
        return 0;
    } else {
    printf("input too big to sort\n");
    return 1;
    }
}
```

<u>In the call to qsort, strcmp and numcmp are addresses of functions. Since they are known to be functions, the & operator is not necessary, in the same way that it is not needed before an array name.</u>

As indicated by the functions prototype, qsort expects an array of pointers, two integers, and a function with two pointer arguments. The generic pointer type void  pointer type void * is used for the pointer arguments. <u>Any pointer can be cast to void * and back again without loss of information, so we can call qsort by casting arguments to void *.</u> The elaborate cast of the function argument casts the arguments of the comparison function. These will generally have no effect on actual representation, but assure the compiler that all is well. 

```c
/* qsort: sort v[left]...v[right] into increasing order */
    void qsort(void *v[], int left, int right,int (*comp)(void *, void *)) {
    int i, last;
    void swap(void *v[], int, int);
        
    if (left >= right) /* do nothing if array contains */
        return; /* fewer than two elements */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
            if ((*comp)(v[i], v[left]) < 0) {
            	swap(v, ++last, i);
            }
    }
    swap(v, left, last);
    qsort(v, left, last-1, comp);
    qsort(v, last+1, right, comp);
}
```

The declaration should be studied with some care. The fourth parameter of qsort is:

```c
int (*comp)(void *, void *)   // one whole parameter, that 
```

<u>Which says that comp is a pointer to a function that has two void * arguments and returns int</u>. 

The use of comp in the line 

```c
if ((*comp)(v[i], v[left]) < 0)
```

is consistent with the declaration: comp is a pointer to a function, *comp is the function and 

```c
(*comp)(v[i], v[left])
```

is the call to it. The parenthesis are needed so the components are correctly associated ; without them,

```c
int *comp(void *, void *)   //wrong 
```

<u>says that comp is a function returning a pointer to an int.</u> 

Note the comparison between both declarations can be made below: 

```c
int (*comp)(void *, void *) // correct way, comp is a pointer to a function
// that has two void * arguments and return a int.
//--------------------------------------------------------
int *comp(void *, void *) // Wrong, comp is a function returning a pointer to 
// int
```

an example would be atof which converts a string into a double value:

```c
#include <stdlib.h>

//numcmp: compare s1 and s2 numerically
int numcmp(char *s1, char *s2) {
    double v1,v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if(v1 < v2) {
        return -1;
    } else if (v1 > v2) {
        return 1;
    } else {
        return 0;
    }
}
```

The swap function, which exchanges two pointers, is identical to what we presented earlier in the chapter, except that the declarations are changed to void *.

```c
void swap(void *v[], int i, int j) {
    void *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
```

**5.12 Complicated Declarations**

C is sometimes frowned upon for the syntax of its declarations, particularly one that involve pointers to functions. <u>The syntax is an attempt to make the declaration and the use agree; it works well for simple cases, but it can be confusing for the harder ones, because declarations cannot be read left to right, and because parenthesis are over-used.</u>  The difference between:

```c
int *f();             //f: function returning pointer to int
int (*pf)();          //*pf: pointer to function returning int 
```

<u>This shows the problem: * is a prefix operator and it has lower precedence than (), so parenthesis are necessary to force the proper association.</u>  

although truly complicated declarations rarely arise in practice in practice, its important to know and understand them. We will present a pair of programs that convert from valid C to a word description and back again. 

The first dcl is the more complex. it converts a c declaration into a word description, as in these examples.

```c
char **argv
    argv: pointer to pointer to char 
int (*daytab)[13]
    daytab: pointer to array[13] of int
int *daytab[13]
    daytab: array[13] of pointers to int with 13 elements(pointers)
void *comp()
    comp: function to returining void
char (*(*x())[])()
    x: function returning pointer to array[] of pointer to array[] of pointer to 	function returning char 
char (*(*x[3])())[5]
    x: array[3] of pointer to function returning pointer to array[5] of char 
        
```

dcl is based on the grammar that specifies a declarator, which is spelled out precisely in appendix. 

```pseudocode
dcl:            optional *s direct dcl 
direct-dcl:     name
                (dcl)
                direct-dcl()
                direct-dcl[optional size]
```

This grammar can be used to parse declarations. For instance, consider this declarator:

```c
(*pfa[])()
```

pfa will be identified as a name and thus as a direct-dcl. Then pfa[ ] is also a direct-dcl. Then *pfa[ ] is recognized as dcl, so (*pfa[ ]) is a direct-dcl. Then (*pfa[ ])() is a direct-dcl and thus a dcl. We can also illustrate the parse with a parse tree like this (where direct-dcl has been abbreviated to dir-dcl):

![image-20200619091531168](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200619091531168.png)

A direct dcl is a name, or parenthesized dcl followed by parenthesis, or a direct dcl followed by brackets with an optional size. 

The heart of the dcl program is pair of functions, dcl and dirdcl, that parse a declaration according to this grammar. Because the grammar is recursively defined, the functions call each other recursively as they recognize pieces of a declaration; the program is called a recursive-descent parser.

```c
//dcl parse a declarator
void dcl(void) {
	int ns;
	for(ns = 0; gettoken() == '*';) {
		ns++;
	}
	dirdcl();
	while(ns-- > 0) {
		strcat(out, "pointer to")
	}
}
```

```c
/* dirdcl: parse a direct declarator */
void dirdcl(void) {
	int type;
    if (tokentype == '(') { /* ( dcl ) */
    	dcl();
    	if (tokentype != ')') {
        	printf("error: missing )\n");
        }
    } else if (tokentype == NAME)  {/* variable name */
            strcpy(name, token);
    } else {
            printf("error: expected name or (dcl)\n");
    }

    while ((type=gettoken()) == PARENS || type == BRACKETS) {
    	if (type == PARENS){
               strcat(out, " function returning");
        }
        else {
        strcat(out, " array");
        strcat(out, token);
        strcat(out, " of");
        }
    }
```

Since the program are intended to be illustrative, not bullet-proof, there are significant restrictions on dcl. It can only handle a simple data type like char or int. It does not handle argument types in functions or qualifiers like const. Spurious black's confuse it. It doesn't do much error recovery, so invalid declarations will also confuse it. 

```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype; /* type of last token */
char token[MAXTOKEN]; /* last token string */
char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];

int main(void) /* convert declaration to words */
{
    while (gettoken() != EOF) { /* 1st token on line */
        strcpy(datatype, token); /* is the datatype */
        out[0] = '\0';
        dcl(); /* parse rest of line */
        if (tokentype != '\n') {
            printf("syntax error\n");
        }
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}
```

The function gettoken skips blanks and tabs, then finds the next token in the input; a "token" is a name, a pair of parentheses, a pair of brackets perhaps including a number, or any other single character. 

```c
int gettoken(void) /* return next token */
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    
    while ((c = getch()) == ' ' || c == '\t')
    	;
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
    	} else {
            ungetch(c);
            return tokentype = '(';
    	}
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); ) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
    return tokentype = NAME;
    } else {
        return tokentype = c;
    }
}
```

 The program undcl converts a word description "x is a function returning a pointer to an array of pointers to functions returning char," which we will express as 

```c
x () * [] * () char 
//to 
char (*(*x())[])()
```

The abbreviated input syntax lets us reuse the gettocken function. undcl also uses the same external variables as dcl does.

```c
/* undcl: convert word descriptions to declarations */
main()
{
    int type;
    char temp[MAXTOKEN];
    while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n')
        if (type == PARENS || type == BRACKETS) {
            strcat(out, token);
        } else if (type == '*') {
            sprintf(temp, "(*%s)", out);
            strcpy(out, temp);
        } else if (type == NAME) {
            sprintf(temp, "%s %s", token, out);
            strcpy(out, temp);
        } else
        printf("invalid input at %s\n", token);
        }
    return 0;
}
```

Here an example of the swap function written on my own:

```c
#include <stdio.h>

void swap(int *, int *);

int main (void) {
    int a = 1, b = 3;
    int *x;
    int *y;
    x = &a;
    y = &b;
    
    printf("Values before swap is called :\na value is: %d\nb value is %d\n",a,b);
    // we have to use address of a and b here becuase both a and b are not pointers there int values
    // declared in the main function
    swap(&a,&b);
    printf("a value is: %d\nb value is %d\n",a,b);
    *x = 9;
    printf("--------------------------------------------------------------\n");
    printf("pointer x value is: %d\npointer y value is %d\n",*x,*y);
    printf("the value for a is : %d",a);
}

void swap(int *pa, int *pb) {
    int *temp;
    temp = *pa;
    *pa = *pb;
    *pb =  temp;
}
```

```output
Values before swap is called :
a value is: 1
b value is 3
a value is: 3
b value is 1
----------------------------------------------------------------
pointer x value is: 9
pointer y value is 1
the value for a is : 9
```

