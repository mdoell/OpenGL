#pragma once

#include <windows.h>
#include <GL/gl.h>

namespace Intro {

	using namespace System;
	using namespace System::Windows::Forms;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void);

	protected:
		~Form1() {}

		virtual void OnShown(EventArgs^ e) override;
		virtual Void OnPaint(PaintEventArgs^ e) override;
		virtual Void OnPaintBackground(PaintEventArgs^ e) override;
		virtual Void OnResize(EventArgs^ e) override;

	private: 
		Void Init(Void);
		Void Render(Void);
		GLvoid ReSizeGLScene(GLsizei width, GLsizei height);
		GLint MySetPixelFormat(HDC hdc);

	private :
		HDC m_hDC;
	};
}

