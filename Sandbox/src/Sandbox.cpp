#include "Sandbox.h"

Sandbox::Sandbox() : Oculum::Application()
{
	new MainWindow(GetManager());
}

Sandbox::~Sandbox()
{

}