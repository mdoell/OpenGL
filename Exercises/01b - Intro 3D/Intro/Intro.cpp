#include "stdafx.h"
#include "Form1.h"

using namespace Intro;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Pour XP
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Fenêtre pricipale
	Form1^ form = gcnew Form1();

	// Démare l'application
	Application::Run(form);
	return 0;
}
