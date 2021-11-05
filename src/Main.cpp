/**
 *  @author Josafá Dieb
 *  @date 02/11/2021
 *  @matricula: 500183 
 **/
#include <iostream>
#include <GL/glut.h>
#include "../includes/Object.h"
#include <math.h>
#include <time.h>
#include <random>
#include <vector>

// escala padrão dos chunks
#define DEFAULT_SCALE 0.05f

// variaveis de escopo global
unsigned int IS_DRAGGING = 0;
unsigned int WIDTH = 512, HEGIHT = WIDTH;
int PECA = 1;
int PECA_AMMOUNT = 0;
float color_pick[10][3] = {
    {1.0f, 0.f, 0.f},
    {0.0f, 0.f, 1.f},
    {0.0f, 1.f, 0.f},
    {1.0f, 1.f, 0.f},
    {1.0f, 0.f, 1.f},
    {0.5f, 0.f, 1.f},
    {0.0f, 1.f, 1.0f},
    {1.f, 0.4f, 0.f},
    {1.0f, 0.0f, 0.7f},
    {0.53f, 0.24f, 0.23f},
};

// definindo um range de números aleatórios para as peças
std::random_device rd;
std::default_random_engine eng(rd());
std::uniform_real_distribution<float> distr(-0.8, 0.8);
Object *objSelected = nullptr;
std::vector<Object *> *pecas = new std::vector<Object *>();

//Funções responsaveis por desenhar as peças e alocar-las na memória para manipulações
Object *draw1(float x, float y, float z);
Object *draw2(float x, float y, float z);
Object *draw3(float x, float y, float z);
Object *draw4(float x, float y, float z);
Object *draw5(float x, float y, float z);
Object *draw6(float x, float y, float z);
Object *draw7(float x, float y, float z);

// handle functions
void keyboardEvent(unsigned char key, int x, int z);
void display(void);
void drawButtonsColors();
void clearBuffer();
void reshape(int w, int h);
void mouseMotionEvent(int x, int y);
void mouseClickEvent(int button, int state, int x, int y);

