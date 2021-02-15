#include "pch.h"
#include "Unity_PluginAPI/IUnityInterface.h"
#include "Unity_PluginAPI/IUnityGraphics.h"
#include <glm/glm.hpp>

#include "MinityEngine.h"
#include "Console.h"
#include <iostream>

static IUnityInterfaces* s_UnityInterfaces = NULL;
static IUnityGraphics* s_Graphics = NULL;
static UnityGfxRenderer s_RendererType = kUnityGfxRendererNull;

MinityEngine* _minityEngine;
ScreenInfo _scrInfo_;

float _time;
float _deltaTime;

void OnRenderEvent(int eventID);

bool openConsole = false;

extern "C" 
{
	void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetTime(float time, float deltaTime)
	{
		_time = time;
		_deltaTime = deltaTime;
	}

	void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API SetScreenValues(int width, int height, float aspect)
	{
		_scrInfo_._dimensions.x = width;
		_scrInfo_._dimensions.y = height;
		_scrInfo_._aspectRatio = aspect;
	}

	UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API Run()
	{
		return OnRenderEvent;
	}
}

static void UNITY_INTERFACE_API OnRenderEvent(int eventID)
{
	if (!openConsole) 
	{
		openConsole = true;
		OpenConsole();
		std::cout << "Opened world";
	}
	


	_minityEngine->Update(_deltaTime, _scrInfo_);
}

static void UNITY_INTERFACE_API
OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	switch (eventType)
	{
	case kUnityGfxDeviceEventInitialize:
	{
		s_RendererType = s_Graphics->GetRenderer();

		//This engine only runs in OpenGL (for now), unity has to be using the OpenGL backend to not crash.
		if (s_RendererType == kUnityGfxRendererOpenGLCore)
		{
			
			_minityEngine = new MinityEngine();
			//RedirectIOToConsole();
		}

		//TODO: user initialization code
		break;
	}
	case kUnityGfxDeviceEventShutdown:
	{
		s_RendererType = kUnityGfxRendererNull;

		delete _minityEngine;

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