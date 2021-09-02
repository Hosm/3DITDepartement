#include<GL/gl.h>
#include<GL/glut.h>
#include<stdio.h>
#include<String.h>
#include "formes.h"
#include "objLoader.h"

// variable blobal
float r= 10, phi = 0, theta = 0;
float sauv_r, sauv_theta, sauv_phi;
float sauv_x, sauv_y, sauv_bouton;
bool aff_grille=true, aff_repere=true;
char curseur[20]="";
enum enum_obj{
     enum_cercle=1,
     enum_disque=2,
     enum_cone=3,
     enum_cylindre=4,
     enum_sphere=5,
     enum_cube=6,
     enum_theiere=7,
     enum_texte3D=8
     }obj=enum_sphere;

 obj_scene_data data;


//-----------------------------------------------------------




//------------------------------  gestion de la lumière   ------------------------------------------------
struct Materiau{
       float r,g, b;
       float speculaire;
       int coeff;
}mat = {0.1, 0.1, 0.1, 1, 120};

struct Lumiere{
       float r, g, b;
       float distance;
       int axe;
       int  type;
       int nb;
}lum = {1, 1, 1, 10, 0, 1, 1};




void setMateriau(Materiau m){
     float coul[4] = {m.r, m.g, m.b, 0};
     float spec[4] = {m.speculaire, m.speculaire, m.speculaire, 0};
     glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, coul);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
     glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, m.coeff);
}

void setLumiere(Lumiere l){
     glEnable(GL_LIGHTING);
     glEnable(GL_LIGHT0);
     if(l.nb == 2){
             glEnable(GL_LIGHT1);
     }
     else glDisable(GL_LIGHT1);
     float amb[4] = {0.1*l.r, 0.1*l.g, 0.1*l.b, 0};
     float diff[4] = {0.9*l.r, 0.9*l.g, 0.9*l.b, 0};
     float spec[4] = {1, 1, 1, 0};
     float pos1[4] = {0, 0,0, 1};
     pos1[l.axe] = l.distance;

     glLightfv(GL_LIGHT0, GL_AMBIENT, amb);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, diff);
     glLightfv(GL_LIGHT0, GL_SPECULAR, spec);
     glLightfv(GL_LIGHT0, GL_POSITION, pos1);

     if(l.nb ==2){
         float  pos2[4] = {0, 0, 0, l.type};
         pos2[l.axe] = -l.distance;

         glLightfv(GL_LIGHT1, GL_AMBIENT, amb);
         glLightfv(GL_LIGHT1, GL_DIFFUSE, diff);
         glLightfv(GL_LIGHT1, GL_SPECULAR, spec);
         glLightfv(GL_LIGHT1, GL_POSITION, pos2);
     }
}
//------------------------------------------------------------------------------
//--------------- la fonction orbite--------------------------------------------
void Orbite(float r, float phi, float theta)
{
     glTranslatef(0,0,-r);
     glRotatef(-phi,1,0,0);
     glRotatef(-theta,0,1,0);
     }
//----------------------------Menu Objet-------------------------------
void MenuObjet(int num){
     obj=(enum_obj) num;
     glutPostRedisplay();
     }
//-----------------------------Menu Materiau------------
void MenuMateriau(int num){
     }
void MenuMatCoul(int numcoul){

     switch(numcoul){
                     case 1 :{mat.r=1;mat.g=1;mat.b=1;  glutPostRedisplay();break;}
                     case 2 : {mat.r=0.3;mat.g=0.3;mat.b=0.3;glutPostRedisplay();break;}
                      case 3 : {mat.r=0;mat.g=0;mat.b=0;  glutPostRedisplay();break;}
                      case 4 : {mat.r=1;mat.g=0;mat.b=0;  glutPostRedisplay();break;}
                      case 5 : {mat.r=0;mat.g=1;mat.b=0;  glutPostRedisplay();break;}
                      case 6 : {mat.r=0;mat.g=0;mat.b=1;  glutPostRedisplay();break;}
                     }
     }


void MenuMatSpec(int spec){

     switch(spec){
                      case 1 :{mat.speculaire=0;  glutPostRedisplay();break;}
                      case 2 : {mat.speculaire=0.25; glutPostRedisplay();break;}
                      case 3 : {mat.speculaire=0.5;  glutPostRedisplay();break;}
                      case 4 : {mat.speculaire=0.75;  glutPostRedisplay();break;}
                      case 5 : {mat.speculaire=1;  glutPostRedisplay();break;}
                     }
     }

