#pragma once

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>

namespace Intro {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void);

		Void Init(Void);
		Void Render(Void);
		Void SwapOpenGLBuffers(Void);
		GLvoid ReSizeGLScene(GLsizei width, GLsizei height);

	protected:
		~Form1();

		virtual void OnShown(EventArgs^ e) override;
		virtual Void OnPaint(PaintEventArgs^ e) override;
		virtual Void OnPaintBackground(PaintEventArgs^ e) override;
		virtual Void OnResize(EventArgs^ e) override;

		GLint MySetPixelFormat(HDC hdc);
		bool InitGL(GLvoid);

	private: 
		System::ComponentModel::IContainer^ components;
		void InitializeComponent(void);

	private :
		HDC m_hDC;
		HGLRC m_hglrc;
	};
}

