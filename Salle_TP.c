/*
 * salle.c
 *
 *  Created on: 28 mai 2011
 *      Author: CHIBANEMOURAD
 */

/**
 *Remarque : Au lancement du programme veuillez
 appuyer sur + ou - pour augmenter ou diminuer la vitesse de déplacement.  
 */
#include "GL/glut.h"
#include <math.h>
#include <stdio.h>
#include "tga.c"

 static float PlastiqueNoirA[]={ 0.1, 0.1, 0.1, 1.0 };
 static float PlastiqueNoirD[]={ .3, .3, .3, 1. };
 static float PlastiqueNoirS[]={ 0., 0., 0., 0. };

 static float PlastiqueGrisA[]={ 0.2, 0.2, 0.2, 1.0 };
 static float PlastiqueGrisD[]={ .4, .4, .4, 1. };
 static float PlastiqueGrisS[]={ 0., 0., 0., 1. };

 static float PlastiqueJauneA[]={ 0.4, 0.4, 0.25, 1.0 };
 static float PlastiqueJauneD[]={ .3, .3, 0.1, 1. };
 static float PlastiqueJauneS[]={ 0., 0., 0., 1. };

 static float PlastiqueMarronA[]={ 0.35, 0.3, 0.1, 1.0 };
 static float PlastiqueMarronD[]={ .5, .4, .2, 1. };
 static float PlastiqueMarronS[]={ 0., 0., 0., 1. };

 static float LumiereA[]={ 1., 1., 1., 1.0 };
 static float LumiereD[]={ 1, 1, 1, 1.0 };
 static float LumiereS[]={ 1, 1, 1, 1. };
 static float Lumiere0[]={ 300., 350.0, 30.0, 1 };
 static float Lumiere1[]={ 300., 350.0, -970.0, 1 };
 static float LumiereFenetre1[]={ 0, 225.0, -250.0, 0 };
 static float LumiereFenetre2[]={ 0, 225.0, -750.0, 0 };
 static float LumiereSphere[] ={302.5,349,-500,1};

 float angle1 = 0.1;
 float angle2 = 0.1;
 float angle3 = 0.1;

 double x_pos_souris=0;
 double y_pos_souris=0;

 int camX = 250;
 int camY = 150;
 int camZ = -1000;

 int cibleX = 20;
 int cibleY = 0.5;
 int cibleZ = -10;

 float fX = 8.66;
 float fY = 6.49;

 float fAv = 5;
 float fAr = 5200;

 int mov;

 int ARBRE,FEUILLE,TOUR,TABLE,PIEDT,CHAISE,PIEDC,PLATC,SALLE,RANGEE,ECRAN, CLAVIER;
 GLuint T_ARBRE,T_PIEDT,T_TABLE,T_ECRAN,T_CLAVIER_GAUCHE,T_CLAVIER_HAUT_GAUCHE,T_CLAVIER_CENTRE,T_CLAVIER_HAUT_CENTRE,T_CLAVIER_DROIT, T_CLAVIER_HAUT_DROIT,T_SOL,T_MUR_COULOIR,T_MUR_DOS,T_PLAFOND, T_UFR,T_HERBE, T_TOUR_GAUCHE,T_TOUR_DROITE,T_TOUR_FACE,T_TOUR_ARRIERE,T_FENETRE,T_PORTE_COULOIR,T_PORTE_FOND,T_TABLEAU,T_TR_PORTE,T_TR_PORTE_SOL,T_TR_SOL1,T_TR_SOL2,T_TR_VITRE1,T_CIEL,T_TR_VITRE2,T_TR_VITRE3 ;

 struct point{float x,y,z;};
 typedef struct point point;


/*++++++*/
 float n_x(point a){
  return sqrt(3)*(a.x/sqrt(a.x*a.x+a.y*a.y+a.z*a.z));
  
}
float n_y(point a){
  return sqrt(3)*(a.y/sqrt(a.x*a.x+a.y*a.y+a.z*a.z));
}
float n_z(point a){
  return sqrt(3)*(a.z/sqrt(a.x*a.x+a.y*a.y+a.z*a.z));
}

point milieu(point a,point b){
  point m;
  m.x = (a.x+b.x)/2.;
  m.y = (a.y+b.y)/2.;
  m.z = (a.z+b.z)/2.;
  return m;
}

void creer_triangle2(point a,point b, point c, int degre){
  point mab,mbc,mca;
  
  if(degre == 0){
    glBegin(GL_TRIANGLES);
    glNormal3f(1,1,1);
    glTexCoord2f(0,0);
    glVertex3f(a.x,a.y,a.z);
    glTexCoord2f(1,0);
    glVertex3f(b.x,b.y,b.z);
    glTexCoord2f(0.5,sqrt(0.75));
    glVertex3f(c.x,c.y,c.z);
    
    glEnd();
  }
  else{
    mab = milieu(a,b);
    mbc = milieu(b,c);
    mca = milieu(c,a);
    
    
    creer_triangle2(a,mab,mca,degre-1);
    creer_triangle2(mbc,mab,mca,degre-1);
    creer_triangle2(b,mab,mbc,degre-1);
    creer_triangle2(c,mbc,mca,degre-1);
  }

}

void creer_tetra(point a, point b, point c, point d ,int degre){

  creer_triangle2(a,b,c,degre);
  creer_triangle2(a,b,d,degre);
  creer_triangle2(a,c,d,degre);
  creer_triangle2(b,c,d,degre);

  
}

