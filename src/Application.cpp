#include "Application.h"

using glm::vec3;

static void error_callback(int error, const char *description) { fputs(description, stderr); }

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

static void window_focus_callback(GLFWwindow *window, int focused) { printf("window_focus_callback \n"); }

static void window_iconify_callback(GLFWwindow *window, int iconified) { printf("window_iconify_callback \n"); }

static void window_size_callback(GLFWwindow *window, int width, int height)
{
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

static void cursor_callback(GLFWwindow *window, double x, double y) { printf("cursor_callback \n"); }

static void button_callback(GLFWwindow *window, int button, int action, int mode)
{
	if (action == GLFW_PRESS)
		printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

Application::Application()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}
}

float points[] = {
	-0.5f, 0.5f, 0.0f, 1, 0, 0,
	0.5f, -0.5f, 0.0f, 0, 1, 0,
	-0.5f, -0.5f, 0.0f, 0, 0, 1};

const float points2[] = {
	0.9f, 0.9f, 0.0f, 0.58f, 0.12f, 0,
	0.9f, 0.7f, 0.0f, 0, 0, 1,
	0.7f, 0.7f, 0.0f, 0, 0, 1,
	0.7f, 0.9f, 0.0f, 0, 0, 1};

const float a[] = {
     -.5f, -.5f, .5f,  1.0f, 0, 1.0f,
     -.5f, .5f, .5f,  1.0f, 0, 1,
       .5f, .5f, .5f,  0, 1.0f, 0,
       .5f, -.5f, .5f,  0, 0, 1.0f };

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
	shaders.push_back(new ShaderProgram("../src/shaders/tree.vert","../src/shaders/tree.frag"));
}

void Application::createModels()
{
	scene1 = new Scene();
	scene2 = new Scene();
	Model* treeModel = new Model(tree,sizeof(tree));
	Model* bushModel = new Model(bushes,sizeof(bushes));
	Model* giftModel = new Model(gift,sizeof(gift));
	Model* suziModel = new Model(suziFlat,sizeof(suziFlat));
	Model* square = new Model(points2,sizeof(points2));
	Model* ball = new Model(sphere,sizeof(sphere));

	//tranformation pos, rot, scale

	DrawableObjectFactory df;

	TransformationComposite* tc = new TransformationComposite();

	tc->add(new Translation(vec3(0.25f,0.2f,0.2f)));
	tc->add(new Rotation(vec3(0.0f,2.8f,0.0f)));
	tc->add(new Scale(vec3(0.3f)));

	//scene1->addObject(df.create(square,shaders[0],tc));
	//scene1->addObject(df.create(giftModel,shaders[2],new Transformation(vec3(-0.5f,0.2f,0.0f),vec3(0.0f,0.25f,0.0f),1.0f)));
	//scene1->addObject(df.create(ball,shaders[2],new Transformation(vec3(-0.4f,-0.2f,0.5f),vec3(0.0f,0.0f,0.0f),0.2f)));
	scene1->addObject(df.create(suziModel,shaders[2],tc));

	//first layer of trees
	//scene2->addObject(df.create(treeModel,shaders[2],new Transformation(vec3(-0.8f,-0.7f,0.5f),vec3(0.0f,0.5f,0.0f),0.2f)));
	//scene2->addObject(df.create(treeModel,shaders[2],new Transformation(vec3(-0.4f,-0.7f,0.5f),vec3(0.0f,2.8f,0.0f),0.26f)));
	//scene2->addObject(df.create(treeModel,shaders[2],new Transformation(vec3(0.0f,-0.7f,0.5f),vec3(0.0f,3.1f,0.0f),0.24f)));
	//scene2->addObject(df.create(treeModel,shaders[2],new Transformation(vec3(0.4f,-0.7f,0.5f),vec3(0.0f,0.5f,0.0f),0.3f)));
	//scene2->addObject(df.create(treeModel,shaders[2],new Transformation(vec3(0.8f,-0.7f,0.5f),vec3(0.0f,0.5f,0.0f),0.18f)));

	//second layer of trees
	//scene2->addObject(df.create(treeModel,shaders[2],new Transformation(vec3(-0.9f,-0.65f,0.8f),vec3(0.0f,0.5f,0.0f),0.16f)));
	//scene2->addObject(df.create(treeModel,shaders[2],new Transformation(vec3(-0.5f,-0.65f,0.8f),vec3(0.0f,1.5f,0.0f),0.22f)));
	//scene2->addObject(df.create(treeModel,shaders[2],new Transformation(vec3(-0.1f,-0.65f,0.8f),vec3(0.0f,2.5f,0.0f),0.2f)));
	//scene2->addObject(df.create(treeModel,shaders[2],new Transformation(vec3(0.3f,-0.65f,0.8f),vec3(0.0f,3.5f,0.0f),0.26f)));
	//scene2->addObject(df.create(treeModel,shaders[2],new Transformation(vec3(0.7f,-0.65f,0.8f),vec3(0.0f,4.5f,0.0f),0.14f)));
	//scene2->addObject(df.create(bushModel,shaders[2],new Transformation(vec3(-0.5f,-0.75f,0.8f),vec3(0.0f,5.5f,0.0f),0.16f)));

	//bushes
	float pos = -0.9f;
	for (int i = 0 ; i<15;i++)
	{
		//scene2->addObject(df.create(bushModel,shaders[2],new Transformation(vec3(pos,-0.8f,-0.5f),vec3(0.7f,pos*i,0.0f),0.2f)));
		pos += 0.15f;
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1/60)
		{
			rotation += 0.5f;
			prevTime = crntTime;
		}
		scene1->drawScene();
		//scene2->drawScene();
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
