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
	window = glfwCreateWindow(800, 600, "Minecraft 2.0 pre-release 1", NULL, NULL);
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
	shaders.push_back(new ShaderProgram("../src/shaders/plain.vert", "../src/shaders/plain.frag"));
	shaders.push_back(new ShaderProgram("../src/shaders/skybox.vert", "../src/shaders/skybox.frag"));
	shaders.push_back(new ShaderProgram("../src/shaders/skybox_n.vert", "../src/shaders/skybox_n.frag"));
}

void Application::createModels()
{
	// skycube texture
	std::vector<std::string> faces = {
		"../src/textures/skybox/posx.jpg",
		"../src/textures/skybox/negx.jpg",
		"../src/textures/skybox/posy.jpg",
		"../src/textures/skybox/negy.jpg",
		"../src/textures/skybox/posz.jpg",
		"../src/textures/skybox/negz.jpg"
	};

	// light for balls
	Light *l1 = new PointLight(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f,0.1f,0.01f));

	// light for day scene
	std::vector<Light*> f_lights;
	f_lights.push_back(new DirectionLight(vec3(0.0,-1.0,-1.0)));

	// flashlight declaration
	Flashlight* flash = new Flashlight(vec3(-20.5f,5.0f,-14.0f),vec3(-1,0,0),20,vec3(1.0f,0.1f,0.01f));


	// lights for night scene
	std::vector<Light*> n_lights;
	n_lights.push_back(flash);
	n_lights.push_back(new PointLight(vec3(5.0f,3.5f,6.0f),vec3(1.0f,0.1f,0.01f)));
	n_lights.push_back(new PointLight(vec3(24.3f,27.3f,45.0f),vec3(1.0f,0.1f,0.01f)));

	// scenes creation
	scenes.push_back(new Scene(this->shaders,{l1}));
	scenes.push_back(new Scene(this->shaders,f_lights));
	scenes.push_back(new Scene(this->shaders,n_lights));
	scenes.push_back(new Scene(this->shaders,{l1}));


	// local models arrays
	Model *treeModel = new Model(tree, sizeof(tree),false);
	Model *bushModel = new Model(bushes, sizeof(bushes),false);
	Model *giftModel = new Model(gift, sizeof(gift),false);
	Model *suziModel = new Model(suziFlat, sizeof(suziFlat),false);
	Model *suziSmoothModel = new Model(suziSmooth, sizeof(suziSmooth),false);
	Model *ball = new Model(sphere, sizeof(sphere),false);
	Model *plainModel = new Model(plain, sizeof(plain),true);

	// extern models obj
	Model *cube = new Model("../src/ext_models/cube.obj");
	Model *house = new Model("../src/ext_models/house.obj");
	Model *login = new Model("../src/ext_models/login.obj");
	Model *zombie = new Model("../src/ext_models/zombie.obj");
	Model *extTree = new Model("../src/ext_models/tree.obj");
	Model *wall = new Model("../src/ext_models/zed.obj");
	Model *teren = new Model("../src/ext_models/teren.obj");
	Model *mnt = new Model("../src/ext_models/mount.blend1.obj");

	
	// texture setting
	plainModel->setTexture("../src/textures/grass.jpg");
	cube->setTexture("../src/textures/wooden_fence.png");
	house->setTexture("../src/textures/house.png");
	login->setTexture("../src/textures/wooden_fence.png");
	zombie->setTexture("../src/textures/zombie.png");
	wall->setTexture("../src/textures/wall.png");
	extTree->setTexture("../src/textures/tree.png");
	teren->setTexture("../src/textures/grass.jpg");
	mnt->setTexture("../src/textures/grass.jpg");

	DrawableObjectFactory df;


	// materials
	Material* treeMat = new Material(vec3(1.0,1.0,1.0),vec3(0.039 ,0.38 ,0.078),vec3(1.0,1.0,1.0));
	Material* ground = new Material(vec3(1.0,1.0,1.0),vec3(0.231 ,0.141 ,0.075),vec3(0.1,0.1,0.1));
	Material* bushMat = new Material(vec3(1.0,1.0,1.0),vec3(0.38 ,0.039 ,0.11),vec3(1.0,1.0,1.0));
	Material* zoombiMaterial = new Material(vec3(1.0,1.0,1.0),vec3(0.38 ,0.039 ,0.11),vec3(0.0,0.0,0.0));

	
	// balls scene
	scenes[0]->addObject(df.create(ball, shaders[4], new TransformationComposite({new Translation(vec3(0.0f, 2.0f, 0.0f)), new Scale(vec3(0.7f))}), treeMat));
	scenes[0]->addObject(df.create(ball, shaders[4], new TransformationComposite({new Translation(vec3(0.0f, -2.0f, 0.0f)), new Scale(vec3(0.7f))}), treeMat));
	scenes[0]->addObject(df.create(ball, shaders[4], new TransformationComposite({new Translation(vec3(2.0f, 0.0f, 0.0f)), new Scale(vec3(0.7f))}), treeMat));
	scenes[0]->addObject(df.create(ball, shaders[4], new TransformationComposite({new Translation(vec3(-2.0f, 0.0f, 0.0f)), new Scale(vec3(0.7f))}), treeMat));

	// flashlight setting - war crime
	scenes[0]->getCamera()->registerObserver(flash);
	flash->registerSubject(scenes[0]->getCamera());

	// day scene
	scenes[1]->setSkybox(faces,shaders[7]);

	scenes[1]->addObject(df.create(plainModel, shaders[4],new TransformationComposite({new Translation(vec3(-22.5f,0,-22.5f)),new Scale(glm::vec3(25.0f))}), ground));
	scenes[1]->addObject(df.create(treeModel,shaders[4],new TransformationComposite({new Translation(vec3(-45,0,-25)),new DynamicRotation(vec3(0,1,0),1)}),treeMat));
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			TransformationComposite *tc2 = new TransformationComposite();
			tc2->add(new Translation(vec3(static_cast<float>(j * -5), 0.0f, static_cast<float>(i * -5))));
			tc2->add(new Rotation(vec3(0.0f, j * i, 0.0f)));
			tc2->add(new Scale(vec3(0.15f)));

			scenes[1]->addObject(df.create(extTree, shaders[4], tc2,treeMat));
		}
	}
	scenes[1]->addObject(df.create(mnt,shaders[6],new TransformationComposite({new Translation(vec3(-60,0,-20)),new Scale(vec3(3.0f))}),zoombiMaterial));

	// zombie bezier curve movement points
	glm::mat4x3 zoombi = glm::mat4x3(glm::vec3(-40, 0, -35),
        glm::vec3(-40, 10, -37.5),
        glm::vec3(-40, 11, -40),
        glm::vec3(-40, 0, -45));


	scenes[1]->addObject(df.create(wall, shaders[4], new Translation(vec3(-40,0,-39)),bushMat));
	scenes[1]->addObject(df.create(zombie, shaders[4], new CurveTranslation(zoombi,1.0f,0.005f),treeMat));
	scenes[1]->addObject(df.create(house, shaders[4],  new TransformationComposite({new Translation(vec3(-10,0,-40)),new Rotation(vec3(0,90,0))}),bushMat));

	// night scene

	scenes[2]->addObject(df.create(teren,shaders[4],new Scale(vec3(1.0f)),ground));

	// zombies
	scenes[2]->addObject(df.create(zombie,shaders[4],new TransformationComposite({new Translation(vec3(10,0,-10))}),zoombiMaterial));
	scenes[2]->addObject(df.create(zombie,shaders[4],new TransformationComposite({new Translation(vec3(-15,0,-8))}),zoombiMaterial));
	scenes[2]->addObject(df.create(zombie,shaders[4],new TransformationComposite({new Translation(vec3(-10,0,-9))}),zoombiMaterial));
	scenes[2]->addObject(df.create(zombie,shaders[4],new TransformationComposite({new Translation(vec3(0,0.1f,-13))}),zoombiMaterial));
	scenes[2]->addObject(df.create(zombie,shaders[4],new TransformationComposite({new Translation(vec3(5,0,-11))}),zoombiMaterial));

	//house
	scenes[2]->addObject(df.create(house,shaders[5],new TransformationComposite({new Translation(vec3(5,0,18))}),treeMat));

	//tree
	scenes[2]->addObject(df.create(extTree,shaders[4],new TransformationComposite({new Translation(vec3(-15,0,18))}),treeMat));

	//login
	scenes[2]->addObject(df.create(login,shaders[5],new TransformationComposite({new Translation(vec3(26,26,51)), new Rotation(vec3(0,180,0))}),treeMat));
	

	// lightting demonstration
	scenes[3]->addObject(df.create(giftModel, shaders[3], new TransformationComposite({new Translation(vec3(-10.0f, -1.2f, -5.6f)), new Rotation(vec3(0.0, 1.0, 0.0))}), treeMat));
	scenes[3]->addObject(df.create(suziSmoothModel, shaders[4], new TransformationComposite({new Translation(vec3(-7.0f, -1.2f, -5.6f)), new Rotation(vec3(0.0, 1.0, 0.0))}),treeMat));
	scenes[3]->addObject(df.create(suziSmoothModel, shaders[5], new TransformationComposite({new Translation(vec3(-4.0f, -1.2f, -5.6f)), new Rotation(vec3(0.0, 1.0, 0.0))}),treeMat));
	scenes[3]->addObject(df.create(suziSmoothModel, shaders[3], new TransformationComposite({new Translation(vec3(-1.0f, -1.2f, -5.6f)), new Rotation(vec3(0.0, 1.0, 0.0))}), treeMat));
	scenes[3]->addObject(df.create(suziSmoothModel, shaders[2], new TransformationComposite({new Translation(vec3(2.0f, -1.2f, -5.6f)), new Rotation(vec3(0.0, 1.0, 0.0))}),treeMat));
}

void Application::run()
{

	int swapScene = 0;
	bool swapPressed = false;


	glEnable(GL_DEPTH_TEST);
    glEnable(GL_STENCIL_TEST);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);


	while (!glfwWindowShouldClose(window))
	{
		// clear color and depth buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

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
