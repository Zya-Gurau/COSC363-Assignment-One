#include <iostream>
#include <GL/freeglut.h>
#include <cmath>
#include <list>

#define MAX_PARTICLES 10000000
#define GRAVITY 0.05

int num_smoke = 0;

struct Smoke_Particle
{
    int time_to_live;
    float mass;
    float pos[3];
    float dir[3];
};

//Smoke_Particle smoke[MAX_PARTICLES];
std::list<Smoke_Particle> smoke;

double generate_random()
{	
    return (rand() % 10000) / 10000.0;
}

void draw_smoke(GLuint tex_id)
{
    glPushMatrix();
        float b = 0.9;
        float c = b/2;
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.5, 0.5, 0.5, 1);
        glEnable(GL_BLEND);

        glBlendFunc(GL_ONE, GL_SRC_ALPHA);
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GEQUAL, 0.5);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glBegin(GL_QUADS);

            std::list<Smoke_Particle>::iterator it;

            for (it = smoke.begin(); it != smoke.end(); it++) {

                glTexCoord2f(0.0,1.0);
                glVertex3f((it->pos[0]), (it->pos[1]),(it->pos[2]));
                glTexCoord2f(0.0,0.0);
                glVertex3f((it->pos[0]), (it->pos[1]) - b,(it->pos[2]));
                glTexCoord2f(1.0,0.0);
                glVertex3f((it->pos[0]+b), (it->pos[1])-b,(it->pos[2]));
                glTexCoord2f(1.0,1.0);
                glVertex3f((it->pos[0]+b), (it->pos[1]),(it->pos[2]));

                glTexCoord2f(0.0,1.0);
                glVertex3f((it->pos[0] + c), (it->pos[1]),(it->pos[2]) + c);
                glTexCoord2f(0.0,0.0);
                glVertex3f((it->pos[0] + c), (it->pos[1]) - b,(it->pos[2]) + c);
                glTexCoord2f(1.0,0.0);
                glVertex3f((it->pos[0]+c), (it->pos[1])-b,(it->pos[2]) - c);
                glTexCoord2f(1.0,1.0);
                glVertex3f((it->pos[0]+c), (it->pos[1]),(it->pos[2])-c);
            }


        glEnd();
        glDisable(GL_TEXTURE_2D);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_ALPHA_TEST);
        glDisable(GL_BLEND);
    glPopMatrix();
} 

void update_smoke() {
    int T = 1000;
    std::list<Smoke_Particle>::iterator it;
    Smoke_Particle p;

    //Remove particles that have passed lifetime
    if (!smoke.empty()) {
        p = smoke.front();
        if (p.time_to_live > T){
            smoke.pop_front();
        } 
    }
    //Update parameters
    for (it = smoke.begin(); it != smoke.end(); it++) {
        (it->time_to_live)++;
        (it->pos[0]) += (it->dir[0]);
        (it->pos[1]) += GRAVITY * (it->mass);
        (it->pos[2]) += (it->dir[2]);
    }
}   

void new_smoke_particle() {
    float b = 2;
    float c = 0.01;
    float d = 0.0025;

    Smoke_Particle p;

    p.time_to_live = 1; 

    p.pos[0] = -b + c * generate_random();
    p.pos[1] = b + c * generate_random();
    p.pos[2] = b + c * generate_random();

    p.dir[0] = c + d * generate_random();
    p.dir[1] = 0.0; 
    p.dir[2] = c + d * generate_random();
        
    p.mass = 0.5 + 0.5 * generate_random();
    smoke.push_back(p);
} 