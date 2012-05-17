/* 
 * File:   Sprite.cpp
 * Author: rnentjes
 * 
 * Created on May 17, 2012, 2:42 PM
 */

#include <cstdlib>

#include <GL/glew.h>

#include "Sprite.h"
#include "location.h"

Sprite::Sprite(float x, float y, float dx, float dy, float size) {
    _x = x;
    _y = y;
    _dx = dx;
    _dy = dy;
    
    _size = size;
    
    _r = drand48();
    _g = drand48();
    _b = drand48();
            
    _next = NULL;
}

Sprite::~Sprite() {
}

void Sprite::draw() {
    glColor4f(_r, _g, _b, 0.02);
    
    glBegin(GL_TRIANGLE_FAN);

    glVertex3f(_x-_size, _y-_size, -0.2);
    glVertex3f(_x+_size, _y-_size, -0.2);
    glVertex3f(_x+_size, _y+_size, 0.2);
    glVertex3f(_x-_size, _y+_size, 0.2);
    
    glEnd();
}

void Sprite::move(float time) {
    _x = _x + (_dx * time);
    _y = _y + (_dy * time);
    
    if (_x > 1.0 || _x < -1.0) {
        _dx = -_dx;
    }
    
    if (_y > 1.0 || _y < -1.0) {
        _dy = -_dy;
    }
    
}

void Sprite::add(Sprite* sprite) {
    if (_next == NULL) {
        _next = sprite;
    } else {
        _next -> add(sprite);
    }
}

Sprite *Sprite::next() {
    return _next;
}
