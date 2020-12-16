#include "pch.h"
#include "Unity_PluginAPI/IUnityInterface.h"
#include "Unity_PluginAPI/IUnityGraphics.h"
#include <GL/glew.h>
#include "DebugCPP.h"

static IUnityInterfaces* s_UnityInterfaces = NULL;
static IUnityGraphics* s_Graphics = NULL;
static UnityGfxRenderer s_RendererType = kUnityGfxRendererNull;

unsigned int _shaderProgram;
bool _result;

const char* vsSource =
"#version 300 core\n"
"layout(location = 0) in vec4 pos;\n"
"void main()\n"
"{\n"
"gl_Position = pos;\n"
"}\n";

const char* fsSource =
"#version 300 core\n"
"layout(location = 0) out vec4 color;\n"
"void main()\n"
"{\n"
"color = vec4(0.0f,1.0f,1.0f,1.0f);\n"
"}\n";

float verts[] =
{
	-0.5f, -0.5f,
	0.5f, -0.5f,
	0.0f, 0.5f,
};
unsigned int _vao;
unsigned int _vbo;

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
	//glUseProgram(_shaderProgram);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 6, verts);

	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);

	//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, &verts, GL_DYNAMIC_DRAW);


	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	//glUnmapBuffer(GL_ARRAY_BUFFER);
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

			//glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
			//glEnableVertexAttribArray(0);

			CreateShaders();
			//glUseProgram(_shaderProgram);
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
