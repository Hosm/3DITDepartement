#include<GL/gl.h>
#include<math.h>
#include "texte.h"
#include "objLoader.h"
#include "SOIL.h"

GLuint	texture[10];			// Storage For One Texture ( NEW )

void LoadGLTextures(obj_scene_data data)									// Load Bitmaps And Convert To Textures
{
    for(int i=0; i<data.material_count; i++)
	{
	    obj_material *m = data.material_list[i];
	/* load an image file directly as a new OpenGL texture */
        texture[i] = SOIL_load_OGL_texture(
            m->texture_filenameDif,
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
             SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_MULTIPLY_ALPHA
            );
        if(texture[i] == 0)
            printf( "SOIL loading error: '%s' ->'%s' \n",SOIL_last_result(),m->texture_filenameDif);
            else
            printf( "SOIL loading succes: '%s' ->'%s' \n",SOIL_last_result(),m->texture_filenameDif);
	}
										// Return Success
}

void repere(float a){
             // l'axe X

     glBegin(GL_LINES);
     glColor3f(1,0,0);
         glVertex3f(0,0,0);
         glVertex3f(a,0,0);
             // l'axe Y
     glColor3f(0,0,1);
         glVertex3f(0,0,0);
         glVertex3f(0,a,0);
              // l'axe Z
     glColor3f(0,1,0);
         glVertex3f(0,0,0);
         glVertex3f(0,0,a);
     glEnd();
    //  Texte2DScene(a,0,0,"X", 1);
     // Texte2DScene(0,a,0,"Y", 1);
    //  Texte2DScene(0,0,a,"Z", 1);
     }


void cercle(float r, int seg){
     float pas= 2*M_PI/seg;
     glBegin(GL_LINE_LOOP);
     glColor3f(0.54,0.15,1);
     for(int i=0;i<seg;i++){
             float x=r*cos(i*pas);
             float z=r*sin(i*pas);
             glVertex3f(x,0,z);
     }
     glEnd();
     }


void disque(float r, int seg){
     float pas= 2*M_PI/seg;
     glBegin(GL_POLYGON);
     glColor3f(0.54,0.15,1);
     for(int i=0;i<seg;i++){
             float x=r*cos(i*pas);
             float z=r*sin(i*pas);
             glVertex3f(x,0,z);
     }
     glEnd();
     }

void cone(float r, float h, int seg){
     float pas= 2*M_PI/seg;
     glBegin(GL_TRIANGLE_FAN);
     glColor3f(0.54,0.15,1);
      glVertex3f(0,h,0);
     for(int i=0;i<=seg;i++){
             float x=r*cos(i*pas);
             float z=r*sin(i*pas);
             glVertex3f(x,0,z);
             }
     glEnd();
     }


void setMaterials(obj_material *m){
     float diffus[4] = {m->diff[0], m->diff[1], m->diff[2], 1};
     float amb[4] = {m->amb[0], m->amb[1], m->amb[2], 1};
     float spec[4] = {m->spec[0], m->spec[1], m->spec[2], 1};
     float emis[4] = {m->emis[0], m->emis[1], m->emis[2], 0};
     glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffus);
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, amb);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
     glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,emis);
     glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, m->shiny);

}

void loadTexture(int i){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[i]);
    glEnable(GL_BLEND);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);  // when texture area is small, bilinear filter the closest mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // when texture area is large, bilinear filter the first mipmap
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  // texture should tile
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


void ProcessObject(obj_scene_data data){

	for(int i=0; i<data.face_count; i++)
	{

	    obj_face *o = data.face_list[i];

	    obj_material *m = data.material_list[o->material_index];
	   printf("facette %i : %s with vertex_count:%i \n ",i,m->name,o->vertex_count);
	    setMaterials(m);
        //loadTexture(o->material_index);
		glBegin(GL_POLYGON);
        obj_vector *vt = data.vertex_texture_list[o->texture_index[0]];
        if (vt->e[0]==NULL)
                for(int j=0; j<o->vertex_count; j++)
                {
                    obj_vector *v = data.vertex_list[o->vertex_index[j]];
                    glVertex3f(v->e[0],v->e[1],v->e[2]);

                    /*obj_vector *vn = data.vertex_normal_list[o->normal_index[j]];
                    glNormal3f(vn->e[0],vn->e[1],vn->e[2]);*/
                    printf("coordonnée  :(%f,%f,%f)\n ",v->e[0],v->e[1],v->e[2]);
                }
        else
                for(int j=0; j<o->vertex_count; j++)
                {
                    obj_vector *vt = data.vertex_texture_list[o->texture_index[j]];
                    glTexCoord3f(vt->e[0],vt->e[1],vt->e[2]);

                    obj_vector *v = data.vertex_list[o->vertex_index[j]];
                    glVertex3f(v->e[0],v->e[1],v->e[2]);

                    obj_vector *vn = data.vertex_normal_list[o->normal_index[j]];
                    glNormal3f(v->e[0],v->e[1],v->e[2]);


                    printf("coordonnée with texture :(%f,%f,%f)\n ",v->e[0],v->e[1],v->e[2]);

                }
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glEnd();
	}
}


void cylindre(float r, float h, int seg){
     float pas= 2*M_PI/seg;
     glBegin(GL_QUAD_STRIP);
     glColor3f(0.54,0.15,1);

     for(int i=0;i<=seg;i++){
             float x=r*cos(i*pas);
             float z=r*sin(i*pas);
             glVertex3f(x,h,z);
             glVertex3f(x,0,z);
             }
     glEnd();
     }

void toure(float r, float h, int seg){
     float pas= 2*M_PI/seg;
     glBegin(GL_TRIANGLE_FAN);
     glColor3f(0.54,0.15,1);
      glVertex3f(0,2*h,0);
     for(int i=0;i<=seg;i++){
             float x=r*cos(i*pas);
             float z=r*sin(i*pas);
             glVertex3f(x,h,z);
             }
     glEnd();
     cylindre(r,h,seg);
     }


//la grille

void grille(float a , int n){
     glBegin(GL_LINES);
     for(int i=0;i<n;i++){
             float pas=(i*a/(n-1));
             glVertex3f(-a/2,0,-a/2+pas);
             glVertex3f(a/2,0,-a/2+pas);
             glVertex3f(-a/2+pas,0,-a/2);
             glVertex3f(-a/2+pas,0,a/2);
             }
     glEnd();
     }






