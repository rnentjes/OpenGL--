/* 
 * File:   main.h
 * Author: rnentjes
 *
 * Created on May 17, 2012, 10:38 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "Window.h"
#include "Keyboard.h"
#include "Mouse.h"

extern Window *window;
extern Keyboard *keyboard;
extern Mouse *mouse;

#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