void creer_triangle(point a,point b, point c, int degre){
  point mab,mbc,mca;
  
  if(degre == 0){
    glBegin(GL_TRIANGLES);
    glNormal3f(1,1,1);
    glTexCoord2f(0,0);
    glVertex3f(n_x(a),n_y(a),n_z(a));
    glTexCoord2f(1,0);
    glVertex3f(n_x(b),n_y(b),n_z(b));
    glTexCoord2f(0.5,sqrt(0.75));
    glVertex3f(n_x(c),n_y(c),n_z(c));
    
    glEnd();
  }
  else{
    mab = milieu(a,b);
    mbc = milieu(b,c);
    mca = milieu(c,a);
    
    
    creer_triangle(a,mab,mca,degre-1);
    creer_triangle(mbc,mab,mca,degre-1);
    creer_triangle(b,mab,mbc,degre-1);
    creer_triangle(c,mbc,mca,degre-1);
  }

}


void creer_piedC(){
  PIEDC = glGenLists(1);
  glNewList(PIEDC, GL_COMPILE);
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueMarronA );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueMarronD );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueMarronS );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);//terne vers brillant
  glScalef(2.,42.,2.);
  glutSolidCube(1);
  glPopMatrix();
  glEndList();
}

void creer_platC(){
  PLATC = glGenLists(1);
  glNewList(PLATC, GL_COMPILE);
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueJauneA );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueJauneD );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueJauneS );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);//terne vers brillant
  glScalef(38.,1.,41.5);
  glutSolidCube(1);
  glPopMatrix();
  glEndList();
}

void creer_chaise(){
  CHAISE = glGenLists(1);
  glNewList(CHAISE, GL_COMPILE);
  
  glColor3f(1,1,0);
  glPushMatrix();
  glTranslatef(19,-21,20.75);
  glCallList(PIEDC);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(19,-21,-20.75);
  glCallList(PIEDC);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-19,-21,20.75);
  glCallList(PIEDC);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-19,-21,-20.75);
  glCallList(PIEDC);
  glPopMatrix();
  
  //début du dossier
  glPushMatrix();
  glTranslatef(-19,21,20.75);
  glCallList(PIEDC);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(19,21,20.75);
  glCallList(PIEDC);
  glPopMatrix();
  
  glPushMatrix();
  glCallList(PLATC);
  glPopMatrix();
  
  glPushMatrix();
  
  glTranslatef(0.,20.75,20.75);
  glRotatef(90., 1.,0.,0.);
  glCallList(PLATC);
  glutSolidCube(1);
  glPopMatrix();
  
  
  glEndList();
  
}





/*++++++*/
void creer_table(){
 TABLE = glGenLists(1);
 glNewList(TABLE, GL_COMPILE);
 
 glPushMatrix();
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
 glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);//terne vers brillant
 
 
 glBindTexture(GL_TEXTURE_2D,T_PIEDT);
 glBegin(GL_QUADS);
 
 glNormal3f(0,0,1);
 glTexCoord2f(0,0);
 glVertex3f(80,1,40);
 glTexCoord2f(1,0);
 glVertex3f(-80,1,40);
 glTexCoord2f(1,1);
 glVertex3f(-80,-1,40);
 glTexCoord2f(0,1);
 glVertex3f(80,-1,40);
 
 glEnd();
 glPopMatrix();
 
 glPushMatrix();
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
 glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);//terne vers brillant
 
 glBindTexture(GL_TEXTURE_2D,T_PIEDT);
 glBegin(GL_QUADS);
 glutSolidCube(1);
 
 glNormal3f(1,0,0);
 glTexCoord2f(0,0);
 glVertex3f(80,1,40);
 glTexCoord2f(1,0);
 glVertex3f(80,-1,40);
 glTexCoord2f(1,1);
 glVertex3f(80,-1,-40);
 glTexCoord2f(0,1);
 glVertex3f(80,1,-40);
 
 glEnd();
 glPopMatrix();
 
 glPushMatrix();
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
 glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);//terne vers brillant
 
 glBindTexture(GL_TEXTURE_2D,T_PIEDT);
 glBegin(GL_QUADS);
 glNormal3f(1,0,0);
 glTexCoord2f(0,0);
 glVertex3f(-80,1,40);
 glTexCoord2f(1,0);
 glVertex3f(-80,-1,40);
 glTexCoord2f(1,1);
 glVertex3f(-80,-1,-40);
 glTexCoord2f(0,1);
 glVertex3f(-80,1,-40);
 
 glEnd();
 glPopMatrix();
 
 glPushMatrix();
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
 glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);//terne vers brillant
 glBegin(GL_QUADS);
 glNormal3f(0,0,1);
 glTexCoord2f(0,0);
 glVertex3f(80,1,-40);
 glTexCoord2f(1,0);
 glVertex3f(-80,1,-40);
 glTexCoord2f(1,1);
 glVertex3f(-80,-1,-40);
 glTexCoord2f(0,1);
 glVertex3f(80,-1,-40);
 
 glEnd();
 glPopMatrix();
 
 glPushMatrix();

 
 //HAUT
 glBindTexture(GL_TEXTURE_2D,T_TABLE);
 glBegin(GL_QUADS);
 glNormal3f(0,1,0);
 glTexCoord2f(0,0);
 glVertex3f(80,1,40);
 glTexCoord2f(1,0);
 glVertex3f(80,1,-40);
 glTexCoord2f(1,1);
 glVertex3f(-80,1,-40);
 glTexCoord2f(0,1);
 glVertex3f(-80,1,40);
 
 glEnd();
 glPopMatrix();
 
 
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,0); 
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueGrisA );
 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueGrisD );
 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueGrisS );
 glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);//terne vers brillant
 
 //BAS
 glBindTexture(GL_TEXTURE_2D,T_TABLE);
 glBegin(GL_QUADS);
 glNormal3f(0,1,0);
 glTexCoord2f(0,0);
 glVertex3f(80,-1,40);
 glTexCoord2f(1,0);
 glVertex3f(80,-1,-40);
 glTexCoord2f(1,1);
 glVertex3f(-80,-1,-40);
 glTexCoord2f(0,1);
 glVertex3f(-80,-1,40);
 
 glEnd();
 glPopMatrix();
 
 
 glPushMatrix();
 glTranslatef(-73,-36,-33);
 glCallList(PIEDT);
 glPopMatrix();
 glPushMatrix();
 glTranslatef(73,-36,-33);
 glCallList(PIEDT);
 glPopMatrix();
 glPushMatrix();
 glTranslatef(-73,-36,33);
 glCallList(PIEDT);
 glPopMatrix();
 glPushMatrix();
 glTranslatef(73,-36,33);
 glCallList(PIEDT);
 glPopMatrix();
 
 
 glPushMatrix();
 glTranslatef(62,23,-15.5);
 glRotatef(3, 0,1.,0.);
 glBindTexture(GL_TEXTURE_2D,0);
 glCallList(TOUR);
 glPopMatrix();
 
 glPushMatrix();
 glTranslatef(0,-28.5,60.75);
 glRotatef(3,0,1,0);
 glCallList(CHAISE);
 glPopMatrix();
 
 glPushMatrix();
 glTranslatef(0,24.,-20.);
 glRotatef(1., 0,1.,0.);
 glCallList(ECRAN);
 glPopMatrix();
 
 glPushMatrix();
 glTranslatef(0.,1.75,15.);
 glRotatef(2., 0,1.,0.);
 glCallList(CLAVIER);
 glPopMatrix();
 
 glEndList();
 
 
 
}

