
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

void basicParabola(int n, int gap, int swidth, int sheight);
void challengeParabola(int n, int gap, int swidth, int sheight);


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
   printf("How many lines do you want to draw? ");
   scanf("%d", &n);
   // must do this before you do 'almost' any other graphical tasks 
   swidth = 600 ;  sheight = 600 ;
   G_init_graphics (swidth,sheight) ;  // interactive graphics

   
   // clear the screen in a given color background color
   G_rgb (0.3, 0.3, 0.3) ; // dark gray
   G_clear () ;

   
   double gap = swidth / (n-1);

//   basicParabola(n, gap, swidth, sheight);
   challengeParabola(n, gap, swidth, sheight);
   double gap2 = swidth / (2*(n-1));
   challengeParabolaRecursive(n, gap2, swidth, sheight, True, True);

   
   int key ;   
   key =  G_wait_key() ; // pause so user can see results
   
   //   G_save_image_to_file("demo.xwd") ;
   G_save_to_bmp_file("demo.bmp") ;
}



void basicParabola(int n, int gap, int swidth, int sheight){
 int x1, x2, y1, y2;
   x1 = y1 = y2 = 0;
   x2 = swidth-1; // the first line ends on the right horizontal

   for(int i = 0; i < n; ++i){
      G_rgb(1,0,0);
      G_fill_circle(x1, y1, 5);
      G_fill_circle(x2, y2, 5);

      G_rgb(0,1,0);
      G_line(x1, y1, x2, y2);
      // x1 does not chage as we go up
      y1 += gap;
      if(y1 >599) y1=599;

      //y2 does not change as it comes closer to the origin
      x2 -= gap;
      if(x2 < 0) x2=0;

      // int key ;   
      // key =  G_wait_key() ; // pause so user can see results
   }
   G_save_to_bmp_file("basic.bmp") ;

} //end basic


void challengeParabola(int n, int gap, int swidth, int sheight){
    int x1, x2, y1, y2;
   x1 = swidth/2;
   y1 = sheight/2;  // at at the centere of the screen

   x2 = swidth-1; // the first line ends on the right horizontal
   y2 = sheight/2;
   double gap2 = swidth / (2*(n-1));

    for(int i = 0; i < n; ++i){
      G_rgb(1,0,0);
      G_fill_circle(x1, y1, 5);
      G_fill_circle(x2, y2, 5);

      G_rgb(0,1,0);
      G_line(x1, y1, x2, y2);
      // x1 does not chage as we go up
      y1 += gap2;
      if(y1 >599) y1=599;

      //y2 does not change as it comes closer to the origin
      x2 -= gap2;
      if(x2 < 0) x2=0;

      // int key ;   
      // key =  G_wait_key() ; // pause so user can see results
   }
   y1 -= gap2; // come back down
   for(int i = 0; i < n-1; ++i){
      G_rgb(1,0,0);
      G_fill_circle(x1, y1, 5);
      G_fill_circle(x2, y2, 5);

      G_rgb(0,1,0);
      G_line(x1, y1, x2, y2);
      // x1 does not chage as we go up
      y1 -= gap2;
      if(y1 <0) y1=0;

      //y2 does not change as it comes closer to the origin
      x2 -= gap2;
      if(x2 <0) x2=0;

      // int key ;   
      // key =  G_wait_key() ; // pause so user can see results
   }

   x2 += gap2; // go backwards now
  for(int i = 0; i < n-1; ++i){
      G_rgb(1,0,0);
      G_fill_circle(x1, y1, 5);
      G_fill_circle(x2, y2, 5);

      G_rgb(0,1,0);
      G_line(x1, y1, x2, y2);
      // x1 does not chage as we go up
      y1 -= gap2;
      if(y1 <0) y1=0;

      //y2 does not change as it comes closer to the origin
      x2 += gap2;
      if(x2 >599) x2=599;

      // int key ;   
      // key =  G_wait_key() ; // pause so user can see results
   }
 y1 += gap2; // come back up
  for(int i = 0; i < n-1; ++i){
      G_rgb(1,0,0);
      G_fill_circle(x1, y1, 5);
      G_fill_circle(x2, y2, 5);

      G_rgb(0,1,0);
      G_line(x1, y1, x2, y2);
      // x1 does not chage as we go up
      y1 += gap2;
      if(y1 >599) y1=599;

      //y2 does not change as it comes closer to the origin
      x2 += gap2;
      if(x2 >599) x2=599;

      // int key ;   
      // key =  G_wait_key() ; // pause so user can see results
   }


   G_save_to_bmp_file("challenge.bmp") ;
}


void challengeParabolaRecursive(int n, int gap, int swidth, int sheight, _Bool upward, _Bool leftward){
int x1, x2, y1, y2;
   x1 = swidth/2;
   y1 = sheight/2;  // at at the centere of the screen

   x2 = swidth-1; // the first line ends on the right horizontal
   y2 = sheight/2;
   

    for(int i = 0; i < n; ++i){
      G_rgb(1,0,0);
      G_fill_circle(x1, y1, 5);
      G_fill_circle(x2, y2, 5);

      G_rgb(0,1,0);
      G_line(x1, y1, x2, y2);
      // x1 does not chage as we go up
      y1 = (upward)? y1+gap : y1-gap;
      if(y1 >599) y1=599;

      //y2 does not change as it comes closer to the origin
      x2 = (leftward)? x2-gap : x2+gap;
      if(x2 < 0) x2=0;

      // int key ;   
      // key =  G_wait_key() ; // pause so user can see results
   }
}
















int main()
 {
     int n, swidth, sheight;
     double x, y, gap, xcenter, ycenter;
     sheight = swidth = 600;
     xcenter = ycenter = sheight / 2;

     printf("Please enter the number of lines \n");
     scanf("%d",&n);
     G_init_graphics(swidth,sheight);

     gap = sheight / (2 * n);
     G_rgb (0.3, 0.3, 0.3) ; // dark gray

     for(int i = 0; i <= n; ++i){
       if (i == 0) {
           G_rgb(0,1,0);
           G_line (xcenter, sheight, xcenter, 0);
       }
       else {
           x = (gap * i);
           y = sheight - x;
           G_rgb(0,1,0);
           G_line (xcenter, y, xcenter - x, ycenter);
           G_line (xcenter, y, xcenter + x, ycenter);
           G_line (xcenter, x, xcenter - x, ycenter);
           G_line (xcenter, x, xcenter + x, ycenter);
      // int key ;   
      // key =  G_wait_key() ; // pause so user can see results
       }
     }

    int key ;
    key =  G_wait_key() ; // pause so user can see results

    //G_save_image_to_file("demo.xwd") ;
    G_save_to_bmp_file("demo.bmp") ;
 }