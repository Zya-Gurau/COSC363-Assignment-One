#include <iostream>
#include <GL/freeglut.h>

void spaceship_satellite_dish(int angle, GLUquadric *q) {
    

    glPushMatrix();
        glColor4f(0.302, 0.298, 0.263, 0.0);
        glRotatef(270,1,0,0);
        glutSolidCone(0.2, 1, 4, 4);
    glPopMatrix();

    glRotatef(angle, 0, 1, 0);

    glPushMatrix();
        glColor4f(0.212, 0.208, 0.173, 0.0);
        glTranslatef(0, 0.9, 0);
        glRotatef(45,1,0,0);
        gluDisk(q, 0.0, 0.6, 20, 3);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0.302, 0.298, 0.263, 0.0);
        glTranslatef(0, 0.9, 0);
        glRotatef(225,1,0,0);
        
        glutSolidCone(0.1, 0.5, 4, 4);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0.431, 0.541, 0.416, 0.0);
        glTranslatef(0, 1.2, -0.3);
        
        gluSphere(q, 0.1, 16, 16);
    glPopMatrix();
}

void spaceship_landing_gear(GLUquadric *q) {
    glRotatef(315,0,1,0);

    glPushMatrix();
        glColor4f(0.396, 0.443, 0.459, 0.0);
        glTranslatef(0, 2, 0.0);
        glRotatef(75,1,0,0);
        
        gluCylinder(q, 0.4, 0.4, 1.8, 15, 1);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0.302, 0.345, 0.361, 0.0);
        glTranslatef(0, 0.25, 0.5);
        glScalef(1.0, 0.5, 1);
        glutSolidCube(1.0);
    glPopMatrix();
}

void spaceship_build(int spaceship_dish_rotate, int spaceship_dish_two_rotate, GLUquadric *q){

    glPushMatrix();
        glColor4f(0.525, 0.549, 0.561, 0.0);
        glTranslatef(0.0, 3.0, 0.0);
        glScalef(4.0, 3.0, 6.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0., 0.5, 0.5, 0.0);
        glTranslatef(0.0, 3, -2.75);
        glScalef(1.5, 1.5, 1.5);
        gluSphere(q,1.0,16, 16);
    glPopMatrix();

    glPushMatrix();
        glColor4f(0.302, 0.345, 0.361, 0.0);
        glTranslatef(2.5, 5, 0.0);
        glScalef(4.0, 3.0, 6.0);
        gluCylinder(q, 0.4, 0.4, 1, 15, 1);
        gluQuadricDrawStyle(q, GLU_FILL);
        gluDisk(q, 0.0, 0.4, 20, 3);
        glTranslatef(0.0, 0.0, 1);
        gluDisk(q, 0.0, 0.4, 20, 3);

    glPopMatrix();

    glPushMatrix();
        glColor4f(0.302, 0.345, 0.361, 0.0);
        glTranslatef(-2.5, 5, 0.0);
        glScalef(4.0, 3.0, 6.0);
        gluCylinder(q, 0.4, 0.4, 1, 15, 1);
        gluQuadricDrawStyle(q, GLU_FILL);
        gluDisk(q, 0.0, 0.4, 20, 3);
        glTranslatef(0.0, 0.0, 1);
        gluDisk(q, 0.0, 0.4, 20, 3);

    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.5, 0, 2.2);
        spaceship_landing_gear(q);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5, 0, 2.2);
        glRotatef(90,0,1,0);
        spaceship_landing_gear(q);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5, 0, -2.5);
        glRotatef(180,0,1,0);
        spaceship_landing_gear(q);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.5, 0, -2.5);
        glRotatef(270,0,1,0);
        spaceship_landing_gear(q);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5, 4.45, -2.25);
        spaceship_satellite_dish(spaceship_dish_rotate, q);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-1.5, 4.45, -2.25);
        spaceship_satellite_dish(spaceship_dish_two_rotate, q);
    glPopMatrix();
}

//SHADOW
void spaceship_satellite_dish_shadow(int angle, GLUquadric *q) {
    

    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glRotatef(270,1,0,0);
        glutSolidCone(0.2, 1, 4, 4);
    glPopMatrix();

    glRotatef(angle, 0, 1, 0);

    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(0, 0.9, 0);
        glRotatef(45,1,0,0);
        gluDisk(q, 0.0, 0.6, 20, 3);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(0, 0.9, 0);
        glRotatef(225,1,0,0);
        
        glutSolidCone(0.1, 0.5, 4, 4);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.2, 0.2, 0.2);
        glTranslatef(0, 1.2, -0.3);
        
        gluSphere(q, 0.1, 16, 16);
    glPopMatrix();
}


void spaceship_landing_gear_shadow(GLUquadric *q, float shadow_mat[]) {
    glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);
    glRotatef(315,0,1,0);

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(0, 2, 0.0);
        glRotatef(75,1,0,0);
        gluCylinder(q, 0.4, 0.4, 1.8, 15, 1);
    glPopMatrix();

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(0, 0.25, 0.5);
        glScalef(1.0, 0.5, 1);
        glutSolidCube(1.0);
    glPopMatrix();
}

void spaceship_build_shadow(int spaceship_dish_rotate, int spaceship_dish_two_rotate, GLUquadric *q, float shadow_mat[]){
    glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(0.0, 3.0, 0.0);
        glScalef(4.0, 3.0, 6.0);
        glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(0.0, 3, -2.75);
        glScalef(1.5, 1.5, 1.5);
        //gluSphere(q,1.0,16, 16);
    glPopMatrix();

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(2.5, 5, 0.0);
        glScalef(4.0, 3.0, 6.0);
        gluCylinder(q, 0.4, 0.4, 1, 15, 1);
        gluQuadricDrawStyle(q, GLU_FILL);
        gluDisk(q, 0.0, 0.4, 20, 3);
        glTranslatef(0.0, 0.0, 1);
        gluDisk(q, 0.0, 0.4, 20, 3);

    glPopMatrix();

    glPushMatrix();
        glMultMatrixf(shadow_mat);
        glTranslatef(-2.5, 5, 0.0);
        glScalef(4.0, 3.0, 6.0);
        gluCylinder(q, 0.4, 0.4, 1, 15, 1);
        gluQuadricDrawStyle(q, GLU_FILL);
        gluDisk(q, 0.0, 0.4, 20, 3);
        glTranslatef(0.0, 0.0, 1);
        gluDisk(q, 0.0, 0.4, 20, 3);

    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.5, 0, 2.2);
        spaceship_landing_gear_shadow(q, shadow_mat);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5, 0, 2.2);
        glRotatef(90,0,1,0);
        spaceship_landing_gear_shadow(q, shadow_mat);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(1.5, 0, -2.5);
        glRotatef(180,0,1,0);
        spaceship_landing_gear_shadow(q, shadow_mat);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-1.5, 0, -2.5);
        glRotatef(270,0,1,0);
        spaceship_landing_gear_shadow(q, shadow_mat);
    glPopMatrix();

    glPushMatrix();
    glMultMatrixf(shadow_mat);
        glTranslatef(1.5, 4.45, -2.25);
        spaceship_satellite_dish_shadow(spaceship_dish_rotate, q);
    glPopMatrix();
    glPushMatrix();
    glMultMatrixf(shadow_mat);
        glTranslatef(-1.5, 4.45, -2.25);
        spaceship_satellite_dish_shadow(spaceship_dish_two_rotate, q);
    glPopMatrix();

}