void creer_piedT(){
 PIEDT = glGenLists(1);
 glNewList(PIEDT, GL_COMPILE);
 
  //première face
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_PIEDT);
 glBegin(GL_QUADS);
 
 glNormal3f(0,0,1);
 glTexCoord2f(0,0);
 glVertex3f(-2.5,-35,2.5);
 glTexCoord2f(5,0);
 glVertex3f(-2.5,35,2.5);
 glTexCoord2f(5,5);
 glVertex3f(2.5,35,2.5);
 glTexCoord2f(0,5);
 glVertex3f(2.5,-35,2.5);
 glEnd();
 glPopMatrix();
 
  //seconde face
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_PIEDT);
 glBegin(GL_QUADS);
 glNormal3f(0,0,1);
 glTexCoord2f(0,0);
 glVertex3f(-2.5,-35,2.5);
 glTexCoord2f(5,0);
 glVertex3f(-2.5,35,2.5);
 glTexCoord2f(5,5);
 glVertex3f(-2.5,35,-2.5);
 glTexCoord2f(0,5);
 glVertex3f(-2.5,-35,-2.5);
 glEnd();
 glPopMatrix();
 
  //troisième face
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_PIEDT);
 glBegin(GL_QUADS);
 
 glNormal3f(0,0,1);
 glTexCoord2f(0,0);
 glVertex3f(-2.5,-35,-2.5);
 glTexCoord2f(1,0);
 glVertex3f(-2.5,35,-2.5);
 glTexCoord2f(1,1);
 glVertex3f(2.5,35,-2.5);
 glTexCoord2f(0,1);
 glVertex3f(2.5,-35,-2.5);
 glEnd();
 glPopMatrix();
 
 //quatrième face
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_PIEDT);
 glBegin(GL_QUADS);
 glNormal3f(0,0,1);
 glTexCoord2f(0,0);
 glVertex3f(2.5,-35,-2.5);
 glTexCoord2f(1,0);
 glVertex3f(2.5,35,-2.5);
 glTexCoord2f(1,1);
 glVertex3f(2.5,35,2.5);
 glTexCoord2f(0,1);
 glVertex3f(2.5,-35,2.5);
 
 glEnd();
 glPopMatrix();
 
 glEndList();
}


