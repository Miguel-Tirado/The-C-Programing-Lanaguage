# Chapter 3: Control Flow

The Control flow statements of a language specify the order in which computations are preformed. The most common control flow are constructions.

**3.1 Statements and Blocks**

An expression such as `x = 0` or `i++` or `printf(...)` becomes a statement when it is followed by a semicolon, as in:

```c
x = 0;
i++;
printf(...);
```

In C, the semicolon is a statement terminator. Braces { and } are used to group declarations and statements together into a *compound statement* or *block*, so that they are syntactically equivalent to a single statement. The braces that surround the statement of a function are one obvious example; braces around multiple statements after an if, else, while, or for are another. Variables can be declared inside any block. There is no semicolon after the right brace that ends a block.

**3.2 If-Else**

The if-else statement is used to express decisions. formally, the syntax is:

```pseudocode
if (expression) {
	statement 1
} else {
	statement 2
}
```

Note the else part is optional. The expression is evaluated ; if it is true (that is, if expression has a non-zero value), statement 1 is executed. If it is false (expression is zero) and if there is an else part, statement 2 is executed instead. 

Coding Shortcut: 

```pseudocode
if(expression) {
	...
} // instead of 
if(expression != 0) {
	...
}
```

Because the else part of an if-else is optional there is an ambiguity when an else is omitted from a nested if sequence. This is resolved by associating the else with the closest previous else-less if. for example

```c
if(n > 0) 
    if(a > b)
        z = a;
	else 
        z = b;
```

Note the else goes to the inner if, as we have shown by indentation . If that isnt what you want, braces must be used to force the proper association:

```c
if(n > 0) {
	if(a > b) {
        z = a;
    }
} else {
    z = b;
}
```

The indentation shows unequivocally what you want, but the compiler doesn't get the message, and associates the else with the inner if. The kind of bug cam be hard to find; its a good idea to use braces when there are nested ifs.

**3.3 Else-If**

The construction: 

```pseudocode
if(expression) {
	statement
} else if (expression) {
	statement 
} else if (expression) {
	statement 
} else {
	statement 
}
```

This sequence of if statements is the most basic way of writing a multi-way decision. The expressions are evaluated in order; if any expression is true, the statement associated with it is executed , and this terminates the whole chain. As always, the code for each statement is either a single statement, or a group in braces.

The last else part handles the "none of the above" or default case where none of the other conditions is satisfied. Sometimes there is no explicit action for the default; in that case the trailing `else statement` can be omitted, or it may be used for error checking to catch an "impossible " condition. 

Binary search first compares the input value x to the middle element of the array v. If the x is less than the middle value, searching focuses on the lower half of the table, otherwise on the upper half. in either case, the next step is to compare x to the middle element of the selected half. 

```c
/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n) {
    int low,high,mid;
    low = 0;
    high = n-1;
    while(low <= high) {
        mid = (low+high)/2;
        if(x < v[mid]) {
            high = mid - 1;
        } else if(x > v[mid]) {
            low = mid + 1;
        } else {
            return mid;
        }
    }
    return -1;
}
```

**3.4 Switch**

The switch statement is multi-way decision that tests whether an expression matches one of a number of constant integer values, and branches accordingly. 

```pseudocode
switch(expression) {
	case const-expr: statement
	case const-expr: statement 
	default: statement 
}
```

Each case is labeled by one or more integer-valued constants or constant expressions. if case matches the expression value, execution starts at the case. All case expressions must be different. The case labeled default is executed if none of the other cases are satisfied. A default is optional; if it isn't there and if none of the cases match, no action at all takes place. 

An example of a switch statement is as follows: 

```c
#include <stdio.h>
 
int main () {

   /* local variable definition */
   char grade = 'B';

   switch(grade) {
      case 'A' :
         printf("Excellent!\n" );
         break;
      case 'B' :
      case 'C' :
         printf("Well done\n" );
         break;
      case 'D' :
         printf("You passed\n" );
         break;
      case 'F' :
         printf("Better try again\n" );
         break;
      default :
         printf("Invalid grade\n" );
   }
   
   printf("Your grade is  %c\n", grade );
 
   return 0;
}
```

another example from the book; note that cases 0-9 all share the same block of code below with ndigit[c-'0']++. 

```c
#include <stdio.h> 

int main (void) {
    int c,i,nwhite,nother,ndigit[10];
    
    nwhite = nother = 0;
    for(i = 0; i < 10; i++){
        ndigit[i] = 0;
    }
    while ((c = getchar()) != EOF) {
        switch(c) {
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
                ndigit[c-'0']++;
                break;
            case ' ':
            case '\n':
            case '\t': 
                nwhite++;
                break;
            default: 
                nother++;
                break;
        }
    }
    printf("digits =");
    for(i = 0; i < 10; i++) {
        printf(" %d", ndigit[i]);
    }
    printf(", white space = %d, other = %d\n", nwhite, nother);
}
```

The break statement causes an immediate exit from the switch. Because cases serve just as labels, after the code for one case is done, execution fall through to the next unless you take explicit action to escape. break and return are the most common ways to leave a switch. A break statement can also be used be used to force an immediate exit from while, for, and do loops, as will discussed later in this chapter. 

Falling through cases is a mixed blessing. on the positive side, it allows several cases to be attached to a single action, as with digits in this example. But it also implies that normally each case must end with a break to prevent falling through to the next. falling through from one case to another is not robust, being more prone to disintegration when the program is modified. With the exception of multiple labels for a single computation, fall throughs should be used sparingly and commented. 

As a matter of good form, put a break after the last case (the default here) even though its logically unnecessary. Some day when another case gets added at the end, this bit of defensive programing will save you. 

**3.5 loops While and For**

while loop:

```pseudocode
while (expression) {
	statement
}
```

