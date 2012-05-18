/* 
 * File:   window.cpp
 * Author: rnentjes
 * 
 * Created on May 17, 2012, 2:01 PM
 */

#include <cstdlib>
#include <iostream>
#include <stdio.h>

#include "Text.h"

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
#include <GL/glut.h>

#include "main.h"
#include "Window.h"
#include "Keyboard.h"

using namespace std;

Window::Window(int width, int height) {
    _windowId = 0;
    
    _width = width;
    _height = height;
    
    _program_start = 0;
    _fps_start = 0;
    _fps_frames = 0;
    
    _sprites = NULL;

    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    
    _last_time_sec = now.tv_sec;
    _last_time_nano = now.tv_nsec;
    
    _fps_buffer[0] = '\0';
    _f1_pressed = false;
    _fullscreen = false;
    
    _text = new Text();
}

Window::~Window() {
    Sprite *sprite = _sprites;
    
    while(sprite != NULL) {
        sprite = sprite->next();
        
        delete(sprite);
    }
    
    delete(_text);
}

bool Window::init() {
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(_width, _height);
    _windowId = glutCreateWindow("My First Triangle");
    
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
    
    glClearColor(0.0, 0.0, 0.0, 0.6);

    return true;
}

void Window::onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT);

    //glBlendEquation(GL_FUNC_SUBTRACT); //GL_FUNC_REVERSE_SUBTRACT
    
    glBlendFunc (GL_ONE, GL_SRC_ALPHA);
    
    /*
    glColor4f(0.0, 0.0, 0.0, 0.6);
    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(-0.8, -0.8, 0.1);
    glVertex3f( 0.8, -0.8, 0.1);
    glVertex3f( 0.8,  0.8, 0.1);
    glVertex3f(-0.8,  0.8, 0.1);

    glEnd();
    */
            
    //glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);
    //glBlendEquation(GL_FUNC_ADD); //GL_FUNC_REVERSE_SUBTRACT
    
    /*
    
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

    if (keyboard->isSpecialPressed(GLUT_KEY_F2)) { 
        glColor4f(1.0, 1.0, 1.0, 1.0);

        _text->print(-1.0, -1.0, _fps_buffer);
    }
    
    glutSwapBuffers();
}

void Window::idle() {
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    
    double delta1 = (now.tv_sec - _last_time_sec);
    
    double delta = delta1 + ((now.tv_nsec - _last_time_nano) / 1000000000.0);
    
    _last_time_sec = now.tv_sec;
    _last_time_nano = now.tv_nsec;
   
    //cout << "DELTA: " << delta1 << "   " << delta << endl;

    _fps_frames++;
    int delta_t = glutGet(GLUT_ELAPSED_TIME) - _fps_start;

    if (delta_t > 1000) {
        sprintf(_fps_buffer, "FPS : %f", (1000.0 * _fps_frames / delta_t));
        cout << _fps_buffer << endl;
        _fps_frames = 0;
        _fps_start = _fps_start + 1000;
    }
    
    Sprite *sprite = _sprites;
    
    while(sprite != NULL) {
        sprite->move((float)delta);
        sprite = sprite->next();
    }
    
    if (keyboard->isSpecialPressed(GLUT_KEY_F1)) {
        cout << "F1 PRESSED" << endl;
        _f1_pressed = true;
    } else if (_f1_pressed == true) {
        _f1_pressed = false;
        cout << "FULLSCREEN" << endl;
        if (_fullscreen) {
            _fullscreen = false;
            glutReshapeWindow(800, 600); 
            glutPositionWindow(10,10);
        } else {
            _fullscreen = true;
            glutFullScreen();
        }
    }
    
    if (keyboard->isPressed(27) && _windowId > 0) {
        glutDestroyWindow ( _windowId );
        _windowId = 0;
        exit(0);
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