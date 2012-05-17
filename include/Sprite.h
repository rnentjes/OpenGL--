/* 
 * File:   Sprite.h
 * Author: rnentjes
 *
 * Created on May 17, 2012, 2:42 PM
 */

#ifndef SPRITE_H
#define	SPRITE_H

class Sprite {
public:
    Sprite(float x, float y, float dx, float dy, float size);
    Sprite(const Sprite& orig);
    virtual ~Sprite();
    
    void draw();
    void move(float time);

    void add(Sprite *sprite);
    Sprite *next();
private:
    float _x, _y;
    float _dx, _dy;
    
    float _size;

    float _r, _g, _b;
    
    Sprite *_next;
};

#endif	/* SPRITE_H */
