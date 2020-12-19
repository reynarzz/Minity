#include "pch.h"
#include "Unity_PluginAPI/IUnityInterface.h"

#include "MinityEngine.h"


MeshRenderer* GetMesh()
{
	string vsSource =
		"#version 330 core\n"
		"layout(location = 0) in vec4 pos;\n"
		"out vec4 color;\n"
		"uniform mat4 model;\n"
		"uniform mat4 view;"
		"uniform mat4 project;\n"
		"void main()\n"
		"{\n"
		"color = pos;\n"
		"//gl_Position = project * view * model * pos;\n"
		"gl_Position = pos;\n"
		"}";

	string fsSource =
		"#version 330 core\n"
		"layout(location = 0) out vec4 outColor;\n"
		"in vec4 color;\n"
		"void main()\n"
		"{\n"
		"outColor =  color;//vec4(1.0f,1.0f,1.0f,1.0f);\n"
		"}";


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

	Mesh* mesh = new Mesh(vertices, indices);
	Shader* shader = new Shader(vsSource, fsSource);

	Material* material = new Material(shader);

	MeshRenderer* meshRenderer = new MeshRenderer(mesh, material);

	return meshRenderer;
}

//Aqui inicializo el renderer de open gl (Creo los shaders, seteo las matrices(world y projection), crear los vertex buffer)

/// <summary>An engine that runs above the unity engine.</summary>
MinityEngine::MinityEngine() 
	: _deltaTime(-1), _screenInfo()
{
	_renderer = new Renderer();

	//Add a geometry at the start.
	_renderer->AddObjectToRenderer(GetMesh());
}

void MinityEngine::Update(float deltaTime, const ScreenInfo& screenInfo)
{
	_deltaTime = deltaTime;
	_screenInfo = screenInfo;


	// Do your rendering stuff below.--------------

	_renderer->Draw();
}

float MinityEngine::GetDeltaTime()
{
	return _deltaTime;
}

MinityEngine::~MinityEngine()
{
	delete _renderer;
}