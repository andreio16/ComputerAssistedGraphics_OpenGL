/*
 *  Programul este un exemplu de utilizare a primitivei bitmap
 *  in OpenGL, pentru desenarea fonturilor.
 */
#include "glos.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

void CALLBACK myReshape(GLsizei w, GLsizei h);
void CALLBACK display(void);
// tabloul care con�ine litera E, 16X12 bi�i
GLubyte litera_E[24] = {
    0xff, 0xc0, 0xff, 0xc0, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0x00, 0xff, 0x00, 0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x00,
    0xff, 0xc0, 0xff, 0xc0};

void CALLBACK display(void)
{
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    glClearColor (1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f (0.0, 0.0, 0.0);

    glRasterPos2i (-2.0, 0.0); //pozitia curent� pentru primul bitmap
	// dat� �n unit�ti logice (sunt 10 unit��i pe axa x �n intervalul(-5, 5))
    glBitmap (10, 12, 0.0, 0.0, 20.0, 0.0, litera_E); // deplasarea este dat�
	//�n pixeli;  20 de pixeli pe axa x
	// 
    glBitmap (10, 12, 0.0, 0.0, 20.0, 0.0, litera_E);
    glBitmap (10, 12, 0.0, 0.0, 20.0, 0.0, litera_E);
	glBitmap (10, 12, 0.0, 0.0, 20.0, 0.0, litera_E);
    glFlush();
}
// proiectie ortogonal�
//se mapeaz� 10 unit�ti pe fiecare ax�, o unitate are 20 pixeli
void CALLBACK myReshape(GLsizei w, GLsizei h)
{
 if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h) 
    glOrtho (-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w, 
        5.0*(GLfloat)h/(GLfloat)w, -5.0, 5.0);
    else 
    glOrtho (-5.0*(GLfloat)w/(GLfloat)h, 
        5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -5.0, 5.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_RGB);
    auxInitPosition (0, 0, 200, 200);
    auxInitWindow ("Bitmap_E");
    auxReshapeFunc (myReshape);
    auxMainLoop(display);
    return(0);
}
