using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using UnityEditor;

namespace MinityEngine
{
    public class MinityWindow : EditorWindow
    {
        private static EditorWindow _window;

        [MenuItem("Window/Minity Engine")]
        public static void Open() 
        {
            _window = GetWindow<MinityWindow>("Minity Engine");
        }

        private void Update()
        {
            
        }

        private void OnGUI()
        {
            MinityViewport.SetScreenValues(Screen.width, Screen.height, (float)Screen.width / (float)Screen.height);
            GL.IssuePluginEvent(MinityViewport.Run(), 0);

            Repaint();
        }
    }
}