int main(int argc, char *argv[])
{

    int window;
    //create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEGIHT);
    window = glutCreateWindow("Tetris - Trabalho individual");

    //configurando
    glutInitWindowPosition(100, 100);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseClickEvent);
    glutKeyboardFunc(keyboardEvent);
    glutMotionFunc(mouseMotionEvent);
    glutIdleFunc(clearBuffer);
    glutMainLoop();

    return 0;
}
void display(void)
{

    glClearColor(1.0f, 1.f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //carrega uma projeção da matriz
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // seleciona a visão no plano
    glOrtho(-1.0f, (float)1.0f, -1.0f, (float)1.0f, -1.0f, 1.0f);
    // inicializa uma matriz indentidade para aplicar transformações, que não serão utilizadas aqui a titulo de aprendizagem.
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutSwapBuffers();
}

// callbacks implementations
void mouseClickEvent(int button, int state, int x, int y)
{
    float coord_X, coord_Y;

    if (button == GLUT_LEFT_BUTTON && state == 0)
    {
        coord_X = ((float)x / ((float)(WIDTH) / 2.0f)) - 1.0f;
        coord_Y = (((float)y / ((float)(HEGIHT) / 2.0f)) - 1.0f) * -1;
        for (std::vector<Object *>::iterator it = pecas->begin(); it != pecas->end(); it++)
        {
            Object *obj;
            obj = *it;
            for (int i = 0; i < 9; i++)
            {
                if (obj->quads[i]->isVisible())
                {
                    float x_start = obj->getPosX(i) - (DEFAULT_SCALE);
                    float x_end = obj->getPosX(i) + (DEFAULT_SCALE);
                    float y_start = obj->getPosY(i) - (DEFAULT_SCALE);
                    float y_end = obj->getPosY(i) + (DEFAULT_SCALE);
                    if (coord_X > x_start && coord_X < x_end && coord_Y > y_start && coord_Y < y_end)
                    {
                        objSelected = obj;
                        IS_DRAGGING = 1;
                        break;
                    }
                }
            }
            for (int i = 0; i < 10; i++)
            {
                float x_start = 1.0f - (float)(i + 1) * DEFAULT_SCALE;
                float y_start = 1.0f - (float)(i + 1) * DEFAULT_SCALE;
                if (coord_X > x_start && coord_X < 1.0f && coord_Y > (1.0f - DEFAULT_SCALE) && coord_Y < 1.0f)
                {

                    objSelected->setColor(color_pick[i][0], color_pick[i][1], color_pick[i][2]);
                    break;
                }
            }
        }
    }
    else if (state == 1)
    {
        IS_DRAGGING = 0;
    }

    if (button == GLUT_RIGHT_BUTTON && state == 0)
    {
        coord_X = distr(eng);
        coord_Y = distr(eng);
        Object *pecaNova;
        switch (PECA)
        {
        case 1:
            pecaNova = draw1(coord_X, coord_Y, 0.f);
            break;
        case 2:
            pecaNova = draw2(coord_X, coord_Y, 0.f);
            break;
        case 3:
            pecaNova = draw3(coord_X, coord_Y, 0.f);
            break;
        case 4:
            pecaNova = draw4(coord_X, coord_Y, 0.f);
            break;
        case 5:
            pecaNova = draw5(coord_X, coord_Y, 0.f);
            break;
        case 6:
            pecaNova = draw6(coord_X, coord_Y, 0.f);
            break;
        case 7:
            pecaNova = draw7(coord_X, coord_Y, 0.f);
            break;
        default:
            pecaNova = draw1(coord_X, coord_Y, 0.f);
            break;
        }
        PECA_AMMOUNT += 1;
        pecas->push_back(pecaNova);
    }
}
void mouseMotionEvent(int x, int y)
{
    float coord_X = ((float)x / ((float)(WIDTH) / 2.0f)) - 1.0f;
    float coord_Y = (((float)y / ((float)(HEGIHT) / 2.0f)) - 1.0f) * -1;
    if (IS_DRAGGING == 1)
    {
        objSelected->setPosX(coord_X);
        objSelected->setPosY(coord_Y);
    }
}

void reshape(int w, int h)
{
    WIDTH = w;
    HEGIHT = h;
    glViewport(0.5, 0.5, (GLsizei)WIDTH, (GLsizei)HEGIHT);
    glutPostRedisplay();
}

void clearBuffer()
{
    glClearColor(1.0f, 1.f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    for (std::vector<Object *>::iterator it = pecas->begin(); it != pecas->end(); it++)
    {
        Object *obj;
        obj = *it;
        obj->draw();
        if (objSelected != nullptr)
        {
            objSelected->drawBorder();
        }
    }
    drawButtonsColors();
    glutSwapBuffers();
}
float coord_buttons_color[10][3]; /// terminar seleção de cores....
//draw buttons color pick up
void drawButtonsColors()
{
    float x = 1.0f, y = 1.0f, z = 1.0f;
    for (int i = 0; i < 10; i++)
    {

        glBegin(GL_QUADS);
        glColor3f(color_pick[i][0], color_pick[i][1], color_pick[i][2]);
        glVertex2f(x, y);
        glVertex2f(x - DEFAULT_SCALE, y);
        glVertex2f(x - DEFAULT_SCALE, y - DEFAULT_SCALE);
        glVertex2f(x, y - DEFAULT_SCALE);
        glEnd();
        x = x - DEFAULT_SCALE;
    }
}

void keyboardEvent(unsigned char key, int x, int z)
{
    switch (key)
    {
    case '1':
        PECA = 1;
        break;
    case '2':
        PECA = 2;
        break;
    case '3':
        PECA = 3;
        break;
    case '4':
        PECA = 4;
        break;
    case '5':
        PECA = 5;
        break;
    case '6':
        PECA = 6;
        break;
    case '7':
        PECA = 7;
        break;
    case 'r':
        if (objSelected != nullptr)
        {
            int L_cursor = 0, I_cursor = 0, J_cursor = 0;
            float xx, yy, visibleCoords[9];
            ;
            Quad *matriz_aux[3][3];
            Quad *matriz_roteted[3][3];
            xx = (float)objSelected->getPosX(0);
            yy = (float)objSelected->getPosY(0);
            for (int i = 0; i < 9; i++)
            {
                if (i % 3 == 0 && i != 0)
                {
                    I_cursor += 1;
                }
                J_cursor = i % 3;
                matriz_aux[I_cursor][2 - J_cursor] = objSelected->quads[L_cursor];
                L_cursor += 1;
            }

            //criando a matriz rotacionada
            L_cursor = 0, I_cursor = 0, J_cursor = 0;
            for (int i = 0; i < 9; i++)
            {
                if (i % 3 == 0 && i != 0)
                {
                    I_cursor += 1;
                }
                J_cursor = i % 3;
                matriz_roteted[I_cursor][J_cursor] = matriz_aux[J_cursor][I_cursor];
            }
            L_cursor = 0, I_cursor = 0, J_cursor = 0;

            //verificando as novas coordenadas e persistindo nas lista de chunk

            for (int i = 0; i < 9; i++)
            {
                if (i % 3 == 0 && i != 0)
                {
                    I_cursor += 1;
                }
                J_cursor = i % 3;
                bool rotatedChunkIsVisible = matriz_roteted[I_cursor][J_cursor]->isVisible();

                if (rotatedChunkIsVisible)
                {
                    visibleCoords[L_cursor] = 1;
                }
                else
                {
                    visibleCoords[L_cursor] = 0;
                }
                L_cursor += 1;
            }

            // esse ultimo for seta a visibilidades salvas
            for (int i = 0; i < 9; i++)
            {
                if (visibleCoords[i] == 1)
                {
                    objSelected->quads[i]->setVisible(true);
                }
                else if (visibleCoords[i] == 0)
                {

                    objSelected->quads[i]->setVisible(false);
                }
            }
        }
    default:
        break;
    }
}

Object *draw1(float x, float y, float z)
{
    Object *L = new Object(x, y, z, DEFAULT_SCALE);
    L->quads[1]->draw();
    L->quads[3]->draw();
    L->quads[4]->draw();
    L->quads[7]->draw();
    return L;
}
Object *draw2(float x, float y, float z)
{
    Object *L = new Object(x, y, z, DEFAULT_SCALE);
    L->quads[1]->draw();
    L->quads[4]->draw();
    L->quads[7]->draw();
    return L;
}
Object *draw3(float x, float y, float z)
{
    Object *L = new Object(x, y, z, DEFAULT_SCALE);
    L->quads[2]->draw();
    L->quads[3]->draw();
    L->quads[4]->draw();
    L->quads[5]->draw();
    return L;
}
Object *draw4(float x, float y, float z)
{
    Object *L = new Object(x, y, z, DEFAULT_SCALE);
    L->quads[0]->draw();
    L->quads[3]->draw();
    L->quads[4]->draw();
    L->quads[5]->draw();
    return L;
}
Object *draw5(float x, float y, float z)
{
    Object *L = new Object(x, y, z, DEFAULT_SCALE);
    L->quads[2]->draw();
    L->quads[1]->draw();
    L->quads[4]->draw();
    L->quads[3]->draw();
    return L;
}
Object *draw6(float x, float y, float z)
{
    Object *L = new Object(x, y, z, DEFAULT_SCALE);
    L->quads[2]->draw();
    L->quads[4]->draw();
    L->quads[5]->draw();
    L->quads[7]->draw();
    return L;
}
Object *draw7(float x, float y, float z)
{
    Object *L = new Object(x, y, z, DEFAULT_SCALE);
    L->quads[1]->draw();
    L->quads[2]->draw();
    L->quads[4]->draw();
    L->quads[5]->draw();
    return L;
}
/**
 *  @author Josafá Dieb
 *  @date 02/11/2021
 *  @matricula: 500183 
 **/