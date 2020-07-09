#define DEBUG
/*
    FPToolkit.c : A simple set of graphical tools.
    FPToolkitDemo.c 
    Copyright (C) 2018  Ely

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License (version 3)
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/





/*

This code assumes an underlying X11 environment.

       Most freshly installed unbuntu environments do not have
       the X11 developr stuff they'll need to do graphics.
       To download X11 developer stuff, connect to the internet and 
       issue the following two commands.  Each will ask for your password
       and each will take a few minutes.  At some point it might even
       look like nothing is happening....be patient :
       
sudo  apt-get  install  libx11-dev     

sudo  apt-get  install  xorg-dev

*/




/*
If this file and the file, FPToolkit.c, are in the
same directory that you are trying to compile in,  
do the following :

cc  FPToolkitDemoB.c   -lm  -lX11

NOTE: The 'X' in -lX11 is capitalized
*/


#include  "../FPToolkit/FPToolkit.c"

#define POINTER(c, x, y) c[0] = &x; c[1] = &y 
// array members of structures are deeply copied. In below program deep copy happens when we returned instance is copied in main.
typedef struct {
   double x, y;
   double* c[2];
}Coord;




// double* click(double* p){
//    G_rgb(1,0,0) ; // circle colors
   
//    G_wait_click(p) ;  // gets the x and y from the click
//    G_fill_circle(p[0],p[1],2) ; // x, y, and radius size 2
//    return p;
// }

Coord getClick(){
   Coord temp;
   // G_rgb(1,0,0) ; // circle colors
   
   G_wait_click(*temp.c) ;  // gets the x and y from the click
   G_fill_circle(temp.x,temp.y,2) ; // x, y, and radius size 2
   G_display_image();  

   return temp;
}

Coord drawClick(int x, int y){
   Coord temp;
   // G_rgb(1,0,0) ; // circle colors
   
   temp.x = x;
   temp.y = y;
   G_fill_circle(temp.x,temp.y,2) ; // x, y, and radius size 2
   G_display_image();  
   printf("Mid point(%d, %d)\n",x,y);

   return temp;
}


double gap(double c1, double c2, int n){
   return (c2 - c1) / n;
}

Coord midpoint(Coord p, Coord q){
   Coord temp;

   temp.x = (p.x + q.x)/2;
   temp.y = (p.y + q.y)/2;
   return temp;
}

double norm(Coord p, Coord q){
   return sqrt(pow(q.x-p.x, 2) + pow(q.y-p.y, 2) );
}



Coord findThirdPoint(Coord p, Coord q){
   Coord temp;
   double lineSize = norm(p, q);
   double hypothenus = lineSize;
   double base = lineSize/2.0;
   printf("Hypothenus = %.0f\n", lineSize);
   printf("Base = %.0f\n", base);

   // opposite is height
   double angle = 60;
   double radians = angle * M_PI/180;
   // tan 60 = Opposite/adjecent;
   double height = tan(radians) * base;
   // double height = sqrt(pow(hypothenus, 2) - pow(base, 2) );

   temp.x = p.x;
   temp.y = q.y;
   // temp = drawClick(temp.x, temp.y);


   return temp;

}




void printNgon(Coord p0, double r, int n){
   double radians = 2*M_PI;
   double theta = radians/(float)n;
   
   double *xs, *ys;
   xs = (double*)malloc(sizeof(double)*n);
   ys = (double*)malloc(sizeof(double)*n);
   
   for(int i = 0; i<n; ++i){
      xs[i] = p0.x + r * cos(i*theta + M_PI/(float)n);
      ys[i] = p0.y + r * sin(i*theta + M_PI/(float)n);
      drawClick(xs[i], ys[i]);
   }

   G_rgb(0,1,0);
   G_polygon(xs, ys, n);
}

void myPixelCircle(Coord p0, Coord p1){
   double r = norm(p0, p1);
   double radians = 2*M_PI;
   double theta = radians;
   
   double x, y;
   
   for(double i = 0; i<radians; i+=0.001){
      x = p0.x + r * cos(i*theta);
      y = p0.y + r * sin(i*theta);
      G_point(x, y);
      G_display_image();  
   }
}


void myPixelEllipse(Coord p0, Coord p1, Coord p2, double a, double b){
   
   double radians = 2*M_PI;
   double theta = radians;

   double x, y;
   G_rgb(1,0,0);
   for(double i = 0; i<radians; i+=0.005){
      x = p0.x + a * cos(i*theta);
      y = p0.y + b * sin(i*theta);
      drawClick(x, y);
      G_point(x, y);
      G_display_image();  
   }
   
   // theta = radians/(float)n;
    
   // for(int i = 0; i<n; ++i){
   //    x1s[i] = p0.x + a * cos(i*theta);
   //    y1s[i] = p0.y + b * sin(i*theta);
   //    drawClick(x, y);
   // }

}

