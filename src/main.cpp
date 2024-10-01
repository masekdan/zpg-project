#include <stdlib.h>
#include <stdio.h>

#include "Application.h"

int main(void)
{
	Application* app = new Application();
	app->initialization();
	app->createShaders();
	app->createModels();
	
	app->run();

	return 0;

}