void MenuMatCoeff(int coeff){

     switch(coeff){
                      case 1 :{mat.coeff=10;  glutPostRedisplay();break;}
                      case 2 : {mat.coeff=40; glutPostRedisplay();break;}
                      case 3 : {mat.coeff=80;  glutPostRedisplay();break;}
                      case 4 : {mat.coeff=120;  glutPostRedisplay();break;}
                     }
     }
//------------------------------------------------------------------------------
//----------------------Menu Lumière -------------------------------------------

void MenuLumCoul(int numcoul){

     switch(numcoul){
                     case 1 :{lum.r=1;lum.g=1;lum.b=1;  glutPostRedisplay();break;}
                     case 2 : {lum.r=0.3;lum.g=0.3;lum.b=0.3;glutPostRedisplay();break;}
                      case 3 : {lum.r=0;lum.g=0;lum.b=0;  glutPostRedisplay();break;}
                      case 4 : {lum.r=1;lum.g=0;lum.b=0;  glutPostRedisplay();break;}
                      case 5 : {lum.r=0;lum.g=1;lum.b=0;  glutPostRedisplay();break;}
                      case 6 : {lum.r=0;lum.g=0;lum.b=1;  glutPostRedisplay();break;}
                     }
     }

void MenuLumDis(int dis){
      switch(dis){
                     case 1 :{lum.distance=10;  glutPostRedisplay();break;}
                     case 2 : {lum.distance=15; glutPostRedisplay();break;}
                      case 3 : {lum.distance=20;  glutPostRedisplay();break;}
                      case 4 : {lum.distance=25;  glutPostRedisplay();break;}
                      case 5 : {lum.distance=30;  glutPostRedisplay();break;}
                      case 6 : {lum.distance=35;  glutPostRedisplay();break;}
                     }
     }


void MenuLumAxe(int axe){
     switch(axe){
                     case 1 :{lum.axe=0;  glutPostRedisplay();break;}
                     case 2 : {lum.axe=1; glutPostRedisplay();break;}
                     case 3 : {lum.axe=2;  glutPostRedisplay();break;}
                     }

     }

void MenuLumType(int type){

     switch(type){
                     case 1 :{lum.type=0;  glutPostRedisplay();break;}
                     case 2 : {lum.type=1; glutPostRedisplay();break;}
                      }
     }

void MenuLumNBR(int num){

     switch(num){
                     case 1 :{lum.nb=1;  glutPostRedisplay();break;}
                     case 2 : {lum.nb=2; glutPostRedisplay();break;}
                      }
     }

void MenuLumiere(int num){
     }
//------------------------------------------------------------------------------
//----------------------------- Menu Option-------------------------------------
void MenuOptions(int num_cmd){
     switch(num_cmd){
                     case 1 : aff_grille=!aff_grille; break;
                     case 2 : aff_repere=!aff_repere; break;
                     }
     }
//------------------------------------------------------------------------------
//-----------------------------Menu Arriere  plan-------------------------------

void MenuArrPlan(int num_cmd){
     switch(num_cmd){
                     case 1 :{glClearColor(1,1,1,0);  glutPostRedisplay();break;}
                     case 2 : {glClearColor(0.3,0.3,0.3,0);  glutPostRedisplay();break;}
                      case 3 : {glClearColor(0,0,0,0);  glutPostRedisplay();break;}
                     }
     }
//------------------------------------------------------------------------------
//-------------------------------Menu Mode         -----------------------------
void MenuMode(int num_cmd){
     switch(num_cmd){
                     case 1 :{glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);break;}
                     case 2 : {glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);break;}
                     case 3 : {glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);break;}
                     case 4 : {glShadeModel(GL_FLAT);break;}
                     case 5 : {glShadeModel(GL_SMOOTH);break;}
                     }
     }
//------------------------------------------------------------------------------
//------------------------------------------- Menu Principale-------------------
void MenuPrincipal(int num_cmd){
     switch(num_cmd){
                     case 0 : exit(0);
                     }
     }
