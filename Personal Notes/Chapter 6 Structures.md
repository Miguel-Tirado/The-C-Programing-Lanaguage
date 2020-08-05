Chapter 6: Structures 

A structure is a collection of one or more variables, possibly different types, grouped together under a single name for convenient handling. A structure is also defined as a user defined data type that allows to combine data items of different kinds. (Note: structure are only available in C and C++). One other fact that might help is that structures are called "records" in other languages, probably because they hold a record of the user  data types that are grouped together under a user defined data type. Structures help to organize complicated data, particularly in large programs, because they permit a group of related variables to be treated as a unit instead of as separate entities. 

One common example of a structure is the payroll is the payroll record where an employee is described by a set of attributes such as name, address, social security number, salary, etc. Some of the attributes could be structures: a name has several components, as does an address and even salary. Another example, more typical for C, comes from graphics: a point is a pair of coordinates, a rectangle is a pair of points, and so on. 

The main change made by ANSI standard is to define structures assignment-- structures may be copied and assigned to, passed to functions, and returned by functions. This has been supported by most compilers for many years, but the properties are now precisely defined. automatic structures and array may also be initialized.  

**6.1 Basics of Structures**

Lets us create a few structures for graphics. The basic object is a point, which we will assume has an x coordinate and a y coordinate, both integers.  A visual representation of a point:

![image-20200620161519367](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200620161519367.png)

The two components can be placed in a structure declared like this:

```c
//struct "structure-tag" {};
struct point {  
    int x;        //members
    int y;        //members
}p1; // variable p1 of type point (optional here)
```

<u>The keyword `struct` introduces a structure declaration, which is a list of declarations enclosed with braces. An optional name called a *structure tag* may follow the word `struct` (as with point here)</u>.  The tag names this kind of structure, and can be used subsequently as a shorthand for the part of the declaration in braces. 

<u>The variables named in a structure are called members.</u> <u>A structure member or tag and an ordinary (i.e, non-member) variable can have the same name with conflict, since they can always be distinguished by context.</u> Furthermore, the same member names may occur in different structures, although as a matter of style one would normally use the same names only for closely related objects. 

A struct declaration defines a type. The right brace that terminates the list of members may be followed by a list of variables, just as for any basic type. That is 

```c
struct {...} x,y,z;
//is syntatically analogous, similer to 
int x,y,z;
```

<u>In the sense that each statement declares x,y,z to be variables of the name type and cause space to be set aside for them.</u>  A struct is a user defined data type where we can add a tag on it to distinguish the structure. Since we declared our own data type we (may) place the variables outside the right brace from the struct or declare them later inside any function.

A structure declaration that is not followed by a list of variables reserves no storage; it merely describes a template or the shape of a structure. If the declaration is tagged. however the tag can  be used later in definition of instances of the structure. For example given the declaration point above: (note i added some stuff here to make it more understandable)

```c
#include <stdio.h>

void somthing(int, int);

//point data type
struct point {
    int x;        
    int y;        
}
int main (void) {
    struct point pt1;   // variable pt1 of type point 
}

void somthing(int a, int b) {
    struct point pt2;  // variable pt2 of type point
}

```

defines a variable pt1 which is a structure of type point . A structure can be initialized by following its definition with a list of initializers, each a constant expression, for the members:

```c
struct point maxpt = { 320, 200}
```

An automatic structure may also be initialized by assignment or by calling a function that returns a structure of the right type.

A member of a particular structure is referred to in an expression by a construction of the form:

```pseudocode
structure-name.member
pt1.x
```

The structure member operator "." connects the structure name and the member name. To print the coordinates of the point pt1, for instance: 

```c
printf("%d,%d" pt1.x,pt1.y);
// or to compute the distance from the origin (0,0) to pt1
double dist, sqrt(double);
dist = sqrt((double)pt1.x * pt1.x + (double)pt1.y * pt1.y);
```

structures can be nested. One representation of a rectangle is a pair of points that denote the diagonally opposite corners:

![image-20200620183727433](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200620183727433.png)

```c
struct rect {
    struct point pt1;
    struct point pt2;
}
```

The rect structure contains two point strcutures. If we declare screen as 

```c
struct rect screen;
//then
screen.pt1.x
```

refers to the x coordinate of the pt1 member of screen. 

**6.2 Structures and Functions**

<u>The only legal operations on a structure are copying it or assigning to it as a unit, taking its address with &, and accessing its members. copy and assignment include passing arguments to functions and returning values from function as well.</u> Structures may not be compared. A structure may be initialized by list of constant member values; an automatic structure may also be initialized by a assignment. 

We are now going to write some functions to manipulate points and rectangles. <u>There are at least  three possible approaches: pass components separately, pass an entire structure, or pass a pointer to it. Each has its  good points and bad points.</u> 

The first function, makepoint, will take two integers and return a point:

```c
//makepoint: make a point from x and y componets 
//note function makepoint will return struct of type point 
//that is why this may look a little confusing in the begining 
// kind look like another struct but its a function
struct point makepoint(int x, int y) {
    struct point temp;
    
    temp.x = x;
    temp.y = y;
    return temp;
}
```

Notice that there is no conflict between the arguments name and the member with the same name; indeed the re-use of the names stresses the relationship. Note that `temp.x` refers to the member x inside struct temp while `x` refers to the value passed into the function.

