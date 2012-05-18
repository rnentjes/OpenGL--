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

#include "main.h"

using namespace std;

Window *window;
Keyboard *keyboard;
Mouse *mouse;

void onDisplay() {
    window->onDisplay();
}

void idle() {
    window->idle();
}

void keyDown(unsigned char key, int x, int y) {
    keyboard->keyDown(key, x, y);
}

void keyUp(unsigned char key, int x, int y) {
    keyboard->keyUp(key, x, y);
}

void specialKeyDown(int key, int x, int y) {
    keyboard->specialKeyDown(key, x, y);
}

void specialKeyUp(int key, int x, int y) {
    keyboard->specialKeyUp(key, x, y);
}

void mouseMotion(int x, int y) {
    mouse->mouseMotion(x,y);
}

void mousePassiveMotion(int x, int y) {
    mouse->mousePassiveMotion(x,y);
}

void mouseEntry(int state) {
    mouse->mouseEntry(state);
}

void processMenuEvents(int option) {
    cout << "Menu: " << option << endl;
}

/*
 * 
 */
int main(int argc, char** argv) {
    timespec now;
    clock_getres(CLOCK_MONOTONIC, &now);
    
    cout << "Resolution: " << now.tv_sec << "s, " << now.tv_nsec << "ns.\n";    
    
    //Initialize SDL
    glutInit(&argc, argv);
    
    window = new Window(800, 600);
    keyboard = new Keyboard();
    mouse = new Mouse();
    
    int menu;
    
    int i = 0;

    for (i = 0; i < 100; i++) {
        window->addSprite(new Sprite(
                (drand48()*2.0)-1.0,    (drand48()*2.0)-1.0, 
                (drand48()-0.5)/2.0,   (drand48()-0.5)/2.0, 0.1));
    }
    
    if (window->init()) {
        glutDisplayFunc(onDisplay);
        glutIdleFunc(idle);
        
        glutIgnoreKeyRepeat(true);
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
        
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
        
        glutPassiveMotionFunc(mousePassiveMotion);
        glutMotionFunc(mouseMotion);
        glutEntryFunc(mouseEntry);
        
	// create the menu and
	// tell glut that "processMenuEvents" will
	// handle the events
	menu = glutCreateMenu(processMenuEvents);

	//add entries to our menu
	glutAddMenuEntry("Red",1);
	glutAddMenuEntry("Blue",2);
	glutAddMenuEntry("Green",3);
	glutAddMenuEntry("Orange",4);

	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);        
        
        glutMainLoop();
    }

    delete keyboard;
    delete window;
    
    glutDestroyMenu(menu);

    return (EXIT_SUCCESS);
}
