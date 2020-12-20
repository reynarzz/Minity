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
    [CustomEditor(typeof(MinityViewport))]
    public class MinityViewportEditor : Editor
    {
        private MinityViewport _minity;

        private void OnEnable()
        {
            _minity = (target as MinityViewport);

            MinityViewport.SetScreenValues(Screen.width, 200f, Screen.width / 200f);
            //MinityViewport.SetPos(_minity.transform.position.x, _minity.transform.position.y, _minity.transform.position.z);
        }

        public override void OnInspectorGUI()
        {
            //Rect rect = GUILayoutUtility.GetRect(10, 1000, 200, 200);

            Rect rect = GUILayoutUtility.GetRect(Screen.width, 200);
            //--MinityViewport.SetPos(_minity.transform.position.x, _minity.transform.position.y, _minity.transform.position.z);

            MinityViewport.SetScreenValues(Screen.width, 200f, Screen.width / 200f);

            if (Event.current.type == EventType.Repaint)
            {
                GUI.BeginClip(rect);
                rect.y = rect.height / 2 - 20;
                GL.Viewport(rect);

                GL.IssuePluginEvent(MinityViewport.Run(), 0);

                GUI.EndClip();
            }

            GUILayout.Space(5);
            if (GUILayout.Button("Open In Window"))
            {
                MinityWindow.Open();
            }

            Event current = Event.current;

            MinityViewport.SetMouseData(current.mousePosition.x, current.mousePosition.y, current.delta.x, current.delta.y);
            Debug.Log(current.delta);

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
