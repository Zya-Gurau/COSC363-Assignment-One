#include <iostream>
#include <GL/freeglut.h>
#include <cmath>

float o_none[4] = {0,0,0,0};

void normal(int i) 
{
    float xd1, zd1, xd2, zd2;
    xd1 = i - (i-1);
    zd1 = (0.03*(i*i)) - (0.03*((i-1)*(i-1)));
    xd2 = i+1 - i;
    zd2 = (0.03*((i+1)*(i+1))) - (0.03*(i*i));
    glNormal3f(-(zd1 + zd2), 0, (xd1 + xd2));
}

void o_normal(int i) //vertex normal
{
    float xd1, zd1, xd2, zd2;
    xd1 = i - (i-1);
    zd1 = -(0.07*(i*i)) +(0.07*((i-1)*(i-1)));
    xd2 = i+1 - i;
    zd2 = -(0.07*((i+1)*(i+1))) + (0.07*(i*i));
    glNormal3f(-(zd1 + zd2), 0, (xd1 + xd2));
}

void landing_pad() {
    glPushMatrix();
        glPushMatrix();
            glColor3f(0,0,0);
            glScalef(25,1,25);
            glTranslatef(0,0.5,0);
            glutSolidCube(1);
        glPopMatrix();
        glColor3f(1,1,1);
    glPopMatrix();
}

void landing_pad_pipe() {
    int n_slices = 20;
    int n_points = 40;
    float angle = 0.08;
    int b = 20;
    GLfloat wx[41];
    GLfloat wz[41];
    GLfloat vx[41]; 
    GLfloat vz[41]; 
    GLfloat wy[41];
    GLfloat vy[41];

    GLfloat vmx[41];
    GLfloat vmy[41];
    GLfloat vmz[41];
    GLfloat vnx[41];
    GLfloat vny[41];
    GLfloat vnz[41];

    for (int i = 0; i <= 40; i++) {
        wx[i] = 0;
        vx[i] = 4;
        wz[i] = i;
        vz[i] = i;
        wy[i] = -(0.07*((i-b)*(i-b)));
        vy[i] = -(0.07*((i-b)*(i-b)));
        }



    glScalef(0.1, 0.1, 0.1);
    glRotatef(180, 0,1,0);
    for (int slice = 0; slice < n_slices; slice++)
    {
        for (int i = 0; i < n_points; i++)
        {
                
                vx[i] = (wx[i] * cos(angle) + wz[i] * sin(angle)+7);
                vy[i] = (wy[i]) ;
                vz[i] = (-wx[i] * sin(angle) + wz[i] * cos(angle));
            }
        glBegin(GL_QUAD_STRIP);
            for (int i = 0; i < n_points; i++)
            {
                if(i > 0) {o_normal(i-b);}
               // glNormal3f(vnx[i], vny[i], vnz[i]);
                glVertex3f(wx[i], wy[i], wz[i]); //vi

                //glNormal3f(vmx[i], vmy[i], vmz[i]);
                glVertex3f(vx[i], vy[i], vz[i]); //wi
                }
        glEnd();
        for (int i = 0; i < n_points; i++)
        {
            if (slice < n_slices-1) {
                wx[i] = vx[i];
            wy[i] = vy[i];
            wz[i] = vz[i];
            vnx[i] = vmx[i]; vny[i] = vmy[i]; vnz[i] = vmz[i];
            }
            
        }
        
    }
}

void fuel_tank(GLUquadric *q) {
    glPushMatrix();
        glRotatef(90, 1,0,0);
        glTranslatef(2.5, 5, 0.0);
        glScalef(4.0, 3.0, 6.0);
        gluCylinder(q, 0.4, 0.4, 1, 15, 1);
        gluQuadricDrawStyle(q, GLU_FILL);
        gluDisk(q, 0.0, 0.4, 20, 3);
        glTranslatef(0.0, 0.0, 1);
        gluDisk(q, 0.0, 0.4, 20, 3);
    glPopMatrix();
}

void fuel_tank_shadow(GLUquadric *q, float shadow_mat[]) {
    glPushMatrix();
    
        glMultMatrixf(shadow_mat);
        glRotatef(90, 1,0,0);
        glTranslatef(2.5, 5, 0.0);
        glScalef(4.0, 3.0, 6.0);
        glRotatef(180,0,1,0);
        gluCylinder(q, 0.4, 0.4, 1, 15, 1);
        gluQuadricDrawStyle(q, GLU_FILL);
        gluDisk(q, 0.0, 0.4, 20, 3);
        glTranslatef(0.0, 0.0, 1);
        gluDisk(q, 0.0, 0.4, 20, 3);
    glPopMatrix();
}

void draw_landing_pad() {
    landing_pad();
}

void draw_fuel_station(GLUquadric *q, float shadow_mat[]) {
    glPushMatrix();
        
        glTranslatef(22,2.5,-14); 
        glRotatef(-60, 0,1,0);
        landing_pad_pipe();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.49, 0.255, 0.169);
        glTranslatef(0,12,-34);
        glScalef(3,2,3);
        fuel_tank(q);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.337, 0.349, 0.29);
        glScalef(1,0.6,1);
        glTranslatef(24.4,2.5,-14);
        glRotatef(-60, 0,1,0);
        glutSolidCube(5);
    glPopMatrix();
}

void draw_fuel_tank_shadow(GLUquadric *q, float shadow_mat[]) {
    glDisable(GL_LIGHTING);
	glColor3f(0.2, 0.2, 0.2);

    glPushMatrix();
        glTranslatef(0,0.01,-34);
        glScalef(3,1,3);
        fuel_tank_shadow(q, shadow_mat);
    glPopMatrix();

    glEnable(GL_LIGHTING);

}

void spotlight_tower(int rotate, GLfloat *pos, GLfloat *dir, int light) {
    glColor4f(0.212, 0.208, 0.173, 0.0);
    glPushMatrix();
        glTranslatef(0,8,0);
        glScalef(0.5, 16, 0.5);
        glutSolidCube(1);
    glPopMatrix();

    glRotatef(rotate, 0,1,0);

    glPushMatrix();
        float red[3] = {1,0,0}; 
        float green[3] = {0,1,0};
        glTranslatef(0,14,-1.75);
        glScalef(0.5, 1, 0.5);
        glRotatef(-20, 1,0,0);
        glutSolidCone(1,4,16,16);

        if (light == GL_LIGHT1) {
            glMaterialfv(GL_FRONT, GL_EMISSION, red);
        } else if (light == GL_LIGHT2) {
            glColor3f(0,1,0);
            glMaterialfv(GL_FRONT, GL_EMISSION, green);
        }
        
        glutSolidSphere(0.5,16,16);
        glLightfv(light, GL_POSITION, pos);
        glLightfv(light, GL_SPOT_DIRECTION, dir);

    glPopMatrix();
    glMaterialfv(GL_FRONT, GL_EMISSION, o_none);
}

void landing_pad_fence() {
    int b = 20;
   glBegin(GL_QUAD_STRIP);
   glColor4f(0.200, 0.19, 0.15, 0.0);
        for (int i = 0; i <= 40; i++) {
        if(i > 0) {normal(i-b);}
        glVertex3f(i, 0, (0.03*((i-b)*(i-b)))); //vi
        glVertex3f(i, 9, (0.03*((i-b)*(i-b)))); //wi
        }
    glEnd();

}