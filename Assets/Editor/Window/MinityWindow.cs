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
        private float _deltaTime;
        private double _totalSecs;

        private static bool _isOpened;
        public static bool IsOpened => _isOpened;

        [MenuItem("Window/Minity")]
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
            _deltaTime = (float)(_stopWatch.Elapsed.TotalMilliseconds / 1000.0f - _totalSecs);
            _totalSecs = _stopWatch.Elapsed.TotalMilliseconds / 1000.0f;


            var windowsOffset = 2;

            var hierarchyRect = new Rect(0, 0, 270, Screen.height);
            var playModeRect = new Rect(hierarchyRect.width + windowsOffset, 0, 750, 30);
            var sceneViewRect = new Rect(hierarchyRect.width + windowsOffset, playModeRect.height, 750, Screen.height - 300 + playModeRect.height);
            var inspectorXPos = (sceneViewRect.x + sceneViewRect.width) + windowsOffset;

            var inspectorRect = new Rect(inspectorXPos, 0, Screen.width - inspectorXPos, Screen.height);

            BeginWindows();

            // Hierarchy window
            EditorGUI.DrawRect(hierarchyRect, Color.black * 0.3f);
            GUI.SetNextControlName("Hierarchy");
            GUI.Window(0, hierarchyRect, (id)=> HierarchyView(id, ref hierarchyRect), "", GUIStyle.none);

            // Scene info
            EditorGUI.DrawRect(playModeRect, Color.black * 0.3f);
            GUI.SetNextControlName("PlayMode");
            GUI.Window(1, playModeRect, (id) => PlayModeControls(id, playModeRect), "", GUIStyle.none);

            // Scene window
            EditorGUI.DrawRect(sceneViewRect, Color.black * 0.4f);
            GUI.SetNextControlName("SceneView");
            GUI.Window(2, sceneViewRect, (id) => SceneWindow(id, sceneViewRect), "", GUIStyle.none);

            // Inspector window
            EditorGUI.DrawRect(inspectorRect, Color.black * 0.3f);
            GUI.SetNextControlName("Inspector");
            GUI.Window(3, inspectorRect, (id) => InspectorView(id, inspectorRect), "", GUIStyle.none);

            EndWindows();

            ResizeControl(new Vector2(hierarchyRect.x, hierarchyRect.y), hierarchyRect.width);
            var current = Event.current;

            if (current.type == EventType.MouseDown && GUIUtility.hotControl == 0)
            {
               // GUI.FocusControl("SceneView");
            }

            Repaint();
        }

        private void ObjectNameControl(ref string name)
        {
            GUILayout.BeginVertical(EditorStyles.helpBox);

            GUILayout.BeginHorizontal();
            EditorGUILayout.Toggle(true, GUILayout.Width(20));
            name = EditorGUILayout.TextField(name);
            GUILayout.EndHorizontal();
            GUILayout.EndVertical();
        }

        private bool _transformFoldout = true;
        private void TransformControl(ref Matrix4x4 model)
        {
            var position = model.GetColumn(3);
            var rotation = Quaternion.identity; //model.rotation;
            var scale = default(Vector3);

            GUI.SetNextControlName("Transform");

            GUILayout.BeginVertical(EditorStyles.helpBox);
            GUILayout.Space(2);
            if (_transformFoldout = EditorGUILayout.Foldout(_transformFoldout, "Model Transform"))
            {
                var labelSpacing = 60;

                GUILayout.Space(2);
                GUILayout.BeginHorizontal();
                GUILayout.Label("Position", GUILayout.Width(labelSpacing));
                position = EditorGUILayout.Vector3Field("", position);
                GUILayout.EndHorizontal();

                GUILayout.Space(2);
                GUILayout.BeginHorizontal();
                GUILayout.Label("Rotation", GUILayout.Width(labelSpacing));
                rotation = Quaternion.Euler(EditorGUILayout.Vector3Field("", rotation.eulerAngles));
                GUILayout.EndHorizontal();

                GUILayout.Space(2);
                GUILayout.BeginHorizontal();
                GUILayout.Label("Scale", GUILayout.Width(labelSpacing));
                scale = EditorGUILayout.Vector3Field("", scale);
                GUILayout.EndHorizontal();
                GUILayout.Space(5);
            }
            GUILayout.EndVertical();

            model.SetColumn(3, position);
        }

        private void HierarchyView(int id, ref Rect hierarchyRect)
        {
            ResizeControl(new Vector2(hierarchyRect.x, hierarchyRect.y), hierarchyRect.width);
        }

        private void PlayModeControls(int id, Rect rect)
        {
            var buttonsWidth = 45;
            var buttons = 3;
            var spacing = 3;

            var areaWidth = buttons * buttonsWidth + spacing * buttons;

            GUILayout.BeginArea(new Rect(rect.width / 2 - areaWidth / 2, 20 / 4, areaWidth, 20));
            GUILayout.BeginHorizontal();
            GUILayout.Button(">", GUILayout.Width(buttonsWidth));
            GUILayout.Button("||", GUILayout.Width(buttonsWidth));
            GUILayout.Button(">|", GUILayout.Width(buttonsWidth));
            GUILayout.EndHorizontal();
            GUILayout.EndArea();
        }

        private void SceneWindow(int id, Rect windowRect)
        {
            var windowVerticalOffset = 20;

            Rect rect = new Rect(windowRect.x, Screen.height - windowRect.height - windowRect.y - windowVerticalOffset, windowRect.width, windowRect.height);

           
            MinityScene.SetTime((float)_stopWatch.Elapsed.TotalMilliseconds, (float)_deltaTime);

            MinityScene.SetScreenValues((int)rect.width, (int)rect.height, rect.width / rect.height);

            MinityScene.SetMoveSpeed(50f);

            // Issue Draw call.
            GL.Viewport(rect);
            GL.IssuePluginEvent(MinityScene.Run(), 0);
            GL.Clear(true, false, default);

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

        private Matrix4x4 modelM = Matrix4x4.identity;
        private string _objName = "Entity";

        private Rect _lineRect;
        private bool _canDragLine;

        private float ResizeControl(Vector2 pos, float width) 
        {
            if(_lineRect == default)
            _lineRect = new Rect(pos.x + width, pos.y, 2, Screen.height);

            EditorGUI.DrawRect(_lineRect, Color.black);

            Event current = Event.current;

            //if (current.type == EventType.muse)
            {
                // Debug.Log("Mouse down");

                var testRect = new Rect(_lineRect);

                testRect.x -= 7;
                testRect.width += 14;

                if (current.type == EventType.MouseDown && testRect.Contains(current.mousePosition))
                {
                    DragAndDrop.visualMode = DragAndDropVisualMode.Copy;

                    _canDragLine = true;
                }
                else if (current.type == EventType.MouseUp) 
                {
                    DragAndDrop.visualMode = DragAndDropVisualMode.None;

                    _canDragLine = false;
                }

                if (_canDragLine)
                {
                    Debug.Log("Above");
                    DragAndDrop.visualMode = DragAndDropVisualMode.Copy;

                    _lineRect.x = current.mousePosition.x;
                }
               


                //Event.current.Use();
                // DragAndDrop.visualMode = DragAndDropVisualMode.Rejected;
                // DragAndDrop.StartDrag("Drag");
                // Event.current.Use();

            }
            return width;
        }

        private void InspectorView(int id, Rect inspectorRect)
        {
            ObjectNameControl(ref _objName);
            TransformControl(ref modelM);


            GUILayout.Space(5);
            if (GUILayout.Button("New Component", GUILayout.Height(25)))
            {

            }
            return;
        }
    }
}
