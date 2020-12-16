using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using UnityEngine.Rendering;

namespace MinityEngine
{
    public class MinityPlugin : MonoBehaviour
    {
        private const string MinityPluginName = "MinityPlugin";
        private CommandBuffer _command;

        [DllImport(MinityPluginName)]
        private static extern IntPtr GetEventFunction();

        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void DebugDelegate(string text);

        [DllImport(MinityPluginName)]
        private static extern int ReturnValue();

        [DllImport(MinityPluginName)]
        private static extern void GlVert(float x, float y, float z);

        static void CallBackFunction(string text) 
        {
            Debug.Log(text);
        }

        private void Start()
        {
            Debug.Log("Called 0");

            _command = new CommandBuffer();
            _command.name = MinityPluginName;

            Camera.main.AddCommandBuffer(CameraEvent.AfterGBuffer, _command);
            print(ReturnValue());
            Debug.Log("Called 1");
        }
         
        private void Update()
        {
            _command.IssuePluginEvent(GetEventFunction(), 0);
        }

        private void OnPreRender()
        {

            GlVert(0, 0, 0);
            GlVert(100, 0, 0);

            GL.IssuePluginEvent(GetEventFunction(), 1);
        }
    }
}