void getNgonPoints(Coord p0, double a, double b, int n, double * xs, double * ys){
   double radians = 2*M_PI;
   double theta = radians/(float)n;
   
   G_rgb(0,1,0);
   for(int i = 0; i<n; ++i){
      xs[i] = p0.x + a * cos(i*theta + M_PI/(float)n);
      ys[i] = p0.y + b * sin(i*theta + M_PI/(float)n);
      drawClick(xs[i], ys[i]);
   }
   
}


void connectEllipseLines(double* x1s, double* y1s, double* x2s, double* y2s, int n){
   G_rgb(0,1,0);
   for(int i = 0; i<n; ++i){
      G_line(x1s[i], y1s[i], x2s[i], y2s[i]);
   }
}





int main()
{
   int    swidth, sheight ;
   double width, height ;
   

//       // must do this before G_init_graphics() if using repl.it
//    G_choose_repl_display() ;

   int n=8;
   // printf("What degree polynomial would you like to build? ");
   // scanf("%d", &n);
   // if(n < 1){
   //    printf("\nERROR: Unacceptable number of circles\n");
   //    exit(1);
   // }

   // must do this before you do 'almost' any other graphical tasks 
   swidth = 600 ;  sheight = 600 ;
   G_init_graphics (swidth,sheight) ;  // interactive graphics

   
   // clear the screen in a given color background color
   G_rgb (0, 0, 0) ; // dark black
   G_clear () ;

   G_rgb(1,0,0) ; // circle colors
   // get the line from the user
   double *x1s, *y1s, *x2s, *y2s;
   Coord p0, p1, p2, p3, p4, p5;;
   POINTER(p0.c, p0.x, p0.y);
   POINTER(p1.c, p1.x, p1.y);
   POINTER(p2.c, p2.x, p2.y);

   POINTER(p3.c, p3.x, p3.y);
   POINTER(p4.c, p4.x, p4.y);
   POINTER(p5.c, p5.x, p5.y);
   x1s = (double*)malloc(n*sizeof(double));
   y1s = (double*)malloc(n*sizeof(double));
   x2s = (double*)malloc(n*sizeof(double));
   y2s = (double*)malloc(n*sizeof(double));
   

   #ifdef DEBUG
      p0 = drawClick(300, 450);
      p1 = drawClick(400, 450);
      p2 = drawClick(300, 500);
   #else
      G_wait_click(*p0.c);
      G_wait_click(*p1.c);
   #endif
  
   double a = norm(p0, p1);
   double b = norm(p0, p2);

   // myPixelCircle(p0, p1);

   #ifdef DEBUG
      p3 = drawClick(300, 150);
      p4 = drawClick(400, 150);
      p5 = drawClick(300, 200);
   #else
      G_wait_click(*p0.c);
      G_wait_click(*p1.c);
   #endif
   double r1 = norm(p3, p4);
   double r2 = norm(p3, p5);

   myPixelEllipse(p0, p1, p2, a, b);
   getNgonPoints(p0, a, b, n, x1s, y1s);
   myPixelEllipse(p3, p4, p5, a, b);
   getNgonPoints(p3, a, b, n, x2s, y2s);

   int key ;
   double tempX, tempY;   
   for(int i = 0; i<n; ++i){
   


      connectEllipseLines(x1s, y1s, x2s, y2s, n);
      key =  G_wait_key() ; // pause so user can see results
      tempX = x2s[0]; tempY = y2s[0];
      for(int j = 0; j<n; ++j){
         x2s[j] = x2s[j+1];
         y2s[j] = y2s[j+1];
      }
      x2s[n-1]=tempX; y2s[n-1]=tempY;
      G_rgb(0,0,0);
      G_clear();
      myPixelEllipse(p0, p1, p2, a, b);
      myPixelEllipse(p3, p4, p5, a, b);
      
   }
   connectEllipseLines(x1s, y1s, x2s, y2s, n);
   


//   printNgon(p0, r, n);

//    G_rgb(.2,.4,.6);
//    G_circle(p0.x, p0.y, r);

   

   
   key =  G_wait_key() ; // pause so user can see results
   
   //   G_save_image_to_file("demo.xwd") ;
   G_save_to_bmp_file("drum.bmp") ;
}

