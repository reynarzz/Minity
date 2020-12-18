#pragma once
#include "pch.h"
#include <stdio.h>
#include <string>
#include <stdio.h>
#include <sstream>

#define DLLExport __declspec(dllexport)

extern "C"
{
    //Create a callback delegate
    typedef void(*FuncCallBack)(const char* message, int color, int size);
    static FuncCallBack callbackInstance = nullptr;
    DLLExport void RegisterDebugCallback(FuncCallBack cb);
}

//Color Enum
enum class Color { Red, Green, Blue, Black, White, Yellow, Orange, Gray };

class  Debug
{
public:
    static void Log(const char* message, Color color = Color::Gray);
    static void Log(const std::string message, Color color = Color::Gray);
    static void Log(const int message, Color color = Color::Gray);
    static void Log(const char message, Color color = Color::Gray);
    static void Log(const float message, Color color = Color::Gray);
    static void Log(const double message, Color color = Color::Gray);
    static void Log(const bool message, Color color = Color::Gray);

private:
    static void send_log(const std::stringstream& ss, const Color& color);
};