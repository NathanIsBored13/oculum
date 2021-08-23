#pragma once

#include "Oculum.h"

class ChildWindow : public Oculum::Window
{
public:
	ChildWindow(Oculum::WindowManager*, Oculum::Window*);
	~ChildWindow();
	void OnUpdateClient(float) override;
	bool OnClose() override;
};