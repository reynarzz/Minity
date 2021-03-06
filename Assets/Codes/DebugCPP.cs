﻿//MIT License

//Copyright (c) 2021 Reynardo Perez

//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this software and associated documentation files (the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions:

//The above copyright notice and this permission notice shall be included in all
//copies or substantial portions of the Software.

//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.

using AOT;
using System;
using System.Runtime.InteropServices;
using UnityEngine;

namespace MinityEngine
{
    [ExecuteAlways]
    public static class DebugCPP
    {
        public static Action<string> OnMessageSent;

        static DebugCPP()
        {
            RegisterDebugCallback(OnDebugCallback);

        }
        // Use this for initialization
        
        //------------------------------------------------------------------------------------------------
        [DllImport("MinityPlugin", CallingConvention = CallingConvention.Cdecl)]
        static extern void RegisterDebugCallback(debugCallback cb);

        //Create string param callback delegate
        delegate void debugCallback(IntPtr request, int color, int size);
        enum Color { red, green, blue, black, white, yellow, orange };
        [MonoPInvokeCallback(typeof(debugCallback))]

        static void OnDebugCallback(IntPtr request, int color, int size)
        {
            //Ptr to string
            string debug_string = Marshal.PtrToStringAnsi(request, size);

            //Add Specified Color
            debug_string =
                String.Format("{0}{1}{2}{3}{4}",
                "<color=",
                ((Color)color).ToString(),
                ">",
                debug_string,
                "</color>"
                );

            //OnMessageSent(debug_string);

            UnityEngine.Debug.Log(debug_string);
        }
    }
}
