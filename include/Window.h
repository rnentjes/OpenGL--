/* 
 * File:   window.h
 * Author: rnentjes
 *
 * Created on May 17, 2012, 2:01 PM
 */

#ifndef WINDOW_H
#define	WINDOW_H

#include <time.h>

#include "Sprite.h"

class Window {
public:
    Window(int width, int height);
    virtual ~Window();
    
    bool init();
    void onDisplay();
    void idle();
    
    void addSprite(Sprite *sprite);
        
private:
    int _width;
    int _height;
    
    Sprite * _sprites;

    long _last_time;
    
    unsigned int _program_start;
    unsigned int _fps_start;
    unsigned int _fps_frames;    
};

#endif	/* WINDOW_H */

