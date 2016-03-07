#include "bibliotheque.h"
#include "image.h"
#include <float.h>


struct gtof{
  float fr;
  float fg;
  float fb;
};

typedef struct gtof gtof ;

gtof glubytetofloat(Glubyte r, Glubyte g ,Glubyte b){
  gtof gt;
  gt.fr = r / 255 ;
  gt.fg = g / 255 ;
  gt.fb = b / 255 ;
  return gt ;
}

void range(float r,float g,float b,float max,float med,float min){
  float aux;
  // 
  if(r > g){
    max = r;
    min = g ; }
  else if (r > b){
    if (g > b){
      med = g ;
      min = b ;
      return ;
    } 
    else{
      med = b;
      min = g;
      return;
    }
  }
 //
  if(g > b ){
    max = g ;
    min = b ;
  }
  else if (r < b){
    med = b;
    min = r;
    return;
  }
  else {
    med = r;
    return; 
  }
  //
  max = b ;
  med = g ; 
  min = r ;
}

void rgb_to_hsl(Glubyte r,Glubyte g, Glybyte b,float *h ,float *s,float *l,float max ,float med ,float mini){
  /*0 A 10*/
  float delta,tmp;
  gtof gt;
  gt = glubytetofloat(r,g,b);
  range(gt.fr,gt.fg,gt.fb,&max,&med,&min);
  // L la lumiere 
  *l = (max+min)/2.0;
  if(max == min){
    *s = 0.0 ;
    *h = 0.0 ;
  }
  else {
    delta = max - min;
    //S la saturation
    *s = (*l <= 0.5) ? (delta/(max+min)) : (delta/2.0-(max+min)) ;
    //H la teinte .
    if(r == max){
      *h = (gt.fg-gt.fb)/delta ;
    }
    
    else if(g == max)
      *h = 2.0 + (gt.fb-gt.fr)/delta;
      else
	*h = 4.0 + (gt.fr-gt.fg)/delta;
    
    
    *h *= 60.0;
    
    if(*h < 0.0)
      *h += 360.0; 
  }
}	      

