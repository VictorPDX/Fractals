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
struct coord{
   double c[2];
};

// double* click(double* p){
//    G_rgb(1,0,0) ; // circle colors
   
//    G_wait_click(p) ;  // gets the x and y from the click
//    G_fill_circle(p[0],p[1],2) ; // x, y, and radius size 2
//    return p;
// }

struct coord getClick(){
   struct coord temp;
   G_rgb(1,0,0) ; // circle colors
   
   G_wait_click(temp.c) ;  // gets the x and y from the click
   G_fill_circle(temp.c[0],temp.c[1],2) ; // x, y, and radius size 2
   return temp;
}

double gap(double c1, double c2, int n){
   return (c2 - c1) / n;
}

struct coord midpoint(struct coord p, struct coord q){
   struct coord temp;

   temp.c[0] = (p.c[0] + q.c[0])/2;
   temp.c[1] = (p.c[1] + q.c[1])/2;
   return temp;
}

double norm(struct coord p, struct coord q){
   return sqrt(pow(q.c[0]-p.c[0], 2) + pow(q.c[1]-p.c[1], 2) );
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
   printf("How many circles do you want to draw on the line? ");
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
   struct coord p, q;
   
   p = getClick();
   q = getClick();

   #ifdef DEBUG
      p.c[0] = 100;
      p.c[1] = 100;
      q.c[0] = 200;
      q.c[1] = 50;
   #endif
   
   G_rgb(0,1,0.5) ;
   G_line(p.c[0],p.c[1], q.c[0],q.c[1]) ;  // draw the line

   double delta[2];   // the gap is equal  to two radi or a diameter
   int gaps = n-1;
   delta[0] = gap(p.c[0], q.c[0], gaps);
   delta[1] = gap(p.c[1], q.c[1], gaps);

   struct coord firstCenter; // really first circle entirely on the line
   firstCenter.c[0] = p.c[0] + delta[0];
   firstCenter.c[1] = p.c[1] + delta[1];

   // the midpoint is the radius, from the center of the first circle to first gap
   struct coord rPt = midpoint(p, firstCenter);  // the coordinates of the radius on the line
   double r = norm(p, rPt);  

   // draw A circles
   G_rgb(0, 0, 1); // circle colors
   double cx, cy;
   cx = p.c[0] + 0;
   cy = p.c[1] + 0;
   G_circle(cx, cy, r);
   for (int i = 0; i<gaps; ++i){
      cx += delta[0];
      cy += delta[1];
      G_circle(cx, cy, r);
      G_display_image();  
   }

   gaps = n*2;

   delta[0] = gap(p.c[0], q.c[0], gaps); // the gap is equal  to two radi or a diameter
   delta[1] = gap(p.c[1], q.c[1], gaps);
   
   firstCenter.c[0] = p.c[0] + delta[0]; // the center of the first circle
   firstCenter.c[1] = p.c[1] + delta[1];

   
   r = norm(p, firstCenter);  // from p the starting point, to the center of the first circle



   // draw B circles
   G_rgb(1, 0, 0); // circle colors
   double cx2, cy2;
   cx2 = firstCenter.c[0] + 0;
   cy2 = firstCenter.c[1] + 0;
   G_circle(cx2, cy2, r);
   G_display_image();  
   for (int i = 1; i<n; ++i){
      cx2 += delta[0]*2;
      cy2 += delta[1]*2;
      // if(i%2==0){
         G_circle(cx2, cy2, r);
         G_display_image();  
      // }
   }




   
   // double gap = swidth / (n-1);

//   basicParabola(n, gap, swidth, sheight);
   // challengeParabola(n, gap, swidth, sheight);
   // double gap2 = swidth / (2*(n-1));
   // challengeParabolaRecursive(n, gap2, swidth, sheight, True, True);

   
   int key ;   
   key =  G_wait_key() ; // pause so user can see results
   
   //   G_save_image_to_file("demo.xwd") ;
   G_save_to_bmp_file("circles.bmp") ;
}