void creer_tour(){
 TOUR = glGenLists(1);
 glNewList(TOUR, GL_COMPILE);
 
 //première face
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_TOUR_ARRIERE);
 glBegin(GL_QUADS);
 
 glNormal3f(0,0,1);
 glTexCoord2f(0,0);
 glVertex3f(-8.25,-22,-22.5);
 glTexCoord2f(0,1);
 glVertex3f(-8.25,22,-22.5);
 glTexCoord2f(1,1);
 glVertex3f(8.25,22,-22.5);
 glTexCoord2f(1,0);
 glVertex3f(8.25,-22,-22.5);
 glEnd();
 glPopMatrix();
 
  //seconde face
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_TOUR_GAUCHE);
 glBegin(GL_QUADS);
 glNormal3f(0,0,1);
 glTexCoord2f(0,0);
 glVertex3f(-8.25,-22,22.5);
 glTexCoord2f(1,0);
 glVertex3f(-8.25,-22,-22.5);
 glTexCoord2f(1,1);
 glVertex3f(-8.25,22,-22.5);
 glTexCoord2f(0,1);
 glVertex3f(-8.25,22,22.5);
 glEnd();
 glPopMatrix();
 //troisième face
 
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_TOUR_DROITE);
 glBegin(GL_QUADS);
 
 glNormal3f(0,0,1);
 glTexCoord2f(0,0);
 glVertex3f(8.25,-22,22.5);
 glTexCoord2f(1,0);
 glVertex3f(8.25,-22,-22.5);
 glTexCoord2f(1,1);
 glVertex3f(8.25,22,-22.5);
 glTexCoord2f(0,1);
 glVertex3f(8.25,22,22.5);
 glEnd();
 glPopMatrix();
 
  //quatrième face
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_TOUR_FACE);
 glBegin(GL_QUADS);
 glNormal3f(0,0,1);
 glTexCoord2f(0,0);
 glVertex3f(-8.25,-22,22.5);
 glTexCoord2f(1,0);
 glVertex3f(8.25,-22,22.5);
 glTexCoord2f(1,1);
 glVertex3f(8.25,22,22.5);
 glTexCoord2f(0,1);
 glVertex3f(-8.25,22,22.5);
 
 glEnd();
 glPopMatrix();
 
 
 
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_TOUR_GAUCHE);
 glPopMatrix();
 
 //face du haut
 glPushMatrix();
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);//terne vers brillant
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0,0);
  glVertex3f(8.25,22,22.5);
  glTexCoord2f(1,0);
  glVertex3f(8.25,22,-22.5);
  glTexCoord2f(1,1);
  glVertex3f(-8.25,22,-22.5);
  glTexCoord2f(0,1);
  glVertex3f(-8.25,22,22.5);
  glEnd();
  glPopMatrix();
  
  
 //main
  glPushMatrix();
  //glBindTexture(GL_TEXTURE_2D,T_MAIN);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0,0);
  glVertex3f(8.25,22.3,22.5);
  glTexCoord2f(1,0);
  glVertex3f(8.25,22.3,0);
  glTexCoord2f(1,1);
  glVertex3f(-8.25,22.3,0);
  glTexCoord2f(0,1);
  glVertex3f(-8.25,22.3,22.5);
  glEnd();
  glPopMatrix();
   //face du bas
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0,0);
  glVertex3f(-8.25,-22,-22.5);
  glTexCoord2f(1,0);
  glVertex3f(8.25,-22,-22.5);
  glTexCoord2f(1,1);
  glVertex3f(8.25,-22,22.5);
  glTexCoord2f(0,1);
  glVertex3f(-8.25,-22,22.5);
  
  glEnd();
  glPopMatrix();
  glEndList();
  
}

void creer_ecran(){
 ECRAN = glGenLists(1);
 glNewList(ECRAN, GL_COMPILE);
 glPushMatrix();
 glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
 glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
 glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
 glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);//terne vers brillant
 glRotatef(-15.5, 1.,0.,0.);
 glScalef(37.,30.5,2.5);
 glutSolidCube(1);
 glPopMatrix();
 
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_ECRAN);
 glRotatef(-15.5,1.,0,0);
 //glScalef(37,30.5,2.5);
 glBegin(GL_QUADS);
 glNormal3f(0,0,1);
 glTexCoord2f(1,1);
 glVertex3f(17,14,1.3);
 glTexCoord2f(0,1);
 glVertex3f(-17,14,1.3);
 glTexCoord2f(0,0);
 glVertex3f(-17,-14,1.3);
 glTexCoord2f(1,0);
 glVertex3f(17,-14,1.3);
 glEnd();
 
 glPopMatrix();
 
 //Génération de la première partie du pied (Penser au materialfv)
 glPushMatrix();
 glBindTexture(GL_TEXTURE_2D,T_TOUR_DROITE);
 glTranslatef(0.,0.,-1.);
 glRotatef(60.,1.,0.,0.);
 glScalef(6.,4.,1.);
 glutSolidCube(1);
 glPopMatrix();
 
 //Génération de la seconde partie du pied
 glPushMatrix();
 glTranslatef(0.,-8,-4);
 glRotatef(8,1,0,0);
 glScalef(6.,15.,1.);
 glutSolidCube(1);
 glPopMatrix();
 
 //Génération de la 3e partie du pied
 glPushMatrix();
 glTranslatef(0 ,-18.5, -2.8);
 glRotatef(-35,1,0,0);
 glScalef(6., 9, 1.);
 glutSolidCube(1);
 glPopMatrix();
 
  //Génération de la base du pied
 glPushMatrix();
 glTranslatef(-5. ,-22.5, 4.8);
 glRotatef(-45,0,1,0);
 glScalef(5.5, 1., 18.);
 glutSolidCube(1);
 glPopMatrix();
 
 glPushMatrix();
 glTranslatef(4. ,-22.5, 4.8);
 glRotatef(45,0,1,0);
 glScalef(5.5, 1., 18.);
 glutSolidCube(1);
 glPopMatrix();
 
 
 glEndList();
 
}

