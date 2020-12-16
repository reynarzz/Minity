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
        private static extern IntPtr Run();

        private Material _mat;

        private void Start()
        {
            Debug.Log("Called 0");

            _command = new CommandBuffer();
            _command.name = MinityPluginName;

            Camera.main.AddCommandBuffer(CameraEvent.AfterGBuffer, _command);
            //print(ReturnValue());
            Debug.Log("Called 1");
        }

        private void Update()
        {
            //_command.IssuePluginEvent(Run(), 0);
        }

        private void OnRenderObject()
        {
            if (_mat == null)
                _mat = new Material(Canvas.GetDefaultCanvasMaterial());

            //GL.IssuePluginEvent(GlVert(0, 0, 0), 0);
            // GL.IssuePluginEvent(GlVert(100, 0, 0), 0);

            _mat.SetPass(0);
            //GL.PushMatrix();
            //// Set transformation matrix for drawing to
            //// match our transform
            //GL.MultMatrix(transform.localToWorldMatrix);

            //GL.Begin(GL.LINES);
            //GL.Color(Color.white);
            //// GlVert(0, 0, 0);
            //// GlVert(100, 0, 0);
            ////GL.Vertex3(0,0,0);
            ////GL.Vertex3(100,0,0);


            //GL.End();
            //GL.PopMatrix();

            GL.IssuePluginEvent(Run(), 1);
            _command.IssuePluginEvent(Run(), 0);

        }
    }
}
