#include "stdafx.h"
#include "Form1.h"

using namespace Intro;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Pour XP
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Fen�tre pricipale
	Form1^ form = gcnew Form1();

	// D�mare l'application
	Application::Run(form);
	return 0;
}