void creer_clavier(){
  CLAVIER = glGenLists(1);
  glNewList(CLAVIER, GL_COMPILE);

  //corps
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);
  glScalef(44.,1.5,12.);
  glutSolidCube(1);
  glPopMatrix();

  //gauche
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);
  glTranslatef(-7.5,1.0,0.75);
  glScalef(28., 0.9, 9.);
  glutSolidCube(1);
  glPopMatrix();

  //image gauche
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_CLAVIER_GAUCHE);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(-21.5,1.47,5.25);
  glTexCoord2f(1,0);
  glVertex3f(6.5,1.47,5.25);
  glTexCoord2f(1,1);
  glVertex3f(6.5,1.47,-3.75);
  glTexCoord2f(0,1);
  glVertex3f(-21.5,1.47,-3.75);
  glEnd();
  glPopMatrix();

  //haut gauche
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);
  glTranslatef(-9.5,1.0,-5.25);
  glScalef(24.,0.9,1.);
  glutSolidCube(1);
  glPopMatrix();

  //image haut gauche
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_CLAVIER_HAUT_GAUCHE);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(-21.5,1.47,-4.75);
  glTexCoord2f(1,0);
  glVertex3f(2.5,1.47,-4.75);
  glTexCoord2f(1,1);
  glVertex3f(2.5,1.47,-5.75);
  glTexCoord2f(0,1);
  glVertex3f(-21.5,1.47,-5.75);
  glEnd();
  glPopMatrix();

  //centre haut
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);
  glTranslatef(10.75,1.0,-2.25);
  glScalef(5.,0.9,3.);
  glutSolidCube(1);
  glPopMatrix();


  //image centre haut
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_CLAVIER_HAUT_CENTRE);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(8.25,1.47,-.75);
  glTexCoord2f(1,0);
  glVertex3f(13.25,1.47,-.75);
  glTexCoord2f(1,1);
  glVertex3f(13.25,1.47,-3.75);
  glTexCoord2f(0,1);
  glVertex3f(8.25,1.47,-3.75);
  glEnd();
  glPopMatrix();


  //centre
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);
  glTranslatef(10.75,1.0,3.75);
  glScalef(5.,0.9,3.);
  glutSolidCube(1);
  glPopMatrix();

  //image centre
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_CLAVIER_CENTRE);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(8.25,1.47,5.25);
  glTexCoord2f(1,0);
  glVertex3f(13.25,1.47,5.25);
  glTexCoord2f(1,1);
  glVertex3f(13.25,1.47,2.25);
  glTexCoord2f(0,1);
  glVertex3f(8.25,1.47,2.25);
  glEnd();
  glPopMatrix();

  //haut droit

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);
  glTranslatef(18.,1.0,0.75);
  glScalef(7.,0.9,9.);
  glutSolidCube(1);
  glPopMatrix();

  //image droite
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_CLAVIER_DROIT);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(14.5,1.47,5.25);
  glTexCoord2f(1,0);
  glVertex3f(21.5,1.47,5.25);
  glTexCoord2f(1,1);
  glVertex3f(21.5,1.47,-3.75);
  glTexCoord2f(0,1);
  glVertex3f(14.5,1.47,-3.75);
  glEnd();
  glPopMatrix();

  //hautdroit

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, PlastiqueNoirA );
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, PlastiqueNoirD );
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, PlastiqueNoirS );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 1);
  glTranslatef(19.,1.0,-5.25);
  glScalef(5.,0.9,1.);
  glutSolidCube(1);
  glPopMatrix();

  //image haut droit
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_CLAVIER_HAUT_DROIT);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(16.5,1.47,-5.75);
  glTexCoord2f(1,0);
  glVertex3f(21.5,1.47,-5.75);
  glTexCoord2f(1,1);
  glVertex3f(21.5,1.47,-4.75);
  glTexCoord2f(0,1);
  glVertex3f(16.5,1.47,-4.75);
  glEnd();
  glPopMatrix();


  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glPopMatrix();

  glEndList();

}


void creer_rangee(){
  RANGEE = glGenLists(1);
  glNewList(RANGEE, GL_COMPILE);
  glPushMatrix();
  glTranslatef(0,0,70);
  glCallList(TABLE);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(160,0,70);
  glCallList(TABLE);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-160,0,70);
  glCallList(TABLE);
  glPopMatrix();

  glEndList();
}


