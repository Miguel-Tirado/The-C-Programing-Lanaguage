# Chapter 7: Input and Output

This chapter will be about the standard library, a set functions that provide input and output, string handling, storage management, mathematical routines, and a variety of other services for C programing. Our main focus will be on input and output. 

The ANSI standard defined these library functions precisely so that they are compatible with any system where C exist. programs that only use facilities from the standard are able to be moved from one system to the other without any issues. 

The properties and abilities of library functions are specified in tons of headers; some of which include <stdio.h>, <string.h>, <ctype.h> and more. 

**7.1 Standard Input and Output**

Text Stream: Consist of a sequence of lines; each line ends with a newline character. If the system doesn't work that way the system will do everything it can to make it appear as if it does. For example the library might convert a carriage return '\r' and linefeed to newline on input and back again on output. 

The simplest form of input is to read one character at a time from the standard library input, the function used is getchar():

```c
int getchar(void)
```

getchar() returns the next input character each time it is called, or EOF when it encounters end of file. Note the symbolic EOF is defined in the <stdio.h> header file. The value is typically -1 however test should be written in terms of EOF so that we can use -1 for other triggers. 

In many environments, a file may be substituted for the keyboard by using the < convention for input redirection: if a program prog used getchar, then the command line 

```
prog <infile
```

causes prog to read characters from infile instead. The switching of the input is done in such a way that prog does not know about the change.; in particular, the string "<infile" is not included in the command line arguments in argv. Input switching is also invisable if the input come from another program via a pipe mechanism; one some systems, the command line. 

```
otherprog | prog
```

runs two programs otherprog and prog, and pipes the standard output of otherprog into the standard input for prog. The function 

```c
int putchar()
```

is used for output: putchar(c) put the character c on the standard output, which is by default the screen. putchar returns the character written, or EOF if an error occurs. Again output can usually be directed to a file with >filename: if prog used putchar, 

```
prog >outfile
//we will write the standard outfile instead. If pipes are supported 
prog | anotherprog
```

If pipes are supported, puts the standard output for prog into the standard input of anotherprog. 

note that output produced by printf also finds its way into standard output. calls to putchar() and printf may be interleaved(to arrange in or as if in alternate layers) -- output appears in the order in which the calls were made. 

\* Each source file that refers to an input/output library function must contain the line 

```c
#include <stdio.h>
```

When the name is bracketed by < and > a search is made for the header in a standard set of places. For unix systems  its typically in the directory /usr/include. 

Many program only read one input steam and write one output stream (input getchar(), output putchar(), printf) , which is acceptable to get started. This is particularly true if redirection is used to connect the output of one program to the input for the next. Ex the program lower which converts its input into lower case:

```c
#include <stdio.h>
#inlcude <ctype.h>

int main() {  //lower: convert input to lower case 
    int c;
    
    while((c = getchar()) != EOF) {
        putchar(tolower(c));
    }
    return 0;
}
```

This tolower function is defined inside the <ctype.h>; it converts an upper case letter to lower case, and returns other characters untouched. Note that functions like getchar() in <stdio.h> and tolower() in <ctype.h> are often macros, thus avoiding overhead of a function call per character. programs that use functions stemming from macros are shielded from knowledge of the character set. 

**7.2 Formatted Output --Printf**

The output function printf translate internal values to characters. To get the full context of printf refer to Appendix B in the C programming language book. The Syntax for printf is the following:

```c
int printf(char *format, arg1, arg2, ...);
int printf("The value of x: %d",x);
```

printf converts formats, and prints its arguments on the standard output under control of the format. It returns the number of characters printed. 

The format string contains two types of objects: ordinary characters, which are copied to the output stream, and conversion specifications, each of which causes conversion and printing of the next successive argument to printf. Each conversion specification begins with a % and ends with a conversion character. Between the % and the conversion character there may be, in order: 

- A minus sign, which specifies left adjustment of the converted argument.
- A number that specifies the minimum field width. The converted argument will be printed in at least this wide. FI necessary it will be padded on the left (or right if left adjustment is called for) to make up the field width. 
- A period, which separates the field width form the precision. 
- A number, the precision, that specifies the maximum number of characters to be printed from a string, or the number of digits after the decimal point of a floating point value, or the minimum number of digits for an integer.  
- an h if the integer is to be printed as a short, or 1 (letter ell) if as long 

