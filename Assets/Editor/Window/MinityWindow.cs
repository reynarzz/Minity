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

            if (current.alt)
            {
                MinityViewport.SetKeyDow(2, 1);
            }
            else
            {
                MinityViewport.SetKeyUp(2);
            }

            if (current.isMouse) 
            {
                if (current.type == EventType.MouseDown)
                {
                    //Debug.Log("left");
                    MinityViewport.SetKeyDow(1, 1);
                }

                if (current.type == EventType.MouseUp)
                {
                    MinityViewport.SetKeyUp(1);
                }
            }

            if (current.type == EventType.KeyDown)
            {
                
                if (current.keyCode == KeyCode.A)
                {
                    MinityViewport.SetKeyDow(0, 2);
                }
                else if (current.keyCode == KeyCode.D) 
                {
                    MinityViewport.SetKeyDow(0, 4);
                }

                if (current.keyCode == KeyCode.W)
                {
                    MinityViewport.SetKeyDow(0, 1);
                }
                else if (current.keyCode == KeyCode.S)
                {
                    MinityViewport.SetKeyDow(0, 3);
                }

                if (current.keyCode == KeyCode.Q)
                {
                    MinityViewport.SetKeyDow(0, 5);
                }
                else if (current.keyCode == KeyCode.E)
                {
                    MinityViewport.SetKeyDow(0, 6);
                }

            }
            else if (current.type == EventType.KeyUp)
            {
                    MinityViewport.SetKeyUp(0);

                //if (current.keyCode == KeyCode.A)
                //{
                //    MinityViewport.SetKeyUp(0);

                //    Debug.Log("Release A");
                //}
                //else if (current.keyCode == KeyCode.D)
                //{
                //    MinityViewport.SetKeyUp(0);

                //    Debug.Log("Release D");
                //}
            }

            Repaint();
        }
    }
}
