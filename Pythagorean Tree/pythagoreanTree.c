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


double solveHeight(double BC, double CD){
   double AC;
   AC = sqrt(BC*CD);
   
   double height;
   height = sqrt(AC*AC - CD*CD);
   return height;
}

Coord newCoord(double x, double y){
   Coord temp;
   temp.x = x;
   temp.y = y;
   POINTER(temp.c, temp.x, temp.y);
   return temp;
}


int main()
{
   int    swidth, sheight ;
   double lowleftx, lowlefty, width, height ;
   double x[10], y[10] ;
   double numxy ;
   double a[20], b[20] ;
   double numab ;

//       // must do this before G_init_graphics() if using repl.it
//    G_choose_repl_display() ;

   int n;
   // printf("How many levels do you want to draw? ");
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

   // get the line from the user
   Coord p1, p2, v;
   POINTER(p1.c, p1.x, p1.y);
   POINTER(p2.c, p2.x, p2.y);
   POINTER(v.c, v.x, v.y);
   
   
   #ifdef DEBUG
      // p1.x = 500;
      // p1.y = 500;
      // p2.x = 200;
      // p2.y = 200;
      p1 = drawClick(200, 100);
      p2 = drawClick(300, 100);
   #else

      G_wait_click(*p1.c);
      G_wait_click(*p2.c);
   
   #endif

   Gi_rgb(205, 133, 63) ; // trunk color
   // create first square outside recursive function
   Coord p3, p4;
   double BC = norm(p1, p2);
   p3.x = p1.x; p3.y = p1.y + BC;
   p4.x = p2.x; p4.y = p2.y + BC;
   G_fill_rectangle(p1.x, p1.y, BC, BC);

   // Generate Point 2  & 3

   //dx = x1-x0
   double CD = .4 * BC;
   double theight;
   theight = solveHeight(BC, CD);

   Coord p5 = newCoord(p4.x - CD, p4.y + theight);
   G_triangle(p3.x, p3.y, p4.x, p4.y, p5.x, p5.y);

   // create right triangle using P2 and P3



   int key ;   
   key =  G_wait_key() ; // pause so user can see results
   
   //   G_save_image_to_file("demo.xwd") ;
   G_save_to_bmp_file("tree.bmp") ;
}

