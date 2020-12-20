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
            _window = GetWindow<MinityWindow>("Minity Editor");
        }

        private void Update()
        {

        }

        private void OnGUI()
        {
            MinityScene.SetScreenValues(Screen.width, Screen.height, (float)Screen.width / Screen.height);

            GL.IssuePluginEvent(MinityScene.Run(), 0);

            //Event current = Event.current;

            ////MinityViewport.SetMouseData(current.mousePosition.x, current.mousePosition.y, current.delta.x / 12, current.delta.y / 12);
            
            //if (current.type == EventType.ScrollWheel)
            //{

            //}

            //if (current.alt)
            //{
            //    MinityScene.SetKeyDow(2, 1);
            //}
            //else
            //{
            //    MinityScene.SetKeyUp(2);
            //}

            //if (current.isMouse) 
            //{
            //    if (current.type == EventType.MouseDown)
            //    {
            //        //Debug.Log("left");
            //        MinityScene.SetKeyDow(1, 1);
            //    }

            //    if (current.type == EventType.MouseUp)
            //    {
            //        MinityScene.SetKeyUp(1);
            //    }
            //}

            //if (current.type == EventType.KeyDown)
            //{
                
            //    if (current.keyCode == KeyCode.A)
            //    {
            //        MinityScene.SetKeyDow(0, 2);
            //    }
            //    else if (current.keyCode == KeyCode.D) 
            //    {
            //        MinityScene.SetKeyDow(0, 4);
            //    }

            //    if (current.keyCode == KeyCode.W)
            //    {
            //        MinityScene.SetKeyDow(0, 1);
            //    }
            //    else if (current.keyCode == KeyCode.S)
            //    {
            //        MinityScene.SetKeyDow(0, 3);
            //    }

            //    if (current.keyCode == KeyCode.Q)
            //    {
            //        MinityScene.SetKeyDow(0, 5);
            //    }
            //    else if (current.keyCode == KeyCode.E)
            //    {
            //        MinityScene.SetKeyDow(0, 6);
            //    }

            //}
            //else if (current.type == EventType.KeyUp)
            //{
            //        MinityScene.SetKeyUp(0);

            //    //if (current.keyCode == KeyCode.A)
            //    //{
            //    //    MinityViewport.SetKeyUp(0);

            //    //    Debug.Log("Release A");
            //    //}
            //    //else if (current.keyCode == KeyCode.D)
            //    //{
            //    //    MinityViewport.SetKeyUp(0);

            //    //    Debug.Log("Release D");
            //    //}
            //}

            Repaint();
        }
    }
}
