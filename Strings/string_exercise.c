#include <stdio.h>
#include <string.h>

// (FPToolkit.c includes these for you)

// convention :  strings in C are null-terminated character arrays

// useful string manipulation tools

char rep[] = "zzz";

char u[1000000] = {'+', '+', 'F', NULL};
char rule[100] = {'-', 'F', '+', 'F', '-', '\0'};
char TEMP[1000000] = {NULL};

char symbol[] = {'F'};

const int NUM_RULES = 1;

typedef struct {
  char var;
  char rule[100];
} Production;


typedef struct {
  char axiom[100];
  // Production prods[NUM_RULES];
} Grammar;

void string_replace(Grammar* grammar){
  int j, match, offset = 0;

  strcpy(TEMP, u);

  //erase U to be refilled
  memset(u, 0, sizeof(u));
  int len = strlen(TEMP);
  for(int i=0; i<len; i++){
    match = 0;
    //check each production rule match var and if match replace with rule value
    for(int j=0; j<NUM_RULES; ++j){
      //no match, take next character with no replacement
      if(match==0){
        
      }
    }
  }
}

void find_and_replace(char * word){
  int len = strlen(word);
  int counter = 0;
  char output[100];


  for(int i=len-1; i>=0; --i){
    if((tolower(word[i]) == 'a') || 
       (tolower(word[i]) == 'e') || 
       (tolower(word[i]) == 'i') || 
       (tolower(word[i]) == 'o') || 
       (tolower(word[i]) == 'u')
      )
    {
        ++counter;
    }
  }

  char* final;
  int len_final = len+(counter*2);
  final = (char*)malloc(sizeof(char)*(len_final+1));
  final[len_final] = '\0';

  int in = len-1;
  for(int o = len_final-1; o>=0; --o ){
    if((tolower(word[in]) == 'a') || 
      (tolower(word[in]) == 'e') || 
      (tolower(word[in]) == 'i') || 
      (tolower(word[in]) == 'o') || 
      (tolower(word[in]) == 'u')
    )
    {
      final[o--] = 'z';
      final[o--] = 'z';
      final[o] = 'z';  // for loop reduces o already
    }else 
      final[o] = word[in];
    --in;
  }

  printf("\n\nfinal word: %s\n\n", final);



}

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

  printf("The word %s has %d letters in it.\n",c,n) ;
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
  printf("The string $%s$ has %d letters in it.\n",
	 d,length) ;

}

void stringBuilder(int depth){
  if(depth < 1) return;
  printf("\nU is %s\n", u);

  char temp[100];
  int len = strlen(u);
  int j = 0, len_rule = strlen(rule);

  for(int i =0; i<len; ++i){
    if(u[i] == 'F'){
      strcat(TEMP, rule);
      // strcat(TEMP, "-F+F-");
      j += len_rule;
    } else
    {
      TEMP[j++] = u[i];
    }
    
    printf("u[i] = %c\n", (u[i]));
  }

  strcpy(u, TEMP);
  memset(TEMP, 0, strlen(TEMP));
  stringBuilder(--depth);

}

void replaceVowels(char * word){
  const int size = 100;
  char b[size];
  int j = 0;
  int len = strlen(word);
  memset(b, 0, size);
  for(int i = 0; i<len && j < size; ++i){

    if( (tolower(word[i]) == 'a') || 
        (tolower(word[i]) == 'e') || 
        (tolower(word[i]) == 'i') || 
        (tolower(word[i]) == 'o') || 
        (tolower(word[i]) == 'u')
      )
      {
        strcat(b, "zzz");
        j += 3;
      }else{
        b[j++] = word[i];
      }
  }
  strcpy(word, b);

}


int main()
{
  // char rep[] = {"zzz"};
  // char a[100];
  // printf("enter first word : ") ; 
  // scanf("%s",a);

  // printf("First word enterd: %s\n", a) ; 
  // printf("Second word entered: %s\n", rep);
  // int n = strlen(rep);
  // printf("The word %s has %d letters in it.\n",rep,n);

  // replaceVowels(a);

  stringBuilder(3);
  // find_and_replace("CAreful");
  // test01() ;
  // test02() ;
}



