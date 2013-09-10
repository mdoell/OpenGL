#include "StdAfx.h"
#include "GLUtils.h"

namespace Utils
{
	GLint GLUtils::ActivateContext(HDC hDC)
	{
		static	PIXELFORMATDESCRIPTOR pfd=				// pfd d�crit a Windows notre format de pixel
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
		 
		// On obtient le format le plus pr�s disponible avec le mat�riel courant.
		if((iPixelFormat = ChoosePixelFormat(hDC, &pfd)) == 0)
		{
			//ChoosePixelFormat Failed
			return 1;
		}
			 
		// on l'applique
		if(SetPixelFormat(hDC, iPixelFormat, &pfd) == FALSE)
		{
			//SetPixelFormat Failed
			return 2;
		}

		HGLRC hglrc = 0;
		// cr�ation d'un contexte OpenGL
		if((hglrc = wglCreateContext(hDC)) == NULL)
		{
			//wglCreateContext Failed
			return 3;
		}

		// on active le contexte
		if((wglMakeCurrent(hDC, hglrc)) == NULL)
		{
			//wglMakeCurrent Failed
			return 4;
		}

		return 0;
	}

}