makepoint can now be used to initialize any structure dynamically, or to provide a structure dynamically, or to provide structure arguments to a function:

```c
struct rect screen;
struct point middle;
struct point makepoint(int, int);

screen.pt1 = makepoint(0,0);
screen.pt2 = makepoint(XMAX, YMAX);
middle = makepoint((screen.pt1.x + screen.pt2.x)/2,
                  (screen.pt1.y + screen.pt2.y)/2);
```

The next step is a set of functions to do arithmetic on points. For instance 

```c
//addpoint: add two points 
struct point addpoint (struct point p1, struct point p2) {
    p1.x += p2.x;
    p1.y += p2.y;
    return p1;
}
```

Here both the arguments and the return value are structures. we incremented the components in p1 rather than using an explicit temporary variable to emphasize that structure parameters are passed by value like any others. (pass by value: means that a copy of the actual parameters value is made in memory, i.e the caller and the callee have two independent variables with the same value)

As another example, the functions ptinrect tests whether a point is inside a rectangle, where wee have adopted the convention that a rectangle includes its left and bottom side but not its top and right sides:

```c
//ptinrect: return 1 if p in r, 0 if not
int ptinrect(struct point p, struct rect r) {
    return p.x >= r.pt1.x && p.x < r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y;
}
```

This assumes that the rectangle is represented in a standard form where the pt1 coordinates are less than the pt2 coordinates. The following function returns a rectangle guaranteed to be in canonical form:

```c
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

//canonrect: canonrect (struct rect r)
struct rect canonrect(struct rect r) {
    struct rect temp;
    
    temp.pt1.x = min(r.pt1.x, r.pt2.x);
    temp.pt1.y = min(r.pt1.y, r.pt2.y);
    temp.pt2.x = max(r.pt1.x, r.pt2.x);
    temp.pt2.y = max(r.pt1.y, r.pt2.y);
    return temp;
}
```

<u>If a large structure is to be passed to a function, it is generally more efficient to pass a pointer than to copy the whole structure. Structure pointers are just like pointers are just like pointers to ordinary variables.</u> The declaration:

```c
struct point *pp;
```

says that pp is a pointer to a structure of type struct point. if pp points to a point structure, \*pp is the structure, and (\*pp).x and (\*pp).y are the members. To use pp, we might write, for example,

```c
struct point origin, *pp;         //we are declaring two struct variables orgin 

pp = &origin;   // sets pp to the address location of origin 
printf("origin is (%d.%d)\n",(*pp).x, (*pp).y);
```

The parentheses are necessary in (*pp).x because the precedence of the structure member operator '.' is higher than \*. The expression \*pp.x means \*(pp.x), which is illegal here because x is not a pointer.

<u>Pointers to structure are so frequently used that an alternative notation is provided as a shorthand. If p is a pointer to a structure, then</u> 

```pseudocode
p->member-of-structure
p->x
```

refers to the particular member. (the operator -> is a minus sign immediately followed by >). So we could write instead 

```c
printf("origin is (%d, %d)\n" pp->x, pp->y);
```

both . and -> associate from left to right, so if we have:

```c
struct rect r, *rp = &r;
//then these four expressions are quivilant to 
r.pt1.x
rp->pt1.x
(r.pt1).x
(rp->pt1).x
```

The structure operators . and -> together with ( ) for function calls and [ ] for subscripts, are at the top of the precedence hierarchy and thus bind very tightly. This means they they are in top priority when evaluating expressions or statements. For example, given the declartion

```c
struct {
    int len;
    char *str;
}*p;
//then 
++p->len
```

increments len, not p, because the implied parenthesization is ++(p->len). Parentheses can be used to alter the binding: (++p)->len increments p before accessing len, and (p++)->len increments p afterward.(this last set of parenthesis is unnecessary)

In the same way, \*p->str fetches whatever str points to; \*p->str++ increments str after accessing whatever it points to (just like \*s++); (*ptr->str)++ increments whatever str points to: and \*p++-->str increments p after accessing whatever str points to. 

**passing struct into functions**

A structure can be passed to any function from main function or from any sub function. structure definition will be available within the function only. Note it wont be available to other functions unless it is passed to those functions by value or by address(reference). Else we have to declare structure variable as global variable. 

There are 3 ways to pass a structure to functions in c:

1. Passing structure to a function by value
2. Passing structure to a function by address(reference) '&'
3. No need to pass a structure -- Declare structure variables as global

Example 1 - Passing Structure To Function In C By Value:

The whole structure is passed to another function by value. This means that the whole structure is passed to another function with all members and their values. So, this structure can be accessed from called function.

```c
#include <stdio.h>
#include <string.h>
 
struct student 
{
            int id;
            char name[20];
            float percentage;
};
 
void func(struct student record);
 
int main() 
{
            struct student record;
 
            record.id=1;
            strcpy(record.name, "Raju");
            record.percentage = 86.5;
 
            func(record);
            return 0;
}
 
void func(struct student record)
{
            printf(" Id is: %d \n", record.id);
            printf(" Name is: %s \n", record.name);
            printf(" Percentage is: %f \n", record.percentage);
}
```

```p
//OUTPUT TERMINAL
Id is: 1
Name is: Raju
Percentage is: 86.500000
```

Example 2 - Passing Structure To Function In C By Address

