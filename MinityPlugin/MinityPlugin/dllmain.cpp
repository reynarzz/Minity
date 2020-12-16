// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Unity_PluginAPI/IUnityGraphics.h"
#include "Unity_PluginAPI/IUnityEventQueue.h"

#include <GL/glew.h>

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

extern "C"
{
	static void UNITY_INTERFACE_API  OnRenderEvent(int eventID)
	{

	}

	void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* interfaces)
	{

	}

	void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
	{

	}

	int UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API ReturnValue()
	{
		return 24;
	}

	void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GlVert(float x, float y, float z)
	{
		glVertex3f(x, y, z);
	}

	UnityRenderingEvent UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API GetEventFunction()
	{
		return OnRenderEvent;
	}



}

