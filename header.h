#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>


struct Image {
  unsigned long sizeX;
  unsigned long sizeY;
  unsigned long sizedata;
  GLubyte *data;
};
typedef struct Image Image;

struct pix{
  GLubyte r;
  GLubyte g;
  GLubyte b;
  int use;
};
typedef struct pix Pixels;

struct histo{
  int i,j;
  Pixels p;
};
typedef struct histo Historique;

struct T_header{
  unsigned short int type;                 /* Magic identifier            */
  unsigned int size;                       /* File size in bytes          */
  unsigned short int reserved1, reserved2;
  unsigned int offset;                     /* Offset to image data, bytes */
};
typedef struct T_header Theader;

struct T_infoheader{
  unsigned int size;               /* Header size in bytes      */
  int width,height;                /* Width and height of image */
  unsigned short int planes;       /* Number of colour planes   */
  unsigned short int bits;         /* Bits per pixel            */
  unsigned int compression;        /* Compression type          */
  unsigned int imagesize;          /* Image size in bytes       */
  int xresolution,yresolution;     /* Pixels per meter          */
  unsigned int ncolours;           /* Number of colours         */
  unsigned int importantcolours;   /* Important colours         */
};
typedef struct T_infoheader Tinfoheader;


void principale(int,char**);
void use_erreur(void);
void clavier(unsigned char,int,int);
void affichage(void);
int LoadBMP(char* , Image*);
Pixels** datachange(Image *);
void datachange_AfterEffect(Image *,Pixels **,int);
void contrasterhaut(Pixels **,int,unsigned long,unsigned long);
void contrasterbas(Pixels **,int,unsigned long,unsigned long);
void noir_blanc(Pixels **,unsigned long,unsigned long);
void chaleur(Pixels **,unsigned long,unsigned long);
void griser(Pixels **,unsigned long,unsigned long);
void contrastercentre(Pixels **,int,unsigned long,unsigned long);
void contrasterperipherie(Pixels **,int,unsigned long,unsigned long);
void deplacepixg(Pixels **,int,int,int);
void deplacepixd(Pixels **,int,int,int);
void pivoteg(Pixels** ,int ,int ,int ,unsigned long ,unsigned long );
void pivoted(Pixels** ,int ,int ,int ,unsigned long ,unsigned long );
void chaleur_clavier(Pixels **,unsigned long,unsigned long);
void froideur_clavier(Pixels **,unsigned long,unsigned long);
void untrait(Pixels **,unsigned long,unsigned long);
int testColorpix(Pixels);
void menu(int);
void copie_data(Pixels**,Image *);
void save(Image*);

