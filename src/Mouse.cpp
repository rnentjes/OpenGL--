/* 
 * File:   Mouse.cpp
 * Author: rnentjes
 * 
 * Created on May 17, 2012, 11:14 PM
 */

#include <iostream>

#include "Mouse.h"

using namespace std;

Mouse::Mouse() {
}

Mouse::~Mouse() {
}

void Mouse::mouseMotion(int x, int y) {
    //cout << "Mouse (" << x << "," << y << ")" << endl;     
}

void Mouse::mousePassiveMotion(int x, int y) {
    //cout << "Passive mouse (" << x << "," << y << ")" << endl; 
}

void Mouse::mouseEntry(int state) {
    //cout << "Mouse entry (" << state << ")" << endl; 
}