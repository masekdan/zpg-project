#include "Application.h"

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
	-0.5f, 0.5f, 0.0f, 0, 0, 0,
	0.5f, -0.5f, 0.0f, 0, 0, 0,
	-0.5f, -0.5f, 0.0f, 0, 0, 0};

const float points2[] = {
	0.9f, 0.9f, 0.0f, 0, 0, 0,
	0.9f, 0.7f, 0.0f, 0, 0, 0,
	0.7f, 0.7f, 0.0f, 0, 0, 0,
	0.7f, 0.9f, 0.0f, 0, 0, 0};

void Application::initialization()
{
	window = glfwCreateWindow(800, 600, "ZPG 2: Electric boogaloo", NULL, NULL);
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
	shaders.push_back(new Shader("../src/shaders/default.vert", "../src/shaders/default.frag"));
	shaders.push_back(new Shader("../src/shaders/square.vert", "../src/shaders/square.frag"));
}

void Application::createModels()
{
	models.push_back(new Model(points, sizeof(points), shaders[0]));
	models.push_back(new Model(points2, sizeof(points2), shaders[1]));
	models.push_back(new Model(gift, sizeof(gift), shaders[0]));
}

void Application::run()
{
	glEnable(GL_DEPTH_TEST);
	while (!glfwWindowShouldClose(window))
	{
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// models[0]->drawModel();
		// models[1]->drawModel();
		models[2]->drawModel();
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
