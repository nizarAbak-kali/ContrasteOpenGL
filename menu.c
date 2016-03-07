#include "header.h"

Image* monimage;
char* nomdeImage;
int decoupage=3;
Pixels **pixcomp;
//Historique **histo;

void principale(int argc,char **argv){ 	 

  monimage=(Image*)malloc(sizeof(Image));
  nomdeImage=argv[1];

  if(LoadBMP(nomdeImage,monimage)==-1){
    free(monimage);
    return;
  }

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA /*| GLUT_DEPTH*/);
  glutInitWindowPosition(200, 150);
  glutInitWindowSize(500, 512);
  glutCreateWindow("Image et Constraste");
  glutReshapeWindow(monimage->sizeX,monimage->sizeY);
  pixcomp=datachange(monimage);  /*contenu de l'image en 2d*/
  glutCreateMenu(menu);
  glutAddMenuEntry("Informations", 0);

  glutAddMenuEntry("Constraste haut", 1);
  glutAddMenuEntry("Constraste bas", 2);
  glutAddMenuEntry("Constraste centre",3);
  glutAddMenuEntry("Constraste peripherie",4);
  glutAddMenuEntry("Rotation gauche",5);
  glutAddMenuEntry("Rotation droite",6);
  glutAddMenuEntry("Decalage gauche",7);
  glutAddMenuEntry("Decalage droite",8);

  glutAddMenuEntry("Trait", 10);
  glutAddMenuEntry("Chaleur", 11);
  glutAddMenuEntry("Gris", 12);
  glutAddMenuEntry("Noir et Blanc(contraste)", 13);
  glutAddMenuEntry("Inverse", 14);
  
  glutAddMenuEntry("Ouvrir", 15);
  glutAddMenuEntry("Sauvegarder", 16);
  glutAddMenuEntry("Annuler", 17);
  glutAddMenuEntry("Quit", 18);

  glutAttachMenu(GLUT_LEFT_BUTTON);
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier); 
  glutMainLoop();
}