If it is non zero, statement is executed and expression is re evaluated. This cycle continues until expression becomes zero, at which point execution resumes after statement. The for statement:

```pseudocode
for(expr1; expr2 ; expr3) {
	statement
}
// is equivilant to 
expr1;
while (expr2) {
	statement 
	expr3;
}
```

Most commonly, expr1 and expr3 are assignments or function calls and expr2, is a relational expression. Any of the three parts can be omitted, although the semicolon must remain. If the test, expr2, is not present, it is taken as permanently true so

```c
for(;;) {
    ...
}
```

This is a infinite loop, presumably to be broken by other means, such as a break or return. The for is preferable when there is a simple initialization and increment, since it keeps the loop control statements close together and visible at the top of the loop. For example 

```c
for (i = 0; i < n; i++) {
    ...
}
```

Note for loops are not restricted to arithmetic progressions. Nonetheless, it is a bad style to force unrelated computations into the initialization and increment of a for, which are better reserved for loop control operations.

As a larger example, here is another version of atoi for converting a string to its numeric equivalent. Each step does it part, and leaves things  in a clean state for the next part. The whole process terminates on the first character that could not be part of a number.

```c
#include <stdio.h>

int atoi(char s1[]) {
    int i, n, sign;
    
    for(i = 0; isspace(s[i]); i++) 
        ;
    sign = (s[i] == '-') ? -1 : 1;
    
    if(s[i] == '+' || s[i] == '-') {
        i++;
    }
    for(n=0; isdigit(s[i]); i++) {
        n = 10 * n + (s[i] - '0');
    }
    return sign * n;
}
```

The following is a shell sort for sorting an array of integers. The concepts involves comparing far apart elements first rather than adjacent ones as in simpler interchange sorts. This tends to eliminate large amounts of disorder quickly, so later stages have to do less work. The interval between compared elements is gradually decreased to one, at which point the sort effectively becomes an adjacent interchange method.

```c
/* Shellsort: sort v[0] ... v[n-1] into increasing order */
void shellsort(int v[], int n) {
    int gap,i,j,temp;
    
    for(gap = n/2; gap > 0; gap /= 2) {
        for(i = gap; i < n; i ++) {
            for(j = i - gap; j >= 0 && v[j] > v[j+gap];j-=gap){
                temp = v[j];
                v[j] = V[j+gap];
                v[j+gap] = temp;
            }
        }  
    }
}
```

There are 3 nested loops. The outermost controls the gap between compared elements, shrinking it from n/2 by a factor of two each pass until it becomes zero. The middle loop steps along the elements. the innermost loop compare each pair of elements that is separated by gap and reverse any that are out of order. 

One final C operator is the comma ",", which most often finds use in the for statement. A pair of expressions separated by a comma is evaluated left to right, and the type and value of the result are the type and value of the right operand. This in a for statement, it is possible to place multiple expressions in the various parts, for example to process two indices in parallel. This is illustrated in the function reverse(s), which reverses the string s in place.

```c
#include <stdio.h>

/* reverse: reverse string s in place */
void reverse(char s[]) {
    int c,i,j;
    
    for(i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
	}
}
```

comma operators should be used sparingly. A comma expression might also be appropriate for the exchange of elements in reverse, where the exchange can be thought of a single operation. 

**3.7 Break and Continue**

The break statement provides an early exit from for, while, and do, just as from switch. A break causes the innermost enclosing loop switch to be exited immediately. The following function, trim  remove trailing blanks, tabs, and newline  from the end of a string, using a break to exit from a loop when the rightmost non-blank, non tab non newline is found. 

```c
int trim(char s[]) {
    int n;
    
    for(n = strlen(s)-1; n >= 0; n--;) {
        if(s[n] != ' ' && s[n] != '\t' && s[n] != '\n') {
            break;
        }
    }
    s[n+1] = '\0';
    return n;
}
```

strlen returns the length of the string. The for loop starts at the end and scans backwards looking for the first character that is not  a blank or tab or newline. 

The *continue* statement is related to break, but less often used; it causes the next iteration if the enclosing for, while, or do loop to begin. In the while and do, this means that the test part is executed immediately; in the for, control passes to the increment step.  The continue statement only applies only to loops not to switch.

as an example, this fragment processes only the non negative elements in the array a; negative values are skipped. 

```c
for(i = 0; i < n; i++) {
    if(a[i] < 0) { //skip negative elements 
        continue;
    }
    ... /* do positive elements */
}
```

**3.8 Goto and Labels**

C provides the infinitely abusable goto statement, and labels to branch to. The most common is to abandon processing in some deeply nested structure, such as breaking out of two or more loops at once. The break statement cannot be used directly since it only exits from the innermost loop. Thus:

```pseudocode
for(...) {
	for(...) {
		...
		if(disaster) {
			goto error;
		}
	}
}
...
error:
	clean up the mess 
```

A label has the same form as a variable name, and is followed by a colon. it can be attached to any statement in the same function as the goto. the scope of the label is the entire function. another example:

```c
for(i = 0; i < n; i++) {
    for(j = 0; j < m; j++) {
        if(a[i] == b[j]) {
            goto found;
        }
    }
}
/* didnt find any common element */
found: 
	/* got one: a[i] == b[j] */
	...
```

here an example without using labels and gotos below:

```c
found = 0;
for(i = 0; i < n && !found;i++) {
    for(j = 0; j < m && !found; j++) {
        if(a[i] == b[i]) {
            found = 1;
        }
    }
}
if (found) {
    /* got one: a[i-1] == b[j-1] */
    ...
} else {
    /* didint find any common element */
    ...
}
```

With few exceptions like those cited here, code that relies on goto  statements is generally harder to understand and to maintain than code without gotos. 