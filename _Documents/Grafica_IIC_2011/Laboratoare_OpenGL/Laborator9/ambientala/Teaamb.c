
/*
 *  teaamb.c
 *  Programul afiseaza trei cesti de ceai, cu aceeasi surs� de lumin�
 *  dar cu diferite valori pentru coeficientii de reflexie pentru lumina ambiental� 
 */
#include "glos.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

void myinit(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);

/*  Initializeaza sursa de lumina si modelul de iluminare.
 */
void myinit(void)
{  //set�ri pentru sursa de lumin�
    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };//intensitatea
	//componentei ambientale din sursa 0 este nula
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };//intensitatea
	//componentei difuze din sursa 0 este maxima pentru fiecrae compopnenta de
	//culoare
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };//intensitatea
	//componentei speculare din sursa 0 este maxima pentru fiecrae compopnenta de
	//culoare
/*  pozitia sursei de lumin� nu este cea implicit� */
	
    GLfloat light_position[] = { 1.0, 0.0, 0.0, 0.0 };
	//sursa de lumina pe axa x la infinit
    GLfloat global_ambient[] = { 0.75, 0.75, 0.75, 1.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	//lumina ambientala in scena
    
    glFrontFace (GL_CW);//orientarea implicit[ a v�rfurilor �n sensul rotirii acelor
    glEnable(GL_LIGHTING); //activare iluminare
    glEnable(GL_LIGHT0); //activare sursa 0
    glEnable(GL_AUTO_NORMAL); //activare calculare normale daca v�rfurile 
	//s-au determinat cu GL_MAP2_VERTEX_3 sau GL_MAP2_VERTEX_4
    glEnable(GL_NORMALIZE); //activare normalizare (vectori unitari) vectori
    glDepthFunc(GL_LESS); //compara�ia la ascunderea suprafe�elor
    glEnable(GL_DEPTH_TEST); //activare test ad�ncime
}

void CALLBACK display(void)
{
    GLfloat low_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
    GLfloat more_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
    GLfloat most_ambient[] = { 1.0, 1.0, 1.0, 1.0 };

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*  material has small ambient reflection   */
	//coeficient de reflexie pentru lumina ambientala mic
    glMaterialfv(GL_FRONT, GL_AMBIENT, low_ambient);
    glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
    glPushMatrix ();
    glTranslatef (0.0, 2.0, 0.0);
    auxSolidTeapot(1.0);
    glPopMatrix ();

    /*  material has moderate ambient reflection    */
	//coeficient de reflexie pentru lumina ambientala mediu
    glMaterialfv(GL_FRONT, GL_AMBIENT, more_ambient);
    glPushMatrix ();
    glTranslatef (0.0, 0.0, 0.0);
    auxSolidTeapot(1.0);
    glPopMatrix ();

    /*  material has large ambient reflection   */
	//coeficient de reflexie pentru lumina ambientala mare
    glMaterialfv(GL_FRONT, GL_AMBIENT, most_ambient);
    glPushMatrix ();
    glTranslatef (0.0, -2.0, 0.0);
    auxSolidTeapot(1.0);
    glPopMatrix ();
    glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) 
    glOrtho (-4.0, 4.0, -4.0*(GLfloat)h/(GLfloat)w, 
        4.0*(GLfloat)h/(GLfloat)w, -10.0, 10.0);
    else 
    glOrtho (-4.0*(GLfloat)w/(GLfloat)h, 
        4.0*(GLfloat)w/(GLfloat)h, -4.0, 4.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}


int main(int argc, char** argv)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
    auxInitPosition (0, 0, 500, 500);
    auxInitWindow ("Iluminarea ambiental� pentru materiale cu coeficien�i de reflexie diferi�i");
    myinit();
    auxReshapeFunc (myReshape);
    auxMainLoop(display);
    return(0);
}
