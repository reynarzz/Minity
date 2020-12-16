#include "pch.h"
#include "Unity_PluginAPI/IUnityInterface.h"
#include "Unity_PluginAPI/IUnityGraphics.h"
#include "DebugCPP.h"

#include <GL/glew.h>
#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec4;
using glm::mat4;

static IUnityInterfaces* s_UnityInterfaces = NULL;
static IUnityGraphics* s_Graphics = NULL;
static UnityGfxRenderer s_RendererType = kUnityGfxRendererNull;

unsigned int _shaderProgram;
bool _result;

const char* vsSource =
"#version 330 core\n"
"layout(location = 0) in vec4 pos;\n"
"uniform mat4 rotate;"
"void main()\n"
"{\n"
"gl_Position = rotate * pos;\n"
"}\n";

const char* fsSource =
"#version 330 core\n"
"layout(location = 0) out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(0.0f, 0.0f, 1.0f, 1.0f);\n"
"}\n";

float verts[] =
{
	-1.0f, -1.0f,
	1.0f, -1.0f,
	1.0f, 1.0f,
};

unsigned int _vao;
unsigned int _vbo;
float _time;
float _deltaTime;

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetTime(float time, float deltaTime) 
{
	_time = time;
}

mat4 ZRotation(float angle)
{
	mat4 zRot;

	zRot = mat4(vec4(cos(angle), sin(angle), 0.0f, 0.0f),
				vec4(-sin(angle), cos(angle), 0.0f, 0.0f),
				vec4(0, 0, 1, 0),
				vec4(0, 0, 0, 1));

	return zRot;
}
mat4 _modelMatrix;

void CreateShaders()
{
	_shaderProgram = glCreateProgram();

	unsigned int vsID = glCreateShader(GL_VERTEX_SHADER);
	unsigned int fsID = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vsID, 1, &vsSource, 0);
	glShaderSource(fsID, 1, &fsSource, 0);

	glCompileShader(vsID);
	glCompileShader(fsID);

	glAttachShader(_shaderProgram, vsID);
	glAttachShader(_shaderProgram, fsID);

	glLinkProgram(_shaderProgram);
	glValidateProgram(_shaderProgram);

	glDeleteShader(vsID);
	glDeleteShader(fsID);
}

static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	//Aqui es donde se dibuja,
	//Render estate: glDepthFunc(GL_LEQUAL);
	//Uso el shader program.
	//se setea el vertex array object si se esta usando el core profile. (siempre se esta usando)
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	//glUseProgram(_shaderProgram);

	/*if (_result)
	{
		Debug::Log("fine", Color::White);
	}
	else
	{
		Debug::Log("bad", Color::White);
	}*/

	//Generate vertex array object
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	//Bind buffer and set data.
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 6, verts);

	//Set data layout for the shader.
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	CreateShaders();
	glUseProgram(_shaderProgram);

	unsigned int rotateID = glGetUniformLocation(_shaderProgram, "rotate");

	glUniformMatrix4fv(rotateID, 1, GL_FALSE, glm::value_ptr(ZRotation(_time)));

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDeleteVertexArrays(1, &_vao);
}

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

			if (glewInit() == GLEW_OK)
			{
				_result = true;
			}
			else
			{
				_result = false;
			}

			glGenBuffers(1, &_vbo);
			glBindBuffer(GL_ARRAY_BUFFER, _vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, verts, GL_STREAM_DRAW);
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
}
