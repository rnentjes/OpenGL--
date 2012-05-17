/* 
 * File:   main.cpp
 * Author: rnentjes
 *
 * Created on January 18, 2012, 12:34 PM
 */

#include <cstdlib>
#include <iostream>
#include <time.h>

/* Use glew.h instead of gl.h to get all the GL prototypes declared */
#include <GL/glew.h>
/* Using the GLUT library for the base windowing setup */
#include <GL/glut.h>

#include "Window.h"

using namespace std;

Window *window;
    
void onDisplay() {
    window->onDisplay();
}

void idle() {
    window->idle();
}

/*
 * 
 */
int main(int argc, char** argv) {
    timespec now;
    clock_getres(CLOCK_PROCESS_CPUTIME_ID, &now);
    
    cout << "Resolution: " << now.tv_sec << "s, " << now.tv_nsec << "ns.\n";    
    
    glutInit(&argc, argv);
    
    window = new Window(1280, 1024);
    
    int i = 0;
    for (i = 0; i < 10000; i++) {
        window->addSprite(new Sprite((drand48()*2.0)-1.0, (drand48()*2.0)-1.0, (drand48()-0.5)/25.0, (drand48()-0.5)/25.0, 0.1));
    }
    
    if (window->init()) {
        glutDisplayFunc(onDisplay);
        glutIdleFunc(idle);
        
        glutMainLoop();
    }

    delete window;

    return (EXIT_SUCCESS);
}
