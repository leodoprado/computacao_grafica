#pragma once
#include "SceneBaseClass.h"
#include "CTexture.h"
#include "CTimer.h"
#include "CTexto.h"
#include "CCamera.h"
#include "VertexData.h"
#include <vector>

class CScene4 : public CSceneBaseClass
{
public:
	CScene4();
	~CScene4(void);


	virtual void MouseMove(void);					// Tratamento de movimento do mouse
	virtual void KeyPressed(void);					// Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);					// Fun��o que desenha a cena

	void Draw3DSGrid(float width, float length);
	void DrawAxis();
	void DrawFloor(float PosX, float PosZ);
	void DrawHouse();

private:

	bool	keys[256];		// Array usado para rotinas do teclado
	bool	active;			// Window Active Flag Set To TRUE By Default
	bool	fullscreen;		// Exibir janela em modo fullscreem (TRUE) ou em janela (FALSE)


	CCamera* pCamera;	// Gerencia c�mera OpenGL
	float fDeltaY;				// Rota��o da c�mera OpenGL no eixo Y
	float fDeltaX;				// Rota��o da c�mera OpenGL no eixo X

	CTexto* pTexto;	// Objeto que gerencia texto
	CTexture* pTextures;	// Objeto que gerencia texturas
	CTimer* pTimer;	// Objeto que gerencia o timer


	int		iFPS;			// FPS and FPS Counter
	int		iFrames;		// FPS and FPS Counter
	DWORD	ulLastFPS;		// FPS and FPS Counter
	char	szTitle[256];	// FPS and FPS Counter


	bool bIsWireframe;	// Modos Wireframe/Solid
	bool bIsCameraFPS;	// Ativa modo de camera First Person Shooter (true) ou Third Person Shooter (false)

	float fRenderPosY;
	float fTimerPosY;

