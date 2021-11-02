#include "../includes/Object.h"
#include <GL/glut.h>
#include <iostream>

Object::Object(float x, float y, float z, float scale) {
    scaleDefault = scale;
    Quad *quad1 = new Quad(x, y, z, scale);               //x y z s
    Quad *quad2 = new Quad((x + 2 * scale), y, z, scale); // 2*scale+x, y,z
    Quad *quad3 = new Quad(x, (y + 2 * scale), z, scale); // x, 2*scale+y, z
    Quad *quad4 = new Quad((x + 2 * scale), (y + 2 * scale), z, scale);
    Quad *quad5 = new Quad(x, (y - 2 * scale), z, scale);
    Quad *quad6 = new Quad((x + 2 * scale), (y - 2 * scale), z, scale);
    Quad *quad7 = new Quad((x - 2 * scale), y, z, scale);
    Quad *quad8 = new Quad((x - 2 * scale), (y + 2 * scale), z, scale);
    Quad *quad9 = new Quad((x - 2 * scale), (y - 2 * scale), z, scale);
    quads[0] = quad1;
    quads[1] = quad2;
    quads[2] = quad3;
    quads[3] = quad4;
    quads[4] = quad5;
    quads[5] = quad6;
    quads[6] = quad7;
    quads[7] = quad8;
    quads[8] = quad9;
}

void Object::draw(float r, float g, float b) {
    for (int i = 0; i < 9; i++) {
        if (quads[i]->isVisible()) {
            quads[i]->draw(1.f, 0.f, 0.f);
        }
    }
}
// fazer uma função para desenhar as bordas
void Object::drawBorder()
{
    for (int i = 0; i < 9; i++)
    {
        if (quads[i]->isVisible())
        {
            glLineWidth(2.f);
            glBegin(GL_LINES);
            glColor3f(0.f, 0.f, 0.f);
            glVertex2f(quads[i]->getPosX() + scaleDefault, quads[i]->getPosY() + scaleDefault);
            glVertex2f(quads[i]->getPosX() + scaleDefault, quads[i]->getPosY() - scaleDefault);
            glVertex2f(quads[i]->getPosX() + scaleDefault, quads[i]->getPosY() + scaleDefault);
            glVertex2f(quads[i]->getPosX() - scaleDefault, quads[i]->getPosY() + scaleDefault);
            glVertex2f(quads[i]->getPosX() - scaleDefault, quads[i]->getPosY() + scaleDefault);
            glVertex2f(quads[i]->getPosX() - scaleDefault, quads[i]->getPosY() - scaleDefault);
            glVertex2f(quads[i]->getPosX() - scaleDefault, quads[i]->getPosY() - scaleDefault);
            glVertex2f(quads[i]->getPosX() + scaleDefault, quads[i]->getPosY() - scaleDefault);
            glEnd();
        }
    }
}

float Object::getPosX(int index)
{
    return quads[index]->getPosX();
}

float Object::getPosY(int index)
{
    return quads[index]->getPosY();
}

float Object::getPosZ(int index)
{
    return quads[index]->getPosZ();
}

void Object::setPosX(float x)
{
    quads[0]->setPosX(x);
    quads[1]->setPosX(x + 2 * scaleDefault);
    quads[2]->setPosX(x);
    quads[3]->setPosX(x + 2 * scaleDefault);
    quads[4]->setPosX(x);
    quads[5]->setPosX((x + 2 * scaleDefault));
    quads[6]->setPosX((x - 2 * scaleDefault));
    quads[7]->setPosX((x - 2 * scaleDefault));
    quads[8]->setPosX((x - 2 * scaleDefault));
}
void Object::setPosY(float y)
{
    quads[0]->setPosY(y);
    quads[1]->setPosY(y);
    quads[2]->setPosY(y + 2 * scaleDefault);
    quads[3]->setPosY(y + 2 * scaleDefault);
    quads[4]->setPosY(y - 2 * scaleDefault);
    quads[5]->setPosY(y - 2 * scaleDefault);
    quads[6]->setPosY(y);
    quads[7]->setPosY(y + 2 * scaleDefault);
    quads[8]->setPosY(y - 2 * scaleDefault);
}

void Object::setPosZ(float z)
{
}
Object::~Object()
{
}