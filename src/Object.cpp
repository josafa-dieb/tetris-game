/**
 *  @author Josafá Dieb
 *  @date 02/11/2021
 *  @matricula: 500183 
 **/
#include "../includes/Object.h"
#include <GL/glut.h>
#include <iostream>

Object::Object(float x, float y, float z, float scale)
{
    scaleDefault = scale;
    quads[0] = new Quad((x - 2 * scale), (y + 2 * scale), z, scale);
    quads[1] = new Quad(x, (y + 2 * scale), z, scale);
    quads[2] = new Quad((x + 2 * scale), (y + 2 * scale), z, scale);
    quads[3] = new Quad((x - 2 * scale), y, z, scale);
    quads[4] = new Quad(x, y, z, scale);
    quads[5] = new Quad((x + 2 * scale), y, z, scale);
    quads[6] = new Quad((x - 2 * scale), (y - 2 * scale), z, scale);
    quads[7] = new Quad(x, (y - 2 * scale), z, scale);
    quads[8] = new Quad((x + 2 * scale), (y - 2 * scale), z, scale);
}

void Object::draw(float r, float g, float b)
{
    for (int i = 0; i < 9; i++)
    {
        if (quads[i]->isVisible())
        {
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

    quads[0]->setPosX(x - 2 * scaleDefault);
    quads[1]->setPosX(x);
    quads[2]->setPosX(x + 2 * scaleDefault);
    quads[3]->setPosX(x - 2 * scaleDefault);
    quads[4]->setPosX(x);
    quads[5]->setPosX((x + 2 * scaleDefault));
    quads[6]->setPosX((x - 2 * scaleDefault));
    quads[7]->setPosX((x));
    quads[8]->setPosX((x + 2 * scaleDefault));
}
void Object::setPosY(float y)
{
    quads[0]->setPosY(y + 2 * scaleDefault);
    quads[1]->setPosY(y + 2 * scaleDefault);
    quads[2]->setPosY(y + 2 * scaleDefault);
    quads[3]->setPosY(y);
    quads[4]->setPosY(y);
    quads[5]->setPosY(y);
    quads[6]->setPosY(y - 2 * scaleDefault);
    quads[7]->setPosY(y - 2 * scaleDefault);
    quads[8]->setPosY(y - 2 * scaleDefault);
}
// não precisaremos implementar por enquanto
void Object::setPosZ(float z)
{
}
Object::~Object()
{
}
/**
 *  @author Josafá Dieb
 *  @date 02/11/2021
 *  @matricula: 500183 
 **/