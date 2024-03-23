#include <iostream>
#include <GL/freeglut.h>


static void alien_head(){
    glPushMatrix();
        glColor4f(0.314, 0.412, 0.6, 0.0);
        glTranslatef(0,1.8,0);
        glutSolidSphere(0.4, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0.314, 0.412, 0.6, 0.0);
        glTranslatef(0.2,2,0);
        glRotatef(-90,1,0,0);
        glutSolidCone(0.1, 0.8, 4, 4);
    glPopMatrix();
    glPushMatrix();
        glColor4f(0.314, 0.412, 0.6, 0.0);
        glTranslatef(0.2,2.7,0);
        glutSolidSphere(0.1, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0.314, 0.412, 0.6, 0.0);
        glTranslatef(-0.2,2,0);
        glRotatef(-90,1,0,0);
        glutSolidCone(0.1, 0.8, 4, 4);
    glPopMatrix();
    glPushMatrix();
        glColor4f(0.314, 0.412, 0.6, 0.0);
        glTranslatef(-0.2,2.7,0);
        glutSolidSphere(0.1, 16, 16);
    glPopMatrix();
}

static void alien_build(int angle, int alien_rotate) {
    glRotatef(angle, 0.0, -1.0, 0.0);   
    glTranslatef(5.0, 0.0, 0.0);

    //body
    glPushMatrix();
        glColor4f(0.314, 0.412, 0.6, 0.0);
        glTranslatef(0,1,0);
        glutSolidSphere(0.6, 16, 16);
    glPopMatrix();

    //head
    glPushMatrix();
        alien_head();
    glPopMatrix();

    //legs
    glPushMatrix();
        glColor4f(0.314, 0.412, 0.6, 0.0);
        glTranslatef(0.3,0.7,0);
        glRotatef(alien_rotate, 1,0,0);
        glTranslatef(-0.3,-0.7,0);

        glTranslatef(0.3,0.3,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor4f(0.314, 0.412, 0.6, 0.0);
        glTranslatef(-0.3,0.7,0);
        glRotatef(-alien_rotate, 1,0,0);
        glTranslatef(0.3,-0.7,0);

        glTranslatef(-0.3,0.3,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    //arms
    glPushMatrix();
    glColor4f(0.314, 0.412, 0.6, 0.0);
        glTranslatef(0.7,1.1,0);
        glRotatef(-alien_rotate, 1,0,0);
        glTranslatef(-0.7,-1.1,0);

        glTranslatef(0.7,0.7,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor4f(0.314, 0.412, 0.6, 0.0);
        glTranslatef(-0.7,1.1,0);
        glRotatef(alien_rotate, 1,0,0);
        glTranslatef(0.7,-1.1,0);

        glTranslatef(-0.7,0.7,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();

}

static void alien_head_shadow(float shadow_mat[]) {
    glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(0,1.8,0);
        glutSolidSphere(0.4, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(0.2,2,0);
        glRotatef(-90,1,0,0);
        glutSolidCone(0.1, 0.8, 4, 4);
    glPopMatrix();
    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(0.2,2.7,0);
        glutSolidSphere(0.1, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(-0.2,2,0);
        glRotatef(-90,1,0,0);
        glutSolidCone(0.1, 0.8, 4, 4);
    glPopMatrix();
    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(-0.2,2.7,0);
        glutSolidSphere(0.1, 16, 16);
    glPopMatrix();
}

static void build_alien_shadow(float shadow_mat[], int angle, int alien_rotate) {
    glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);

    //glRotatef(angle, 0.0, -1.0, 0.0);   
    //glTranslatef(5.0, 0.0, 0.0);

    //body
    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(0,1,0);
        glutSolidSphere(0.6, 16, 16);
    glPopMatrix();

    //head
    glPushMatrix();
        alien_head_shadow(shadow_mat);
    glPopMatrix();

    //legs
    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(0.3,0.7,0);
        glRotatef(alien_rotate, 1,0,0);
        glTranslatef(-0.3,-0.7,0);

        glTranslatef(0.3,0.3,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(-0.3,0.7,0);
        glRotatef(-alien_rotate, 1,0,0);
        glTranslatef(0.3,-0.7,0);

        glTranslatef(-0.3,0.3,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    //arms
    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(0.7,1.1,0);
        glRotatef(-alien_rotate, 1,0,0);
        glTranslatef(-0.7,-1.1,0);

        glTranslatef(0.7,0.7,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(-0.7,1.1,0);
        glRotatef(alien_rotate, 1,0,0);
        glTranslatef(0.7,-1.1,0);

        glTranslatef(-0.7,0.7,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();


}

static void pacing_alien_build(int alien_rotate) {

    //body
    glPushMatrix();
        glColor4f(0.255, 0.478, 0.027,0);
        glTranslatef(0,1,0);
        glutSolidSphere(0.6, 16, 16);
    glPopMatrix();

    //head
    glPushMatrix();
        glPushMatrix();
        glColor4f(0.255, 0.478, 0.027, 0.0);
        glTranslatef(0,1.8,0);
        glutSolidSphere(0.4, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0.255, 0.478, 0.027, 0.0);
        glTranslatef(0.2,2,0);
        glRotatef(-90,1,0,0);
        glutSolidCone(0.1, 0.8, 4, 4);
    glPopMatrix();
    glPushMatrix();
        glColor4f(0.255, 0.478, 0.027, 0.0);
        glTranslatef(0.2,2.7,0);
        glutSolidSphere(0.1, 16, 16);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0.255, 0.478, 0.027, 0.0);
        glTranslatef(-0.2,2,0);
        glRotatef(-90,1,0,0);
        glutSolidCone(0.1, 0.8, 4, 4);
    glPopMatrix();
    glPushMatrix();
        glColor4f(0.255, 0.478, 0.027, 0.0);
        glTranslatef(-0.2,2.7,0);
        glutSolidSphere(0.1, 16, 16);
    glPopMatrix();
    glPopMatrix();

    //legs
    glPushMatrix();
        glColor4f(0.255, 0.478, 0.027, 0.0);
        glTranslatef(0.3,0.7,0);
        glRotatef(alien_rotate, 1,0,0);
        glTranslatef(-0.3,-0.7,0);

        glTranslatef(0.3,0.3,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor4f(0.255, 0.478, 0.027, 0.0);
        glTranslatef(-0.3,0.7,0);
        glRotatef(-alien_rotate, 1,0,0);
        glTranslatef(0.3,-0.7,0);

        glTranslatef(-0.3,0.3,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    //arms
    glPushMatrix();
    glColor4f(0.255, 0.478, 0.027, 0.0);
        glTranslatef(0.7,1.1,0);
        glRotatef(-alien_rotate, 1,0,0);
        glTranslatef(-0.7,-1.1,0);

        glTranslatef(0.7,0.7,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glColor4f(0.255, 0.478, 0.027, 0.0);
        glTranslatef(-0.7,1.1,0);
        glRotatef(alien_rotate, 1,0,0);
        glTranslatef(0.7,-1.1,0);

        glTranslatef(-0.7,0.7,0);
        glScalef(0.25, 1, 0.25);
        glutSolidCube(1);
    glPopMatrix();
}

void pacing_alien(float alien_x_coord, bool end_of_path, int alien_path_rotate, int alien_rotate) {
    
    glPushMatrix();
        glTranslatef(0,0,alien_x_coord);
        if (end_of_path) {
            glRotatef(alien_path_rotate,0,1, 0);
        } 
        pacing_alien_build(alien_rotate);
    glPopMatrix();
    
}
