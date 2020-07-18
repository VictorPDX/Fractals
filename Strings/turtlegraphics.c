#include <stdio.h>
#include <string.h>
#include "../FPToolkit/coord.h"

// (FPToolkit.c includes these for you)

// convention :  strings in C are null-terminated character arrays

// useful string manipulation tools

#define NUM_RULES 1

char u[1000000] = {NULL};
char TEMP[1000000] = {NULL};
int swidth = 600, sheight = 600;

Coord points[10000];

typedef struct {
  char Symbol;
  char rule[100];
  int len;
} Production;


typedef struct {
  char axiom[100];
  Production prods[NUM_RULES];
} Grammar;

void string_replace(Grammar* g, int depth){
  int k, Symbol, offset = 0;
   int len_rule;

  // strcpy(TEMP, u);

  //erase U to be refilled
  // memset(u, 0, sizeof(u));
  int len;
  for(int d = 0; d<depth; ++d){
    len = strlen(u); k =0;
    // printf("\nDepth %d: U is %s\n", d, u);
    for(int i=0; i<len; i++){ // u index
    Symbol=0;
      //check each production rule match Symbol and if match replace with rule value
      for(int j=0; j<NUM_RULES; ++j){ // check current index for symbols
        if(u[i] == g->prods[j].Symbol){
          strcat(TEMP, g->prods[j].rule);
          k += g->prods[j].len;
          ++Symbol;
        }
      }
      //no match, take next character with no replacement
      if(!Symbol){
        TEMP[k++] = u[i];      
        
      }
    }
    strcpy(u, TEMP);
    // printf("\nDepth %d: U is %s\n", d, u);
    memset(TEMP, 0, strlen(TEMP)); 
  }
}

