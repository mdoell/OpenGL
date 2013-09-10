#pragma once

#include <windows.h>
#include <GL/gl.h>

namespace Utils 
{

	public ref class GLUtils
	{
	public:
		static GLint ActivateContext(HDC hDC);
	};
}