void creer_salle(){
  SALLE = glGenLists(1);
  glNewList(SALLE, GL_COMPILE);

    /*placement de bureau*/
  glPushMatrix();
  glTranslatef(350,71,-840);
  glRotatef(180,0,1,0);
  glCallList(TABLE);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(350,71,-310);
  glCallList(RANGEE);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(350,71,-480 );
  glCallList(RANGEE);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(350,71,-650);
  glCallList(RANGEE);
  glPopMatrix();
  glPushMatrix();
  glTranslatef(350,71,-820);
  glCallList(RANGEE);
  glPopMatrix();



  /*sol*/
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_SOL);

  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(0,0,0);
  glTexCoord2f(10,0);
  glVertex3f(0,0,-1000);
  glTexCoord2f(10,10);
  glVertex3f(605,0,-1000);
  glTexCoord2f(0,10);
  glVertex3f(605,0,0);
  glEnd();
  glPopMatrix();


  /*mur coté couloir*/
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_MUR_COULOIR);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(605,0,0);
  glTexCoord2f(1,0);
  glVertex3f(605,0,-1000);
  glTexCoord2f(1,1);
  glVertex3f(605,350,-1000);
  glTexCoord2f(0,1);
  glVertex3f(605,350,0);
  glEnd();
  glPopMatrix();

  /*mur dos*/
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_MUR_DOS);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(0,0,0);
  glTexCoord2f(1,0);
  glVertex3f(605,0,0);
  glTexCoord2f(1,1);
  glVertex3f(605,350,0);
  glTexCoord2f(0,1);
  glVertex3f(0,350,0);
  glEnd();
  glPopMatrix();

  /*mur face*/
  glPushMatrix();
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(0,0,-1000);
  glTexCoord2f(1,0);
  glVertex3f(605,0,-1000);
  glTexCoord2f(1,1);
  glVertex3f(605,350,-1000);
  glTexCoord2f(0,1);
  glVertex3f(0,350,-1000);
  glEnd();
  glPopMatrix();

  /*plafond*/

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_PLAFOND);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(0,350,0);
  glTexCoord2f(1,0);
  glVertex3f(605,350,0);
  glTexCoord2f(1,1);
  glVertex3f(605,350,-1000);
  glTexCoord2f(0,1);
  glVertex3f(0,350,-1000);
  glEnd();
  glPopMatrix();

  //image fenetre -1
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_UFR);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(-1500,-300,1500);
  glTexCoord2f(1,0);
  glVertex3f(-1500,-300,0);
  glTexCoord2f(1,1);
  glVertex3f(-1500,1500,0);
  glTexCoord2f(0,1);
  glVertex3f(-1500,1500,1500);
  glEnd();
  glPopMatrix();

  //image fenetre 0
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_UFR);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(-1500,-300,0);
  glTexCoord2f(-1,0);
  glVertex3f(-1500,-300,-1500);
  glTexCoord2f(-1,1);
  glVertex3f(-1500,1500,-1500);
  glTexCoord2f(0,1);
  glVertex3f(-1500,1500,0);
  glEnd();
  glPopMatrix();

  //image fenetre 1
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_UFR);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(-1500,-300,-1500);
  glTexCoord2f(1,0);
  glVertex3f(-1500,-300,-1500);
  glTexCoord2f(1,1);
  glVertex3f(-1500,1500,-1500);
  glTexCoord2f(0,1);
  glVertex3f(-1500,1500,-1500);
  glEnd();
  glPopMatrix();

  //image fenetre coin 1
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_UFR);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(-1500,-300,1500);
  glTexCoord2f(1,0);
  glVertex3f(300,-300,1500);
  glTexCoord2f(1,1);
  glVertex3f(300,1500, 1500);
  glTexCoord2f(0,1);
  glVertex3f(-1500,1500,1500);
  glEnd();
  glPopMatrix();

  //image fenetre coin 2
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_UFR);
  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(1,0);
  glVertex3f(-1500,-300,-1500);
  glTexCoord2f(0,0);
  glVertex3f(300,-300,-1500);
  glTexCoord2f(0,1);
  glVertex3f(300,1500,-1500);
  glTexCoord2f(1,1);
  glVertex3f(-1500,1500,-1500);
  glEnd();
  glPopMatrix();




  //herbe

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_HERBE);

  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0,0);
  glVertex3f(-1500,-300,1500);
  glTexCoord2f(10,0);
  glVertex3f(300,-300,1500);
  glTexCoord2f(10,10);
  glVertex3f(300,-300,-1500);
  glTexCoord2f(0,10);
  glVertex3f(-1500,-300,-1500);
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glPopMatrix();

  //Ciel

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_CIEL);

  glBegin(GL_QUADS);

  glNormal3f(0, 1, 0);
  glTexCoord2f(1,0);
  glVertex3f(-1500,+1500,-1500);
  glTexCoord2f(1,1);
  glVertex3f(+1500,+1500,-1500);
  glTexCoord2f(0,1);
  glVertex3f(+1500,+1500,+1500);
  glTexCoord2f(0,0);
  glVertex3f(-1500,+1500,+1500);
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glPopMatrix();

  //murs de la fenetre
  //Fenetre_bas mur
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_MUR_COULOIR);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,0);
  glVertex3f(0,0,0);

  glTexCoord2f(1,1);
  glVertex3f(0,100,0);
  glTexCoord2f(0,1);
  glVertex3f(0,100,-1000);
  glTexCoord2f(1,0);
  glVertex3f(0,0,-1000);
  glEnd();

  //Fenetre_haut mur
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,0);
  glVertex3f(0,330,0);
  glTexCoord2f(1,1);
  glVertex3f(0,350,0);
  glTexCoord2f(0,1);
  glVertex3f(0,350,-1000);
  glTexCoord2f(1,0);
  glVertex3f(0,330,-1000);
  glEnd();

  //Fenetre_gauche mur
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,0);
  glVertex3f(0,100,-990);
  glTexCoord2f(1,1);
  glVertex3f(0,100,-1000);
  glTexCoord2f(0,1);
  glVertex3f(0,330,-1000);
  glTexCoord2f(1,0);
  glVertex3f(0,330,-990);
  glEnd();

  //Fenetre_droite mur
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,0);
  glVertex3f(0,100,0);
  glTexCoord2f(1,1);
  glVertex3f(0,100,-10);
  glTexCoord2f(0,1);
  glVertex3f(0,330,-10);
  glTexCoord2f(1,0);
  glVertex3f(0,330,0);

  //Fenetre_milieu mur
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,0);
  glVertex3f(0,100,-490);
  glTexCoord2f(1,1);
  glVertex3f(0,100,-510);
  glTexCoord2f(0,1);
  glVertex3f(0,330,-510);
  glTexCoord2f(1,0);
  glVertex3f(0,330,-490);

  glEnd();
  glPopMatrix();

  //Fenetre vitres 1 et 2
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,T_FENETRE);

  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,0);
  glVertex3f(0,99,-10);
  glTexCoord2f(1,0);
  glVertex3f(0,99,-490);
  glTexCoord2f(1,1);
  glVertex3f(0,330.5,-490);
  glTexCoord2f(0,1);
  glVertex3f(0,330.5,-10);
  glEnd();

  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,0);
  glVertex3f(0,99,-510);
  glTexCoord2f(1,0);
  glVertex3f(0,99,-990);
  glTexCoord2f(1,1);
  glVertex3f(0,330.5,-990);
  glTexCoord2f(0,1);
  glVertex3f(0,330.5,-510);
  glEnd();

  glPopMatrix();

  //porte couloir
  glPushMatrix();

  glBindTexture(GL_TEXTURE_2D,T_PORTE_COULOIR);
  glBegin(GL_QUADS);
  glNormal3f(1,0,0);
  glTexCoord2f(0,0);
  glVertex3f(604.5,0,-965);
  glTexCoord2f(0,1);
  glVertex3f(604.5,0,-865);
  glTexCoord2f(1,1);
  glVertex3f(604.5,200,-865);
  glTexCoord2f(1,0);
  glVertex3f(604.5,200,-965);
  glEnd();

  glPopMatrix();

  //portes fonds
  glPushMatrix();

  glBindTexture(GL_TEXTURE_2D,T_PORTE_FOND);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0,0);
  glVertex3f(45,0,-999.5);
  glTexCoord2f(0,1);
  glVertex3f(145,0,-999.5);
  glTexCoord2f(1,1);
  glVertex3f(145,230,-999.5);
  glTexCoord2f(1,0);
  glVertex3f(45,230,-999.5);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,T_PORTE_FOND);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0,0);
  glVertex3f(45,0,-0.5);
  glTexCoord2f(0,1);
  glVertex3f(145,0,-0.5);
  glTexCoord2f(1,1);
  glVertex3f(145,230,-0.5);
  glTexCoord2f(1,0);
  glVertex3f(45,230,-0.5);
  glEnd();

  glPopMatrix();

  //tableau
  glBindTexture(GL_TEXTURE_2D,T_TABLEAU);
  glBegin(GL_QUADS);
  glNormal3f(0,0,1);
  glTexCoord2f(0,0);
  glVertex3f(165,90,-999.5);
  glTexCoord2f(0,1);
  glVertex3f(490,90,-999.5);
  glTexCoord2f(1,1);
  glVertex3f(490,230,-999.5);
  glTexCoord2f(1,0);
  glVertex3f(165,230,-999.5);
  glEnd();

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glPopMatrix();

  glEndList();
}