//------------------------------------------------------------------------------
//-------------------------------- Créer Menu ----------------------------------
void CreerMenu(){

                 int id_mat_coul = glutCreateMenu(MenuMatCoul);
                 glutAddMenuEntry("Blanc", 1);
                 glutAddMenuEntry("Gris", 2);
                 glutAddMenuEntry("Noir", 3);
                 glutAddMenuEntry("Rouge", 4);
                 glutAddMenuEntry("Vert", 5);
                 glutAddMenuEntry("Bleu", 6);

                 int id_mat_spec = glutCreateMenu(MenuMatSpec);
                 glutAddMenuEntry("0", 1);
                 glutAddMenuEntry("0.25",2);
                 glutAddMenuEntry("0.5", 3);
                 glutAddMenuEntry("0.75", 4);
                 glutAddMenuEntry("1", 5);

                 int id_mat_coeff = glutCreateMenu(MenuMatCoeff);
                 glutAddMenuEntry("10", 1);
                 glutAddMenuEntry("40",2);
                 glutAddMenuEntry("80", 3);
                 glutAddMenuEntry("120", 4);

                 int id_lum_coul = glutCreateMenu(MenuLumCoul);
                 glutAddMenuEntry("Blanc", 1);
                 glutAddMenuEntry("Gris", 2);
                 glutAddMenuEntry("Noir", 3);
                 glutAddMenuEntry("Rouge", 4);
                 glutAddMenuEntry("Vert", 5);
                 glutAddMenuEntry("Bleu", 6);

                 int id_lum_dis= glutCreateMenu(MenuLumDis);
                 glutAddMenuEntry("10", 1);
                 glutAddMenuEntry("15", 2);
                 glutAddMenuEntry("20", 3);
                 glutAddMenuEntry("25", 4);
                 glutAddMenuEntry("30", 5);
                 glutAddMenuEntry("35", 6);

                 int id_lum_axe=glutCreateMenu(MenuLumAxe);
                 glutAddMenuEntry("X", 1);
                 glutAddMenuEntry("Y", 2);
                 glutAddMenuEntry("Z", 3);

                 int id_lum_type=glutCreateMenu(MenuLumType);
                 glutAddMenuEntry("Directionnelle", 1);
                 glutAddMenuEntry("Omnidirectionnelle", 2);

                 int id_lum_nbr=glutCreateMenu(MenuLumNBR);
                 glutAddMenuEntry("Une", 1);
                 glutAddMenuEntry("Deux", 2);

                 int id_options = glutCreateMenu(MenuOptions);
                 glutAddMenuEntry("Grille on/of\tG", 1);
                 glutAddMenuEntry("Repere on/of\tR", 2);

                 int id_arr_plan = glutCreateMenu(MenuArrPlan);
                 glutAddMenuEntry("Blanc", 1);
                 glutAddMenuEntry("Gris", 2);
                 glutAddMenuEntry("Noir", 3);


                 int id_mode = glutCreateMenu(MenuMode);
                 glutAddMenuEntry("Sommets", 1);
                 glutAddMenuEntry("Filaire", 2);
                 glutAddMenuEntry("Solide", 3);
                 glutAddMenuEntry("Facettes", 4);
                 glutAddMenuEntry("Lissage", 5);

                 int id_objet = glutCreateMenu(MenuObjet);
                 glutAddMenuEntry("Cercle", enum_cercle);
                 glutAddMenuEntry("Disque", enum_disque);
                 glutAddMenuEntry("Cône", enum_cone);
                 glutAddMenuEntry("Cylindre", enum_cylindre);
                 glutAddMenuEntry("Sphere", enum_sphere);
                 glutAddMenuEntry("Cube", enum_cube);
                 glutAddMenuEntry("Théière", enum_theiere);
                 glutAddMenuEntry("Texte3D", enum_texte3D);

                 int id_Materiau = glutCreateMenu(MenuMateriau);
                 glutAddSubMenu("Couleur", id_mat_coul);
                 glutAddSubMenu("Speculaire",id_mat_spec);
                 glutAddSubMenu("Coeff.Spec",id_mat_coeff);

                 int id_lumiere=glutCreateMenu(MenuLumiere);
                 glutAddSubMenu("Couleur",id_lum_coul);
                 glutAddSubMenu("Distance",id_lum_dis);
                 glutAddSubMenu("Axe",id_lum_axe);
                 glutAddSubMenu("Type",id_lum_type);
                 glutAddSubMenu("Nombre",id_lum_nbr);

                 int id_principal = glutCreateMenu(MenuPrincipal);
                 glutAddSubMenu("Objets", id_objet);
                 glutAddSubMenu("Options", id_options);
                 glutAddSubMenu("Arriere Plan", id_arr_plan);
                 glutAddSubMenu("Mode", id_mode);
                 glutAddSubMenu("Materiau", id_Materiau);
                 glutAddSubMenu("Lumière",id_lumiere);
                 glutAddMenuEntry("Quitter", 0);


                 glutAttachMenu(GLUT_RIGHT_BUTTON);
     }
