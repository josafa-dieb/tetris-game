#include "Quad.h"

/* data */



class Object
{
private:
    float scaleDefault;
    float border = {};
public:
    // we will keep pointers to bit quads save in a vector and each block is a little chunk of the piece
    Quad *quads[9];
    // getPos get a position of first element from Quads pointers vector
    float getPosX(int index);
    float getPosY(int index);
    float getPosZ(int index);
    void drawBorder();
    void draw(float r, float g, float b);
    // setPos set position of the piece in each index of Quads pointers vector
    void setPosX(float x);
    void setPosY(float y);
    void setPosZ(float z);

    //not need setScale and getScale why it will be all scale default 0.05f
    Object(float x, float y, float z, float scale);
    ~Object();
};