The whole structure is passed to another function by address (location in memory). It means only the address of the structure is passed to another function. The whole structure is not passed to another function will all members and their values.

```c
#include <stdio.h>
#include <string.h>
 
struct student 
{
           int id;
           char name[20];
           float percentage;
};
 
void func(struct student *record);
 
int main() 
{
          struct student record;
 
          record.id=1;
          strcpy(record.name, "Raju");
          record.percentage = 86.5;
 
          func(&record);
          return 0;
}
 
void func(struct student *record)
{
          printf(" Id is: %d \n", record->id);
          printf(" Name is: %s \n", record->name);
          printf(" Percentage is: %f \n", record->percentage);
}
```

```
//Terminal output
Id is: 1
Name is: Raju
Percentage is: 86.500000
```

Example 3 - Program To Declare A Structure Variable As Global In C

Structure variables can be declared as global variables as we declare other variables in C. So when a structure variable in a goal, then it is visible to all functions in a program. In this scenario , we dont need to pass the structure to any function separately.

```c
#include <stdio.h>
#include <string.h>
 
struct student 
{
            int id;
            char name[20];
            float percentage;
};
struct student record; // Global declaration of structure
 
void structure_demo();
 
int main() 
{
            record.id=1;
            strcpy(record.name, "Raju");
            record.percentage = 86.5;
 
            structure_demo();
            return 0;
}
 
void structure_demo()
{
            printf(" Id is: %d \n", record.id);
            printf(" Name is: %s \n", record.name);
            printf(" Percentage is: %f \n", record.percentage);
}
```

```
//output terminal 
Id is: 1
Name is: Raju
Percentage is: 86.500000
```

**Arrays of Structures**

Lets write a program that would count the occurrence of each C keyword. We need an array of character strings to hold the names, and an array of integers for the counts. One possibility is to use two parallel arrays, keyword and keycount, as in:

```c
char *keyword[NKEYS];
int keycount[NKEYS];
```

But the very fact the arrays are parallel suggest a different organization, an array of structures. Each keyword entry is a pair:

```c
char *word;
int count;
```

and there is an array of pairs. The Structure declaration

```c
struct key {
    char *word;
    int count;
} keytab[NKEYS];
```

declares a structure type key, defines an array keytab of structures of this type, and sets aside storage for them. Each element of the array is a structure. This could also be written as 

```c
//Another way of declaring a structure
struct key {
    char *word;
    int count;
};

struct key keytab[NKEYS];
```

Since the structure keytab contains a constant set of names. It is easiest to make it external variable and initialize it once and for all when it is defined. The structure initialization is analogous to earlier ones -- the definition is followed by a list of initializers enclosed in braces:

```c
struct key {
    char *word;
    int count;
} keytab[] = {
    "auto", 0,
    "break",0,
    "case",0,
    "char",0,
    "const",0,
    "continue",0,
    "defualt",0,
    "unsigned",0,
    "void",0,
    "volatile",0,
    "while",0
};
```

<u>The initializers are listed in pairs corresponding to the structure members.</u> It would be more precise to enclose initializers for each "row" or structure in, braces as in

```c
{ "auto", 0},
{ "break",0},
{ "case",0},
...
```

But the inner braces are not necessary when the initializers are simple variables or character strings, and when all are present. As usual, the number of entries in the array keytab will be computed if initializers are present and the [] is left empty.

The keyword-counting program begins with the definition of keytab. The main routine reads the input by repeatedly calling the function getword that fetches one word at a time. Each word is looked up in the keytab with a version of the binary search function. The list keywords must be sorted in increasing order in the table.

```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

int getword(char *, int);
int binsearch(char *, struct key *, int);

int main(void) {
    int n;
    char word[MAXWORD];

    while(getword(word, MAXWORD) != EOF) {
        if(isalpha(word[0])) {
            if((n = binsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }
    for (n = 0; n < NKEYS;n++) {
        if(keytab[n].count > 0) {
            printf("%4d %s\n",keytab[n].count,keytab[n].word);
        }
    }
}

int binsearch(char *word, struct key tab[], int n) {
    int cond;
    int low,high,mid;

    low = 0;
    high = n-1;
    while(low <= high) {
        mid = (low+high)/2;
        if((cond = strcmp(word, tab[mid].word)) < 0) {
            high = mid-1;
        } else if (cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}
```

We know that each call to getword finds a word, which is copied into the array named as its first argument.

<u>The quantity NKEYS is the number of keywords in keytab.</u> Although we could count this by hand, its a lot easier and safer to do it by machine, especially if the list will change later. One possibility would be to terminate the list of initializers with a null pointer, then loop along keytab until the end is found,

The size of the array is the size of one entry times the number of entries, so the number of entries is just 

```c
sizeof object
//and
sizeof(type name)
```

<u>yield an integer equal to the size of the specified object or type in bytes.</u> (strictly, sizeof produces an unsigned integer value whose type, size_t, is defined in the header <stddef.h>.) An object can be variable or array or structure. A type name can be the name of aa basic type like int or double, or derived type like structure or a pointer. 

In our case, the number of keywords is the size of the array divided by the size of one element. This computation is used in a #define statement to set the value of NKEYS:

```c
#define NKEYS (sizeof keytab / sizeof(struct key))
```

Another way to write this is to divide the array size by the size of a specific element:

