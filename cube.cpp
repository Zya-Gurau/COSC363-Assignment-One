#include <iostream>
#include <GL/freeglut.h>

static void make_cube(GLuint id){
  glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, id);
	glBegin(GL_QUADS);

        glNormal3f(0,0,1);
        glTexCoord2f(0.0,0.0);
        glVertex3f(0.0, 0.0, 0.0);      //front
        glTexCoord2f(0.0,1.0);
        glVertex3f(0, 1, 0.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(1, 1, 0.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(1, 0.0, 0.0);
        glTexCoord2f(0.0,0.0);
        
        glNormal3f(0,1,0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(0.0, 1.0, 0.0);      //top
        glTexCoord2f(0.0,1.0);
        glVertex3f(0, 1, 1.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(1, 1, 1.0);
        glTexCoord2f(1.0,0.0);
        glVertex3f(1, 1.0, 0.0);

        glNormal3f(0,0,-1);
        glTexCoord2f(0.0,0.0);
        glVertex3f(0.0, 0.0, 1);      //back
        glTexCoord2f(0.0,1.0);
        glVertex3f(0.0, 1, 1);
        glTexCoord2f(1.0,1.0);
        glVertex3f(1, 1, 1);
        glTexCoord2f(1.0,0.0);
        glVertex3f(1, 0.0, 1);
             
        glNormal3f(-1, 0, 0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(0.0, 0.0, 0.0);      //left side
        glTexCoord2f(1.0,0.0);
        glVertex3f(0.0, 0.0, 1);
        glTexCoord2f(1.0,1.0);
        glVertex3f(0.0,1.0, 1.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(0.0,1.0, 0.0);
        
        glNormal3f(1, 0, 0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(1.0, 0.0, 0.0);     //right side
        glTexCoord2f(1.0,0.0);
        glVertex3f(1.0, 0.0, 1.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(1.0,1.0, 1.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(1.0,1.0, 0.0);

        glNormal3f(0,1,0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(0.0, 0.0, 0.0);     //bottom
        glTexCoord2f(1.0,0.0);
        glVertex3f(0.0, 0.0, 1.0);
        glTexCoord2f(1.0,1.0);
        glVertex3f(1.0,0.0, 1.0);
        glTexCoord2f(0.0,1.0);
        glVertex3f(1.0,0.0, 0.0);
  

    glEnd();
    glDisable(GL_TEXTURE_2D);

}

static void make_cube_shadow() {
  glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);
          
  glPushMatrix();
    glutSolidCube(1);
  glPopMatrix();
}

void wood_crate(GLuint tex_id){
    glPushMatrix();
        make_cube(tex_id);
    glPopMatrix();
}

void metal_crate(GLuint tex_id){
    glPushMatrix();
        make_cube(tex_id);
    glPopMatrix();
}

void crate_stack(GLuint tex_id_one, GLuint tex_id_two){
    glTranslatef(0,0.01,0);
    glPushMatrix();
        glTranslatef(10,0,0);
        glScalef(2,2,2);
        metal_crate(tex_id_one);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(10,2,-1);
        glScalef(2,2,2);
        metal_crate(tex_id_one);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(10,0,-2.5);
        glScalef(2,2,2);
        wood_crate(tex_id_two);
    glPopMatrix();
}

void crate_stack_shadow(float shadowMat[]){
    glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);

    glTranslatef(0,0.01,0);

    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(10,0,0);
        glScalef(2,2,2);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(10,2,-1);
        glScalef(2,2,2);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glMultMatrixf(shadowMat);
        glTranslatef(10,0,-2.5);
        glScalef(2,2,2);
        glutSolidCube(1);
    glPopMatrix();
}