	// Casa
	CVector3 vCasaVertices[204] = {
		{7.34,11.26,-2.34},
		{-7.34,11.26,-2.34},
		{-7.34,11.26,2.34},
		{-7.34,11.26,2.34},
		{7.34,11.26,2.34},
		{7.34,11.26,-2.34},
		{10.48,7.46,-5.48},
		{10.48,7.46,5.48},
		{10.48,0.00,5.48},
		{10.48,0.00,5.48},
		{10.48,0.00,-5.48},
		{10.48,7.46,-5.48},
		{10.48,7.46,-5.48},
		{10.48,0.00,-5.48},
		{-10.48,0.00,-5.48},
		{-10.48,0.00,-5.48},
		{-10.48,7.46,-5.48},
		{10.48,7.46,-5.48},
		{-10.48,7.46,5.48},
		{-10.48,7.46,-5.48},
		{-10.48,0.00,-5.48},
		{-10.48,0.00,-5.48},
		{-10.48,0.00,5.48},
		{-10.48,7.46,5.48},
		{-0.41,1.43,4.89},
		{-0.41,1.43,5.48},
		{2.37,1.43,5.48},
		{2.37,1.43,5.48},
		{2.37,1.43,4.89},
		{-0.41,1.43,4.89},
		{2.37,4.66,5.48},
		{2.37,4.66,4.89},
		{2.37,1.43,4.89},
		{2.37,1.43,4.89},
		{2.37,1.43,5.48},
		{2.37,4.66,5.48},
		{-0.41,4.66,5.48},
		{-0.41,4.66,4.89},
		{2.37,4.66,4.89},
		{2.37,4.66,4.89},
		{2.37,4.66,5.48},
		{-0.41,4.66,5.48},
		{-0.41,4.66,5.48},
		{-0.41,1.43,5.48},
		{-0.41,1.43,4.89},
		{-0.41,1.43,4.89},
		{-0.41,4.66,4.89},
		{-0.41,4.66,5.48},
		{4.45,4.66,4.89},
		{7.24,4.66,4.89},
		{7.24,4.66,5.48},
		{7.24,4.66,5.48},
		{4.45,4.66,5.48},
		{4.45,4.66,4.89},
		{4.45,4.66,5.48},
		{4.45,1.43,5.48},
		{4.45,1.43,4.89},
		{4.45,1.43,4.89},
		{4.45,4.66,4.89},
		{4.45,4.66,5.48},
		{4.45,1.43,5.48},
		{7.24,1.43,5.48},
		{7.24,1.43,4.89},
		{7.24,1.43,4.89},
		{4.45,1.43,4.89},
		{4.45,1.43,5.48},
		{7.24,1.43,4.89},
		{7.24,1.43,5.48},
		{7.24,4.66,5.48},
		{7.24,4.66,5.48},
		{7.24,4.66,4.89},
		{7.24,1.43,4.89},
		{-3.30,0.18,5.48},
		{-3.30,0.18,4.67},
		{-8.35,0.18,4.67},
		{-8.35,0.18,4.67},
		{-8.35,0.18,5.48},
		{-3.30,0.18,5.48},
		{-3.30,6.03,5.48},
		{-3.30,6.03,4.67},
		{-3.30,0.18,4.67},
		{-3.30,0.18,4.67},
		{-3.30,0.18,5.48},
		{-3.30,6.03,5.48},
		{-8.35,6.03,5.48},
		{-8.35,6.03,4.67},
		{-3.30,6.03,4.67},
		{-3.30,6.03,4.67},
		{-3.30,6.03,5.48},
		{-8.35,6.03,5.48},
		{-8.35,0.18,4.67},
		{-8.35,6.03,4.67},
		{-8.35,6.03,5.48},
		{-8.35,6.03,5.48},
		{-8.35,0.18,5.48},
		{-8.35,0.18,4.67},
		{-10.48,7.46,5.48},
		{-3.30,6.03,5.48},
		{4.45,4.66,5.48},
		{-10.48,7.46,5.48},
		{4.45,4.66,5.48},
		{7.24,4.66,5.48},
		{10.48,7.46,5.48},
		{-10.48,7.46,5.48},
		{7.24,4.66,5.48},
		{10.48,7.46,5.48},
		{7.24,4.66,5.48},
		{7.24,1.43,5.48},
		{10.48,0.00,5.48},
		{10.48,7.46,5.48},
		{7.24,1.43,5.48},
		{10.48,0.00,5.48},
		{7.24,1.43,5.48},
		{4.45,1.43,5.48},
		{4.45,1.43,5.48},
		{4.45,4.66,5.48},
		{2.37,4.66,5.48},
		{4.45,1.43,5.48},
		{2.37,4.66,5.48},
		{2.37,1.43,5.48},
		{10.48,0.00,5.48},
		{4.45,1.43,5.48},
		{2.37,1.43,5.48},
		{10.48,0.00,5.48},
		{2.37,1.43,5.48},
		{-0.41,1.43,5.48},
		{2.37,4.66,5.48},
		{4.45,4.66,5.48},
		{-3.30,6.03,5.48},
		{-0.41,4.66,5.48},
		{2.37,4.66,5.48},
		{-3.30,6.03,5.48},
		{-0.41,1.43,5.48},
		{-0.41,4.66,5.48},
		{-3.30,6.03,5.48},
		{-0.41,1.43,5.48},
		{-3.30,6.03,5.48},
		{-3.30,0.18,5.48},
		{10.48,0.00,5.48},
		{-0.41,1.43,5.48},
		{-3.30,0.18,5.48},
		{10.48,0.00,5.48},
		{-3.30,0.18,5.48},
		{-8.35,0.18,5.48},
		{-8.35,6.03,5.48},
		{-3.30,6.03,5.48},
		{-10.48,7.46,5.48},
		{-8.35,0.18,5.48},
		{-8.35,6.03,5.48},
		{-10.48,7.46,5.48},
		{-8.35,0.18,5.48},
		{-10.48,7.46,5.48},
		{-10.48,0.00,5.48},
		{10.48,0.00,5.48},
		{-8.35,0.18,5.48},
		{-10.48,0.00,5.48},
		{-10.48,7.46,5.48},
		{10.48,7.46,5.48},
		{11.70,7.02,6.12},
		{11.70,7.02,6.12},
		{-11.70,7.02,6.12},
		{-10.48,7.46,5.48},
		{10.48,7.46,5.48},
		{10.48,7.46,-5.48},
		{11.70,7.02,-6.12},
		{11.70,7.02,-6.12},
		{11.70,7.02,6.12},
		{10.48,7.46,5.48},
		{10.48,7.46,-5.48},
		{-10.48,7.46,-5.48},
		{-11.70,7.02,-6.12},
		{-11.70,7.02,-6.12},
		{11.70,7.02,-6.12},
		{10.48,7.46,-5.48},
		{-10.48,7.46,-5.48},
		{-10.48,7.46,5.48},
		{-11.70,7.02,6.12},
		{-11.70,7.02,6.12},
		{-11.70,7.02,-6.12},
		{-10.48,7.46,-5.48},
		{-11.70,7.02,6.12},
		{11.70,7.02,6.12},
		{7.34,11.26,2.34},
		{7.34,11.26,2.34},
		{-7.34,11.26,2.34},
		{-11.70,7.02,6.12},
		{11.70,7.02,6.12},
		{11.70,7.02,-6.12},
		{7.34,11.26,-2.34},
		{7.34,11.26,-2.34},
		{7.34,11.26,2.34},
		{11.70,7.02,6.12},
		{11.70,7.02,-6.12},
		{-11.70,7.02,-6.12},
		{-7.34,11.26,-2.34},
		{-7.34,11.26,-2.34},
		{7.34,11.26,-2.34},
		{11.70,7.02,-6.12},
		{-11.70,7.02,-6.12},
		{-11.70,7.02,6.12},
		{-7.34,11.26,2.34},
		{-7.34,11.26,2.34},
		{-7.34,11.26,-2.34},
		{-11.70,7.02,-6.12}
	};