void creerListeFeuille(){

  FEUILLE=glGenLists(1);
  glNewList(FEUILLE, GL_COMPILE);

  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, T_ARBRE);		
  glBegin(GL_QUADS);

  glNormal3f(1, 0, 0);

  glTexCoord2f(0,0);
  glVertex3f(+0.5,-0.5,-0.5);

  glTexCoord2f(1,0);
  glVertex3f(+0.5,-0.5,+0.5);

  glTexCoord2f(1,1);
  glVertex3f(+0.5,+0.5,+0.5);

  glTexCoord2f(0,1);
  glVertex3f(+0.5,+0.5,-0.5);
  glEnd();
  glPopMatrix();
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glPopMatrix();
  glEndList();
}

void creerListeArbre(){
  ARBRE=glGenLists(1);
  glNewList(ARBRE, GL_COMPILE);

  glPushMatrix();
  glScalef(200,500,200);
  glCallList(FEUILLE);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(100,0,100);
  glScalef(200,500,200);
  glRotatef(90,0,1,0);
  glCallList(FEUILLE);
  glPopMatrix();

  glEndList();
}

/********************** FONCTION D'AFFICHAGE DES DIFFERENTS OBJETS ***********************/
void afficheArbre(){

  glPushMatrix();
  glTranslatef(-1000,0,-100);
  glCallList(ARBRE);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-600,0,400);
  glCallList(ARBRE);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-800,0,750);
  glCallList(ARBRE);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-400,0,100);
  glCallList(ARBRE);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-300,0,900);
  glCallList(ARBRE);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-800,0,100);
  glCallList(ARBRE);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-400,0,200);
  glCallList(ARBRE);
  glPopMatrix();


  glPushMatrix();
  glTranslatef(-400,0,-200);
  glCallList(ARBRE);
  glPopMatrix();

}


void affiche()
{

  point origine;
  origine.x = 0;
  origine.y = 0.;
  origine.z = 0.;
  angle1 += fmod(7*M_PI/360.,2*M_PI);  
  angle2 -= fmod(1*M_PI/360.,2*M_PI);  
  angle3 = angle3 + fmod((angle1+angle2-angle3)*M_PI/360.,2*M_PI);  
  int degre = 2;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);               /* selection de la matrice de projection                 */
  glLoadIdentity();

  glFrustum(-fX,fX, -fY, fY,fAv , fAr ); 

  glMatrixMode(GL_MODELVIEW); 
  glLoadIdentity();
  gluLookAt(camX,camY,camZ ,cibleX,cibleY,cibleZ, 0,1,0);
  glLightfv(GL_LIGHT0,GL_POSITION, Lumiere0);
  glLightfv(GL_LIGHT1,GL_POSITION, Lumiere1);
  glLightfv(GL_LIGHT2,GL_POSITION, LumiereFenetre1);
  glLightfv(GL_LIGHT3,GL_POSITION, LumiereFenetre2);
  glLightfv(GL_LIGHT4,GL_POSITION, LumiereSphere);

  glPushMatrix();
  glCallList(SALLE);  
  glTranslatef(0.,0.,-1.);

  afficheArbre();

  if(glGetError() == 1){
    gluErrorString(glGetError());
  }
  /** fixer l'image */
  glPopMatrix();

  glutSwapBuffers();

}

void camera(unsigned char key, int x, int y){
  switch(key){
    case '+':
    mov += 2;
    break;
    case '-':
    {
     if(mov > 0) mov -= 2;
   }
   break;
   case 'a':
   camX += mov;
   break;
   case 'q':
   camX -= mov;
   break;
   case 'z':
   camY += mov;
   break;
   case 's':
   camY -= mov;
   break;
   case 'e':
   camZ += mov;
   break;
   case 'd':
   camZ -= mov;
   break;
   case 't':
   cibleX += mov;
   break;
   case 'g':
   cibleX -= mov;
   break;
   case 'y':
   cibleY += mov;
   break;
   case 'h':
   cibleY -= mov;
   break;
   case 'o':
   fX += mov;
   break;
   case 'l':
   fX -= mov;
   break;
   case 'p':
   fY += mov;
   break;
   case 'm':
   fY -= mov;
   break;
   case 'c':
   fAr += mov;
   break;
   case 'v':
   fAr -= mov;
   break;
   case 27:
   exit(0);
   break;
   
 }

}

void special(int key, int x, int y){
  switch(key){
    case GLUT_KEY_DOWN :
    fAv -= mov;
    break;
    case GLUT_KEY_UP :
    fAv += mov;
    break;
    case GLUT_KEY_LEFT :
    cibleZ += mov+20;
    break;
    case GLUT_KEY_RIGHT :
    cibleZ -= mov+20;
    break;
  }
}

