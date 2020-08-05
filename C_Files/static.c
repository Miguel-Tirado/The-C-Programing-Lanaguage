
// C program to demonstrate 
// Internal Static Variables 
  
#include <stdio.h> 
  
int value(); 
  
int main() 
{ 
    printf("%d", value()); 
    return 0; 
} 
  
int value() 
{ 
    int a = 5; 
    return a; 
} 
