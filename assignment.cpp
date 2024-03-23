#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include "loadTGA.h"
#include "cube.cpp"
#include "alien.cpp"
#include "spaceship.cpp"
#include "pad.cpp"
#include "smoke_engine.cpp"

#define PI 3.1415926535

GLUquadric *q;
GLuint texture_id[5];

float none[4] = {0,0,0,0};

float spotlight_pos[4] = {-20., 14.,11, 1.0};  //light's position
float spotlight_dir[3] = {0,-1,-1};

float spotlight_two_pos[4] = {20., 14.,11, 1.0};  //light's position
float spotlight_two_dir[3] = {0,-1,-1};


float lpos[4] = {10., 10.,10., 0.0};  //light's position

float shadowMat[16] = {lpos[1], 0, 0, 0, -lpos[0], 0, -lpos[2],-1, 0, 0, lpos[1], 0, 0, 0, 0, lpos[1]};

//Pacing alien
float alien_x_coord = 10;
bool walking_backward = false;
bool end_of_path = false;
int alien_path_rotate = 0;

//Circle walking alien
int alien_rotate = 20;
bool backward = true;
int spaceship_dish_rotate = 0;
int spaceship_dish_two_rotate = 90;
int alien_one_walk_angle = 20;


//Ship lift off
bool is_lift_off = false;
float ship_x = 0;
float ship_y = 0;
int ship_tick = 0;

float ship_acc_z = 6; float ship_vel_z = 0;
float ship_acc_y = 3; float ship_vel_y = 0;

//Falling crate
float crate_y = 70;
float crate_z = 0;
float crate_acc_y = 2; float crate_vel_y = 0;
int crate_tick = 0;
int crate_fall = 32;
 
//Camera variables
float cam_angle=0, look_x = 0, look_z=-100., cam_x = 0, cam_y = 15, cam_z = 0;  

void prog_timer(int time) {
    if(backward == true) {
		alien_rotate-=2;
	} if (backward == false) {
		alien_rotate+=2;
	}
	if (alien_rotate >= 20) {
		backward = true;
	}
	if (alien_rotate <= -20) {
		backward = false;
	}

    if (!end_of_path) {
        if (alien_x_coord >= 10) {
            alien_x_coord = 9.9;
            walking_backward = true;
            end_of_path = true;
        }
        if (alien_x_coord <= -10) {
            alien_x_coord = -9.9;
            walking_backward = false;
            end_of_path = true;
        }
        if (walking_backward) {
            alien_x_coord-=0.2;
        } else {
            alien_x_coord+=0.2;
        }
    } else {
        alien_path_rotate+=5;
        if (alien_path_rotate >= 180){
            alien_path_rotate = 0;
            end_of_path = false;
        }
    }
    
    if (is_lift_off) {
        ship_tick += 1;
        crate_tick += 1;
        if(ship_tick < 15) {
            ship_y += 1;
        } 
        if(ship_tick >= 15) {

            ship_vel_y += ship_acc_y * 0.2;
            ship_vel_z += ship_acc_z * 0.2;
            ship_x += ship_vel_z * 0.2;
            ship_y += ship_vel_y * 0.2;
            
        }
        if(crate_tick >=crate_fall && crate_y > 1.5) {
            if(crate_tick == crate_fall) {
                crate_y = ship_y;
                crate_z = -ship_x;
            }
            crate_vel_y += crate_acc_y * 0.2;
            crate_y -= crate_vel_y * 0.2;
            //glutPostRedisplay();
        }
    }
    
    spaceship_dish_rotate+=2;
    spaceship_dish_two_rotate-=2;
    alien_one_walk_angle++;
    glutTimerFunc(20, prog_timer, 0);
    glutPostRedisplay();
}

