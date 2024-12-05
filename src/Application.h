#ifndef APPLICATION_CLASS_H
#define APPLICATION_CLASS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>					// glm::vec3
#include <glm/vec4.hpp>					// glm::vec4
#include <glm/mat4x4.hpp>				// glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>			// glm::value_ptr

// Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <SOIL/SOIL.h>

#include <assimp/Importer.hpp>// C++ importerinterface
#include <assimp/scene.h>// aiSceneoutputdata structure
#include <assimp/postprocess.h>// Post processingflags

#include "ShaderProgram.h"
#include "VBO.h"
#include "VAO.h"
#include "Model.h"
#include "DrawableObject.h"
#include "Scene.h"

#include "Rotation.h"
#include "Scale.h"
#include "Translation.h"
#include "DynamicRotation.h"
#include "CurveTranslation.h"
#include "TransformationComposite.h"

#include "Light.h"
#include "PointLight.h"
#include "DirectionLight.h"
#include "SpotLight.h"
#include "Flashlight.h"



#include "Material.h"
#include "Controller.h"

// model inclusion

#include "models/gift.h"
#include "models/suzi_flat.h"
#include "models/tree.h"
#include "models/suzi_smooth.h"
#include "models/bushes.h"
#include "models/sphere.h"
#include "models/plain.h"

class Application
{
private:
    GLFWwindow *window;
    std::vector<ShaderProgram*> shaders;
    std::vector<Scene*> scenes;
    float width;
    float height;
public:
    Application();
    void initialization();
    void createShaders();
    void createModels();
    void run();
};



#endif