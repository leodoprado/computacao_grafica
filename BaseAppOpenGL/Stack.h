#ifndef STACK_H
#define STACK_H

#include "Cube.h"
#include <windows.h>	// Header File For Windows
#include <gl.h>			// Header File For The OpenGL32 Library
#include <glaux.h>		// Header File For The Glaux Library
#include <glext.h>		// Header File For The Glext Library
#include <string>
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>
#include <vector>
#include "CTimer.h"

class Stack {
private:
    std::vector<Cube> cubos;

public:
    void adicionarCubo(Cube& cubo);
    void draw();
    void clear();
    float getHeight();
    bool isFull();
    CTimer* pTimer;	// Objeto que gerencia o timer
};

#endif