	CIndex3 vCasaIndexes[69] = {
		{0,1,2},
		{ 3,4,5 },
		{ 6,7,8 },
		{ 9,10,11 },
		{ 12,13,14 },
		{ 15,16,17 },
		{ 18,19,20 },
		{ 21,22,23 },
		{ 24,25,26 },
		{ 27,28,29 },
		{ 30,31,32 },
		{ 33,34,35 },
		{ 36,37,38 },
		{ 39,40,41 },
		{ 42,43,44 },
		{ 45,46,47 },
		{ 48,49,50 },
		{ 51,52,53 },
		{ 54,55,56 },
		{ 57,58,59 },
		{ 60,61,62 },
		{ 63,64,65 },
		{ 66,67,68 },
		{ 69,70,71 },
		{ 72,73,74 },
		{ 75,76,77 },
		{ 78,79,80 },
		{ 81,82,83 },
		{ 84,85,86 },
		{ 87,88,89 },
		{ 90,91,92 },
		{ 93,94,95 },
		{ 96,97,98 },
		{ 99,100,101 },
		{ 102,103,104 },
		{ 105,106,107 },
		{ 108,109,110 },
		{ 111,112,113 },
		{ 114,115,116 },
		{ 117,118,119 },
		{ 120,121,122 },
		{ 123,124,125 },
		{ 126,127,128 },
		{ 129,130,131 },
		{ 132,133,134 },
		{ 135,136,137 },
		{ 138,139,140 },
		{ 141,142,143 },
		{ 144,145,146 },
		{ 147,148,149 },
		{ 150,151,152 },
		{ 153,154,155 },
		{ 156,157,158 },
		{ 159,160,161 },
		{ 162,163,164 },
		{ 165,166,167 },
		{ 168,169,170 },
		{ 171,172,173 },
		{ 174,175,176 },
		{ 177,178,179 },
		{ 180,181,182 },
		{ 183,184,185 },
		{ 186,187,188 },
		{ 189,190,191 },
		{ 192,193,194 },
		{ 195,196,197 },
		{ 198,199,200 },
		{ 201,202,203 },
		{ 204,205,206 }
	};

