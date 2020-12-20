#include "pch.h"
#include "Scene.h"
#include <iostream>
#include <fstream>

#include <Obj/OBJ_Loader.h>
#include "MyOBJParser.h"

MeshRenderer* GetSimpleMeshRenderer(const string& objectPath);
using objl::Loader;

Mesh* GetMesh(const string& objectPath);

Scene::Scene()
{
	// I have to remove this later. An scene is able to exist without camera.
	_cameras.push_back(new Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(0.0f, -90.0f), 0));

	_objects.push_back(GetSimpleMeshRenderer("../OBJModels/worldtest2.obj"));
	_objects.push_back(GetSimpleMeshRenderer("../OBJModels/bigBoat.obj"));
}

MeshRenderer* GetSimpleMeshRenderer(const string& objectPath)
{
	string vsSource =
		"#version 330 core\n"
		"layout(location = 0) in vec4 pos;\n"
		"out vec4 color;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;"
		"uniform mat4 projection;\n"
		"void main()\n"
		"{\n"
		"color = pos;\n"
		"gl_Position = projection * view * model * pos;\n"
		"//gl_Position = pos;\n"
		"}";

	string fsSource =
		"#version 330 core\n"
		"layout(location = 0) out vec4 outColor;\n"
		"in vec4 color;\n"
		"void main()\n"
		"{\n"
		"outColor =  color;//vec4(1.0f,1.0f,1.0f,1.0f);\n"
		"}";

	Mesh* mesh = GetMesh(objectPath);

	if (mesh == nullptr)
	{
		vector<float>* vertices = new vector<float>
		{
			0.0f, 1.0f, 0.0f,
			-1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, 1.0f,
			1.0f, 0.0f, -1.0f,
			-1.0f, 0.0f, -1.0f,
		};

		vector<unsigned int>* indices = new vector<unsigned int>
		{
			0, 1, 2,
			0, 2, 3,
			0, 3, 4,
			0, 4, 1
		};


		mesh = new Mesh(vertices, indices);
	}

	Shader* shader = new Shader(vsSource, fsSource);
	Material* material = new Material(shader);

	MeshRenderer* meshRenderer = new MeshRenderer(mesh, material);

	return meshRenderer;
}

Mesh* GetMesh(const string& objectPath)
{
	Mesh* mesh = nullptr;

	vector<float>* vertices = new vector<float>();
	vector<unsigned int>* indices = new vector<unsigned int>();


	Loader loader;
	bool loaded = loader.LoadFile(objectPath);

	if (loaded)
	{
		objl::Mesh curMesh = loader.LoadedMeshes[0];

		// Print Mesh Name
		// file << "Mesh " << i << ": " << curMesh.MeshName << "\n";

		// Print Vertices
		// file << "Vertices:\n";

		// Go through each vertex and print its number,
		//  position, normal, and texture coordinate
		for (int i = 0; i < loader.LoadedMeshes.size(); i++)
		{
			for (int j = 0; j < curMesh.Vertices.size(); j++)
			{
				vertices->push_back(curMesh.Vertices[j].Position.X * 0.1f);
				vertices->push_back(curMesh.Vertices[j].Position.Y * 0.1f);
				vertices->push_back(-curMesh.Vertices[j].Position.Z * 0.1f);

				/*"P(" << curMesh.Vertices[j].Position.X << ", " << curMesh.Vertices[j].Position.Y << ", " << curMesh.Vertices[j].Position.Z << ") " <<
				"N(" << curMesh.Vertices[j].Normal.X << ", " << curMesh.Vertices[j].Normal.Y << ", " << curMesh.Vertices[j].Normal.Z << ") " <<
				"TC(" << curMesh.Vertices[j].TextureCoordinate.X << ", " << curMesh.Vertices[j].TextureCoordinate.Y << ")\n";*/
			}

			// Go through every 3rd index and print the
			//	triangle that these indices represent
			for (int j = 0; j < curMesh.Indices.size(); j += 3)
			{
				indices->push_back(curMesh.Indices[j]);
				indices->push_back(curMesh.Indices[j + 1]);
				indices->push_back(curMesh.Indices[j + 2]);
				//file << "T" << j / 3 << ": " <<  << ", " << curMesh.Indices[j + 1] << ", " << curMesh.Indices[j + 2] << "\n";
			}
		}
		mesh = new Mesh(vertices, indices);
	}

	/*auto obj = ParseOBJModel("../OBJModels/boat.obj");

	for (auto vert : obj.verts)
	{
		vertices->push_back(vert.x * 0.2f);
		vertices->push_back(vert.y * 0.2f);
		vertices->push_back(-vert.z * 0.2f);
	}

	for (auto indice : obj.elements)
	{
		indices->push_back(indice);
	}

	mesh = new Mesh(vertices, indices);*/

	return mesh;
}

//void MoveCamera()
//{
//	unsigned int viewUniformID = glGetUniformLocation(_shaderProgram, "view");
//
//	if (_mouseKey == MouseKeys::LEFT_CLICK)
//	{
//		_angleX += -_mouseDelta.y;
//		_angleY += _mouseDelta.x;
//	}
//
//	glm::vec3 forward(0.0f, 0.0f, -1.0f);
//
//	forward.x = cos(glm::radians(_angleY)) * cos(glm::radians(_angleX));
//	forward.y = sin(glm::radians(_angleX));
//	forward.z = sin(glm::radians(_angleY)) * cos(glm::radians(_angleX));
//
//	forward = glm::normalize(forward);
//
//	glm::vec3 right(glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0, 0.0f))));
//	glm::vec3 up(glm::normalize(glm::cross(right, forward)));
//
//	if (_normalKey == NormalKey::A)
//	{
//		right *= 0.01f;
//
//		position += -right;
//
//	}
//	else if (_normalKey == NormalKey::D)
//	{
//		right *= 0.01f;
//
//		position += right;
//	}
//
//	if (_normalKey == NormalKey::W)
//	{
//		forward *= 0.01f;
//
//		position += forward;
//	}
//	if (_normalKey == NormalKey::S)
//	{
//		forward *= 0.01f;
//
//		position += -forward;
//	}
//
//	if (_normalKey == NormalKey::Q) 
//	{
//		position += glm::vec3(0.0f, -0.01f, 0.0f);
//	}
//	else if (_normalKey == NormalKey::E)
//	{
//		position += glm::vec3(0.0f, 0.01f, 0.0f);
//	}
//
//	glm::mat4 view = glm::lookAt(position, position + forward, up);
//
//
//	glUniformMatrix4fv(viewUniformID, 1, GL_FALSE, glm::value_ptr(view));
//}

const vector<MeshRenderer*>& Scene::GetMeshRenderers() const
{
	return _objects;
}

const vector<Camera*>& Scene::GetCameras() const
{
	return _cameras;
}

void Scene::SetAspectRatio(float aspect)
{
	for (auto camera : _cameras)
	{
		camera->UpdateProjectionMatrix(aspect);
	}
}

Scene::~Scene()
{
	// Clear destroys the objects!
	_objects.clear();
	_objects.shrink_to_fit();
}