Conversion charcters are shown in Table 7-1, if the character after the % is not a conversion specification, the behavior is undefined.

![image-20200629113718814](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200629113718814.png)

Note that a width or precision may be specified with *, to indicate the value is computed by converting the next argument (which must be an int). For example, to print at most max characters from a string s,

```c
printf("%.*s", max,s);
```

Now we will go over precision in particular with strings. The following table shows the effect if a variety of specifications in printing "hello world" (12 characters). We have put colons around each field so you can see its extent. 

:%s: 					   :hello, world:
:%10s: 				   :hello, world:
:%.10s:				   :hello, wor:
:%-10s: 				 :hello, world:
:%.15s:			      :hello, world:
:%-15s: 				 :hello, world :
:%15.10s: 			 : hello, wor:
:%-15.10s: 			:hello, wor :

:warning:Printf uses its first argument to decide how many arguments follow and what their types are. It will get confused, and you will get wrong answers, if there are not enough arguments or if they are the wrong type. You should also be aware of the difference between these two calls:

```c
printf(s);        //Fails if s contains %
printf("%s", s);  //SAFE
```

The function sprintf does the same conversions as printf does however stores the ouput in a string. 

```c
int sprintf(char *string, char *format, arg1, arg2,...);
```

sprintf formats the arguments in arg1, arg2, etc,. according to format as before, but places the result in string instead of on the standard output; string must be big enough to receive the result. 

**7.3 Variable Length Argument Lists**

This section contains a minimal version of printf so that we know how to write a function that process variable-length argument list in a portable way. We are mainly interested in the argument processing so we will call the printf statement to do the format conversions for us. 

The proper declaration for print f is 

```c
int printf(char *fmt,...);
```

<u>Note that the declaration `...`  means that the number and types of these arguments may vary.</u>  The declaration `...` can only appear at the end of an argument list. Now our minprintf will be declared as:

```c
void minprintf(char *fmt,...);
```

The tricky bit is how minprintf walks along the argument list when the list doesn't even have a name. The standard header file <stdarg.h> contains a set of macro definitions that define how to step through argument list. Note that the implementation of header will vary from machine to machine but the interface it present is uniform. 

<stdarg.h>

- The type list is used to declare a variable that will refer to each argument in turn; in minprintf, this variable is called ap, for "argument pointer"
- The macro va_start initializes ap to point to the first unnamed argument. It must be called once before ap is used. 
- There must be at least one named argument; the final named argument is used by va_start to get stated.
- Each call of va_arg returns one argument and steps ap to the next; va_arg uses a type name to determine what type  to return and how big a step to take.
- va_end does whatever cleanup is necessary. It must be called before the function returns. 

```c
#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt,...) {
    va_list ap;     //argument pointer which points to each unamed arg in turn 
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap,fmt); //must make ap point to 1st unamed arg, requirment 
    for(p=fmt;*p;p++) {
        if(*p != '%') {
            //prints characters that are not % 
            //skips the switch block below with continue
            putchar(*p);
            continue;  // this continue would skip the swith block and go to the next iteration in the for loop 
        }
        // note that *++p goes to the next character in the string
        //ex *P = "hello", then *++p would give you "ello"
        // this is needed if the first character is '%' since this indicates
        // that were using an argument here in the switch statement 
        switch(*++p) {
            case 'd':
                ival = va_arg(ap,int);
                printf("%d",ival);
                break;
            case 'f':
                dval = va_arg(ap,double);
                printf("%f",dval);
                break;
            case 's':
                for (sval = va_arg(ap,char *);*sval;sval++) {
                    putchar(*sval);
                }
                break;
            default:
                putchar(*p);
                break;
        }    
    }
    va_end(ap);

}
```

**7.4 Formatted input - Scanf**

The function scanf is the input analog of printf, providing many of the same conversions facilities in the opposite direction.

```c
int scanf(char *foramt,...);
```

scanf: reads characters from the standard input, interprets them according to the specification in format, and stores the results through the remaining arguments. The format argument is described below, the other arguments, *each of which must be a pointer*, indicate where the corresponding converted input should be stored. 

