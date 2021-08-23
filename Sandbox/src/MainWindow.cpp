#include "MainWindow.h"
#include "ChildWindow.h"
#include "TestEntity.h"

MainWindow::MainWindow(Oculum::WindowManager* windowManager) : Oculum::Window(L"MainWindow", 400, 400, nullptr, windowManager)
{
	Oculum::Layer* layer;
	layer = new Oculum::Layer("1");
	GetStack()->PushLayer(layer);
	layer = new Oculum::Layer("2");
	GetStack()->PushLayer(layer);
	layer = new Oculum::Layer("3");
	GetStack()->PushLayer(layer);
	new TestEntity(this, 0);
	new TestEntity(this, 0);
	new TestEntity(this, 0);
	new TestEntity(this, 1);
	new TestEntity(this, 1);
	new TestEntity(this, 2);
	OC_INFO(GetStack()->ToString().c_str());
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