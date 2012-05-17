/* 
 * File:   window.cpp
 * Author: rnentjes
 * 
 * Created on May 17, 2012, 2:01 PM
 */

#include <cstdlib>
#include <iostream>

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
#include <GL/glut.h>

#include "Window.h"

using namespace std;

Window::Window(int width, int height) {
    _width = width;
    _height = height;
    
    _program_start = 0;
    _fps_start = 0;
    _fps_frames = 0;
    
    _sprites = NULL;

    timespec now;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
    _last_time = now.tv_nsec;
}

Window::~Window() {
    Sprite *sprite = _sprites;
    
    while(sprite != NULL) {
        sprite = sprite->next();
        
        delete(sprite);
    }
}

bool Window::init() {
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_width, _height);
    glutCreateWindow("My First Triangle");
    
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        cerr << "Error: " << glewGetErrorString(glew_status) << endl;
        return false;
    }

    _program_start = _fps_start = glutGet(GLUT_ELAPSED_TIME);
        // Enable alpha
    glEnable(GL_DEPTH);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
    
    glClearColor(0.0, 0.0, 0.0, 1.0);

    return true;
}

void Window::onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor4f(0.8, 0.4, 0.4, 0.2);
    /*
    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(-0.8, -0.8, 0.1);
    glVertex3f( 0.8, -0.8, 0.1);
    glVertex3f( 0.8,  0.8, 0.1);
    glVertex3f(-0.8,  0.8, 0.1);

    glEnd();
    
    glColor4f(0.4, 0.4, 0.8, 0.2);
    
    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(-0.6, -0.6, 0.0);
    glVertex3f( 0.6, -0.6, 0.0);
    glVertex3f( 0.6,  0.6, 0.2);
    glVertex3f(-0.6,  0.6, 0.2);

    glEnd();
    */
    glColor4f(1.0, 1.0, 1.0, 0.1);
    
    Sprite *sprite = _sprites;
    
    while(sprite != NULL) {
        sprite->draw();
        sprite = sprite->next();
    }
    
    glutSwapBuffers();
}

void Window::idle() {
    timespec now;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &now);
    
    float delta = (now.tv_nsec - _last_time) / 1000000000.0f;
    
    if (delta < 0.0) {
        //cout << "-delta: " << delta << endl;
        delta += 1.0;
        //cout << "+delta: " << delta << endl;
    }

    /*
    if (delta < 0.01) {
        return;
    }*/
    
    _last_time = now.tv_nsec;

    //cout << "DELTA: " << delta << endl;

    _fps_frames++;
    int delta_t = glutGet(GLUT_ELAPSED_TIME) - _fps_start;

    if (delta_t > 1000) {
        cout << "FPS: " << (1000.0 * _fps_frames / delta_t) << endl;
        _fps_frames = 0;
        _fps_start = _fps_start + 1000;
    }

    Sprite *sprite = _sprites;
    
    while(sprite != NULL) {
        sprite->move(delta);
        sprite = sprite->next();
    }
    
    //float cur_fade = sinf(glutGet(GLUT_ELAPSED_TIME) / 1000.0 * (2 * 3.14) / 5) / 2 + 0.5; // 0->1->0 every 5 seconds
    //glUseProgram(program);
    //glUniform1f(uniform_fade, cur_fade);

    glutPostRedisplay();
}

void Window::addSprite(Sprite* sprite) {
    if (_sprites == NULL) {
        _sprites = sprite;
    } else {
        _sprites->add(sprite);
    }
}