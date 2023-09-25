#include "Scene3.h"

CScene3::CScene3()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;
	
	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impress�o de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 0.0f, 1.0f, 0.1f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	glPushAttrib(GL_TEXTURE_BIT);
	pTextures = new CTexture();	
	pTextures->CreateTextureMipMap(1, "../Scene1/grama.bmp");
	pTextures->CreateTextureMipMap(2, "../Scene1/parede.bmp");
	pTextures->CreateTextureMipMap(3, "../Scene1/paredejanela.bmp");
	pTextures->CreateTextureMipMap(4, "../Scene1/paredeporta.bmp");
	pTextures->CreateTextureMipMap(5, "../Scene1/R1.jpg");
	pTextures->CreateTextureMipMap(6, "../Scene1/CRATE.BMP");
	glPopAttrib();


	fRotY = 0.0f;

	fPosX = 0.0f;
	fPosY = 0.0f;
	fPosZ = 0.0f;


	for (int i = 0; i < 38; i++)
		faceColor[i] = { (rand() % 255), (rand() % 255), (rand() % 255) };


	fAlphaFactor = 0.0f;

	// Carrega o terreno com HeightMap
	pTerreno = NULL;
	//pTerreno = new CTerreno();
	//pTerreno->LoadRawFile("../Scene1/Terreno.raw");
}


CScene3::~CScene3(void)
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

	if (pTerreno)
	{
		delete pTerreno;
		pTerreno = NULL;
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
}

