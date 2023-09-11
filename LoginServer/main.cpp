#include "LoginApp.h"
#include <iostream>

int main(void)
{
	CLoginApp app;
	if (app.Init())
	{
		app.Run();
	}
	app.Destroy();
	return 0;
}