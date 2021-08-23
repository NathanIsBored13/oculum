#include "ChildWindow.h"
#include "TestEntity.h"

ChildWindow::ChildWindow(Oculum::WindowManager* windowManager, Oculum::Window* par) : Oculum::Window(L"ChildWindow", 200, 200, par, windowManager)
{
	OC_INFO("MADE CHILD");
}

ChildWindow::~ChildWindow()
{

}

void ChildWindow::OnUpdateClient(float)
{

}

bool ChildWindow::OnClose()
{
	return true;
}