void menu(int choix){
  int i , j,nbdec;
  char l[256];
  switch(choix){
  case 0:
    printf("Nom de l'image:%s\nTaille de l'image: %ld %ld\n",nomdeImage,monimage->sizeX, monimage->sizeY);
    break;


  case 1:
    printf("Pixels les plus contrastes tasses vers le haut \n");  
    printf("Veuillez saisir le decoupage\n");
    scanf("%d",&decoupage);
    contrasterhaut(pixcomp,decoupage,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;

 
  case 2:
    printf("Pixels les plus contrastes tasses vers le bas \n");
    printf("Veuillez saisir le decoupage\n");
    scanf("%d",&decoupage);  
    contrasterbas(pixcomp,decoupage,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;

  case 3:
    printf("Pixels les plus contrastes tasses au centre\n");
    printf("Veuillez saisir le decoupage\n");
    scanf("%d",&decoupage);  
    contrastercentre(pixcomp,decoupage,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;

  case 4:
    printf("Pixels les plus contrastes tasses sur les bords gauche et droite\n");
    printf("Veuillez saisir le decoupage\n");
    scanf("%d",&decoupage);  
    contrasterperipherie(pixcomp,decoupage,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;


  case 5:
    printf("ROTATION GAUCHE\n"); 
    printf("Veuillez saisir le decoupage\n");
    scanf("%d",&decoupage);
    printf("veuillez saisir la ligne :\n");
    scanf("%d",&i);
    printf("veuillez saisir la colonne :\n");
    scanf("%d",&j); 
    pivoteg(pixcomp,i,j,decoupage,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;

  case 6:
    printf("ROTATION DROITE\n");
    printf("Veuillez saisir le decoupage\n");
    scanf("%d",&decoupage);
    printf("veuillez saisir la ligne :\n");
    scanf("%d",&i);
    printf("veuillez saisir la colonne :\n");
    scanf("%d",&j); 
    printf("test\n");
    pivoted(pixcomp,i,j,decoupage,monimage->sizeX,monimage->sizeY);
    printf("fini\n");
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;

  case 7:
    printf("Veuillez saisir le decoupage\n");
    scanf("%d",&decoupage);
    printf("veuillez saisir la ligne :\n");
    scanf("%d",&i);
    printf("veuillez saisir la colonne :\n");
    scanf("%d",&j); 
    printf("Veuillez sasir le nombre de fois que vous allez effectuer l'operation de decalage\n");
    scanf("%d",&nbdec);
    while(nbdec--)
      deplacepixg(pixcomp,i,j,decoupage);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;

  case 8:
   
    printf("Veuillez saisir le decoupage\n");
    scanf("%d",&decoupage);
    printf("veuillez saisir la ligne :\n");
    scanf("%d",&i);
    printf("veuillez saisir la colonne :\n");
    scanf("%d",&j); 
    printf("Veuillez sasir le nombre de fois que vous allez effectuer l'operation\n");
    scanf("%d",&nbdec);
    while(nbdec--)
      deplacepixd(pixcomp,i,j,decoupage);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;


case 10:
	printf("Un trait\n");
    untrait(pixcomp,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();	
	break;

  case 11:
    printf("IMAGE RECHAUFFE AUTOMATIQUEMENT\n");
    chaleur(pixcomp,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;

  case 12:
    printf("IMAGE GRISER\n");
    griser(pixcomp,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;

  case 13:
    printf("Image mise en noir et blanc\n");
    noir_blanc(pixcomp,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
    break;

  case 14:
    printf("INVERSION\n");
    datachange_AfterEffect(monimage,pixcomp,0);
    copie_data(pixcomp,monimage);
    affichage();
    break;

  case 15:
    printf("OUVRIR\n");
    printf("Veuillez entrer chemin d'accès de votre image:\n");
    scanf("%s",l);
    LoadBMP(l,monimage);
    nomdeImage=l;
    pixcomp=datachange(monimage);
    affichage();
    glutReshapeWindow(monimage->sizeX,monimage->sizeY);
    break;

  case 16:
    printf("SAUVEGARDE\n");
    save(monimage);
    break;



  case 17:
    printf("Annulation de toutes les operations\n");
    LoadBMP(nomdeImage,monimage);
    copie_data(pixcomp,monimage);
    affichage();
    break;

  case 18:
    printf("EXIT\n");
    free(monimage);
    free(pixcomp);  
    exit(0);
    break;
  
  default:
    printf("ce choix n'existe pas\n");
    break;
  }
}

void use_erreur(){
  printf("Erreur d'utilisation\n");
  printf("Usage: ./ex cheminImage\n");
  exit(-1);
}


void affichage(){
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(monimage->sizeX, monimage->sizeY, GL_RGB, GL_UNSIGNED_BYTE,  monimage->data);
  glFlush();
  glutSwapBuffers();
}


void clavier(unsigned char touche,int x,int y){
  if(touche==27 || touche =='q'){      		/*echap*/
    free(monimage);
    free(pixcomp);
    exit(1);
  }
  if(touche=='+'){                               //chaleur
    chaleur_clavier(pixcomp,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
   }
  if(touche=='-'){                               //froideur  
    froideur_clavier(pixcomp,monimage->sizeX,monimage->sizeY);
    datachange_AfterEffect(monimage,pixcomp,1);
    affichage();
   }
}

Pixels** datachange(Image *img){  
  int i,j;
  int tmax=img->sizeX*img->sizeY;
  Pixels** linepix;

  /*Tansforme le tableau data de l'image en (1D)
    en tableau (2D) avec une structure
    qui associe les 3 bytes d'un pixels*/
  if(pixcomp)
    free(pixcomp);  

    linepix=(Pixels**)malloc(sizeof(Pixels*)*img->sizeX);
    for(i=0;i<=img->sizeX;i++)
      linepix[i]=(Pixels*)malloc(sizeof(Pixels)*img->sizeY);
 
 copie_data(linepix,img);
  return linepix;
}

void datachange_AfterEffect(Image *img,Pixels **linepix,int test){  
  /*img->data redevient ce qu'il
  etait sous forme d'un tableau de bytes (1D)*/
  int i,j,c=img->sizedata;  

  if(test==1)
    for(i=0,c=0;i<img->sizeX;i++){  
      for(j=0;j<img->sizeY;j++){  
	img->data[c++]=linepix[i][j].r;
	img->data[c++]=linepix[i][j].g;
	img->data[c++]=linepix[i][j].b;
      }
    }
  else
    //Copie dans le sens inverse pour inverser l'image
    for(i=0;i<img->sizeX;i++){  
      for(j=0;j<img->sizeY;j++){  
	img->data[c--]=linepix[i][j].r;
	img->data[c--]=linepix[i][j].b;
	img->data[c--]=linepix[i][j].g;
      }
    }
}

int LoadBMP(char *filename, Image *image) {
  FILE *file;
  unsigned long size;  
  unsigned long i;     
  unsigned short int planes;
  unsigned short int bpp;   
  GLubyte temp;                

  if ((file = fopen(filename, "rb"))==NULL) {
    printf("Fichier introuvable : %s\n",filename);
    return -1;
  }
  fseek(file, 18, SEEK_SET);
  //lecture de la largeur
  if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
    printf("Error reading width from %s.\n", filename);
    return -1;
  }
  //lecture de la hauteur
  if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
    printf("Error reading height from %s.\n", filename);
    return -1;
  }
  //serie de test pour savoir si l'image est conforme
  if ((fread(&planes, 2, 1, file)) != 1) {
    printf("Error reading planes from %s.\n", filename);
    return -1;
  }

  if (planes != 1) {
    printf("Planes from %s is not 1: %u\n", filename, planes);
    return -1;
  }
  if ((i = fread(&bpp, 2, 1, file)) != 1) {
    printf("Error reading bpp from %s.\n", filename);
    return -1;
  }
  if (bpp != 24) {
    printf("Bpp from %s is not 24: %u\n", filename, bpp);
    return -1;
  }
  fseek(file, 24, SEEK_CUR);
 
  size = image->sizeX * image->sizeY * 3;
  image->data = (GLubyte *) malloc(size);
  image->sizedata=size;
 
  if (image->data == NULL) {
    printf("Error allocating memory for color-corrected image data");
    return -1;	
  }

  if ((i = fread(image->data, size, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename);
    return -1;
  }
  
  /*ici il ya une permutation du rouge et vert de chaque pixel
    i avance de 3 en 3 car pour le cas i vaut 0
    i(qui est egale a 0) vaut le degres de vert du premier pixel
    i+1 vaut le degres de rouge du premier pixel
    i+2 vaut le degres de bleu du premier pixel
    on permute les bytes car la fonction gldrawpixels est dans la norme
    rgb or ici pour 3 bytes on a grb donc permutation des du g et du r
  */

  for (i=0;i<size;i+=3) {
    temp = image->data[i];
    image->data[i] = image->data[i+2];
    image->data[i+2] =temp;
  }
  fclose(file);
  return 0;
}



void save(Image* image){
  FILE *file;
  Theader header;
  Tinfoheader infoheader;
  GLuint size;
  GLuint temp;
  GLuint i;

  char s[256];
  printf("Saisir le nom de l'image a sauvegarder:");
  scanf("%s",s);
  file = fopen(s, "wb+");
     
#define UNDEFINED 0

  header.type = 0x4d42;
#ifdef __OSX__
  header.type = ((header.type>>8)&0x00ff) | ((header.type & 0xff)<<8);
#endif    

  header.size = 54+3*image->sizeX+image->sizeY;

#ifdef __OSX__
  header.size = (((header.size)>>24)&0xff) | ((((header.size)>>16)&0x00ff)<<8) | 
    ((((header.size)>>8)&0x0000ff)<<16) | ((((header.size)>>0)&0x000000ff)<<24);
#endif    

  header.reserved1 = 0;
#ifdef __OSX__
  header.reserved2 = 0x3600; 
#else
  header.reserved2 = 0x36;
#endif
 
#ifdef __OSX__
  header.offset = 0x49d0;
#else
  header.offset = 0;
#endif
        
  fwrite(&header, 14, 1, file);

  infoheader.size=40;
#ifdef __OSX__
  infoheader.size = (((infoheader.size)>>24)&0xff) | ((((infoheader.size)>>16)&0x00ff)<<8) | 
    ((((infoheader.size)>>8)&0x0000ff)<<16) | ((((infoheader.size)>>0)&0x000000ff)<<24);
#endif    

  infoheader.width=image->sizeX;
  infoheader.height=image->sizeY;

#ifdef __OSX__
  infoheader.width = (((infoheader.width)>>24)&0xff) | ((((infoheader.width)>>16)&0x00ff)<<8) | 
    ((((infoheader.width)>>8)&0x0000ff)<<16) | ((((infoheader.width)>>0)&0x000000ff)<<24);
  infoheader.height = (((infoheader.height)>>24)&0xff) | ((((infoheader.height)>>16)&0x00ff)<<8) | 
    ((((infoheader.height)>>8)&0x0000ff)<<16) | ((((infoheader.height)>>0)&0x000000ff)<<24);
#endif    


#ifdef __OSX__
  infoheader.planes=256;
#else
  infoheader.planes=1;
#endif
#ifdef __OSX__
  infoheader.bits= 0x1800;
#else
  infoheader.bits= 24;
#endif

  infoheader.compression=0;
    
  infoheader.imagesize = 3*image->sizeX*image->sizeY;
  /*
    printf("Taille %d %x\n",3*image->sizeX*image->sizeY, 3*image->sizeX*image->sizeY);
  */

#ifdef __OSX__
  infoheader.imagesize = (((infoheader.imagesize)>>24)&0xff) | ((((infoheader.imagesize)>>16)&0x00ff)<<8) | 
    ((((infoheader.imagesize)>>8)&0x0000ff)<<16) | ((((infoheader.imagesize)>>0)&0x000000ff)<<24);
#endif    

  infoheader.xresolution = infoheader.yresolution = 0;

  infoheader.ncolours = 0;
  infoheader.importantcolours = 0;

  /*
    printf("%x %x %x %x %x\n", header.type, header.size, 
    header.reserved1, header.reserved2, header.offset);
    printf("%x %x %x %x %x %x %x %x %x %x %x\n", infoheader.size, 
    infoheader.width, infoheader.height,
    infoheader.planes, infoheader.bits, 
    infoheader.compression, infoheader.imagesize, 
    infoheader.xresolution, infoheader.yresolution, 
    infoheader.ncolours, infoheader.importantcolours);

  */

  fwrite(&infoheader, 40, 1, file);
  for (i=0;i<image->sizedata;i+=3) {
    temp = image->data[i];
    image->data[i] = image->data[i+2];
    image->data[i+2] =temp;
  }
  
  fwrite (image->data,image->sizedata,1,file);  
  
  for (i=0;i<image->sizedata;i+=3) {
    temp = image->data[i];
    image->data[i] = image->data[i+2];
    image->data[i+2] =temp;
  }


fclose(file);
}
