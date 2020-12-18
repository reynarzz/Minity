#include "pch.h"
#include "Unity_PluginAPI/IUnityInterface.h"
#include "Unity_PluginAPI/IUnityGraphics.h"
#include "DebugCPP.h"
#include "MeshRenderer.h"
#include <glm/glm.hpp>

#include "Renderer.h"
#include "vector";

using std::vector;

static IUnityInterfaces* s_UnityInterfaces = NULL;
static IUnityGraphics* s_Graphics = NULL;
static UnityGfxRenderer s_RendererType = kUnityGfxRendererNull;

Renderer* _renderer;

unsigned int _shaderProgram;
bool _result;

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
"gl_Position = pos;"
"\n"
"}";

string fsSource =
"#version 330 core\n"
"layout(location = 0) out vec4 outColor;\n"
"in vec4 color;\n"
"void main()\n"
"{\n"
"outColor =color;// vec4(1.0f,1.0f,1.0f,1.0f);\n"
"}";


float _time;
float _deltaTime;

float _screenWidth;
float _screenHeight;
float _screenAspectRatio;

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetTime(float time, float deltaTime)
{
	_time = time;
	_deltaTime = deltaTime;
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetScreenValues(float width, float height, float aspect)
{
	_screenWidth = width;
	_screenHeight = height;
	_screenAspectRatio = aspect;
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetPos(float x, float y, float z)
{
	//_pos = glm::vec3(x, y, z);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetRot(float x, float y, float z)
{
	//_rot = glm::vec3(x, y, z);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetMouseData(float xPos, float yPos, float deltaX, float deltaY)
{
	/*_mousePos = glm::vec2(xPos, yPos);
	_mouseDelta = glm::vec2(deltaX, deltaY);*/
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetKeyDow(int keyType, int key)
{
	/*if (keyType == 0)
	{
		_normalKey = static_cast<NormalKey>(key);
	}
	if (keyType == 1)
	{
		_mouseKey = static_cast<MouseKeys>(key);
	}
	else if (keyType == 2)
	{
		_modifierKey = static_cast<ModifierKeys>(key);
	}

	if (keyType > 2)
	{
		Debug::Log("Wrong key number");
	}*/
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetKeyUp(int keyType)
{
	/*if (keyType == 0)
	{
		_normalKey = NormalKey::RELEASED;
	}

	if (keyType == 1)
	{
		_mouseKey = MouseKeys::RELEASED;
	}

	if (keyType == 2)
	{
		_modifierKey = ModifierKeys::RELEASED;
	}

	if (keyType > 2)
	{
		Debug::Log("Wrong key number");
	}*/
}


static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	_renderer->Draw();
}

float _angleX;
float _angleY;
float _xMove;

MeshRenderer* GetMesh() 
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

	Mesh* mesh = new Mesh(vertices, indices);
	Shader* shader = new Shader(vsSource, fsSource);

	Material* material = new Material(shader);

	MeshRenderer* meshRenderer = new MeshRenderer(mesh, material);

	return meshRenderer;
}

//mat4 viewRot(1.0f);
//glm::vec3 position;

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

extern "C"
UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API Run()
{
	//Necesario para acceder al renderEvent desde unity.
	return OnRenderEvent;
}

static void UNITY_INTERFACE_API
OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	switch (eventType)
	{
	case kUnityGfxDeviceEventInitialize:
	{
		s_RendererType = s_Graphics->GetRenderer();

		if (s_RendererType == kUnityGfxRendererOpenGLCore)
		{
			//Aqui inicializo el renderer de open gl (Creo los shaders, seteo las matrices(world y projection), crear los vertex buffer)
			_renderer = new Renderer();

			_renderer->AddMeshToRenderer(GetMesh());
		}

		//TODO: user initialization code
		break;
	}
	case kUnityGfxDeviceEventShutdown:
	{
		s_RendererType = kUnityGfxRendererNull;
		//TODO: user shutdown code
		break;
	}
	case kUnityGfxDeviceEventBeforeReset:
	{
		//TODO: user Direct3D 9 code
		break;
	}
	case kUnityGfxDeviceEventAfterReset:
	{
		//TODO: user Direct3D 9 code
		break;
	}
	};
}

// Unity plugin load event
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginLoad(IUnityInterfaces * unityInterfaces)
{
	s_UnityInterfaces = unityInterfaces;
	s_Graphics = unityInterfaces->Get<IUnityGraphics>();

	s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

	// Run OnGraphicsDeviceEvent(initialize) manually on plugin load
	// to not miss the event in case the graphics device is already initialized
	OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

// Unity plugin unload event
extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API
UnityPluginUnload()
{
	s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
	delete _renderer;
}
