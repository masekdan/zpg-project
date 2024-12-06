#include "Model.h"

Model::Model(const GLfloat *verticies, GLsizeiptr size, bool hasTexture)
{
	this->hasTexture = hasTexture;
	vertexArray = new VAO();
	vertexArray->Bind();
	this->size = size;
	vertexBuffer = new VBO(verticies, size);

	vertexArray->LinkVBO(vertexBuffer, this->hasTexture);
	vertexArray->Unbind();
	vertexArray->Unbind();

	this->indices = false;
}

struct Vertex
{
	float Position[3];
	float Normal[3];
	float Texture[2];
};

Model::Model(char *path)
{
	Assimp::Importer importer;

	unsigned int importOptions = aiProcess_Triangulate		 // Converts polygons to triangles
								 | aiProcess_OptimizeMeshes // Reduces the number of submeshes
								 | aiProcess_JoinIdenticalVertices     // Removes duplicate vertices
								 | aiProcess_CalcTangentSpace;

	const aiScene *scene = importer.ReadFile(path, importOptions);

	if (scene)
	{
		/*for (int i = 0; i<scene->mNumMaterials;i++)
		{
			const aiMaterial* mat = scene->mMaterials[i];
			aiScene name;
			mat->Get(AI_MATKEY_NAME,name);
			aiColor4D d;
			glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
			if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
				diffuse = glm::vec4(d.r, d.g, d.b, d.a);
		}*/

		for (int i = 0; i < scene->mNumMeshes; i++)
		{
			aiMesh *mesh = scene->mMeshes[i];
			Vertex *pVertices = new Vertex[mesh->mNumVertices];
			std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);
			for (int j = 0; j < mesh->mNumVertices; j++)
			{
				if (mesh->HasPositions())
				{
					pVertices[j].Position[0] = mesh->mVertices[j].x;
					pVertices[j].Position[1] = mesh->mVertices[j].y;
					pVertices[j].Position[2] = mesh->mVertices[j].z;
				}

				if (mesh->HasNormals())
				{
					pVertices[j].Normal[0] = mesh->mNormals[j].x;
					pVertices[j].Normal[1] = mesh->mNormals[j].y;
					pVertices[j].Normal[2] = mesh->mNormals[j].z;
				}

				if (mesh->HasTextureCoords(0))
				{
					pVertices[j].Texture[0] = mesh->mTextureCoords[0][j].x;
					pVertices[j].Texture[1] = mesh->mTextureCoords[0][j].y;
				}
			}

			unsigned int *pIndices = nullptr;
			if (mesh->HasFaces())
			{
				pIndices = new unsigned int[mesh->mNumFaces * 3];
				for (int j = 0; j < mesh->mNumFaces; j++)
				{
					pIndices[j * 3] = mesh->mFaces[j].mIndices[0];
					pIndices[j * 3 + 1] = mesh->mFaces[j].mIndices[1];
					pIndices[j * 3 + 2] = mesh->mFaces[j].mIndices[2];
				}
			}

			this->vertexArray = new VAO();
			vertexArray->Bind();
			this->size = sizeof(Vertex) * mesh->mNumVertices;
			this->vertexBuffer = new VBO((GLfloat *)pVertices, this->size);
			this->vertexArray->LinkVBO(this->vertexBuffer, true);

			GLuint IBO = 0;
			glGenBuffers(1, &IBO);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			this->indicesCount = mesh->mNumFaces * 3;

			this->indices = true;

			
			vertexArray->Unbind();
			std::cout << "Model loaded" << std::endl;
		}
	}
}

bool Model::hasTextureMet()
{
	return this->hasTexture;
}

void Model::setTexture(char *path)
{
	this->img = SOIL_load_OGL_texture(path, SOIL_LOAD_RGBA, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);

	this->hasTexture = true;

	glBindTexture(GL_TEXTURE_2D, this->img);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Model::drawModel()
{
	if (hasTexture)
	{
		glActiveTexture(GL_TEXTURE0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glBindTexture(GL_TEXTURE_2D, this->img);
	}

	vertexArray->Bind();

	if (!this->indices)
	{
		glDrawArrays(GL_TRIANGLES, 0, this->size / 8);
	}
	else
	{
		glDrawElements(GL_TRIANGLES, this->indicesCount, GL_UNSIGNED_INT, NULL);
	}
}

Model::~Model()
{
	this->vertexArray->Delete();
	this->vertexBuffer->Delete();
}