/**
 *  @author Josafá Dieb
 *  @date 02/11/2021
 *  @matricula: 500183 
 **/
#ifndef H_QUAD
#include "../includes/Quad.h"
#include <iostream>
#include <GL/glut.h>

Quad::Quad(float x, float y, float z, float scale)
{
    Quad::visible = false;
    Quad::x = x;
    Quad::y = y;
    Quad::z = z;
    Quad::scale = scale;
}
void Quad::draw(float r, float g, float b) {
    glBegin(GL_QUADS);
        glColor3f(r, g, b);
        glVertex2f(getPosX() + getScale(), getPosY() - getScale());
        glVertex2f(getPosX() + getScale(), getPosY() + getScale());
        glVertex2f((getPosX() - getScale()), (getPosY() + getScale()));
        glVertex2f((getPosX() - getScale()), (getPosY() - getScale()));
    glEnd();
    Quad::visible = true;
}
bool Quad::isVisible(){
    return Quad::visible;
}
float Quad::getPosX() {
    return x;
}
float Quad::getPosY() {
    return y;
}
float Quad::getPosZ() {
    return z;
}
float Quad::getScale() {
    return scale;
}
void Quad::setPosX(float x) {
    Quad::x=x;
}
void Quad::setPosY(float y) {
    Quad::y=y;
}
void Quad::setPosZ(float z) {
    Quad::z=z;
}
void Quad::setScale(float scale) {
    Quad::scale = scale;
}
Quad::~Quad()
{
}
#endif
/**
 *  @author Josafá Dieb
 *  @date 02/11/2021
 *  @matricula: 500183 
 **/