void replaceVowels(char * word){
  const int size = 100;
  int j = 0;
  int len = strlen(word);
  char b[size];
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

// void stringBuilder(int depth){
//   int j, len;
//   int len_rule = strlen(rule);

//   for(int d = 0; d< depth; ++d){
//     j = 0; len = strlen(u);
//     for(int i =0; i<len; ++i){
//       if(u[i] == 'F'){
//         strcat(TEMP, rule);
//         // strcat(TEMP, "-F+F-");
//         j += len_rule;
//       } else
//         TEMP[j++] = u[i];      
//       printf("u[i] = %c\n", (u[i]));
//     } // end for loop
//     strcpy(u, TEMP);
//     printf("\nU is %s\n", u);
//     memset(TEMP, 0, strlen(TEMP));
//   }
// }

void stringInterpreter(double sx, double sy, double gangle, double radian, int len){
  double theta = gangle, x, y;
  for(int i=0; i<strlen(u); ++i){
    switch(u[i]){
      case '+':
        theta += radian;
        break;
      case '-':
        theta -= radian;
        break;
      default:
        x = sx + len * cos(theta);
        y = sy + len * sin(theta);
        G_line(sx, sy, x, y);
        G_display_image();  
        sx=x; sy=y;
        break;
    }
  }

}

// needs to calculate sx, sy, strech len (len is a scale factor)
// minx and miny then we know the bounding box
// need to keep track of all points
//
// ASSUME the STARTING Point is (0,0)
void autoPlacer(double sx, double sy, double gangle, double radian, double len){
  double minx=sx, miny=sy, maxX=sx, maxY=sy;
  double theta = gangle, x=sx, y=sy;
  double deltaX, deltaY, n_deltaX, n_deltaY;
  int n = strlen(u);
  int j = 1;
  points[0].x = sx;
  points[0].y = sy;
        
  for(int i=0; i<n; ++i){
    switch(u[i]){
      case '+':
        theta += radian;
        break;
      case '-':
        theta -= radian;
        break;
      default:
        x = sx + len * cos(theta);
        y = sy + len * sin(theta);
        points[j].x = x;
        points[j].y = y;
        ++j;
        if(x<minx){
          minx = x;
          printf("%d) MinX: %.0lf\n", i, minx);
          } 
        else if(x>maxX){
          maxX = x;
          printf("%d) MaxX: %.0lf\n", i, maxX);
          }
        if(y<miny){
          miny = y;
          printf("%d) MinY: %.0lf\n", i, miny);
          } 
        else if(y>maxY){
          maxY = y;
          printf("%d) MaxY: %.0lf\n", i, maxY);
          }
        G_line(sx, sy, x, y);
        G_display_image();  
        sx=x; sy=y;
        break;
    }
  }
  // we should now have the minx and maxx
  deltaX = maxX-minx;
  deltaY  = maxY-miny;

  if(deltaX>deltaY){
    n_deltaX = 0.9*swidth;
    n_deltaY =n_deltaX*deltaY/deltaX;
  }else{
    n_deltaY = 0.9*sheight;
    n_deltaX = n_deltaY*deltaX/deltaY;
  }
  sy = (sheight-n_deltaY)/2;
  sx = (swidth-n_deltaX)/2;
  G_rectangle(sx, sy, n_deltaX, n_deltaY);

  
    if (gangle <= M_PI/2){

    }else if (gangle <= M_PI){
        sx += n_deltaX;
      
    }else if (gangle <= 3 * M_PI/2){
        sy += n_deltaY;
      
    }else if (gangle <= 2 * M_PI){
      
    }
  
  double ratio = deltaX/deltaY;
  double n_ratio = n_deltaX/n_deltaY;
  double scaleX = n_deltaX/deltaX;
  double scaleY = n_deltaY/deltaY;
  G_rectangle(minx, miny, deltaX, deltaY);
  // G_rectangle(minx, miny, n_deltaX, n_deltaY); 

  // TRANSFORMATIONAL mathematics 
  // need to figure out the new sx and sy center the image
  G_display_image(); 

  // need to figure out the new step size for the larger image
  
double tx = len+sx;
double ty = len+sy;
  G_rgb(1,1,0);
  for(int i = 0; i<j; ++i){

    // scale
    G_fill_circle(points[i].x, points[i].y, 3);
    points[i].x = (points[i].x * scaleX);
    points[i].y = (points[i].y * scaleY);
    G_display_image(); 
  }

  G_rgb(1,1,1);
  int i =0;
  for(i; i<j;++i){
    //translate
    points[i].x = (points[i].x + sx);
    points[i].y = (points[i].y + sy);
    // G_fill_circle(points[i].x, points[i].y, 3);
    // if(i>0){
    //   G_line(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
    // }
    // G_display_image(); 

  }
  G_line(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
  minx = sx; miny=sy; maxX=sx; maxY=sy;
  for(int k=0; k<j; ++k){
     if(points[k].x<minx){
          minx = points[k].x;
          printf("%d) MinX: %.0lf\n", i, minx);
          } 
        else if(points[k].x>maxX){
          maxX = points[k].x;
          printf("%d) MaxX: %.0lf\n", i, maxX);
          }
        if(points[k].y<miny){
          miny = points[k].y;
          printf("%d) MinY: %.0lf\n", i, miny);
          } 
        else if(points[k].y>maxY){
          maxY = points[k].y;
          printf("%d) MaxY: %.0lf\n", i, maxY);
          }
  }
  double centerX = (maxX+minx)/2;
  double centerY = (maxY+miny)/2;
  G_rgb(1,0,0);
  // G_fill_circle(centerX, centerY, 5);
  G_display_image(); 

  G_rgb(1,1,1);
  for(int k=0; k<j; ++k){
    //translate
    points[k].x = (points[k].x - centerX);
    points[k].y = (points[k].y - centerY);
    points[k].x = (points[k].x + swidth/2);
    points[k].y = (points[k].y + sheight/2);

    G_fill_circle(points[k].x, points[k].y, 3);
    if(k>0){
      G_line(points[k-1].x, points[k-1].y, points[k].x, points[k].y);
    }
    G_display_image(); 
  }
}

// to test vertical change start angle
int main()
{
  double sangle = 0;
  double sx=0, sy=0, step = 1;
  int depth = 4, angle = 36, rules=0;
  double radian = angle * M_PI / 180.0;
  char a[100];
  double gangle = sangle * M_PI /180.0;
  Grammar g;
  


  G_init_graphics(swidth, sheight) ;
  G_rgb(0,0,0) ;
  G_clear() ;

  G_rgb(1,0,0);
  G_fill_circle(300, 300, 4);

  // printf("Enter depth: ") ; 
  // scanf("%d", &depth);


  // strcpy(g.axiom, "F");
  // strcpy(u, g.axiom);
  
  // g.prods[rules].Symbol = 'F';
  // strcpy(g.prods[rules].rule, "F+F--F+F");
  // g.prods[rules].len = strlen(g.prods[rules].rule);
  // ++rules;

  strcpy(g.axiom, "F++F++F++F++F");
  strcpy(u, g.axiom);
  
  g.prods[rules].Symbol = 'F';
  strcpy(g.prods[rules].rule, "F++F++F+++++F-F++F");
  g.prods[rules].len = strlen(g.prods[rules].rule);
  ++rules;




  // strcpy(g.axiom, "A");
  // strcpy(u, g.axiom);
  
  // g.prods[rules].Symbol = 'A';
  // strcpy(g.prods[rules].rule, "A-B-A");
  // g.prods[rules].len = strlen(g.prods[rules].rule);
  // ++rules;

  // g.prods[rules].Symbol = 'B';
  // strcpy(g.prods[rules].rule, "B+A+B");
  // g.prods[rules].len = strlen(g.prods[rules].rule);
  // ++rules;

  // printf("Enter movement unit (length): ", a) ; 
  // scanf("%d", &step);
  // printf("Enter angle: ");
  // scanf("%d", &angle);

  string_replace(&g, depth); 
  // printf("\nU is %s\n", u);
  G_rgb(0,1,0);
  autoPlacer(sx, sy, gangle, radian, step);
  
  // stringInterpreter(sx, sy, gangle, radian, step);
  // stringBuilder(2);
  // find_and_replace("CAreful");
  // test01() ;
  // test02() ;
  
  int k = G_wait_key();
  k = G_wait_key();
}