<u>scanf stops when it exhausts its format string, or when some input fails to match control specification. It returns as its value the number of successfully matched and assigned input items.</u> This can be used to decide how many items were found. Note that difference between EOF end of file and 0 on sanf return. If scanf returns 0 this means the next input character does not match the first specification in the format string. The next call to scanf resumes searching immediately after the last character already converted. 

There is also a function sscanf that reads from a string but stores the standard input:

```c
int sscanf(char *string, char *format, arg1,arg2,...);
```

 sscanf: scans the string according to the format in format, and stores the resulting values through arg1, arg2, etc. These arguments must be pointers.

The format string usually contain format specifiers, which are used to control the conversion of input. The format string may contain:

- Blanks or tabs, which are ignored.
- Ordinary characters (not %), which are expected to match the next non-white space character of the input stream. 
- Conversion specifications consisting of the character % an optional assignment suppression character *, an optional number specifying a maximum field width, and optional h,l, or L indicating the width of the target, and a conversion character. 

A conversion specification directs the conversion of the next input field. normally the result is placed in the variable pointed to by the corresponding argument. If assingment suppresion is indicated by the * character, however the input field is skipped; no assignment is made. 

Input field: is defined as a string of non white space characters; it extends either to the next white space character or until the field width, if specified , is exhausted. This applies that scanf will read across line boundaries to find its input, since newlines are white space. (white space characters are blank, tab, newline, carriage return, vertical tab, and form feed)

The conversion character indicates the interpretation of the input field. The corresponding argument must be a pointer, as required by the call by value semantics of C. 

![image-20200630124530083](C:\Users\Miguel Tirado\AppData\Roaming\Typora\typora-user-images\image-20200630124530083.png)

The conversion characters d, i, o, u, and x may be proceeded by h to indicate that a pointer to a short rather than int appears in the argument list, or by l to indicate that a pointer to long appears in the argument list. Similarly the conversion characters e, f, and g may be proceeded by 1  to indicate that a pointer to double rather than float is in the argument list. 

example 1: The rudimentary calculator can be written with scanf to do the input conversions. 

```c
#include <stdio.h>

int main(void) {
    double sum, v;
    
    sum = 0;
    while(scanf("%1f", &v) == 1) {
        printf("\t%.2f\n",sum += v);
    }
    return 0;
}
```

lets say we want to read input lines that contain dates of the form

```
25 Dec 1998
```

The scanf is 

```c
int day, year;
char monthname[20];

scanf("%d %s %s", &day, monthname, &year);
```

Note that & is not used with month name since  an array name is a pointer. 

Literal characters can appear in the scanf format string; they must match the same characters in the input. So we could read dates in the form mm/dd/yy with this scanf statement:

```c
int day,month, year;
scanf("%d %d %d", &month, &day, &year);
```

scanf ignores blanks and tabs in its format string. Furthermore, it skips over white space(blanks, tabs, newlines, etc) as it looks for input values. To read input whose format is not fixed, it is often best to read lines at a time, then pick it apart with sscanf. 

```c
while (getline(line, sizeof(line)) > 0) {
    if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
        printf("valid: %s\n", line); /* 25 Dec 1988 form */
    else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
        printf("valid: %s\n", line); /* mm/dd/yy form */
    else
        printf("invalid: %s\n", line); /* invalid form */
}
```

calls to scanf can be mixed with calls to other input functions. The next call to any input functions will begin by reading the first character not read by scanf.

:warning: A final warning the argument to scanf and sscanf must be pointers. By far the most common error is writing

```c
scanf("%d", n);         //wrong
//instead of 
scanf("%d", &n);        // correct
```

This error is not generally detected at compile time. 

**7.5 File Access**

Now were going to write a program that accesses a file that is not already connected to the program. One program that follows this is cat, which concatenates a set of named files onto the standard output. cat is used for printing files on the screen, and as a general purpose input collector for programs that do not have the capability of accessing files by name. 

For example, the command:

```
cat x.c y.c
```

prints the contents of the files x.c and y.c on the standard output. Now how do we arrange the files to be read -- that is, how to connect external names that a user thinks of to the statements that read the data.

The rules:

