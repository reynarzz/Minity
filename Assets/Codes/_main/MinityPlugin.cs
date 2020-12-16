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
        public static extern IntPtr Run();

        [DllImport(MinityPluginName)]
        public static extern void SetTime(float time, float deltaTime);

        [SerializeField] private Material _mat;

        private void Start()
        {
            Debug.Log("Called 0");

            _command = new CommandBuffer();
            _command.name = MinityPluginName;

            Camera.main.AddCommandBuffer(CameraEvent.AfterGBuffer, _command);
            //print(ReturnValue());
            Debug.Log("Called 1");
            // StartCoroutine(Call());
        }

        private IEnumerator Call()
        {
            while (true)
            {
                yield return new WaitForEndOfFrame();


                //_mat.SetPass(0);


                //GL.IssuePluginEvent(Run(), 1);
                //Debug.Log("Called");
            }
        }

        private void Update()
        {
            SetTime(Time.time, Time.deltaTime);
        }

        private void OnRenderObject()
        {
            //_mat.SetPass(0);
            //_command.IssuePluginEvent(Run(), 0);

            //GL.IssuePluginEvent(Run(), 1);
        }


        private void OnPostRender()
        {

            //GL.IssuePluginEvent(Run(), 1);

        }
    }
}
