// #define DEBUG
// #include "FPToolkit.c"

#include "../FPToolkit/coord.h"


// appropriate for a 600x600 window
double x[13] = {263,338,338,450,338,338,375,300,225,263,263,150,263} ;
double y[13] = {450,450,375,338,338,300,150,263,150,300,338,338,375} ;
int n = 13 ;

double xp[13], yp[13];


// distance to move in x and y
void translate (double dx, double dy){
  for(int i = 0; i < n; ++i) {
    x[i] = x[i] + dx ;
    y[i] = y[i] + dy ;
  }
}

//x[i] += scale *(300-x[i]);
//where 300 is the x-coordinate at the center

// shoudl scale by any factor that you chose
// start by scaling by a third
void scale(double sx, double sy){
  

  for(int i = 0; i<n; ++i){
    x[i] = (x[i] * sx);
    y[i] = (y[i] * sy);
  }

}

void rotate(double theta){
  double temp;
  for(int i =0; i<n; ++i){
    temp = x[i];
    x[i] = x[i]*cos(theta) - y[i]*sin(theta);
    y[i] = temp*sin(theta) + y[i]*cos(theta);
  }

}

void kochCurve(Coord p0, Coord p1, double scalar, double g, int n){
  if(n<1) return;
  Coord p2, p3, p4, p5;
  double tempX, tempY;
  G_line(p0.x,p0.y, p1.x,p1.y);
  POINTER(p2.c, p2.x, p2.y);
  POINTER(p3.c, p3.x, p3.y);
  POINTER(p4.c, p4.x, p4.y);
  POINTER(p5.c, p5.x, p5.y);

  G_display_image();  
  
  tempX = p0.x; tempY=p0.y;

   p2.x= p0.x + scalar*(p1.x - p0.x);
   p2.y= p0.y + scalar*(p1.y - p0.y);
   p3.x= p1.x + scalar*(tempX - p1.x);
   p3.y= p1.y + scalar*(tempY - p1.y);

  // p4 is just the deltaX from the cutout part
  //295, 50
  p4.x = p2.x + g*(p3.x-p2.x);
  p4.y = p2.y + g*(p3.y-p2.y);
  // third point
  p5.x = p4.x - (p3.y - p2.y);
  p5.y = p4.y + (p3.x - p2.x);
  
  G_rgb(0,0,0);
  lineOfCircles(p3, p2, 1.3);
  // G_line(p2.x, p2.y, p3.x, p3.y);
  // G_line(p2.x, p2.y, p3.x, p3.y);
  G_rgb(0,0,1);
  G_line(p2.x, p2.y, p5.x, p5.y);
  G_line(p3.x, p3.y, p5.x, p5.y);
  G_display_image();  

  G_rgb(0,1,0);
  // left
  kochCurve(p0, p2, scalar, g, n-1);
  kochCurve(p2, p5, scalar, g, n-1);
  kochCurve(p5, p3, scalar, g, n-1);
  kochCurve(p3, p1, scalar, g, n-1);
  
}



int main() 
{
  int q=1;
  int centerX=300, centerY=300;
  int swidth = 600, sheight = 600;
  int n = 5;
  
  //TODO
  //ask user for depth
  
  //  G_choose_repl_display() ;
  // center is 300, 300
  G_init_graphics(swidth, sheight) ;

  G_rgb(0,0,0) ;
  G_clear() ;

  double *x1s, *y1s, *x2s, *y2s;
  Coord p0, p1, p2, p3, p4, p5;;
  POINTER(p0.c, p0.x, p0.y);
  POINTER(p1.c, p1.x, p1.y);
  POINTER(p2.c, p2.x, p2.y);

  #ifdef DEBUG
    p0 = drawClick(50, 50);
    p1 = drawClick(swidth-50, 50);
    
  #else
    G_wait_click(*p0.c);
    G_wait_click(*p1.c);
  #endif

  if(p0.x > p1.x)
    swapPoint(&p0, &p1);
  
  double base = norm(p0, p1);
  double x = base/2;
  double height = x*sqrt(3);
  double tempX, tempY;
  double scalar = 1/3.0;
  double g = sqrt(scalar*(1-scalar));
  G_rgb(1,0,0);

  kochCurve(p1, p0, scalar, g, n);
  // p4 is just the deltaX from the cutout part
  //295, 50
  p4.x = p0.x + g*(p1.x-p0.x);
  p4.y = p0.y + g*(p1.y-p0.y);
// third point
  p2.x = p4.x - (p1.y - p0.y);
  p2.y = p4.y + (p1.x - p0.x);
  kochCurve(p0, p2, scalar, g, n);
  kochCurve(p2, p1, scalar, g, n);

 
  int k = G_wait_key();
  k = G_wait_key();
}