	CVector3 vTexturaVertices[204] = {
		{0.73,0.58},
		{0.30,0.58},
		{0.30,0.44},
		{0.30,0.44},
		{0.73,0.44},
		{0.73,0.58},
		{0.50,0.22},
		{0.34,0.22},
		{0.34,0.11},
		{0.34,0.11},
		{0.50,0.11},
		{0.50,0.22},
		{0.50,0.22},
		{0.50,0.11},
		{0.82,0.11},
		{0.82,0.11},
		{0.82,0.22},
		{0.50,0.22},
		{0.98,0.22},
		{0.82,0.22},
		{0.82,0.11},
		{0.82,0.11},
		{0.98,0.11},
		{0.98,0.22},
		{0.59,0.85},
		{0.59,0.84},
		{0.67,0.84},
		{0.67,0.84},
		{0.67,0.85},
		{0.59,0.85},
		{0.76,0.84},
		{0.76,0.85},
		{0.67,0.85},
		{0.67,0.85},
		{0.67,0.84},
		{0.76,0.84},
		{0.84,0.84},
		{0.84,0.85},
		{0.76,0.85},
		{0.76,0.85},
		{0.76,0.84},
		{0.84,0.84},
		{0.50,0.84},
		{0.59,0.84},
		{0.59,0.85},
		{0.59,0.85},
		{0.50,0.85},
		{0.50,0.84},
		{0.75,0.89},
		{0.67,0.89},
		{0.67,0.88},
		{0.67,0.88},
		{0.75,0.88},
		{0.75,0.89},
		{0.75,0.88},
		{0.84,0.88},
		{0.84,0.89},
		{0.84,0.89},
		{0.75,0.89},
		{0.75,0.88},
		{0.50,0.88},
		{0.58,0.88},
		{0.58,0.89},
		{0.58,0.89},
		{0.50,0.89},
		{0.50,0.88},
		{0.58,0.89},
		{0.58,0.88},
		{0.67,0.88},
		{0.67,0.88},
		{0.67,0.89},
		{0.58,0.89},
		{0.51,0.94},
		{0.51,0.96},
		{0.37,0.96},
		{0.37,0.96},
		{0.37,0.94},
		{0.51,0.94},
		{0.67,0.94},
		{0.67,0.96},
		{0.51,0.96},
		{0.51,0.96},
		{0.51,0.94},
		{0.67,0.94},
		{0.82,0.94},
		{0.82,0.96},
		{0.67,0.96},
		{0.67,0.96},
		{0.67,0.94},
		{0.82,0.94},
		{0.98,0.96},
		{0.82,0.96},
		{0.82,0.94},
		{0.82,0.94},
		{0.98,0.94},
		{0.98,0.96},
		{0.03,0.22},
		{0.13,0.20},
		{0.25,0.18},
		{0.03,0.22},
		{0.25,0.18},
		{0.29,0.18},
		{0.34,0.22},
		{0.03,0.22},
		{0.29,0.18},
		{0.34,0.22},
		{0.29,0.18},
		{0.29,0.13},
		{0.34,0.11},
		{0.34,0.22},
		{0.29,0.13},
		{0.34,0.11},
		{0.29,0.13},
		{0.25,0.13},
		{0.25,0.13},
		{0.25,0.18},
		{0.22,0.18},
		{0.25,0.13},
		{0.22,0.18},
		{0.22,0.13},
		{0.34,0.11},
		{0.25,0.13},
		{0.22,0.13},
		{0.34,0.11},
		{0.22,0.13},
		{0.18,0.13},
		{0.22,0.18},
		{0.25,0.18},
		{0.13,0.20},
		{0.18,0.18},
		{0.22,0.18},
		{0.13,0.20},
		{0.18,0.13},
		{0.18,0.18},
		{0.13,0.20},
		{0.18,0.13},
		{0.13,0.20},
		{0.13,0.12},
		{0.34,0.11},
		{0.18,0.13},
		{0.13,0.12},
		{0.34,0.11},
		{0.13,0.12},
		{0.06,0.12},
		{0.06,0.20},
		{0.13,0.20},
		{0.03,0.22},
		{0.06,0.12},
		{0.06,0.20},
		{0.03,0.22},
		{0.06,0.12},
		{0.03,0.22},
		{0.03,0.11},
		{0.34,0.11},
		{0.06,0.12},
		{0.03,0.11},
		{0.04,0.97},
		{0.32,0.97},
		{0.34,0.98},
		{0.34,0.98},
		{0.03,0.98},
		{0.04,0.97},
		{0.32,0.97},
		{0.32,0.82},
		{0.34,0.81},
		{0.34,0.81},
		{0.34,0.98},
		{0.32,0.97},
		{0.32,0.82},
		{0.04,0.82},
		{0.03,0.81},
		{0.03,0.81},
		{0.34,0.81},
		{0.32,0.82},
		{0.04,0.82},
		{0.04,0.97},
		{0.03,0.98},
		{0.03,0.98},
		{0.03,0.81},
		{0.04,0.82},
		{0.17,0.32},
		{0.86,0.32},
		{0.73,0.44},
		{0.73,0.44},
		{0.30,0.44},
		{0.17,0.32},
		{0.86,0.32},
		{0.86,0.70},
		{0.73,0.58},
		{0.73,0.58},
		{0.73,0.44},
		{0.86,0.32},
		{0.86,0.70},
		{0.17,0.70},
		{0.30,0.58},
		{0.30,0.58},
		{0.73,0.58},
		{0.86,0.70},
		{0.17,0.70},
		{0.17,0.32},
		{0.30,0.44},
		{0.30,0.44},
		{0.30,0.58},
		{0.17,0.70}
	};
};