void loadTexture(void)				
{
	glGenTextures(4, texture_id); 	// Create 2 texture ids
	glBindTexture(GL_TEXTURE_2D, texture_id[0]);  //Use this texture
    loadTGA("ground.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

    glBindTexture(GL_TEXTURE_2D, texture_id[1]);  //Use this texture
    loadTGA("wood.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

    glBindTexture(GL_TEXTURE_2D, texture_id[2]);  //Use this texture
    loadTGA("skybox.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

    glBindTexture(GL_TEXTURE_2D, texture_id[3]);  //Use this texture
    loadTGA("crate_metal.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	

    
    glBindTexture(GL_TEXTURE_2D, texture_id[4]);  //Use this texture
    loadTGA("smoke.tga");
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);	//Set texture parameters
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
} 

void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT) cam_angle -= 0.08;  
    else if(key == GLUT_KEY_RIGHT) cam_angle += 0.08;
    else if(key == GLUT_KEY_DOWN) {  
        //move backward
        cam_x -= 5*sin(cam_angle);
        cam_z += 5*cos(cam_angle);
    } else if(key == GLUT_KEY_UP) { 
        //move forward
        cam_x += 5*sin(cam_angle);
        cam_z -= 5*cos(cam_angle);
    } else if (key == GLUT_KEY_PAGE_UP) {
        //move up
        cam_y += 1;
    } else if (key == GLUT_KEY_PAGE_DOWN) {
        //move down
        cam_y -= 1;
    } 
    look_x = cam_x + (20 * 5*sin(cam_angle));
    look_z = cam_z - (20 * 5*cos(cam_angle));

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
 switch(key)
 {
 case ' ': is_lift_off = true; break; //turn left
 }
 glutPostRedisplay(); //update display
}

void floor(void)
{
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[0]);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    for(int i = -200; i < 200; i+=30)
    {
        for(int j = -200;  j < 200; j+=30)
        {
            glTexCoord2f(0.0,0.0);
            glVertex3f(i, 0.0, j);
            glTexCoord2f(0.0,1.0);
            glVertex3f(i, 0.0, j+30);
            glTexCoord2f(1.0,1.0);
            glVertex3f(i+30, 0.0, j+30);
            glTexCoord2f(1.0,0.0);
            glVertex3f(i+30, 0.0, j);
        }
    }  
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void skybox() {
    
    int distance = 200;
    glTranslatef(0,-180,0);
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id[2]);
    glDisable(GL_LIGHTING);
    glBegin(GL_QUADS);			//4 walls
    glColor3f(1,1,1);
      //glNormal3f(0, -1, 0); 1,1    0,1   00    10
        glTexCoord2f(0.25, 0.667); glVertex3f(distance, 0, -distance);
        glTexCoord2f(0, 0.667); glVertex3f(-distance, 0, -distance);
        glTexCoord2f(0, 0.334); glVertex3f(-distance, (2*distance), -distance);
        glTexCoord2f(0.25, 0.334); glVertex3f(distance, (2*distance), -distance);

        glTexCoord2f(0.25, 0.667); glVertex3f(distance, 0, -distance);
        glTexCoord2f(0.5, 0.667); glVertex3f(distance, 0, distance);
        glTexCoord2f(0.5, 0.334); glVertex3f(distance, (2*distance), distance);
        glTexCoord2f(0.25, 0.334); glVertex3f(distance, (2*distance), -distance);
        
        glTexCoord2f(0.5, 0.667); glVertex3f(distance, 0, distance);
        glTexCoord2f(0.75, 0.667); glVertex3f(-distance, 0, distance);
        glTexCoord2f(0.75, 0.334); glVertex3f(-distance, (2*distance), distance);
        glTexCoord2f(0.5, 0.334); glVertex3f(distance, (2*distance), distance);
        
        glTexCoord2f(0.75, 0.667); glVertex3f(-distance, 0, distance);
        glTexCoord2f(1, 0.667); glVertex3f(-distance, 0, -distance);
        glTexCoord2f(1, 0.334); glVertex3f(-distance, (2*distance), -distance);
        glTexCoord2f(0.75, 0.334); glVertex3f(-distance, (2*distance), distance);


        glTexCoord2f(0.25, 0.334); glVertex3f(distance+3, (2*distance)-1, (distance+3)*-1);
        glTexCoord2f(0.25, 0); glVertex3f((distance+3)*-1, (2*distance)-1, (distance+3)*-1);
        glTexCoord2f(0.5, 0); glVertex3f((distance+3)*-1, (2*distance)-1, distance+3);
        glTexCoord2f(0.5, 0.334); glVertex3f(distance+3, (2*distance)-1, distance+3);

    glEnd();
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
  glPopMatrix();

}