- before it can be read or written, a file has to be opened by the library function fopen.  fopen takes an external name such as x.c or y.c does some housekeeping and negotiation with the operating system and returns a pointer to be used in subsequent reads or writes of the file. 
- File Pointer: is a pointer that points to a structure that contains information about the file, such as the location of the buffer, the current character position in the buffer, whether the file is being read or written,  and whether errors or end of file have occurred. 
- Users dont need to know the details because the definitions obtained form <stdio.h> include a structure declaration called FILE. The only declaration needed for a file pointer is exemplified by :

```c
FILE *fp;
FILE *fopen(char *name, char *mode);
```

This says that fp is a pointer to a FILE, and fopen returns a pointer to a FILE. Notice that FILE is a type name like int, not a structure tag; it is defined with a typedef. The call to fopen in a program is 

```c
fp = fopen(char *name, mode);
```

Arguments in fopen:

1. The first argument of fopen is a character string containing the name of the file. 
2. The second argument is the mode, also a character string, which indicates how one intends to use the file. Allowable modes include read ("r"), writes ("w"), and append ("a"). 

Some systems distinguish between text and binary files; for the latter, a "b" must be appended to the node string. Note if a file does not exits is opened for writing or appending then it is created if possible. Opening an existing file for writing causes the old contents to be discarded, while opening for appending preserves them. trying to read a file that does not exist is an error, and there may be other causes of error as well, like fopen will return NULL. The error can be identified more precisely.

Now we need a way to read or write the file once it is open. There are several possibilities, of which getc and putc are the simplist. getc returns the next character form a file; it needs the file pointer to tell it which file.

```c
int getc(FILE *fp)
```

<u>getc returns the next character from the start stream referred to by fp; it returns EOF for end of file or error.</u> 

putc is an output function:

```c
int putc(int c, FILE *fp)
```

<u>putc writes the character c to the file fp and returns the character written, or EOF if an error occurs.</u> Like getchar and putchar getc and putc may be macros instead of functions. 

When a C program is started, the operating system environment is responsible for opening three files and providing file pointers for them. These files are the standard input, the standard output, and the standard error; the corresponding file pointers are call stdin, stdout, stderr, and are declared in <stdio.h>. Normally stdin is connected to the keyboard and stdout and redirected to files or pipes. 

getchar and putchar can be defined in terms of getc, putc, and stdin, and stdout as follows:

```c
#define getchar() getc(stdin)
#define putchar(c) putchar((c), stdout)
```

For formatted input or output files, the functions fscanf and fprintf may be used. Note these are the same as printf and scanf, except that the first argument is a file pointer that specifies the file to be read or written; the format string is the second argument. 

```c
int fscanf(FILE *fp, char *format,...);
int fprintf(FILE *fp, char *format,...);
```

We now can  write a program cat to concatenate files. The design is one that had been found convenient for many programs. If there are command line arguments they are interpreted as filenames, and processed in order. If there are no arguments the standard input  is processed. 

```c
#include <stdio.h>
/* cat: concatenate files, version 1 */
int main(int argc, char *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *)
    if (argc == 1) /* no args; copy standard input */
        filecopy(stdin, stdout);
    else {
        while(--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                printf("cat: can't open %s\n, *argv);
            	return 1;
            } else {
                filecopy(fp, stdout);
                fclose(fp);
            }
            return 0;
        }
    }

}
/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF)
    putc(c, ofp);
}
```

The file pointers stdin and stdout are objects of type FILE *, They are constants, however not variables, so it is not passive to assign to them.

The function

```c
int fclose(FILE *fp)
```

is the inverse of fopen; it breaks the connection between the file pointer and the external name that was established by fopen, freeing the file pointer for another file. Since most operating systems have some limit on the number of file that a program may have open simultaneously, its a good idea to free file pointers when they are no longer needed, as we did in cat. There is also another reason for fclose on an output file- it flushes the buffer in which putc is collecting output. fclose is called automatically for each open file when a program terminates normally. (you can chose stdin and stdout if they are not needed. they can also be reassigned by the library function freopen)

**7.6 Error  Handling -- Stderr and Exit **

The cat functions handling of error is not the most optimal approach. The problem is that if one of the files cant be accessed for some reason, the diagnostic is printed at the end of the concatenated output. This might be good enouph if the output was going into a screen, but not if its going into another file or into another program via a pipeline. 

