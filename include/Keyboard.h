/* 
 * File:   Keyboard.h
 * Author: rnentjes
 *
 * Created on May 17, 2012, 9:44 PM
 */

#ifndef KEYBOARD_H
#define	KEYBOARD_H

class Keyboard {
public:
    Keyboard();
    virtual ~Keyboard();
    
    void keyDown(unsigned char key, int x, int y);
    void keyUp(unsigned char key, int x, int y);
    void specialKeyDown(int key, int x, int y);
    void specialKeyUp(int key, int x, int y);
    
    bool isPressed(char key);
    bool isSpecialPressed(int key);
    
private:
    bool* _keyStates;
    bool* _keySpecialStates;

};

#endif	/* KEYBOARD_H */
