#include "StdAfx.h"
#include "Form1.h"

namespace Intro 
{

Form1::Form1(void)
{
	InitializeComponent();

	m_hDC = 0;
	m_hglrc = 0; 
	SetStyle(ControlStyles::ResizeRedraw, true);
}

Form1::~Form1()
{
	if (components)
	{
		delete components;
	}
}

void Form1::OnShown(EventArgs^ e)
{
	Init();
	Render();
	SwapOpenGLBuffers();
}

void Form1::InitializeComponent(void)
{
	this->components = (gcnew System::ComponentModel::Container());
	this->SuspendLayout();
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(795, 489);
	this->Name = L"Form1";
	this->Text = L"Intro - Tristan";
	this->ResumeLayout(false);
}

Void Form1::OnPaint(PaintEventArgs^ e)
{
	// Désactive le "OnPaint"
	//__super::OnPaint(e);
}

Void Form1::OnPaintBackground(PaintEventArgs^ e)
{
	// Désactive le "OnPaintBackground"
	//__super::OnPaintBackground(e);
}

Void Form1::OnResize(EventArgs^ e)
{
	__super::OnResize(e);
	ReSizeGLScene(Width, Height);
}

System::Void Form1::Init(System::Void)
{	
	m_hDC = GetDC((HWND)this->Handle.ToPointer());
	if(m_hDC)
	{
		MySetPixelFormat(m_hDC);
		ReSizeGLScene(Width, Height);
		InitGL();
	}
}

System::Void Form1::Render(System::Void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Vide le tampon de couleur et de profondeur
	glLoadIdentity();									// Réinitialise la matrice modèle/vue

	glBegin(GL_LINES);									// Début - en mode ligbe
	
	glColor3f(1.f,1.f,1.f);								// Couleur des vertex (blanc)
	
	glVertex3f( -1.f, 0.f, 0.f);						// Point de départ
	glVertex3f( 1.f, 0.f, 0.f);							// Point d'arrivée

	glEnd();											// ligne complète
}

System::Void Form1::SwapOpenGLBuffers(System::Void)
{
	SwapBuffers(m_hDC) ;
}

GLint Form1::MySetPixelFormat(HDC hdc)
{
	static	PIXELFORMATDESCRIPTOR pfd=				// pfd décrit a Windows notre format de pixel
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Taille
		1,											// Version
		PFD_DRAW_TO_WINDOW |						// Le format doit Supporter Window
		PFD_SUPPORT_OPENGL |						// Le format doit Supporter OpenGL
		PFD_DOUBLEBUFFER,							// Le format doit Supporter le tampon double
		PFD_TYPE_RGBA,								// Nous voulons un format RGBA
		16,										
		0, 0, 0, 0, 0, 0,						
		0,										
		0,										
		0,											
		0, 0, 0, 0,								
		16,										
		0,										
		0,											
		PFD_MAIN_PLANE,							
		0,										
		0, 0, 0									
	};
			
	GLint  iPixelFormat; 
		 
	// On obtient le format le plus près disponible avec le matériel courant.
	if((iPixelFormat = ChoosePixelFormat(hdc, &pfd)) == 0)
	{
		MessageBox::Show("ChoosePixelFormat Failed");
		return 0;
	}
			 
	// on l'applique
	if(SetPixelFormat(hdc, iPixelFormat, &pfd) == FALSE)
	{
		MessageBox::Show("SetPixelFormat Failed");
		return 0;
	}

	// création d'un contexte OpenGL
	if((m_hglrc = wglCreateContext(m_hDC)) == NULL)
	{
		MessageBox::Show("wglCreateContext Failed");

		System::String^ s = "Error " + GetLastError();
		const wchar_t* chars = (const wchar_t*)(System::Runtime::InteropServices::Marshal::StringToHGlobalUni(s)).ToPointer();
		OutputDebugString(chars); 

		return 0;
	}

	// on active le contexte
	if((wglMakeCurrent(m_hDC, m_hglrc)) == NULL)
	{
		MessageBox::Show("wglMakeCurrent Failed");
		return 0;
	}

	return 1;
}

bool Form1::InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);							// Ombrage lisse (smooth shading) 
	glClearColor(0.f, 0.f, 0.f, 1.f);					// Fond noir             *************************
	glClearDepth(1.f);									// On vide le tampon de profondeur 
	glEnable(GL_DEPTH_TEST);							// On active le test de profondeur
	glDepthFunc(GL_LEQUAL);								// Type de test
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Haute qualité

	return TRUE;										// Initialisation sans erreur
}
// GL_Lines F12 *******************************************************************************************
GLvoid Form1::ReSizeGLScene(GLsizei width, GLsizei height)
{
	glViewport(0,0,width,height);						// Re-initialise le Viewport

	glMatrixMode(GL_PROJECTION);						// On active la matrice de projection
	glLoadIdentity();									// La matrice de projection est remise à zero

	glOrtho(-2.0 ,2.0, -2.0 ,2.0, -2.0 ,2.0);

	glMatrixMode(GL_MODELVIEW);							// On active la matrice modèle / vue
	glLoadIdentity();									// La matrice modèle / vue est remise à zero

	Render();
	SwapOpenGLBuffers();
}


}