//------------------------------------------------------------------------------
//-------------------------------- fonction d'affichage ------------------------
void Afficher(){
     glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // pour effacer l'ecran: liberer des tempons ; des zones memoires.
     //position du camera
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
      Orbite(r, phi, theta);
     int h=3;
     glDisable(GL_LIGHTING);
      glColor3f(0,0,1);
     if(aff_repere){repere(4.0); glutPostRedisplay();}
     if(aff_grille){ grille(3, 20); glutPostRedisplay();}
     glEnable(GL_LIGHTING);
     setLumiere(lum);
    // setMateriau(mat);
     switch(obj){
                 case enum_cercle: cercle(4, 20); break;
                 case enum_cone: cone(1, h, 120); break;
                 case enum_cube: glutSolidCube(1); break;
                 case enum_cylindre:   cylindre(1, h, 120); break;
                 case enum_disque:  disque(5,20); break;
                 case enum_sphere: glutSolidSphere(1, 24, 12); break;
               //  case enum_theiere: glutSolidTeapot(2); break;
                 case enum_theiere: ProcessObject(data); break;
                // case enum_texte3D: Texte3D("OPENGL",1);
                 }
     glColor3f(1,1,1);
     Texte2DScene(5,20,0,curseur,3);

     //fin
     glutSwapBuffers();// ou glFlush()
}
//------------------------------------------------------------------------------
//---------------------------- Fonction Clavier---------------------------------
void Clavier(unsigned char Key, int x, int y)
{
     switch (Key)
     {
            case '-': r+=0.1;
            break;
            case '+': if(r>0.1) r-=0.1; break;
            case 'G': MenuOptions(1); break;
            case 'R': MenuOptions(2); break;

            }
glutPostRedisplay();
}
//------------------------------------------------------------------------------
     void Special(int Key, int x, int y)
{
     switch (Key)
     {
            case GLUT_KEY_RIGHT: theta+=1;
            break;
            case GLUT_KEY_LEFT: theta-=1;break;
            case GLUT_KEY_UP: phi+=1;break;
            case GLUT_KEY_DOWN: phi-=1;break;
            case 'GLUT_KEY_F1': MenuMode(1); break;
            case 'GLUT_KEY_F2': MenuMode(2); break;
            case 'GLUT_KEY_F3': MenuMode(3); break;
            }
glutPostRedisplay();
}
//------------------------------------------------------------------------------
//--------------------------------- fonctions souris----------------------------
void Souris (int bouton , int etat , int x, int y){
     sauv_r =r;
     sauv_phi = phi;
     sauv_theta = theta;
     sauv_x = x;
     sauv_y = y;
     sauv_bouton = bouton;
     }
 //------------------------------------------------------------------------------
void Motion(int x, int y)
{
     if(sauv_bouton == GLUT_LEFT_BUTTON){
                       theta = sauv_theta +0.2 *(x-sauv_x);
                       phi = sauv_phi - 0.2 *(y-sauv_y);
                       glutPostRedisplay();
                    }
     else if(sauv_bouton == GLUT_MIDDLE_BUTTON){
                         r = sauv_r + 0.1* (y - sauv_y);
                         if(r< 0.1) r = 0.1;
                         glutPostRedisplay();
          }
 }
//------------------------------------------------------------------------------
 void Passive(int x, int y){
      sprintf(curseur,"X: %d  Y: %d",x,y);
       glutPostRedisplay();
      }
//------------------------------------------------------------------------------
//-----------------------------Redimension--------------------------------------
void Redimensionner(int w, int h){
     glViewport(0,0,w,h);
     //projection
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();
     gluPerspective(60,(float)w/h, 0.1, 1000);  //cette fonction est utilisee ici car elle aura besoin des parametre w et h pour que limage ne deforme pas.

}
int importObj(){
    parse_obj_scene(&data, (char *)"dept.obj");
    return 0;
}

//------------------------------------------------------------------------------
//------------------------------- la méthode principale-------------------------

int main(int argc, char ** argv){
    //glut initialisation
    importObj();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(50,50);
    glutCreateWindow("TP OPENGL");
    LoadGLTextures(data);
    glutDisplayFunc( Afficher );
    glutReshapeFunc( Redimensionner );
    glutKeyboardFunc(Clavier);
    glutSpecialFunc(Special);

    glutMouseFunc(Souris);
    glutMotionFunc(Motion);
    glutPassiveMotionFunc(Passive);
    CreerMenu();
    // gl Initialisation
    glClearColor(0,0,0,0);
    glEnable(GL_DEPTH_TEST);
    //Terminer

    glutMainLoop(); // boocle de fin
    return 0;

}