```c
#define NKEYS (sizeof keytab / sizeof keytab[0])
```

This has the advantage that it does not need to be changed if the type changes. A sizeof can not be used in a #if line, because the preprocessor does not parse type names. But the expression in the #define is not evaluated by the preprocessor so the code here is legal. 

We have written a more general getword than is necessary for this program, but it is not complicated. Getword fetches the next "word" form the input, where a word is either a string of letters and digits beginning with a letter, or a single non-white space character. The function value is the first character of the word, or EOF for end of file, or the character itself if it is not alphabetic. 

```c
int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while(isspace(c = getchar()))
        ;
    if(c != EOF) {
        *w++ = c;
    }
    if(!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for ( ; --lim > 0; w++) {
        if(!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}
```

Here getword uses the getch and ungetch that we wrote in chapter 4. When the collection of an alphanumeric token stops, getword has gone one character too far. The call to ungetch pushes that character back on the input for the next call. getword also uses isspace to skip white space, isalpha to identify letters, and isalnum to identify letters and digits; all are from the standard header <ctype.h>. 

An array of structures in c can be defined as the collection of multiple structure variables where each variables contains information about different entities. The array if structures in c are used to store information about multiple entities of different data type. The array of structures is also known as the collection of structures. 

![image-20200622185823210](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200622185823210.png)

Example 1

```c
#include<stdio.h>  
#include <string.h>    
struct student{    
int rollno;    
char name[10];    
};    
int main(){    
int i;    
struct student st[5];    
printf("Enter Records of 5 students");    
for(i=0;i<5;i++){    
printf("\nEnter Rollno:");    
scanf("%d",&st[i].rollno);    
printf("\nEnter Name:");    
scanf("%s",&st[i].name);    
}    
printf("\nStudent Information List:");    
for(i=0;i<5;i++){    
printf("\nRollno:%d, Name:%s",st[i].rollno,st[i].name);    
}    
   return 0;    
}
```

Output from terminal:

```
Enter Records of 5 students
Enter Rollno:1
Enter Name:Sonoo
Enter Rollno:2
Enter Name:Ratan
Enter Rollno:3
Enter Name:Vimal
Enter Rollno:4
Enter Name:James
Enter Rollno:5
Enter Name:Sarfraz

Student Information List:
Rollno:1, Name:Sonoo
Rollno:2, Name:Ratan
Rollno:3, Name:Vimal
Rollno:4, Name:James
Rollno:5, Name:Sarfraz
```

**6.4 Pointers in Structures **

Let us write the keyword counting program again, this time using pointers instead of array indices. 

The external declaration of keytab need not to change, but main and binsearch do need modification. 

```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 100

int getword(char *, int);
struct key *binsearch(char *, struct key *, int);

int main (void) {
    char word[MAXWORD];
    struct key *p;
    
    while(getword(word, MAXWORD) != EOF) {
        if(isalpha(word[0])) {
            if((p=binsearch(word, keytab,NKEYS)) != NULL) {
                p->count++;
            }
        }
    }
    for(p = keytab; p < keytab + NKEYS; p++) {
        if(p->count > 0) {
            printf("%4d %s\n", p->count, p->word);
        }
    }
}

struct key *binsearch(char *word, struct key *tab, int n) {
    int cond;
    struct key *low = &tab[0];
    struct key *high = &tab[n];
    struct key *mid;
    
    while(low < high) {
        mid = low + (high-low)/2;
        if((cond = strcmp(word,mid->word)) < 0) {
            high = mid;
        } else if(cond > 0) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return NULL;
}
```

<u>First the declaration of binsearch must indicate that it returns a pointer to struct key instead of an integer</u>; this is declared both in the function prototype and in binsearch. if binsearch finds the word, it returns a pointer to it; if it fails, it returns NULL. 

second, the elements of keytab are now accessed by pointers. This requires significant changes in binsearch. 

The initializers for low and high are now pointer to the beginning and just past the end of the table. The computation of the middle element can no longer be simply:

```c
mid = (low+high) /2;  //wrong
//this is wrong becuase the addition of two pointers is illegal
//Subtraction however is legal, so high-low is the num of elements, then 
mid = low + (high-low)/2;
```

sets mid to point to the element halfway between low and high. The most important change is to adjust the algorithm to make sure that it does not generate an illegal pointer or attempt to access an element outside the limits of the array tab. The problem here is that &tab[-1] and &tab[n] are both outside the limits of the array tab. The former is strictly illegal and it is illegal to dereference the latter. The language definitions does not guarantee, however that pointer arithmetic that involves the first element beyond the end of an array (that is, &tab[n]) will work correctly.

```c
for(p=keytab; p< keytab +NKEYS;p++)
```

 if p is a pointer to a structure, arithmetic on p takes onto account the size of the structure, so p++ increments p by the correct amount to get the next element of the array structures, and the test stops the loop at the right time.

Dont assume however, that the size of a structure is the sum of the size of its members:exclamation: Because of alignment requirements for different objects, there may be unnamed holes in a structure. Thus for example if a char is one byte and a int is four bytes, the strcuture

```c
struct {
    char c;  // 1 byte 
    int i;   // 4 bytes
};
//struct might require 8 bytes for allignment 
```

might well require eight bytes, not five. The sizeof operator returns the proper value.

