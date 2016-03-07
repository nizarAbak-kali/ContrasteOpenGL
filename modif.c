#include "header.h"




int testColorpix(Pixels pix){
  int min,max;
  /*retourne (le v du hsv)*/
  return (pix.r+pix.g+pix.b)/3;
}

void contrasterbas(Pixels **pixcomp,int dec,unsigned long maxX,unsigned long maxY){
  printf("Pixels les plus contrastes tasses vers le bas \n");
  int i,j;
  int it,jt,value;
  Pixels pixtmp;

  for(i=0;i<maxX-dec;i+=dec){
    for(j=0;j<maxY-dec;j+=dec){
      for(jt=0;jt<=(dec*dec)-1;jt++)  
	for(it=0;it<(dec*dec)-1;it++)
	  if(testColorpix(pixcomp[i+(it/dec)][j+(it%dec)]) < testColorpix(pixcomp[i+((it+1)/dec)][j+((it+1)%dec)])){
	    pixtmp=pixcomp[i+(it/dec)][j+(it%dec)];
	    pixcomp[i+(it/dec)][j+(it%dec)]=pixcomp[i+((it+1)/dec)][j+((it+1)%dec)];
	    pixcomp[i+((it+1)/dec)][j+((it+1)%dec)]=pixtmp;
	  }
	
    }
  }
}


void contrasterhaut(Pixels **pixcomp,int dec,unsigned long maxX,unsigned long maxY){
  printf("Pixels les plus contrastes tasses vers le haut \n");
  int i,j;
  int it,jt,value;
  Pixels pixtmp;
  // int place=0;  
  //  Historique plg;
  


  for(i=0;i<maxX-dec;i+=dec){
    for(j=0;j<maxY-dec;j+=dec){
      for(jt=0;jt<=(dec*dec)-1;jt++)  
	for(it=0;it<(dec*dec)-1;it++)
	  if(testColorpix(pixcomp[i+(it/dec)][j+(it%dec)])>
	     testColorpix(pixcomp[i+((it+1)/dec)][j+((it+1)%dec)])){
	    pixtmp=pixcomp[i+(it/dec)][j+(it%dec)];
	    pixcomp[i+(it/dec)][j+(it%dec)]=pixcomp[i+((it+1)/dec)][j+((it+1)%dec)];
	    pixcomp[i+((it+1)/dec)][j+((it+1)%dec)]=pixtmp;
	  }
	
    }
  }

}

void contrastercentre(Pixels **pixcomp,int dec,unsigned long maxX,unsigned long maxY){
  printf("Pixels les plus contrastes placer au centre \n");
  int i,j;
  int it,jt,value;
  Pixels pixtmp;
  int tmp;
  //on tasse d'abord les plus lumineux en bas 
  contrasterbas(pixcomp,dec,maxX,maxY);

  //puis on deplace d'un certain nombre trouve apres un certain nombre d'observation
  for(i=0;i<maxX-dec;i+=dec)
    for(j=0;j<maxY-dec;j+=dec){
      
      tmp=(3*(dec*dec))/4;   
      while(tmp>0){
	deplacepixg(pixcomp,i,j,dec);
	tmp--;
      }  
    }
}

void contrasterperipherie(Pixels **pixcomp,int dec,unsigned long maxX,unsigned long maxY){
  printf("Pixels les plus contrastes placer a la peripherie \n");
  int i,j;
  int it,jt,value;
  Pixels pixtmp;
  int tmp;
  // on tasse vers le bas
  contrasterbas(pixcomp,dec,maxX,maxY);

  for(i=0;i<maxX-dec;i+=dec)
    for(j=0;j<maxY-dec;j+=dec){
      value=testColorpix(pixcomp[i+dec-1][j+dec-1]);
     
      for(it=0;it<(dec*dec)-1;it++)
	if(value==testColorpix(pixcomp[i+(it/dec)][j+(it%dec)]))
	  break;  
      
      tmp=(dec*dec)/2;   
      //on deplace les pixels 
      while(tmp>0){
	deplacepixd(pixcomp,0,0,dec);
	tmp--;
      }  
      //on fait pivoter vers la gauche
      pivoteg(pixcomp,i,j,dec,maxX,maxY);

    }
}


void deplacepixg(Pixels** pixcomp,int maxi,int maxj,int dec){
  Pixels pixtmp;
  int it,i,j;

  /*chaque pixel vaut son suivant et le dernier sera premier  */
  //Il s'agit d'une fenetre est circulaire 
  pixtmp=pixcomp[maxi][maxj];

  for(it=0;it<dec*dec-1;it++){
    i=(it+1)/dec;
    j=(it+1)%dec;
    pixcomp[maxi+(it/dec)][maxj+(it%dec)]=pixcomp[maxi+i][maxj+j];
  }
    pixcomp[maxi+(it/dec)][maxj+(it%dec)]=pixtmp;

}

void deplacepixd(Pixels** pixcomp,int maxi,int maxj,int dec){
  Pixels pixtmp;
  int it,i,j;
  /*chaque pixel vaut son suivant et le premier sera dernier*/
  pixtmp=pixcomp[maxi+dec-1][maxj+dec-1];

for(it=dec*dec-1;it>0;it--){
    i=(it-1)/dec;
    j=(it-1)%dec;
    pixcomp[maxi+(it/dec)][maxj+(it%dec)]=pixcomp[maxi+i][maxj+j];
  }
  
pixcomp[maxi+i][maxj+j]=pixtmp;

}