To deal with this a second output stream called `stderr` is assigned to a program in the same way that stdin and stdout are. Output written in stderr normally appears on the screen even if the standard output is redirected somewhere else. 

now let use revise the cat function in c

```c
#include <stdio.h>
/* cat: concatenate files, version 2 */
int main(int argc, char *argv[]) {
    FILE *fp;
    void filecopy(FILE *, FILE *);
    char *prog = argv[0]; /* program name for errors */
    
    if (argc == 1 ) /* no args; copy standard input */
        filecopy(stdin, stdout);
    else {
            while (--argc > 0) {
                  if ((fp = fopen(*++argv, "r")) == NULL) {
                    fprintf(stderr, "%s: can't open %s\n",
                    prog, *argv);
                    exit(1);
                 } else {
                    filecopy(fp, stdout);
                    fclose(fp);
                }
            }
           if (ferror(stdout)) {
           	fprintf(stderr, "%s: error writing stdout\n", prog);
           	exit(2);
           }         
    }
     exit(0);   
}
```

The program signals errors in two ways:

1. The diagnostic output produced by fprintf goes into stderr, so it finds its way to the screen instead of disappearing down a pipeline or into an output file. We included the program name, from argv[0], in the message, so if this program is used with others, the source of an error is identified. 
2. The program uses the standard library function exit, which terminates program execution when it is called. The argument of exit is available to whatever process called this one, so the success or failure of the program can be tested by another program that uses this one as a sub-process. 

Note that a return value of 0 indicates that all is well; non-zero values usually signal abnormal situations. exit calls fclose for each open output file, to flush out any buffered output. (kind of like resetting the buffer)

inside main, return expr is equivalent to exit(expr). exit has the advantage that it can be called from other functions and that calls to it can be found with a pattern searching program. 

The function ferror returns non-zero if an error occurred on the stream fp. 

```c
int ferror(FILE *fp)
```

Although output errors are rare, they do occur (for instance, if a disk fills up), so a production program should check this as well. 

The function feof(FILE*) is analogous to ferror; it returns non-zero if end of file has occurred on the specified file. 

```c
int feof(FILE *fp)
```

We have generally no worried about exit status in our small illustrative programs but any serious program should take care to return sensible, useful status values. 

**7.7 Line Input and Output**

The standard library provides an input routine fgets that is similar to the getline function that we have used in passed chapters.

```c
char *fgets(char *line, int maxline, FILE *fp);
```

fgets: reads the next input line (including the new line) from the file pointer fp into the character array line; at most maxline-1 characters will be read. Note that the resulting line line is terminated with '\0'. Normally fgets returns line; on end of file or error it returns NULL. (Our getline returns the line length, which is a more useful value; zero means end of file.)

Now for output the function fgets writes a string (which need not contain newline) to a file:

```c
int fputs(char *line, FILE *fp);
```

The function fgets returns EOF if an error occurs, and zero otherwise. 

Note that library functions such as gets and puts are similar to fgets and fputs but operate on stdin and stdout. Confusingly gets deletes the terminal '\n' and puts add it. 

To show that there is nothing special about functions like fgets  and fputs, here they are, copied from the standard library on our system. 

```c
/* fgets: get at most n chars from iop */
char *fgets(char *s, int n, FILE *iop)
{
    register int c;
    register char *cs;
    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF) {
            if ((*cs++ = c) == '\n')
            break;
    }

    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}
/* fputs: put string s on file iop */
int fputs(char *s, FILE *iop)
{
    int c;
    while (c = *s++)
    putc(c, iop);
    return ferror(iop) ? EOF : 0;
}
```

For no obvous reason the standard specifies different return values for ferror and fputs . Its easy to implement our getline from fgets:

```c
/* getline: read a line, return length */
int getline(char *line, int max)
{
    if (fgets(line, max, stdin) == NULL)
        return 0;
    else
        return strlen(line);
}
```

**7.8 Miscellaneous Functions**

The standard library comes with a ton of functions. This section will go over a brief glance on the ones that are the most useful. 

7.8.1 String Operations

We have already mentioned the string functions strlen, strcpy, strcat, and strcmp, found in <string.h>. In the following, s and t are char \*'s  and c and n are ints. 

