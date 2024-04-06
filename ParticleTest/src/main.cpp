#include "pch.h"
#include "Application.h"

int main()
{
	auto* app = new ptt::Application();
	app->Run();
	delete app;
	return 0;
}