void pivoteg(Pixels** pixcomp,int maxi,int maxj,int dec,unsigned long maxX,unsigned long maxY){
  Pixels pixtmp[dec][dec];
  int i,j;    
  for(i=0;i<dec;i++)
    for(j=0;j<dec;j++)
      pixtmp[dec-j-1][i]=pixcomp[i+maxi][j+maxj];
  

  for(i=0;i<dec;i++)
    for(j=0;j<dec;j++)
      pixcomp[maxi+i][j+maxj]=pixtmp[i][j];

}
void pivoted(Pixels** pixcomp,int maxi,int maxj,int dec,unsigned long maxX,unsigned long maxY){ 
  Pixels pixtmp[dec][dec];
  int i,j;    
  for(i=0;i<dec;i++)
    for(j=0;j<dec;j++)
      pixtmp[i][j]=pixcomp[j+maxi][(i%(dec-1))+maxj];
  

  for(i=0;i<dec;i++)
    for(j=0;j<dec;j++)
      pixcomp[maxi+i][j+maxj]=pixtmp[i][j];

}

void noir_blanc(Pixels **pixcomp,unsigned long maxX,unsigned long maxY){
  printf("Image en noir et blanc\n"); 
  int i,j,moy;
  for(i=0;i<maxX;i++){
    for(j=0;j<maxY;j++){

      moy=(pixcomp[i][j].r+pixcomp[i][j].g+pixcomp[i][j].b)/3;
      if(moy<127){
	pixcomp[i][j].r=0;
	pixcomp[i][j].b=0;
	pixcomp[i][j].g=0;
      } 
      else{
	pixcomp[i][j].r=255;
	pixcomp[i][j].b=255;
	pixcomp[i][j].g=255;
      }
    }
  }
  
}

void untrait(Pixels **pixcomp,unsigned long maxX,unsigned long maxY){
int i,j;
Pixels pix;
pix.r=0;
pix.b=0;
pix.g=0;
  for(i=0;i<maxX;i++)
    for(j=0;j<maxY;j++)
if(i==j)pixcomp[i][j]=pix;


}


void chaleur(Pixels **pixcomp,unsigned long maxX,unsigned long maxY){
  printf("la Chaleur est resortie \n");
  int i,j;
  for(i=0;i<=maxX;i++){
    for(j=0;j<=maxY;j++){
      if(pixcomp[i][j].r<pixcomp[i][j].b&&pixcomp[i][j].r<pixcomp[i][j].g){
	pixcomp[i][j].g=0;
	pixcomp[i][j].b=0;
	continue;
      }
      pixcomp[i][j].g=0;
      pixcomp[i][j].r=0;

    }  
  }
  
}
  

void chaleur_clavier(Pixels **pixcomp,unsigned long maxX,unsigned long maxY){

  int i,j;
  for(i=0;i<=maxX;i++){
    for(j=0;j<=maxY;j++){
      if(pixcomp[i][j].r<pixcomp[i][j].b&&pixcomp[i][j].r<pixcomp[i][j].g)
	pixcomp[i][j].r--;

      if(pixcomp[i][j].b<pixcomp[i][j].r&&pixcomp[i][j].b<pixcomp[i][j].g)
	pixcomp[i][j].b--;
  
      if(pixcomp[i][j].g<pixcomp[i][j].b&&pixcomp[i][j].g<pixcomp[i][j].g)
	pixcomp[i][j].g--;
    }  
  }
  
}

void froideur_clavier(Pixels **pixcomp,unsigned long maxX,unsigned long maxY){

  int i,j;
  for(i=0;i<=maxX;i++){
    for(j=0;j<=maxY;j++){
  	
      if(pixcomp[i][j].r>pixcomp[i][j].b&&pixcomp[i][j].r>pixcomp[i][j].g)
	pixcomp[i][j].r++;

      if(pixcomp[i][j].b>pixcomp[i][j].r&&pixcomp[i][j].b>pixcomp[i][j].g)
	pixcomp[i][j].b++;
  
      if(pixcomp[i][j].g>pixcomp[i][j].b&&pixcomp[i][j].g>pixcomp[i][j].g)
	pixcomp[i][j].g++;
    }  
  }
}
  

void griser(Pixels **pixcomp,unsigned long maxX,unsigned long maxY){
  int i,j;
  for(i=0;i<=maxX;i++){
    for(j=0;j<=maxY;j++){
      pixcomp[i][j].r=pixcomp[i][j].g;
      pixcomp[i][j].b=pixcomp[i][j].g;
    }  
  }
}

void copie_data(Pixels**linepix,Image *img){
  int i,j,c=0;
  for(i=0;i<img->sizeX;i++){  
    for(j=0;j<img->sizeY;j++){  
      linepix[i][j].r=img->data[c++];    
      linepix[i][j].g=img->data[c++];    
      linepix[i][j].b=img->data[c++];    
      linepix[i][j].use=0;
    }
  }
}


