// #define DEBUG
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

   G_rgb(1,0,0) ; // circle colors
   // get the line from the user
   Coord p, q, v;
   POINTER(p.c, p.x, p.y);
   POINTER(q.c, q.x, q.y);
   POINTER(v.c, v.x, v.y);

   #ifdef DEBUG
      // p.x = 500;
      // p.y = 500;
      // q.x = 200;
      // q.y = 200;
      p = drawClick(500, 500);
      q = drawClick(200, 200);
   #else

   G_wait_click(*p.c);
   G_wait_click(*q.c);
   
   #endif
   // p.x = &p.x;
   // p.y = &p.y;
   // q.x = &q.x;
   // q.y = &q.y;
   
   if(q.x > p.x){
      Coord temp;
      temp.x = p.x;
      temp.y = p.y;
      p.x = q.x;
      p.y = q.y;
      q.x = temp.x;
      q.y = temp.y;

   }
   
   v = findThirdPoint(p, q);
   G_rgb(.2,.4,.6);
   // G_triangle(p.x, p.y, q.x, q.y, v.x, v.y);
   // G_display_image();  

   double theight = norm(p, v);
   G_rgb(1,0,0);
   G_fill_rectangle(v.x, v.y, theight, theight);
   G_display_image();  
   
   double base = norm(q, v);
   Coord bp;
   bp.y = q.y - base;
   bp.x = q.x;
   G_rgb(0,1,0);
   G_fill_rectangle(bp.x, bp.y, base, base);
   G_display_image();  

   double hyp = norm(q, p);
   double z = sqrt(2*hyp*hyp);
   double xp[4], yp[4];
   double num = 4;
   xp[0] = q.x;       yp[0] = q.y;
   xp[1] = p.x;       yp[1] = p.y;
   
   xp[2] = p.x - base;       yp[2] = p.y+  theight;
   xp[3] = q.x - base;       yp[3] = q.y+  theight;
   G_rgb(0,0,1);
   G_fill_polygon (xp,yp,num) ; // x and y are double arrays


   int key ;   
   key =  G_wait_key() ; // pause so user can see results
   
   //   G_save_image_to_file("demo.xwd") ;
   G_save_to_bmp_file("pythagorean_Theorem.bmp") ;
}

