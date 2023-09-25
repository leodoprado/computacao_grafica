#include "Scene1.h"


CScene1::CScene1()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;
	pModel3DS_1 = NULL;
	pModel3DS_2 = NULL;
	pModel3DS_3 = NULL;

	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f, 0.1f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	rotacao = 0;
	valorRotacao = 1;

	fPosX = 0.0f;
	fPosY = 10.0f;
	fPosZ = 0.0f;
	fMovementFactor = 0.1f;

	// Cria esfera com coordenadas de textura
	this->sphere1 = gluNewQuadric();
	gluQuadricTexture(this->sphere1, TRUE);

}

CScene1::~CScene1(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}

	gluDeleteQuadric(this->sphere1);

	if (pModel3DS_1)
	{
		delete pModel3DS_1;
		pModel3DS_1 = NULL;
	}

	if (pModel3DS_2)
	{
		delete pModel3DS_2;
		pModel3DS_2 = NULL;
	}

	if (pModel3DS_3)
	{
		delete pModel3DS_3;
		pModel3DS_3 = NULL;
	}
}

int CScene1::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter
	
	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posições da câmera
	pCamera->setView();

	// Desenha grid 
	//Draw3DSGrid(20.0f, 20.0f);

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	glColor4ub(255, 255, 255, 255);

	// Desenha o terreno
	glPushMatrix();
	glBegin(GL_QUADS);
	glVertex3f(-8.0f, 0.0f, 8.0f);
	glVertex3f(10.0f, 0.0f, 10.0f);
	glVertex3f(8.0f, 0.0f, -8.0f);
	glVertex3f(-10.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();

	glColor4ub(240, 240, 255, 255);

	// Desenha corpo do boneco de neve
	glPushMatrix();
	glTranslatef(5.0f, 0.25f, 4.0f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
	glRotatef(rotacao, 0.0f, 0.0f, 1.0f);
	glScalef(0.25f, 0.25f, 0.25f);
	auxSolidSphere(2.0);

	glPushMatrix();
	glTranslatef(0.0f, 2.5f, 0.0f);
	glScalef(0.75f, 0.75f, 0.75f);
	auxSolidSphere(2.0);

	glColor4ub(240, 240, 255, 255);
	glPushMatrix();
	glTranslatef(0.0f, 2.5f, 0.0f);
	glScalef(0.5f, 0.5f, 0.5f);
	auxSolidSphere(2.0);

	// Desenha nariz e olhos do boneco de neve
	glPushMatrix();
	glColor4ub(50, 50, 50, 255);
	glTranslatef(-0.5f, 0.75f, 2.0f);
	auxSolidSphere(0.25);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, 0.75f, 2.0f);
	auxSolidSphere(0.25);
	glPopMatrix();

	glPushMatrix();
	glColor4ub(235, 165, 50, 255);
	glTranslatef(0.0f, -0.25f, 1.5f);
	auxSolidCone(0.5f, 2.0f);
	glPopMatrix();

	// Desenha o chapeu do boneco de neve
	glPushMatrix();
	glColor4ub(60, 60, 145, 255);
	glTranslatef(0.0f, 1.75f, 0.0f);
	glScalef(1.0f, 0.0f, 1.0f);
	auxSolidSphere(2.0f);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 1.50f, 0.0f);
	glScalef(1.0f, 2.0f, 1.0f);
	auxSolidCylinder(1.5, 1.0);
	glPushMatrix();
	glTranslatef(0.0f, 1.0f, 0.0f);
	glScalef(0.75f, 0.0f, 0.75f);
	auxSolidSphere(2.0f);
	glPopMatrix();
	glPopMatrix();

	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	DrawForest();

	rotacao += valorRotacao;

	if (rotacao == 45) {
		valorRotacao = -1;
	}
	else if (rotacao == -45) {
		valorRotacao = 1;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 100, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime()/1000));


	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}

void CScene1::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene1::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}


	if (GetKeyState(VK_UP) & 0x80)
	{
		fPosZ -= fMovementFactor;
	}
	if (GetKeyState(VK_DOWN) & 0x80)
	{
		fPosZ += fMovementFactor;
	}
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		fPosX -= fMovementFactor;
	}
	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		fPosX += fMovementFactor;
	}
	if (GetKeyState(VK_PRIOR) & 0x80)
	{
		fPosY += fMovementFactor;
	}
	if (GetKeyState(VK_NEXT) & 0x80)
	{
		fPosY -= fMovementFactor;
	}
}

void CScene1::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
	{
		pTimer->Init();
	}
		break;

	case VK_RETURN:

		break;
	}
}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene1::Draw3DSGrid(float width, float length)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void CScene1::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}

void CScene1::DrawTree(float eixoX, float eixoY, float eixoZ, float propX, float propY, float propZ)
{
	// Define sua posição
	glTranslatef(eixoX, eixoY, eixoZ);

	// Desenha eu tronco
	glColor4ub(80, 60, 5, 255);

	// Define sua proporção
	glScalef(propX, propY, propZ);
	auxSolidCylinder(0.25, 1.0);

	// Desenha as folhas da arvore
	glPushMatrix();
	glTranslatef(0.0f, 0.5f, 0.0f);
	glColor4ub(40, 110, 40, 255);
	glScalef(1.0f, 1.0f, 1.0f);
	glRotatef(-90, 1.0f, 0.0f, 0.0f);
	auxSolidCone(1.0f, 2.0f);
	
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.25f);
	glColor4ub(40, 110, 40, 255);
	auxSolidCone(1.0f, 2.0f);
	
	glPopMatrix();
	glPopMatrix();
}

void CScene1::DrawForest()
{
	glPushMatrix();
	DrawTree(-5.0f, 0.0f, -4.0f, 1.0f, 2.6f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(7.0f, 0.0f, 8.0f, 1.0f, 3.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(-3.0f, 0.0f, 1.5f, 1.0f, 2.4f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(-7.0f, 0.0f, 6.0f, 2.0f, 4.0f, 2.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(6.0f, 0.0f, -6.0f, 1.0f, 3.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(7.0f, 0.0f, 2.0f, 1.0f, 2.6f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(3.0f, 0.0f, -2.0f, 2.0f, 5.0f, 2.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(2.0f, 0.0f, 3.0f, 1.0f, 2.0f, 1.0f);
	glPopMatrix();

	glPushMatrix();
	DrawTree(0.5f, 0.0f, 7.0f, 1.0f, 2.2f, 1.0f);
	glPopMatrix();
}