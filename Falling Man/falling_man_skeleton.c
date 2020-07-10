// #include "FPToolkit.c"

#include  "../FPToolkit/FPToolkit.c"


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



int main() 
{
  int q ;
  int centerX=300, centerY=300;

  //  G_choose_repl_display() ;
  // center is 300, 300
  G_init_graphics(600, 600) ;

  G_rgb(0,0,0) ;
  G_clear() ;

  // G_rgb(0,0,1) ;
  // G_fill_polygon(x,y,n) ;
  // q = G_wait_key() ;

//step 1
  // move it to the right but not up or down
  // scale(x, y, 0.3);
  // translate(-centerX, -centerY) ; // need to move it to the origin first!!
  // scale(0.3,  0.3);   // then it is ok to scale it
  // rotate(M_PI/6);
  // translate(centerY, centerY) ;
  // // translate(150, 0) ;
  double r=0.5, g, b;
  double fade = 0.01;
  double theta = M_PI/100;
  while(q!='q'){
    G_rgb(r,0,1);
    (q=='j')? (r -= fade) : (r += fade);
    G_fill_polygon(x,y,n) ;
    q = G_wait_key() ;
    
    translate(-centerX, -centerY) ; 
    (q=='j')? scale(0.98,  0.98) : scale(1.02, 1.02); 
    (q=='j')? rotate(theta) : rotate(-theta);
    translate(centerY, centerY) ;

    G_rgb(0,0,0) ;
    G_clear();
  }



}


