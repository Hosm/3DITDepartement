#include<GL/glut.h>
#include<GL/gl.h>
void Texte2DScene(float x, float y, float z, char * texte , int taille){

     void * police;
     switch(taille)
     {
                   case 1: police=GLUT_BITMAP_HELVETICA_10; break;
                   case 2: police=GLUT_BITMAP_HELVETICA_12; break;
                   case 3: police=GLUT_BITMAP_HELVETICA_18; break;
                   default: police=GLUT_BITMAP_TIMES_ROMAN_24; break;
                   }

     glRasterPos3f(x,y,z);
     for(int i=0; texte[i] != '\0'; i++)
     glutBitmapCharacter(police,texte[i]);


              }

