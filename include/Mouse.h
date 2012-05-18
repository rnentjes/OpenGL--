/* 
 * File:   Mouse.h
 * Author: rnentjes
 *
 * Created on May 17, 2012, 11:14 PM
 */

#ifndef MOUSE_H
#define	MOUSE_H

class Mouse {
public:
    Mouse();
    virtual ~Mouse();
    
    void mouseMotion(int x, int y);
    void mousePassiveMotion(int x, int y);
    void mouseEntry(int state);
private:

};

#endif	/* MOUSE_H */