void display(void) 
{ 
    float white[4] = {1.0, 1.0, 1.0, 1.}; // diffuse and spec color
    float none[4] = {0,0,0,0};

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

    gluLookAt(cam_x, cam_y, cam_z,  look_x, 15, look_z, 0, 1, 0);
    glRotatef(cam_angle, 0, 1, 0);
    

	glLightfv(GL_LIGHT0,GL_POSITION, lpos);   //Set light position

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 30.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.1);

    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 30.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.1);


	glEnable(GL_LIGHTING);			
    
    floor();

    draw_landing_pad();

    glPushMatrix();
        glTranslatef(20,0,25);
        glRotatef(180, 0,1,0);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
        landing_pad_fence();
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, none);
    glPopMatrix();

    glPushMatrix();
	    skybox();
    glPopMatrix();

    glPushMatrix();
        glScalef(2,2,2);
        glPushMatrix();

            glTranslatef(0 ,0.01,-ship_x);

            glTranslatef(0,0.01,0);
            spaceship_build_shadow(spaceship_dish_rotate, spaceship_dish_two_rotate, q, shadowMat);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
            glEnable(GL_LIGHTING);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0 ,0.01 + ship_y,-ship_x);
            glTranslatef(0,0.5,0);
            spaceship_build(spaceship_dish_rotate, spaceship_dish_two_rotate, q);
            glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, none);
        glPopMatrix();
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
        glTranslatef(20, 0.2, 0);
        alien_build(alien_one_walk_angle, alien_rotate);
        build_alien_shadow(shadowMat, alien_one_walk_angle, alien_rotate);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
        glTranslatef(10,1,0);
        pacing_alien(alien_x_coord, end_of_path, alien_path_rotate, alien_rotate);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
        glTranslatef(3, 0, 10);
        crate_stack(texture_id[3], texture_id[1]);
        crate_stack_shadow(shadowMat);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
        glTranslatef(6, 0, 12);
        crate_stack(texture_id[3], texture_id[1]);
        crate_stack_shadow(shadowMat);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
        glTranslatef(20, 0, 12);
        crate_stack(texture_id[1], texture_id[3]);
        crate_stack_shadow(shadowMat);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
        glTranslatef(23, 0, 14);
        crate_stack(texture_id[3], texture_id[1]);
        crate_stack_shadow(shadowMat);
    glPopMatrix();

    glEnable(GL_LIGHTING);

    glPushMatrix();
        draw_fuel_station(q, shadowMat);
        draw_fuel_tank_shadow(q, shadowMat);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(20,0.01,13);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
        spotlight_tower(spaceship_dish_two_rotate, spotlight_pos, spotlight_dir, GL_LIGHT1);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, none);
    glPopMatrix();

    if(is_lift_off && crate_tick >= crate_fall) {
            glPushMatrix();
                glTranslatef(0,crate_y*2, crate_z*2);
                glScalef(3,3,3);
                wood_crate(texture_id[1]);
            glPopMatrix();
    } 

    glPushMatrix();
        glTranslatef(-20,0.01,13);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
        spotlight_tower(spaceship_dish_rotate, spotlight_two_pos, spotlight_two_dir, GL_LIGHT2);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, none);
    glPopMatrix();

    glPushMatrix();
        
        glTranslatef(18,0,-22); 

        new_smoke_particle();
        update_smoke();
        draw_smoke(texture_id[4]);
    glPopMatrix();

       

	glFlush(); 
    
} 

void initialize(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glEnable(GL_LIGHTING);		//Enable OpenGL states
	glEnable(GL_LIGHT0);
    float grey[4] = {0.4, 0.4, 0.4, 1.}; //light’s ambient color
    float white[4] = {1.0, 1.0, 1.0, 1.}; // diffuse and spec color
    float red[4] = {1,0,0,1};
    float green[4] = {0,1,0,1};
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, red);

    glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, green);

    glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, grey);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    q = gluNewQuadric();
    loadTexture();
    glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(100, 4/3, 10.0, 1000.0);   //Camera Frustum
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_DEPTH);
    glutInitWindowSize (1024, 768); 
    glutInitWindowPosition (10, 10);
    glutCreateWindow ("Zya Gurau 64646853");
    initialize();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutTimerFunc(20, prog_timer, 0);
    glutSpecialFunc(special);
    glutMainLoop();
    return 0;
}
