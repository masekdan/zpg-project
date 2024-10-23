#include "Application.h"

using glm::vec3;

static void error_callback(int error, const char *description) { fputs(description, stderr); }

Application::Application()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
}

void Application::initialization()
{
	window = glfwCreateWindow(800, 600, "KCD 3: pre-alpha", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);
}

void Application::createShaders()
{
	shaders.push_back(new ShaderProgram("../src/shaders/default.vert", "../src/shaders/default.frag"));
	shaders.push_back(new ShaderProgram("../src/shaders/square.vert", "../src/shaders/square.frag"));
	shaders.push_back(new ShaderProgram("../src/shaders/tree.vert", "../src/shaders/tree.frag"));
	shaders.push_back(new ShaderProgram("../src/shaders/lambert.vert","../src/shaders/lambert.frag"));
}

void Application::createModels()
{
	scene1 = new Scene(this->shaders);
	scene2 = new Scene(this->shaders);
	Model *treeModel = new Model(tree, sizeof(tree));
	Model *bushModel = new Model(bushes, sizeof(bushes));
	//Model *giftModel = new Model(gift, sizeof(gift));
	Model *suziModel = new Model(suziFlat, sizeof(suziFlat));
	Model *ball = new Model(sphere, sizeof(sphere));

	DrawableObjectFactory df;

	TransformationComposite *tc = new TransformationComposite();

	tc->add(new Translation(vec3(0.0f, 1.0f, 0.0f)));
	tc->add(new Rotation(vec3(0.0f, 0.0f, 0.0f)));
	//tc->add(new Scale(vec3(0.8f)));

	scene1->addObject(df.create(ball,shaders[3],new Translation(vec3(0.0f, 2.0f, 0.0f))));
	scene1->addObject(df.create(ball,shaders[3],new Translation(vec3(0.0f, -2.0f, 0.0f))));
	scene1->addObject(df.create(ball,shaders[3],new Translation(vec3(2.0f, 0.0f, 0.0f))));
	scene1->addObject(df.create(ball,shaders[3],new Translation(vec3(-2.0f, 0.0f, 0.0f))));
	

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			TransformationComposite *tc2 = new TransformationComposite();
			tc2->add(new Translation(vec3(static_cast<float>(j * 7), 1.0f, static_cast<float>(i * 7))));
			tc2->add(new Rotation(vec3(0.0f,j*i,0.0f)));
			tc2->add(new Scale(vec3((float)rand()/RAND_MAX)));

			scene2->addObject(df.create(treeModel, shaders[0], tc2));
			TransformationComposite *tc3 = new TransformationComposite();
			TransformationComposite *tc4 = new TransformationComposite();
			TransformationComposite *tc5 = new TransformationComposite();
			TransformationComposite *tc6 = new TransformationComposite();
			tc3->add(tc2);
			tc4->add(tc2);
			tc5->add(tc2);
			tc6->add(tc2);
			tc3->add(new Translation(vec3(0.0f,0.0f,1.0f)));
			tc4->add(new Translation(vec3(0.0f,0.0f,-1.0f)));
			tc5->add(new Translation(vec3(1.0f,0.0f,0.0f)));
			tc6->add(new Translation(vec3(-1.0f,0.0f,0.0f)));
			scene2->addObject(df.create(bushModel,shaders[0],tc3));
			scene2->addObject(df.create(bushModel,shaders[0],tc4));
			scene2->addObject(df.create(bushModel,shaders[0],tc5));
			scene2->addObject(df.create(bushModel,shaders[0],tc6));
		}
	}

}

void Application::run()
{
	float rotation = 0.0f;
	double prevTime = glfwGetTime();

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		// clear color and depth buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1 / 60)
		{
			rotation += 0.05f;
			prevTime = crntTime;
		}


		scene1->getCamera()->inputs(this->window);
		scene1->drawScene();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
