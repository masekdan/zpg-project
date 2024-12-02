#include "Skybox.h"

Skybox::Skybox(std::vector<std::string> faces, ShaderProgram* shader)
{
    
    this->shader = shader;
    vbo = new VBO(skycube,sizeof(skycube));

    glGenVertexArrays(1,&this->vao);
    glBindVertexArray(this->vao);

    this->vbo->Bind();
    glEnableVertexAttribArray(0); 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (GLvoid*)0);
    glBindVertexArray(0);

   
    this->cubemapTexture = SOIL_load_OGL_cubemap(faces[0].c_str(),faces[1].c_str(),faces[2].c_str(),faces[3].c_str(),faces[4].c_str(),faces[5].c_str(),SOIL_LOAD_RGB, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
    if (this->cubemapTexture == NULL) {
        std::cout << "An error occurred while loading CubeMap." << std::endl;
        exit(EXIT_FAILURE);
    }
    for (auto x : faces)
    {
        std::cout << x << std::endl;
    }

}

void Skybox::draw(glm::mat4 projection, glm::mat4 view)
{
    shader->Activate();
    glActiveTexture(GL_TEXTURE0);
    shader->SetUniform("view",glm::mat4(glm::mat3(view)));
    shader->SetUniform("projection",projection);
    shader->SetUniform("skybox", 0);

    glDepthMask(GL_FALSE);
    glBindVertexArray(this->vao);
    glBindTexture(GL_TEXTURE_2D,this->cubemapTexture);
    glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
    glDrawArrays(GL_TRIANGLES,0,108);
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
    this->shader->Deactivate();

}