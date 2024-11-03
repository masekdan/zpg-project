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
	window = glfwCreateWindow(1366, 768, "KCD 3: pre-alpha", NULL, NULL);
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
	shaders.push_back(new ShaderProgram("../src/shaders/lambert.vert", "../src/shaders/lambert.frag"));
	shaders.push_back(new ShaderProgram("../src/shaders/phong.vert", "../src/shaders/phong.frag"));
	shaders.push_back(new ShaderProgram("../src/shaders/blinn.vert", "../src/shaders/blinn.frag"));
}

void Application::createModels()
{

	scenes.push_back(new Scene(this->shaders));
	scenes.push_back(new Scene(this->shaders));
	scenes.push_back(new Scene(this->shaders));
	scenes.push_back(new Scene(this->shaders));
	Model *treeModel = new Model(tree, sizeof(tree));
	Model *bushModel = new Model(bushes, sizeof(bushes));
	Model *giftModel = new Model(gift, sizeof(gift));
	Model *suziModel = new Model(suziFlat, sizeof(suziFlat));
	Model *suziSmoothModel = new Model(suziSmooth, sizeof(suziSmooth));
	Model *ball = new Model(sphere, sizeof(sphere));
	Model *plainModel = new Model(plain,sizeof(plain));

	DrawableObjectFactory df;

	Light* l1 = new Light(glm::vec3(0.0f,0.0f,0.0f));

	scenes[0]->addObject(df.create(ball, shaders[5], new TransformationComposite({new Translation(vec3(0.0f, 2.0f, 0.0f)), new Scale(vec3(0.7f))}),l1));
	scenes[0]->addObject(df.create(ball, shaders[5], new TransformationComposite({new Translation(vec3(0.0f, -2.0f, 0.0f)), new Scale(vec3(0.7f))}),l1));
	scenes[0]->addObject(df.create(ball, shaders[5], new TransformationComposite({new Translation(vec3(2.0f, 0.0f, 0.0f)), new Scale(vec3(0.7f))}),l1));
	scenes[0]->addObject(df.create(ball, shaders[5], new TransformationComposite({new Translation(vec3(-2.0f, 0.0f, 0.0f)), new Scale(vec3(0.7f))}),l1));
	
	Light * forest_light = new Light(glm::vec3(25.0f,20.0f,25.0f));
	scenes[1]->addObject(df.create(plainModel,shaders[0],new Scale(glm::vec3(50.0f)),l1));
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			TransformationComposite *tc2 = new TransformationComposite();
			tc2->add(new Translation(vec3(static_cast<float>(j * -5), 0.0f, static_cast<float>(i * -5))));
			tc2->add(new Rotation(vec3(0.0f, j * i, 0.0f)));
			tc2->add(new Scale(vec3((float)rand() / RAND_MAX)));

			scenes[1]->addObject(df.create(treeModel, shaders[5], tc2,forest_light));
			TransformationComposite *tc3 = new TransformationComposite();
			TransformationComposite *tc4 = new TransformationComposite();
			TransformationComposite *tc5 = new TransformationComposite();
			TransformationComposite *tc6 = new TransformationComposite();
			tc3->add(tc2);
			tc4->add(tc2);
			tc5->add(tc2);
			tc6->add(tc2);
			tc3->add(new Translation(vec3(0.0f, 0.0f, 1.0f)));
			tc4->add(new Translation(vec3(0.0f, 0.0f, -1.0f)));
			tc5->add(new Translation(vec3(1.0f, 0.0f, 0.0f)));
			tc6->add(new Translation(vec3(-1.0f, 0.0f, 0.0f)));
			scenes[1]->addObject(df.create(bushModel, shaders[3], tc3,forest_light));
			scenes[1]->addObject(df.create(bushModel, shaders[3], tc4,forest_light));
			scenes[1]->addObject(df.create(bushModel, shaders[3], tc5,forest_light));
			scenes[1]->addObject(df.create(bushModel, shaders[3], tc6,forest_light));
		}
	}

	scenes[2]->addObject(df.create(suziModel,shaders[3],new TransformationComposite({new Translation(vec3(-10.0f,-1.2f,-5.6f)),new DynamicRotation(vec3(0.0,1.0,0.0),1)}),l1));

	scenes[3]->addObject(df.create(giftModel,shaders[3],new TransformationComposite({new Translation(vec3(-10.0f,-1.2f,-5.6f)),new DynamicRotation(vec3(0.0,1.0,0.0),1)}),l1));
	scenes[3]->addObject(df.create(suziSmoothModel,shaders[4],new TransformationComposite({new Translation(vec3(-7.0f,-1.2f,-5.6f)),new DynamicRotation(vec3(0.0,1.0,0.0),1)}),l1));
	scenes[3]->addObject(df.create(suziSmoothModel,shaders[5],new TransformationComposite({new Translation(vec3(-4.0f,-1.2f,-5.6f)),new DynamicRotation(vec3(0.0,1.0,0.0),1)}),l1));
	scenes[3]->addObject(df.create(suziSmoothModel,shaders[3],new TransformationComposite({new Translation(vec3(-1.0f,-1.2f,-5.6f)),new DynamicRotation(vec3(0.0,1.0,0.0),1)}),l1));
	scenes[3]->addObject(df.create(suziSmoothModel,shaders[2],new TransformationComposite({new Translation(vec3(2.0f,-1.2f,-5.6f)),new DynamicRotation(vec3(0.0,1.0,0.0),1)}),l1));
}

void Application::run()
{
	float rotation = 0.0f;
	double prevTime = glfwGetTime();
	int swapScene = 0;
	bool swapPressed = false;

	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		// clear color and depth buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			if (!swapPressed)
			{
				if (swapScene < this->scenes.size() - 1)
				{
					swapScene++;
				}
				else
				{
					swapScene = 0;
				}
				swapPressed = true;
			}
		}
		else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_RELEASE)
		{
			swapPressed = false;
		}

		scenes[swapScene]->getCamera()->inputs(this->window);
		scenes[swapScene]->drawScene();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
