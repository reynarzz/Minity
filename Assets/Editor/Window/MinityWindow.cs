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
        private System.Diagnostics.Stopwatch _stopWatch;
        private double _totalSecs;

        private static bool _isOpened;
        public static bool IsOpened => _isOpened;

        public static void Open()
        {
            _window = GetWindow<MinityWindow>("Minity Engine");
            _isOpened = true;
        }

        private void OnEnable()
        {
            _isOpened = true;

            if (_stopWatch == null)
            {
                _stopWatch = new System.Diagnostics.Stopwatch();
                _stopWatch.Start();
                _totalSecs = _stopWatch.Elapsed.TotalSeconds / 1000.0f;
            }


        }

        private void OnDestroy()
        {
            _isOpened = false;
        }

        private void Update()
        {

        }

        private void OnGUI()
        {
            var hierarchyRect = new Rect(0, 0, 300, Screen.height);
            var sceneViewRect = new Rect(hierarchyRect.width, 0, 600, Screen.height - 300);

            var offset = 2;
            var inspectorRect = new Rect((sceneViewRect.x + sceneViewRect.width) + offset, 0, Screen.width - (sceneViewRect.x + sceneViewRect.width) + offset, Screen.height);

            BeginWindows();

            EditorGUI.DrawRect(hierarchyRect, Color.black * 0.3f);

            GUI.Window(0, hierarchyRect, HierarchyView, "");

            //  Rect rect = GUILayoutUtility.GetRect(100, 100);
            EditorGUI.DrawRect(sceneViewRect, Color.black * 0.5f);

            GUI.Window(1, sceneViewRect, (id) => SceneWindow(id, sceneViewRect), "", GUIStyle.none);


            EditorGUI.DrawRect(inspectorRect, Color.black * 0.3f);

            GUI.Window(2, inspectorRect, InspectorView, "", GUIStyle.none);


            EndWindows();

            Repaint();
        }

        private void HierarchyView(int id) 
        {
        
        }

        private void InspectorView(int id)
        {
            GUILayout.Button("Add Component");
            return;
        }

        private void SceneWindow(int id, Rect windowRect)
        {
            // GUI.DragWindow();

            Rect rect = new Rect(windowRect.x, Screen.height - windowRect.height, windowRect.width, windowRect.height);

            var deltaTime = _stopWatch.Elapsed.TotalMilliseconds / 1000.0f - _totalSecs;
            _totalSecs = _stopWatch.Elapsed.TotalMilliseconds / 1000.0f;

            MinityScene.SetTime((float)_stopWatch.Elapsed.TotalMilliseconds, (float)deltaTime);

            MinityScene.SetScreenValues((int)rect.width, (int)rect.height, rect.width / rect.height);

            MinityScene.SetMoveSpeed(10f);

            // Background.

            // if (Event.current.type == EventType.Repaint)
            {
                //rect.y = rect.height /;
                GUI.BeginClip(rect);
                rect.y -= 20;
                GL.Viewport(rect);

                GL.IssuePluginEvent(MinityScene.Run(), 0);
                GUI.EndClip();
            }

            Event current = Event.current;
            MinityScene.SetMouseData(current.mousePosition.x, current.mousePosition.y, current.delta.x, current.delta.y);

            if (current.type == EventType.ScrollWheel)
            {

            }

            if (current.alt)
            {
                MinityScene.SetKeyDow(2, 1);
            }
            else
            {
                MinityScene.SetKeyUp(2);
            }

            if (current.isMouse)
            {
                if (current.type == EventType.MouseDown)
                {
                    //Debug.Log("left");
                    MinityScene.SetKeyDow(1, 1);
                }

                if (current.type == EventType.MouseUp)
                {
                    MinityScene.SetKeyUp(1);
                }
            }


            if (current.type == EventType.KeyDown)
            {
                if (current.keyCode == KeyCode.A)
                {
                    MinityScene.SetKeyDow(0, 2);
                }
                else if (current.keyCode == KeyCode.D)
                {
                    MinityScene.SetKeyDow(0, 4);
                }

                if (current.keyCode == KeyCode.W)
                {
                    MinityScene.SetKeyDow(0, 1);
                }
                else if (current.keyCode == KeyCode.S)
                {
                    MinityScene.SetKeyDow(0, 3);
                }

                if (current.keyCode == KeyCode.Q)
                {
                    MinityScene.SetKeyDow(0, 5);
                }
                else if (current.keyCode == KeyCode.E)
                {
                    MinityScene.SetKeyDow(0, 6);
                }
            }
            else if (current.type == EventType.KeyUp)
            {
                MinityScene.SetKeyUp(0);

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
        }
    }
}
