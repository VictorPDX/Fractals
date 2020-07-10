#include  "../FPToolkit/FPToolkit.c"

#define POINTER(c, x, y) c[0] = &x; c[1] = &y 


// array members of structures are deeply copied. In below program deep copy happens when we returned instance is copied in main.
typedef struct {
   double x, y;
   double* c[2];
}Coord;



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



Coord midpoint(Coord p, Coord q){
   Coord temp;

   temp.x = (p.x + q.x)/2;
   temp.y = (p.y + q.y)/2;
   return temp;
}

double norm(Coord p, Coord q){
   return sqrt(pow(q.x-p.x, 2) + pow(q.y-p.y, 2) );
}

void swapPoint(Coord *p, Coord *q){   
   Coord temp;
   temp.x = q->x;
   temp.y = q->y;
   q->x = p->x;
   q->y = p->y;
   p->x = temp.x;
   p->y = temp.y;

}


void lineOfCircles(Coord p, Coord q, double r){
   if(p.x > q.x)
      swapPoint(&p, &q);
   double slopeY = (q.y-p.y);
   double slopeX = (q.x-p.x);
   double i = 0.01;
   while(p.x < q.x){
      G_fill_circle(p.x, p.y, r);
      p.x = p.x + slopeX*(i);
      p.y = p.y + slopeY*(i);
      G_display_image();  
   }
}
