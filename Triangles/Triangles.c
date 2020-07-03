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

// array members of structures are deeply copied. In below program deep copy happens when we returned instance is copied in main.
typedef struct {
   double c[2];
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
   
   G_wait_click(temp.c) ;  // gets the x and y from the click
   G_fill_circle(temp.c[0],temp.c[1],2) ; // x, y, and radius size 2
   G_display_image();  

   return temp;
}

Coord drawClick(int x, int y){
   Coord temp;
   // G_rgb(1,0,0) ; // circle colors
   
   temp.c[0] = x;
   temp.c[1] = y;
   G_fill_circle(temp.c[0],temp.c[1],2) ; // x, y, and radius size 2
   G_display_image();  

   return temp;
}


double gap(double c1, double c2, int n){
   return (c2 - c1) / n;
}

Coord midpoint(Coord p, Coord q){
   Coord temp;

   temp.c[0] = (p.c[0] + q.c[0])/2;
   temp.c[1] = (p.c[1] + q.c[1])/2;
   return temp;
}

double norm(Coord p, Coord q){
   return sqrt(pow(q.c[0]-p.c[0], 2) + pow(q.c[1]-p.c[1], 2) );
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

   int x = p.c[0] + base;
   int y = p.c[1] + height;
   temp.c[0] = x;
   temp.c[1] = y;
   temp = drawClick(x, y);


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
   printf("How many levels do you want to draw? ");
   scanf("%d", &n);
   if(n < 1){
      printf("\nERROR: Unacceptable number of circles\n");
      exit(1);
   }

   // must do this before you do 'almost' any other graphical tasks 
   swidth = 600 ;  sheight = 600 ;
   G_init_graphics (swidth,sheight) ;  // interactive graphics

   
   // clear the screen in a given color background color
   G_rgb (0, 0, 0) ; // dark black
   G_clear () ;

   // get the line from the user
   Coord p, q, v;
   
   G_rgb(1,0,0) ; // circle colors
   p = drawClick(50, 50);
   q = drawClick(550, 50);
   v = findThirdPoint(p, q);
   G_triangle(p.c[0], p.c[1], q.c[0], q.c[1], v.c[0], v.c[1]);

   Coord pq_mid = midpoint(p, q);
   Coord qv_mid = midpoint(q, v);
   Coord vp_mid = midpoint(p, v);

   for(int i = 0; i<n; ++i){
      // compute the midpoints
      pq_mid = midpoint(p, q);
      qv_mid = midpoint(q, v);
      vp_mid = midpoint(p, v);

      !(i%2)? G_rgb(0, 1, 0) : G_rgb(1, 0, 0);
      drawClick(pq_mid.c[0], pq_mid.c[1]);
      drawClick(qv_mid.c[0], qv_mid.c[1]);
      drawClick(vp_mid.c[0], vp_mid.c[1]);

      p = pq_mid;
      q = qv_mid;
      v = vp_mid;

      // fill triangle
      G_triangle(p.c[0], p.c[1], q.c[0], q.c[1], v.c[0], v.c[1]);
   }

   #ifdef DEBUG
      p.c[0] = 100;
      p.c[1] = 100;
      q.c[0] = 200;
      q.c[1] = 50;
   #endif
   
   
   int key ;   
   key =  G_wait_key() ; // pause so user can see results
   
   //   G_save_image_to_file("demo.xwd") ;
   G_save_to_bmp_file("circles.bmp") ;
}

