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
    [CustomEditor(typeof(MinityScene))]
    public class MinityViewportEditor : Editor
    {
        private MinityScene _minity;
        private System.Diagnostics.Stopwatch _stopWatch;
        private double _totalSecs;

        private void OnEnable()
        {
            _minity = (target as MinityScene);

            MinityScene.SetScreenValues(Screen.width, 230f, Screen.width / 230f);
            _stopWatch = new System.Diagnostics.Stopwatch();
            _stopWatch.Start();
            _totalSecs = _stopWatch.Elapsed.TotalSeconds / 1000.0f;
            //MinityViewport.SetPos(_minity.transform.position.x, _minity.transform.position.y, _minity.transform.position.z);
        }

        public override void OnInspectorGUI()
        {
            Rect rect = GUILayoutUtility.GetRect(Screen.width, 230);

            // MinityScene.SetPos(_minity.transform.position.x, _minity.transform.position.y, _minity.transform.position.z);

            var prevRect = GUILayoutUtility.GetLastRect();

            rect.width += rect.x - 3;
            rect.x = 3;
            EditorGUI.DrawRect(rect, Color.black * 0.5f);

            if (!MinityWindow.IsOpened)
            {
                var deltaTime = _stopWatch.Elapsed.TotalMilliseconds / 1000.0f - _totalSecs;
                _totalSecs = _stopWatch.Elapsed.TotalMilliseconds / 1000.0f;

                MinityScene.SetTime((float)_stopWatch.Elapsed.TotalMilliseconds, (float)deltaTime);

                MinityScene.SetScreenValues(rect.width, 230f, rect.width / 230f);
                MinityScene.SetMoveSpeed(10f);
                Debug.Log(rect.y);

                GUI.BeginClip(rect);

                GL.Viewport(rect);

                GL.IssuePluginEvent(MinityScene.Run(), 0);

                GUI.EndClip();

            }
            else
            {
                GUI.Label(new Rect(rect.x, rect.y, Screen.width, 20), "Opened in another window");
            }
            GUILayout.Space(5);

            if (GUILayout.Button("Open In Window"))
            {
                MinityWindow.Open();
            }

            if (!MinityWindow.IsOpened)
            {
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


            Repaint();
        }
    }
}