Finally, an aside on program format: when a function returns a complicated type like a structure pointer as in 

```c
struct key *binsearch(char *word, struct key *tab, int n)
```

The function name can be hard to see, and to find with a text editor. Accordingly an alternate style is sometimes used.

```c
struct key*
binsearch(char *word, struct key *tab, int n)
```

This is optional as its a matter of personal taste. 

**6.5 Self Referential Structures**

Suppose we want to handle the more general problem of counting the occurrences of all the words in the same input. Since we dont know the list of the words in advance we cant use binary search or sort it. Yet we cant do a linear search for each word as it arrives, to see if its already been seen; the program would take too long. Now how can we organize the data to cope efficiently with a list of arbitrary words?

One solution is to keep the set of words seen so far sorted at all times, by placing each word into its proper position in the order as it arrives. This shoudnt be done by shifting i a linear array, though that also takes too long. Instead we will use a data structure called *binary tree*. 

The tree contains one "node" per distinct word; each node contains 

- a pointer to the text of the word
- a count of the number of occurances
- a pointer to the left child node
- a pointer to the right child node 

<u>No node may have more than two children, however they may have one or zero children.</u>  

Binary Tree works:

The nodes are maintained so that at any node the left subtree contains only words that are lexicographically less than the word at the node, and the right subtree contains only words that are greater. This is the tree for the sentence "now is the time for all good men to come to the aid of their party" as built by inserting each word as it encountered.  

![image-20200623125808806](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200623125808806.png)

To find out whether a new word is already in the tree, start at the root and compare the new
word to the word stored at that node. If they match, the question is answered affirmatively. If
the new record is less than the tree word, continue searching at the left child, otherwise at the
right child. If there is no child in the required direction, the new word is not in the tree, and in
fact the empty slot is the proper place to add the new word. This process is recursive, since the
search from any node uses a search from one of its children. Accordingly, recursive routines
for insertion and printing will be most natural.

:star:Going back to the description of a node, it is conveniently represented as a structure with four components:

```c
struct node {             // the tree node 
    char *word;           //points to the text 
    int count;            //number of occurances
    struct tnode *left;   // left child
    struct tnode *right;  // right child
}
```

The recursive declaration of a node might look chancy, but its correct. It is illegal for a structure to contain an instance of itself, but 

```c
struct tnode *left;
```

declares left to be a pointer to a tnode itself. Note that because the recursive declarations of node where declared as pointer they are valid however if they weren't declared as pointers they would be invalid.

Sometimes we need variations of self-referential structures: Two structure that refer to each other. The way to handle this is:

```c
struct t {
    ...
    struct  s *p;  // p points to an s 
};
struct s {
    ...
    struct t *q;   // q points to a t 
}
```

Now the main routine reads words with getword and install them in the tree with addtree. 

```c
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 100

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

/* word frequency count */
int main()
{
    struct tnode *root;
    char word[MAXWORD];
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
}
```

Note that the function addtree is recursive. A word is presented by main to the top level (the root) of the tree. At each stage, that word is compared to the word already stored at the node. and is percolated down to either the left or right subtree by a recursive call to adtree. eventually the word either matches something already in the tree( in which case the count is incremented) or a null pointer is encountered, indicating that a node must be created and added to the tree. If a new node is created, addtree returns a pointer to it, which is installed in the parent node. 

```c
struct tnode *talloc(void);
char *strdup(char *);

/* addtree: add a node with w, at or below p */
struct treenode *addtree(struct tnode *p, char *w)
{
    int cond;
    if (p == NULL) { /* a new word has arrived */
        p = talloc(); /* make a new node */
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
        p->count++; /* repeated word */
    else if (cond < 0) /* less than into left subtree */
        p->left = addtree(p->left, w);
    else /* greater than into right subtree */
        p->right = addtree(p->right, w);
    return p;
}
```

storage for the new node is gained by calling the routine talloc, which returns a pointer to a free space suitable for holding a tree node, and the new word is copied into a hidden space by `strdup`. The count is initalized, and the two children are made null. This part of the code is executed only at the leaves of the tree, when a new node is being added. We have unwisly omitted error checing in the values returned by strup and talloc. 

treeprint prints the tree in sorted order; at each node, it prints the left subtree (all the words less than this word), then the word itself, then the right subtree (all the words greater). If you feel shaky about how recursion works, simulate treeprint as it operates on the tree shown above. 

```c
// treeprint: in-order print of tree
void treeprint(struct tnode *p) {
    if(p != NULL) {
        treeprint(p->left);
        printf("4%d %s\n", p->count,p->word);
    }
}
```

A practical note if the tree becomes "unbalanced" because the words dont arrive in random order, the running time of the program can grow too much. As a worst case, if the words are already in order, this program does an expensive simulation of linear search.

Before we leave this example, it is also worth a brief digestion on a problem related to storage allocators. clearly its desirable there be only storage allocator in a program, even though it allocates different kinds of objects. But if one allocator is to process request for, say, pointers to chars and pointers to struct tnodes, two questions arise. First how does it meet the requirement of most real machines that object of certain types must satisfy alignment restrictions (for example, integers often must be located at even address)?

Alignment requirements can generally be satisfied easily, at the cost of some wasted space, by ensuring that the allocator always returns a pointer that meets all alignment restrictions. The alloc in chapter 5 does not gurantee any particular alignment, so we will use the standard library function malloc, which does.

