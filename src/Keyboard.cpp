/* 
 * File:   Keyboard.cpp
 * Author: rnentjes
 * 
 * Created on May 17, 2012, 9:44 PM
 */

#include <iostream>

#include "Keyboard.h"

using namespace std;

Keyboard::Keyboard() {
    _keyStates = new bool[256];
    _keySpecialStates = new bool[256];
    
    int i=0;
    for (;i<256;i++) {
        _keyStates[i] = false;
        _keySpecialStates[i] = false;
    }
}

Keyboard::~Keyboard() {
}

void Keyboard::keyDown(unsigned char key, int x, int y) {
    cout << "Key down: " << (int)key << endl;
    
    if (key<256) {
        _keyStates[(int)key] = true;
    }
}

void Keyboard::keyUp(unsigned char key, int x, int y) {
    cout << "Key up: " << (int)key << endl;
    
    if (key<256) {
        _keyStates[(int)key] = false;
    }
}

void Keyboard::specialKeyDown(int key, int x, int y) {
    cout << "SKey down: " << key << endl;
    
    if (key<256) {
        _keySpecialStates[key] = true;
    }
}

void Keyboard::specialKeyUp(int key, int x, int y) {
    cout << "SKey up: " << key << endl;
    
    if (key<256) {
        _keySpecialStates[key] = false;
    }
}

bool Keyboard::isPressed(char key) {
    return _keyStates[(int)key];
}

bool Keyboard::isSpecialPressed(int key) {
    return _keySpecialStates[key];
}
