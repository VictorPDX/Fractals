#include <stdio.h>
#include <string.h>

// (FPToolkit.c includes these for you)

// convention :  strings in C are null-terminated character arrays

// useful string manipulation tools



int test01()
{
  // If the user inputs the word "dog" and then the word "food"
  // what does the program print?
  int n ;
  char a[100],b[100],c[100] ;

  printf("enter first word : ") ; 
  scanf("%s",a) ;
  printf("enter second word : ") ;   
  scanf("%s",b) ;
  strcpy(c, a) ; // copies a into c
  strcat(c, b) ; // concatenates b onto c.
  n = strlen(c) ;
  
  printf("\n");
  printf("First word enterd: %s\n", a) ; 
  printf("Second word entered: %s\n", b);   
  printf("The word %s has %d letters in it.\n",c,n) ;
  printf("\n");
}




int test02()
{
  char a[1000],b[1000],c[1000],d[1000] ;
  int length ;
  
  printf("enter first word : ") ;
  scanf("%s",a) ;
  printf("enter second word : ") ;  
  scanf("%s",b) ;
  printf("enter third word : ") ;    
  scanf("%s",c) ;

  strcpy(d,a) ;
  strcat(d,"_and_") ;
  strcat(d,b) ;
  strcat(d,"_and_") ;
  strcat(d,c) ;  
  length = strlen(d) ;

  printf("\n");
  printf("First word enterd: %s\n", a) ; 
  printf("Second word entered: %s\n", b);   
  printf("Third word entered: %s\n", c);   
  printf("The string \"%s\" has %d letters in it.\n",	d, length) ;

}


int main()
{
  test01() ;
  test02() ;
}



