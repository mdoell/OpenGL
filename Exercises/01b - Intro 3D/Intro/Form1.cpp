#include "StdAfx.h"
#include "Form1.h"

namespace Intro 
{

Form1::Form1(void)
{
	m_hDC = 0;

	SuspendLayout();
	AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	ClientSize = System::Drawing::Size(795, 489);
	Name = L"Form1";
	Text = L"Intro - Tristan";
	ResumeLayout(false);
	SetStyle(ControlStyles::ResizeRedraw, true);
}

void Form1::OnShown(EventArgs^ e)
{
	Init();
	Render();
}

Void Form1::OnResize(EventArgs^ e)
{
	__super::OnResize(e);
	ReSizeGLScene(ClientSize.Width, ClientSize.Height);
}

GLvoid Form1::ReSizeGLScene(GLsizei width, GLsizei height)
{
	glViewport(0,0,width,height);						// Re-initialise le Viewport

	glMatrixMode(GL_PROJECTION);						// On active la matrice de projection
	glLoadIdentity();									// La matrice de projection est remise à zero

	gluPerspective(45.f,(GLfloat)width/(GLfloat)height,0.1f,100.f);

	glMatrixMode(GL_MODELVIEW);							// On active la matrice modèle / vue
	glLoadIdentity();									// La matrice modèle / vue est remise à zero

	Render();
}

System::Void Form1::Init(System::Void)
{	
	m_hDC = GetDC((HWND)this->Handle.ToPointer());
	if(m_hDC)
	{
		Utils::GLUtils::ActivateContext(m_hDC);
		ReSizeGLScene(ClientSize.Width, ClientSize.Height);
		
		glClearColor(0.f, 0.f, 0.f, 1.f);					// Fond noir
		glClearDepth(1.f);									// On vide le tampon de profondeur 
		glEnable(GL_DEPTH_TEST);							// On active le test de profondeur
		glDepthFunc(GL_LEQUAL);								// Type de test
	}
}

System::Void Form1::Render(System::Void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Vide le tampon de couleur et de profondeur
	glLoadIdentity();									// Réinitialise la matrice modèle/vue
	

	glTranslatef(0.f,0.f,-5.f);


	glRotatef(30.f, 0.f, 1.f, 0.f); // 30 deg y
	glRotatef(10.f, 1.f, 0.f, 0.f); // 10 x

	glBegin(GL_TRIANGLES);

	glColor3f(1.f,0.f,0.f);
	glVertex3f(1.f,1.f,1.f);
	glColor3f(0.f,1.f,0.f);
	glVertex3f(1.f,-1.f,1.f);
	glColor3f(0.f,0.f,1.f);
	glVertex3f(-1.f,-1.f,1.f);

	glColor3f(0.f,0.f,1.f);
	glVertex3f(1.f,1.f,-1.f);
	glColor3f(1.f,0.f,0.f);
	glVertex3f(-1.f,-1.f,-1.f);
	glColor3f(0.f,1.f,0.f);
	glVertex3f(-1.f,1.f,-1.f);

	glEnd();

	glBegin(GL_LINES);

	glColor3f(1.f,1.f,1.f);
	glVertex3f(0.f,0.f,0.f);
	glVertex3f(1.f,0.f,0.f);

		glVertex3f(0.f,0.f,0.f);
	glVertex3f(0.f,1.f,0.f);

		glVertex3f(0.f,0.f,0.f);
	glVertex3f(0.f,0.f,1.f);

	
	glEnd();

	SwapBuffers(m_hDC);                                 // on affiche le tout à l'écrant
}

}