The question of the type delcaration for a function like malloc is vexing one for any langauge that takes its type checking serously. In C the proper method is to declare that malloc returns a pointer to void, then explicitly coerce the pointer into the desired type with cast . malloc and related routine are declared in the standard header <stdlib.h>. 

**Memory Allocation **

When using dynamic memory in C, The memory is allocated from the heap using some standard library functions. Heap is a pile of memory space available for programmers to use however carefully use of memory is needed in order to avoid memory leak from occurring. The main functions for dynamic memory are malloc() and free(). These will be your bread and butter since malloc is used to allocate memory while free is used to free up memory or space after malloc has been called. 

The malloc function takes a single parameter, which is the size of the requested memory in bytes. It returns a pointer to the allocated memory or NULL if allocation of memory has failed. The prototype is like this:

```c
void *malloc(size_t size);
//malloc is a function that uses void pointer as the type
```

The free() function takes the pointer returned by malloc() and de-allocates the memory. There is no notification if there was a success or failure returned.  The function prototype is like this:

```c
void free(void *pointer);
```

To illustrate the use of  these functions, here is some code to statically define an array and set the fourth element's value:

```c
int my_array[10];
my_array[3] = 99;
```

The following code does the same job using dynamic memory allocation:

```c
int *pointer;
pointer = malloc(10 * sizeof(int));
*(pointer + 3) = 99;
```

The pointer de-referencing syntax is hard to read, so normal array referencing syntax may be used, as [ and  ] are just operators:

```c
pointer[3] = 99;
```

when the array is no longer needed, the memory may be de-allocated thus:

```c
free(pointer);
pointer = NULL;
```

Note that is good practice to assign pointer to NULL because it will cause an error to be generated if the pointer is erroneous(def: incorrect and wrong) utilized after the memory has been de-allocated. 

The amount of heap space actually allocated by malloc() is normally one word larger than that requested. The additional word is used to hold the size of the allocation and is for later use by free(). The size "word" precedes the data area to which malloc() returns a pointer. 

There are two other variants of the malloc() function: called calloc() and realloc()

The calloc() function does the same job as malloc(), except it takes two parameters - the number of array elements and the size of each element - instead of a single parameter(which is the product of these two values). The allocated memory is also initialized to zeros. Here is the prototype:

```c
void *calloc(size_t nelements, size_T elementSize);
```

The realloc() function resizes a memory allocation previously made by malloc(). It takes as parameters a pointer to the memory area and the new size that is required. If the size is reduced, data may be lost. If the size is increased and the function is unable to extend the existing allocation, it will automatically allocate a new memory area and copy data across. In any case, it returns a pointer to the allocated memory. Here is the prototype:

```c
void *realloc(void *pointer, size_t size);
```

Size_t is an unsigned type where it can not represent negative values. Its useful when counting somthing, and are sure that it cannot be negative. 

**6.6 Table look up**

Tp show aspects of structures we are going to write the innards of a table look up package. This code might be found in the symbol table management routines of a macro processor or a compiler. For example, consider the #define statement. When a line like 

```c
#define IN 1
```

is used, the name IN and the replacement test 1 are stored in a table. Later when the name IN appears in a statement like 

```c
state = IN; // IN = 1; so state = 1;
```

it must be replaced by 1.

There are two main routines that manipulate the names and the replacement texts. 

- install(s,t) records the name s and the replacement text t in a table; s and t are just character strings. 

- lookup(s) searches for s in the table and returns a pointer to the place where it was found, or NULL if it wasn't there

The algorithm is a harsh search- the incoming name is converted into small non negative integer, which is then used to index into an array of pointers. An array element points to the beginning of a linked list of blocks describing names that have hash values. It is NULL if no names have hashed to that value.

![image-20200624155509168](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200624155509168.png)

<u>A block in the list is a structure containing pointers to the name, the replacement text, and the next block in the list. A null next-pointer marks the end of the list.</u> 

```c
struct nlist {  //table entry
    struct nlist *next;   // next entry in chain
    char *name;           // defined name
    char *defn;           // replacement text 
}
```

The pointer array is just 

```c
#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; // pointer table
```

The hashing function, which is used by both lookup and install, adds each character value in the string to a scrambled combination of the previous one and returns the remainder modulo the array size.  Note that this is not the best possible hash function but it is short and effective

```c
//hash: form hash value for string
unsigned hash(char *s) {
    unsigned hashval;
    for(hashval = 0; *s != '\0'; s++) {
        hasval *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}
```

Note that unsigned arithmetic is used to make sure that hash value is non-negative.

The hashing process produces a starting index in the array hashtab; if the string is to be found anywhere, it will be in the list of blocks beginning there. The search is performed by lookup finds the entry already present, it returns a pointer to it, it returns NULL. 

```c
//lookup look for s in hastub
struct nlist *lookup(char *s) {
    struct nlist *np;
    for (np = hastab[hash(s)];np != NULL;np = np ->next) {
        if(strcmp(s, np->name) == 0) {
            return np; //found
        }
    }
    return NULL;   //not found
}
```

  t<u>he for loop in lookup is the standard idiom for walking along a linked list:</u>

```c
for(ptr = head; ptr != NULL; ptr = ptr->next) {
    ...
}
```

