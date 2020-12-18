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
            MinityViewport.SetScreenValues(Screen.width, Screen.height, (float)Screen.width / Screen.height);
            GL.IssuePluginEvent(MinityViewport.Run(), 0);

            Event current = Event.current;
            
            MinityViewport.SetMouseData(current.mousePosition.x, current.mousePosition.y, current.delta.x / 12, current.delta.y / 12);

            if (current.type == EventType.ScrollWheel) 
            {
                
            }

            Debug.Log((float)current.delta.y);

            if (current.alt)
            {
                MinityViewport.SetKeyDow(2, 1);
            }
            else
            {
                MinityViewport.SetKeyUp(2);
            }

            Repaint();
        }
    }
}
