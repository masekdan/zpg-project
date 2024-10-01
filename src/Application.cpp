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
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f};

void Application::initialization()
{
    window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
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
    shaderProgram = new Shader("../src/shaders/default.vert", "../src/shaders/default.frag");
}

void Application::createModels()
{
    VAO1 = new VAO();
	VAO1->Bind();

	VBO1 = new VBO(points, sizeof(points));

	VAO1->LinkVBO(VBO1, 0);
	VAO1->Unbind();
	VBO1->Unbind();
}

void Application::run()
{
    while (!glfwWindowShouldClose(window))
	{
		// clear color and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shaderProgram->Activate();
		VAO1->Bind();
		//  draw triangles
		glDrawArrays(GL_POLYGON, 0, 4); // mode,first,count
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	exit(EXIT_SUCCESS);
}
