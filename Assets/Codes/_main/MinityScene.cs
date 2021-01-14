//MIT License

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
using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
/// <summary>
/// Unity Editor Gaming Entry point.
/// </summary>
namespace MinityEngine
{
    public class MinityScene : MonoBehaviour
    {
        private const string MinityPluginName = "MinityPlugin";

        [DllImport(MinityPluginName)]
        public static extern IntPtr Run();

        [DllImport(MinityPluginName)]
        public static extern void SetTime(float time, float deltaTime);

        [DllImport(MinityPluginName)]
        public static extern void SetScreenValues(int width, int height, float aspect);
         
        [SerializeField] private Material _mat;

        //[DllImport(MinityPluginName)]
        //public static extern void SetPos(float x, float y, float z);

        [DllImport(MinityPluginName)]
        public static extern void SetKeyDow(int keyType, int key);

        [DllImport(MinityPluginName)]
        public static extern void SetKeyUp(int keyType);

        [DllImport(MinityPluginName)]
        public static extern void SetMouseData(float xPos, float yPos, float deltaX, float deltaY);

        [DllImport(MinityPluginName)]
        public static extern void SetMoveSpeed(float speed);
    }
}