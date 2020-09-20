/*  mipmap.c
 *  Programul demonstreaz� utilizarea tehnicii mipmap pentru maparea texturilor
 *  Pentru fiecare valoare a parametrului level s-a ales o alt� valoare solid�.
 *  �n acest fel acelasi patrulater este desenat cu culori diferite pe m�sur� 
 *  ce suprafata sa se �ndep�rteaz� de punctul de vizualizare
 */
#include "glos.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glaux.h>

void myinit(void);
void makeImages(void);
void CALLBACK display(void);
void CALLBACK myReshape(GLsizei w, GLsizei h);

GLubyte mipmapImage32[32][32][3]; //nivelul 0
GLubyte mipmapImage16[16][16][3]; //nivelul 1
GLubyte mipmapImage8[8][8][3]; //nivelul 2
GLubyte mipmapImage4[4][4][3]; //nivelul 3
GLubyte mipmapImage2[2][2][3]; //nivelul 4
GLubyte mipmapImage1[1][1][3]; //nivelul 5
//se ini�ializeaz� cele 6 imagini 
void makeImages(void)
{
    int i, j;
    
    for (i = 0; i < 32; i++) {
    for (j = 0; j < 32; j++) {
        mipmapImage32[i][j][0] = 255;
        mipmapImage32[i][j][1] = 255;
        mipmapImage32[i][j][2] = 0;
    }
    }
    for (i = 0; i < 16; i++) {
    for (j = 0; j < 16; j++) {
        mipmapImage16[i][j][0] = 255;
        mipmapImage16[i][j][1] = 0;
        mipmapImage16[i][j][2] = 255;
    }
    }
    for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
        mipmapImage8[i][j][0] = 255;
        mipmapImage8[i][j][1] = 0;
        mipmapImage8[i][j][2] = 0;
    }
    }
    for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
        mipmapImage4[i][j][0] = 0;
        mipmapImage4[i][j][1] = 255;
        mipmapImage4[i][j][2] = 0;
    }
    }
    for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
        mipmapImage2[i][j][0] = 0;
        mipmapImage2[i][j][1] = 0;
        mipmapImage2[i][j][2] = 255;
    }
    }
    mipmapImage1[0][0][0] = 255;
    mipmapImage1[0][0][1] = 255;
    mipmapImage1[0][0][2] = 255;
}

void myinit(void)
{    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glShadeModel(GL_FLAT);

    glTranslatef(0.0, 0.0, -3.6);
    makeImages();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	//se specific� textura corespunz�toare fiec�rui nivel
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 32, 32, 0,
         GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage32[0][0][0]);
    glTexImage2D(GL_TEXTURE_2D, 1, 3, 16, 16, 0,
         GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage16[0][0][0]);
    glTexImage2D(GL_TEXTURE_2D, 2, 3, 8, 8, 0,
         GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage8[0][0][0]);
    glTexImage2D(GL_TEXTURE_2D, 3, 3, 4, 4, 0,
         GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage4[0][0][0]);
    glTexImage2D(GL_TEXTURE_2D, 4, 3, 2, 2, 0,
         GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage2[0][0][0]);
    glTexImage2D(GL_TEXTURE_2D, 5, 3, 1, 1, 0,
         GL_RGB, GL_UNSIGNED_BYTE, &mipmapImage1[0][0][0]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, 
    GL_NEAREST_MIPMAP_NEAREST);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
}

void CALLBACK display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //desenarea unui patrulater
	//i se vor aplica texturi diferite pe m�sur� ce se �ndep�rteaz�
	//de punctul de vizualizare

	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-2.0, -1.0, 0.0);
		glTexCoord2f(0.0, 8.0); glVertex3f(-2.0, 1.0, 0.0);
		glTexCoord2f(8.0, 8.0); glVertex3f(2000.0, 1.0, -6000.0);
		glTexCoord2f(8.0, 0.0); glVertex3f(2000.0, -1.0, -6000.0);
    glEnd();

    glFlush();
}

void CALLBACK myReshape(GLsizei w, GLsizei h)
{
    if (!h) return;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 1.0*(GLfloat)w/(GLfloat)h, 1.0, 30000.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    auxInitDisplayMode (AUX_SINGLE | AUX_RGB | AUX_DEPTH16);
    auxInitPosition (0, 0, 500, 500);
    auxInitWindow ("Maparea texturilor utiliz�nd tehnica mipmap");
    myinit();
    auxReshapeFunc (myReshape);
    auxMainLoop(display);
    return(0);
}