```c
strcat(s,t) concatenate t to end of s
strncat(s,t,n) concatenate n characters of t to end of s
strcmp(s,t) return negative, zero, or positive for s < t, s == t, s > t
strncmp(s,t,n) same as strcmp but only in first n characters
strcpy(s,t) copy t to s
strncpy(s,t,n) copy at most n characters of t to s
strlen(s) return length of s
strchr(s,c) return pointer to first c in s, or NULL if not present
strrchr(s,c) return pointer to last c in s, or NULL if not present
```

7.8.2 Character Class Testing and Convention

Several function from <ctype.h> perform character tests and conversions. In the following, c is an int that can be represented as an unsigned char, or EOF. The function return int.

```c
isalpha(c) non-zero if c is alphabetic, 0 if not
isupper(c) non-zero if c is upper case, 0 if not
islower(c) non-zero if c is lower case, 0 if not
isdigit(c) non-zero if c is digit, 0 if not
isalnum(c) non-zero if isalpha(c) or isdigit(c), 0 if not
isspace(c) non-zero if c is blank, tab, newline, return, formfeed, vertical tab
toupper(c) return c converted to upper case
tolower(c) return c converted to lower case
```

 7.8.3 Ungetc

The standard library provides a rather restricted version of the function ungetch that we wrote in Chapter 4; it is called ungetc.

```c
int ungetc(int c, FILE *fp);
```

pushes the character c back onto file fp, and returns either c, or EOF for an error. Only one character of pushback is guaranteed per file. ungetc may be used with any of the input functions like scanf, getc, or getchar.

7.8.4 Command Execution

The function system(char *s) executes the command contained in the character string s, then resumes execution of the current program. The contents of s depend strongly on the local operating system. for example in UNIX systems, the statement 

```c
system("data");
```

Causes the program date to be run; it prints the date and time of day on the standard output. systems returns system-dependent integer status from the command executed. In the unix system the status return is the value returned by exit. 

7.8.5 Storage Management

The functions malloc and calloc obtain blocks of memory dynamically from the heap.

```c
void *malloc(size_t n)
```

 malloc: returns a pointer to n bytes of initialized storage, or NULL if the request can no be satisfied. 

```c
void *calloc(size_t n, size_t size)
```

calloc: returns a pointer to enough space for an array of n objects of the specialized size, or NULL if the request cannot be satisfied. The storage is initialized to zero. 

The pointer returned by malloc or calloc has the proper alignment for the object in question, but it must be cast into the appropriate type as in:

```c
int *ip;
//remeber that calloc is just a void * pointer so we must cast it here below
ip = (int *) calloc(n, sizeof(int));
```

free(p): frees the space pointed to by p, where p was originally obtained by a call to malloc or calloc. Note there are no restrictions on the order at which space is freed, but it a ghastly error to free something not obtained by calling calloc or malloc.

:warning: It is also an error to use something after is has been freed. A typical but incorrect piece of code is this loop that frees items from a list:

```c
for(p = head; p != NULL; p = p->next)    //WRONG
    free(p);
```

 The right way is to save whatever is needed before freeing. Note that p is a pointer as well so if q = p->next was not called  then free(p) would erase whatever p pointed to. 

```c
for(p = head; p != NULL; p = q) {
    q = p->next;
    free(p);
}
```

7.8.6 Mathematical Functions

There are over 20 mathematical functions declared in <math.h>, here are some of the most used functions. Note that each takes one or two double arguments and returns the result as a double. 

```c
sin(x) sine of x, x in radians
cos(x) cosine of x, x in radians
atan2(y,x) arctangent of y/x, in radians
exp(x) exponential function ex
log(x) natural (base e) logarithm of x (x>0)
log10(x) common (base 10) logarithm of x (x>0)
pow(x,y) xy
sqrt(x) square root of x (x>0)
fabs(x) absolute value of x
```

7.8.7 Random Number Generator 

The function rand() computes a sequence of pseudo-random integers in the range zero to RAND_MAX. which is defined in <stdlib.h> one way to produce random floating point numbers or equal to zero but less than one is:

```c
#define frand() ((double) rand() / (RAND_MAX+1.0))
```

If your library already provides a function for floating point random numbers it is likely to have better statistical properties than this one.)

The function srand(unsigned) sets the seed for rand. The portable implementation of rand and srand suggested by the standard appears in section 2.7.