void motion(int x, int y){
  camX+=(x-x_pos_souris)*0.01;

  camY+=(y-y_pos_souris)*0.01;


  x_pos_souris=x;
  y_pos_souris=y;
}

void timer(int id) {
  glutPostRedisplay();
  glutTimerFunc(id, &timer, id);
}

void initTexture(char * nameFile,GLuint * tid, int bool_repetition){
  printf("Lecture des Texture en cours...\n");
  printf("0");
  gl_texture_t * toto =  ReadTGAFile(nameFile);
  printf("1");  
  glGenTextures(1,tid);
  printf("2");
  glBindTexture(GL_TEXTURE_2D, *tid);
  printf("3");

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  if(bool_repetition == 1 ){
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
  }
  glTexImage2D(GL_TEXTURE_2D,0,toto->internalFormat, toto->width,toto->height,0,toto->format,GL_UNSIGNED_BYTE,toto->texels);
  printf("4\n");
  free(toto->texels);
  free(toto);

}



main(int argc, char *argv[])

{

  glutInit(&argc,argv); 
  glutInitDisplayMode(GLUT_RGBA|GLUT_ALPHA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowSize(800, 800);
  glutInitWindowPosition(10,10);
  glutCreateWindow("Salle TP, Master informatique, Infographie \"Chibane Mourad\" "); 


  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHT2);
  glEnable(GL_LIGHT3);
  glEnable(GL_LIGHT4);

  glEnable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

  glLineWidth(1);
  glLightfv(GL_LIGHT0,GL_AMBIENT, LumiereA);
  glLightfv(GL_LIGHT0,GL_DIFFUSE, LumiereD);
  glLightfv(GL_LIGHT0,GL_SPECULAR, LumiereS);
  glLightfv(GL_LIGHT1,GL_AMBIENT, LumiereA);
  glLightfv(GL_LIGHT1,GL_DIFFUSE, LumiereD);
  glLightfv(GL_LIGHT1,GL_SPECULAR, LumiereS);

  glLightfv(GL_LIGHT2,GL_AMBIENT, LumiereA);
  glLightfv(GL_LIGHT2,GL_DIFFUSE, LumiereD);
  glLightfv(GL_LIGHT2,GL_SPECULAR, LumiereS);
  glLightfv(GL_LIGHT3,GL_AMBIENT, LumiereA);
  glLightfv(GL_LIGHT3,GL_DIFFUSE, LumiereD);
  glLightfv(GL_LIGHT3,GL_SPECULAR, LumiereS);

  glLightfv(GL_LIGHT4,GL_AMBIENT, LumiereA);
  glLightfv(GL_LIGHT4,GL_DIFFUSE, LumiereD);
  glLightfv(GL_LIGHT4,GL_SPECULAR, LumiereS);

  glShadeModel(GL_SMOOTH);//FLAT ou SMOOTH
  
  initTexture("./textures/texture_peinture_noir.tga",&T_PIEDT,0);
  initTexture("./textures/texture_UFR.tga",&T_UFR,1);
  initTexture("./textures/arbre.tga",&T_ARBRE,1);
  initTexture("./textures/herbe.tga",&T_HERBE,0);
  initTexture("./textures/ciel.tga",&T_CIEL,0);
  initTexture("./textures/murFenetre.tga",&T_FENETRE,0);
  initTexture("./textures/texture_plastique_noir.tga",&T_TOUR_DROITE,0);
  initTexture("./textures/texture_plastique_noir.tga",&T_TOUR_GAUCHE,0); 
  initTexture("./textures/texture_tour.tga",&T_TOUR_FACE,0);
  initTexture("./textures/texture_tour_ar.tga",&T_TOUR_ARRIERE,0);
  initTexture("./textures/dalleEcran4.tga",&T_ECRAN,0);
  initTexture("./textures/texture_mur.tga",&T_MUR_COULOIR,1);
  initTexture("./textures/texture_tableDessus.tga",&T_TABLE,0);
  initTexture("./textures/clavierCentre.tga",&T_CLAVIER_CENTRE,0);
  initTexture("./textures/clavierHautCentre.tga",&T_CLAVIER_HAUT_CENTRE,0);
  initTexture("./textures/clavierGauche.tga",&T_CLAVIER_GAUCHE,0);
  initTexture("./textures/clavierHautGauche.tga",&T_CLAVIER_HAUT_GAUCHE,0);
  initTexture("./textures/clavierDroit.tga",&T_CLAVIER_DROIT,0);
  initTexture("./textures/clavierHautDroit.tga",&T_CLAVIER_HAUT_DROIT,0);
  initTexture("./textures/texture_sol.tga",&T_SOL,1);
  initTexture("./textures/texture_murDos.tga",&T_MUR_DOS,1);
  initTexture("./textures/texture_plafond.tga",&T_PLAFOND,1);
  initTexture("./textures/texture_porte.tga",&T_PORTE_COULOIR,0);
  initTexture("./textures/texture_porte.tga",&T_PORTE_FOND,0);
  initTexture("./textures/texture_tableau.tga",&T_TABLEAU,0);
  
  
  creer_tour();
  creerListeFeuille();
  creerListeArbre();
  creer_ecran();
  creer_clavier();
  creer_piedT();
  creer_piedC();
  creer_platC();
  creer_chaise();
  creer_table();
  creer_rangee();  
  creer_salle();
  
  
  glutDisplayFunc(&affiche);
  glutKeyboardFunc(&camera);
  glutSpecialFunc(&special);
  glutMotionFunc(&motion);


  glutTimerFunc(40, &timer, 40);
  
  glutMainLoop();               
}