installs uses lookup to determine whether the name being installed is already present; if so the new definition will supersede the old one. Otherwise, a new entry is created. install returns NULL id for any reason there is no room for a new entry. 

```c
struct nlist *lookup(char *);
char *strdup(char *);

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) { /* not found */
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    } else /* already there */ {
    	free((void *) np->defn); /*free previous defn */
    }
    if ((np->defn = strdup(defn)) == NULL) {
         return NULL;
    }
    return np;
}
```

**6.7 Typedef**

C provides a facility called `typedef` for creating new data type names. for example, the declaration 

```c
typedef int Length;
```

makes the name Length a synonym for int. The type length can be used in declarations, casts, etc, in exactly the same ways that the type int can be:

```c
typedef int Length;

Length len, maxlen;
Length *lengths[];
```

similarly, the declaration 

```c
typedef char *String;
```

makes String a synonym for char * or character pointer, which may then be used in declarations and casts. 

```c
String p, lineptr[MAXLINES], alloc(int);
int strcmp(String, String);
p = (String) malloc(100);
```

Note that the type being declared in a typedef appears in the position of a variable name,not right after the word typedef. Syntactically, typedef is like storage classes extern, static, etc. We have used capitalized names for typedefs to make them stand out. 

As more complicated example, we could make typedefs for the tree nodes shown earlier in this chapter:

```c
typedef struct tnode *Treeptr;

typedef struct tnode  {
    char *word;  // points to the text 
    int count;   //number of occurances 
    Treeptr left; //left child
    Treeptr right; //right child 
} Treenode; 
```

 This creates two new type keywords called Treenode (a structure) and Treeptr (a Pointer to the structure). Then the routine talloc could become 

```c
Treeptr talloc(void) {
    return (Treeptr) malloc(sizeof(Treenode));
}
```

It must be emphasized here that a typedef declaration does not create a new type in any sense; it merely adds a new name for some existing type. (its kind of like renaming different data types) Nor are there any new semantics: variables declared this way have exactly the same properties as variables whose declarations are spelled out explicitly. <u>In effect, typedef is like #define, except that since it is interpreted by the compiler, it can cope with textual substitutions that are beyond the capabilities of the preprocessor.</u> For example: 

```c
typedef int (*PFI)(char *, char *);
```

create the type PFI, for the pointer to function (of two char * arguments) returning int, which can be used in context like

```c
PFI strcmp, numcmp;
```

Besides purely aesthetics, there are two main reasons for using typedefs. <u>The first is to parameterize a program against portability problems.</u> <u>If typedefs are used for data types that may be machine dependent, only the typedefs need change when the program is moved</u>. One common situation is to use typedef names for various integer quantities, then make an appropriate set of choices of short, int and long for each host machine. 

The second purpose of typedefs is to provide better documentation for a program-a type called Treeptr may be easier to understand than one declared only as pointer to a complicated structure. 

**6.8 Unions **

<u>A *union* is a variable that may hold (at different times) objects of different types and sizes, with the compiler keeping track of size and alignment requirements.</u> Unions provide a way to manipulate different kinds of data in a single area of storage, without embedding any machine dependent information in the program. 

As an example such as might be found in a compiler symbol table manager suppose that a constant may be int, a float, or a character pointer. The value of the particular constant must be stored in a variable of the proper type, yet it is most convenient for table management if the value occupies the same amount of storage and is stored in the same place regardless of its type. This is the purpose of a union -- a single variable that can legitimately  hold any one of several types. The syntax is based on structures:

```c
union u_tag {
    int ival;
    float fval;
    char *sval;
}u;
```

:star: The variables u will be large enough to hold the largest data type inside the union.  The specific size is implementation dependent. Any one of these type may be assigned to u and then used in expressions, as long as the usage is consistent through out the program; the type retrieved must be the type most recently stored. It the programmer duty to keep track of which data type is currently being stored in a union; The results are implementation dependent if something is stored as one type and extracted as another. 

Syntactically, members of a union are accessed as 

```pseudocode
union-name.member
//or
union-pointer->member
```

Here is an example of accessing union members

```c
#include <stdio.h>
#include <string.h>
 
union Data {
   int i;
   float f;
   char str[20];
};
 
int main( ) {

   union Data data;        

   data.i = 10;
   data.f = 220.5;
   strcpy( data.str, "C Programming");

   printf( "data.i : %d\n", data.i);
   printf( "data.f : %f\n", data.f);
   printf( "data.str : %s\n", data.str);

   return 0;
}
```

The output is 

```
data.i : 1917853763
data.f : 4122360580327794860452759994368.000000
data.str : C Programming
```

 Just as for structures. If the variable utype is used to keep track of the current type stored in u, then one might see code such as 

```c
if(utype == INT) {
    printf("%d\n",u.ival);
} else if(utype == FLOAT) {
    printf("%f\n",u.fval);
} else if(utype == STRING) {
    printf("%s\n",u.sval);
} else {
    printf("bad type %d un utype\n",utype);
}
```

Unions may occur within structures and arrays, and vice versa. The notation for accessing a member of a union in a structure (or vice versa) is identical to that for nested structures. For example, in the structure array defined by 

```c
struct {
    char *name;
    int flags;
    int utype;
    union {
        int ival;  // this union can only be initialized with int 
        float fval;
        char *sval;
    } u;
} symtab[NSYM];
```

