#include "MainWindow.h"
#include "TestEntity.h"

MainWindow::MainWindow(Oculum::WindowManager* windowManager) : Oculum::Window(L"MainWindow", 400, 400, nullptr, windowManager)
{

}

MainWindow::~MainWindow()
{

}

void MainWindow::OnUpdateClient(float)
{

}

bool MainWindow::OnClose()
{
	return MessageBox(GetHwnd(), L"Are you sure you want to exit?", L"Quit", MB_YESNO) == IDYES;
}