int CScene3::DrawGLScene(void)	// Fun��o que desenha a cena
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


	// Seta as posi��es da c�mera
	pCamera->setView();

	// Desenha grid 
	//Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espa�o)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (IN�CIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	glColor4ub(255, 255, 255, 255);

	// Habilita texturiza��o
	glEnable(GL_TEXTURE_2D);

	// Seta a textura atual
	pTextures->ApplyTexture(1);

	// Desenha o ch�o
	glPushMatrix();
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-10.0f, 0.0f, 10.0f);
	glTexCoord2f(10.0f, 0.0f); glVertex3f(10.0f, 0.0f, 10.0f);
	glTexCoord2f(10.0f, 10.0f); glVertex3f(10.0f, 0.0f, -10.0f);
	glTexCoord2f(0.0f, 10.0f); glVertex3f(-10.0f, 0.0f, -10.0f);
	glEnd();
	glPopMatrix();

	// Desenha as caixas
	pTextures->ApplyTexture(6);
	glPushMatrix();
	glTranslatef(4.0f, 0.5f, 4.0f);
	DrawBox();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(4.2f, 1.37f, 3.8f);
	glRotatef(-45, 0.0f, 1.0f, 0.0f);
	glScalef(0.75f, 0.75f, 0.75f);
	DrawBox();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.5f, 1.5f, 4.0f);
	glScalef(1.5f, 3.0f, 1.5f);
	DrawBox();
	glPopMatrix();

	// Desenha a frente da casa
	pTextures->ApplyTexture(3);
	glPushMatrix();
	glTranslatef(-4.0f, 1.5f, -2.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
	glEnd();
	glPopMatrix();

	pTextures->ApplyTexture(4);
	glPushMatrix();
	glTranslatef(-1.0f, 1.5f, -2.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
	glEnd();
	glPopMatrix();

	pTextures->ApplyTexture(2);
	glPushMatrix();
	glTranslatef(2.0f, 1.5f, -2.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
	glEnd();
	glPopMatrix();

	// Desenha as paredes do lado esquerdo da casa
	pTextures->ApplyTexture(3);
	glPushMatrix();
	glTranslatef(-4.0f, 1.5f, -2.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, -1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, -1.5f);
	glEnd();
	glPopMatrix();

	pTextures->ApplyTexture(2);
	glPushMatrix();
	glTranslatef(-4.0f, 1.5f, -5.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, -1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, -1.5f);
	glEnd();
	glPopMatrix();

	// Desenha as paredes do lado direito da casa
	pTextures->ApplyTexture(2);
	glPushMatrix();
	glTranslatef(2.0f, 1.5f, -2.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, -1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, -1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5f, 1.5f, 1.5f);
	glEnd();
	glPopMatrix();

	pTextures->ApplyTexture(2);
	glPushMatrix();
	glTranslatef(2.0f, 1.5f, -5.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, -1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, -1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1.5f, 1.5f, 1.5f);
	glEnd();
	glPopMatrix();

	// Desenha a parte de tras da casa casa
	pTextures->ApplyTexture(3);
	glPushMatrix();
	glTranslatef(-4.0f, 1.5f, -8.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
	glEnd();
	glPopMatrix();

	pTextures->ApplyTexture(2);
	glPushMatrix();
	glTranslatef(-1.0f, 1.5f, -8.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
	glEnd();
	glPopMatrix();

	pTextures->ApplyTexture(2);
	glPushMatrix();
	glTranslatef(2.0f, 1.5f, -8.0f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1.5f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1.5f, 1.5f, 1.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.5f, 1.5f, 1.5f);
	glEnd();
	glPopMatrix();

	// Desenha o telhado da casa
	pTextures->ApplyTexture(5);
	glPushMatrix();
	glTranslatef(-4.0f, 4.0f, -1.25f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(8.0f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(8.0f, 1.25f, -2.25f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 1.25f, -2.25f);
	glEnd();
	glPopMatrix();

	pTextures->ApplyTexture(5);
	glPushMatrix();
	glTranslatef(-4.0f, 4.0f, -8.75f);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-2.0f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(8.0f, -1.5f, 1.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(8.0f, 1.25f, 5.25f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-2.0f, 1.25f, 5.25f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-4.0f, 4.0f, -2.0f);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.0f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, -1.0f, -4.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5f, 1.25f, -1.5f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(5.0f, 4.0f, -2.0f);
	glBegin(GL_TRIANGLES);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.5f, -1.0f, 1.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.5f, -1.0f, -4.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.5f, 1.25f, -1.5f);
	glEnd();
	glPopMatrix();

	// Desabilita texturiza��o
	glDisable(GL_TEXTURE_2D);
		
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

	// Impress�o de texto na tela...
	// Muda para modo de proje��o ortogonal 2D
	// OBS: Desabilite Texturas e Ilumina��o antes de entrar nesse modo de proje��o
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 150, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

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

	//// Posi��o do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplica��o e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime()/1000));

	glRasterPos2f(10.0f, 100.0f);
	pTexto->glPrint("fRot: %.1f ", fRotY);

	glPopMatrix();

	// Muda para modo de proje��o perspectiva 3D
	PerspectiveMode();

	return true;
}

void CScene3::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os c�lculos de rota��o da vis�o do Player (atrav�s das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a c�mera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene3::KeyPressed(void) // Tratamento de teclas pressionadas
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
	// Sen�o, interrompe movimento do Player
	else
	{
	}

	if (GetKeyState(VK_LEFT) & 0x80)
		fPosX -= 0.1f;
	if (GetKeyState(VK_RIGHT) & 0x80)
		fPosX += 0.1f;
	if (GetKeyState(VK_UP) & 0x80)
		fPosZ -= 0.1f;
	if (GetKeyState(VK_DOWN) & 0x80)
		fPosZ += 0.1f;
	if (GetKeyState(VK_PRIOR) & 0x80)
		fPosY += 0.1f;
	if (GetKeyState(VK_NEXT) & 0x80)
		fPosY -= 0.1f;

	if (GetKeyState(VK_ADD) & 0x80)
	{
		if (fAlphaFactor <= 1.0f)
			fAlphaFactor += 0.05f;
	}

	if (GetKeyState(VK_SUBTRACT) & 0x80)
	{
		if (fAlphaFactor >= 0.0f)
			fAlphaFactor -= 0.05f;
	}

}

void CScene3::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene3::Draw3DSGrid(float width, float length)
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

void CScene3::DrawAxis()
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


void CScene3::DrawCube()
{
	glBegin(GL_QUADS);
	// face frente
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	// face tr�s
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);

	// face direita
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);

	// face esquerda
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	// face baixo
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

	// face cima
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();
}


void CScene3::DrawPyramid()
{
	glBegin(GL_TRIANGLES);

	// Face frente
	glTexCoord2f(0.02f, 0.1f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.435f, 0.1f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.23f, 0.45f); glVertex3f(0.0f, 0.5f, 0.0f);

	// Face direita
	glTexCoord2f(0.52f, 0.1f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.94f, 0.1f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.73f, 0.45f); glVertex3f(0.0f, 0.5f, 0.0f);

	// Face esquerda
	glTexCoord2f(0.02f, 0.56f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.435f, 0.56f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.23f, 0.9f); glVertex3f(0.0f, 0.5f, 0.0f);

	// Face tr�s
	glTexCoord2f(0.53f, 0.56f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.93f, 0.56f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.73f, 0.9f); glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();
}

void CScene3::DrawBox()
{
	glBegin(GL_QUADS);

	// Desenha caixas
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();
}