the member ival is referred to as 

```c
symtab[i].u.ival
```

and the first character of the string sval by either of 

```c
*symtab[i].u.sval;
symtab[i].u.sval[0];
```

Note that a union is a structure in which all members have offset zero from the base, the structure is big enough to hold the "widset" member, and the alignment is appropriate for all of the types in the union. The same operations are permitted on unions as on structures: assignment to or copying as a unit, taking the address, and accessing a member. 

A union may only be initialized with a value of the type of its first member; thus the union u described above can only be initialized with an integer value.

**6.9 Bit fields**

When storage space is at a premium, it may be necessary to pack several objects into a single machine word; one common use is a set of single bit flags in applications like compiler symbol tables. Externally imposed data formats, such as interfaces to hardware devices, also often require the ability to get at pieces of a word. 

Imagine a fragment of a compiler that manipulates a symbol table. Each identifier in a program has certain information associated with it. for example, whether or not it is a keyword, whether or not it is external and/or static, and so on. The most compact way to encode such information is a set of one-bit flags in a single char or int. 

The usual way this is done is to define a set of "masks" corresponding to the relevant bit positions, as in 

```c
#define KEYWORD 01
#define EXTERNAL 02
#define STATIC 04
//or 
enum { KEYWORD = 01, EXTERNAL = 02, STATIC = 04};
```

The numbers must be powers of two. Then accessing the bit becomes a matter of "bit-fiddling" with the shifting, masking, and complementing operators that were described in ch 2.

Certain idioms appear frequently: 

```c
flags |= EXTERNAL | STATIC;
//EXTERNAL = 010
//STATIC   = 100
//turns on the EXTERNAL and STATIC bits in flags, while
flags &= ~(EXTERNAL | STATIC);
//truns them off, and 
if ((flags & (EXTERNAL | STATIC)) == 0) ...
//is true if both bits are off. 
```

There is an alternative that offers the capability of defining and accessing fields within a word directly rather than bitwise logical operators. A bit-field or field for short is a set of adjacent bits within a single implementation-defined storage unit that we will call a "word". The syntax of field definition and access is based on structures. for instance the symbol #defines above could be replaced by the definition of three fields (KEYWORD, EXTERNAL, STATIC).

```c
//bit-field declaration
struct {
    type [member_name] : width; 
}
struct {
    unsigned int is_keyword: 1;
    unsigned int is_extern: 1;
    unsigned int is_static: 1;
} flags;
```

<u>This defines a variable called flags that contains three 1 bit fields. The number following the colon represents the field with in bits.</u> The fields are declared unsigned int to ensure that they are unsigned quantities. 

Note that member_name is for the name of the bit field. Individual fields are referenced the same way as other structure members: flags.is_keyword, flags.is_extern, etc. Fields behave like small integers, and may participate in arithmetic expressions just like other integers. Thus the prevous examples may be written more naturally as 

```c
flags.is_extern = flags.is_statiic = 1;
//to turn bits on;
flags.is_extern = flags.is_static = 0;
//to turn them off, and 
if(flags.is_extern == 0 && flags.is_static == 0)
    ...
//to test them 
```

Almost everything about fields is implementation dependent. Whether a field may overlap a word boundary is implementation-defined. Fields need not to be named; unnamed fields (a colon and width only) are used for padding. The special width 0 may be used to force alignment at the next word boundary. 

Fields are assigned left to right on some machines and right to left on others, therefore, although fields are useful for maintain internally defined data structures, the question of which end comes first has to be carefully considered; programs that depend on such things are not portable. 

Rules for bit fields:

- Fields may be declared only as ints; for portability, specify signed or unsigned explicitly. 
- They are not arrays, and they do not have the address, so the & operator cannot be used on them 

suppose we have a structure like this

```c
struct {
   unsigned int widthValidated;
   unsigned int heightValidated;
} status;
```

this structure will require 8 bytes of memory space, however we are only going to store 0 or 1 in each variable. C offer a better way to use memory space in these type of situations. IF we are only going to store 0 or 1 in each variable then we can specify the width of it.

```c
struct {
   unsigned int widthValidated : 1;
   unsigned int heightValidated : 1;
} status;
```

Note this structure will only require 4 bytes of memory space, but only 2 bits will be stored. Note that the size of one int (4bytes ) is large enough to hold 2 bit variables. This means the maximum amount of 1 bit variables it can store is 32 variables. Here is an example showing memory sizes.

```c
#include <stdio.h>
#include <string.h>

/* define simple structure */
struct {
   unsigned int widthValidated;
   unsigned int heightValidated;
} status1;

/* define a structure with bit fields */
struct {
   unsigned int widthValidated : 1;
   unsigned int heightValidated : 1;
} status2;
 
int main( ) {
   printf( "Memory size occupied by status1 : %d\n", sizeof(status1));
   printf( "Memory size occupied by status2 : %d\n", sizeof(status2));
   return 0;
}
```

The output:

```
Memory size occupied by status1 : 8
Memory size occupied by status2 : 4
```

**Difference between a union and a structure**

A union is only supposed to use one of the elements because there all stored in the same spot. This makes it useful for when you want to store something that could be one of several types. 

A struct on the other hand has separate memory locations for each of its elements and they can all be used at once. 