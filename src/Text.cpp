/* 
 * File:   Text.cpp
 * Author: rnentjes
 * 
 * Created on May 17, 2012, 11:27 PM
 */

#include <GL/glut.h>

#include "Text.h"

Text::Text() {
}

Text::~Text() {
}

void Text::print(float x, float y, char* text) {
  char *c;

  glRasterPos3f(x, y, 0.0);
  
  for (c=text; *c != '\0'; c++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
  }    
}
