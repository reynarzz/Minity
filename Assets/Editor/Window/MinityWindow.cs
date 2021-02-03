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
            _hierarchyRect.width = 230;
            _sceneViewRect.width = 700;
        }

        private void OnDestroy()
        {
            _isOpened = false;
        }

        private void Update()
        {
        }

        private Rect _hierarchyRect;
        private Rect _sceneViewRect;

        private void OnGUI()
        {

            _deltaTime = (float)(_stopWatch.Elapsed.TotalMilliseconds / 1000.0f - _totalSecs);
            _totalSecs = _stopWatch.Elapsed.TotalMilliseconds / 1000.0f;


            EditorGUI.DrawRect(new Rect(0, 0, Screen.width, Screen.height), Color.black * 0.5f);


            //_hierarchyRect.width = ResizeControl(new Vector2(_hierarchyRect.x, _hierarchyRect.y), _hierarchyRect.width);

            var playModeRect = new Rect(0, 0, Screen.width, 30);

            var windowsOffset = 2;
            _hierarchyRect.height = Screen.height;
            _hierarchyRect.y = playModeRect.height;

            _sceneViewRect = new Rect(_hierarchyRect.width + windowsOffset, playModeRect.height + windowsOffset, _sceneViewRect.width, Screen.height - 300 + playModeRect.height);
            _sceneViewRect.width = ResizeControl(new Vector2(_sceneViewRect.x, playModeRect.height), _sceneViewRect.width);

            var inspectorXPos = (_sceneViewRect.x + _sceneViewRect.width) + windowsOffset;
            var inspectorRect = new Rect(inspectorXPos, playModeRect.height, Screen.width - inspectorXPos, Screen.height);

            BeginWindows();

            // Hierarchy window
            EditorGUI.DrawRect(_hierarchyRect, new Color(0.14f, 0.14f, 0.14f, 1));
            GUI.SetNextControlName("Hierarchy");
            GUI.Window(0, _hierarchyRect, (id) => HierarchyView(id, ref _hierarchyRect), "", GUIStyle.none);

            // Toolbar info
            EditorGUI.DrawRect(playModeRect, new Color(0.1f, 0.1f, 0.1f, 1));
            GUI.SetNextControlName("PlayMode");
            GUI.Window(1, playModeRect, (id) => PlayModeControls(id, playModeRect), "", GUIStyle.none);

            // Scene window
            EditorGUI.DrawRect(_sceneViewRect, Color.black * 0.4f);
            GUI.SetNextControlName("SceneView");
            GUI.Window(2, _sceneViewRect, (id) => SceneWindow(id, _sceneViewRect), "", GUIStyle.none);

            // Inspector window
            EditorGUI.DrawRect(inspectorRect, new Color(0.14f, 0.14f, 0.14f, 1));
            GUI.SetNextControlName("Inspector");
            GUI.Window(3, inspectorRect, (id) => InspectorView(id, inspectorRect), "", GUIStyle.none);

            EndWindows();

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

        private class HierarchyObj
        {
            private const float _hSpacing = 14;
            private const float _vSpacing = 1;

            public int Elements => _children.Count;
            private List<HierarchyObj> _children;
            public string Name { get; set; }

            private readonly Rect _defaultRect;

            public Rect Rect { get; set; }

            private bool _foldOut = false;
            private int _index;

            public bool ShowContent
            {
                get => _foldOut;

                set
                {
                    if (_foldOut != value)
                    {
                        OnFoldedOut(_index);
                    }

                    _foldOut = value;
                }
            }

            public event Action<int> OnFoldedOut;

            public HierarchyObj(int index, string name, Rect rect)
            {
                _index = index;
                _defaultRect = rect;
                Rect = _defaultRect;

                _children = new List<HierarchyObj>();

                if (string.IsNullOrEmpty(name))
                {
                    name = "EmptyObj";
                }
                Name = name;
            }

            public void CreateChild(string name)
            {
                var child = new HierarchyObj(_children.Count, name, new Rect(Rect.x + _hSpacing, GetChildrensHeightSum(), 100, 20));
                child.Name = name;

                _children.Add(child);
            }

            public float GetChildrensHeightSum()
            {
                var sum = 0f;

                for (int i = 0; i < _children.Count; i++)
                {
                    sum += _children[i].Rect.height + _vSpacing;
                }

                return sum + Rect.height + _vSpacing + Rect.y;
            }

            public void RecalculateChildren()
            {
                for (int i = 0; i < _children.Count; i++)
                {
                    _children[i].Rect = new Rect(_children[i].Rect.x, _children[i].Rect.height * i + (Rect.y + Rect.height), _children[i].Rect.width, _children[i].Rect.height);
                }
            }

            public HierarchyObj GetChild(int index)
            {
                return _children.ElementAtOrDefault(index);
            }

            public void RestartRect()
            {
                Rect = _defaultRect;
                RecalculateChildren();
            }
        }

        private class HierarchyLayout
        {
            private const float _hSpacing = 15;
            private const float _vSpacing = 3;

            private readonly List<HierarchyObj> _hierarchyObjs;
            public List<HierarchyObj> HierarchyObjs => _hierarchyObjs;

            public HierarchyLayout()
            {
                _hierarchyObjs = new List<HierarchyObj>();
            }

            public void AddObj(string name)
            {
                var child = new HierarchyObj(_hierarchyObjs.Count, name, new Rect(_hSpacing, GetChildrensHeightSum(), 100, 20));
                child.OnFoldedOut += RecalculateLayout;

                _hierarchyObjs.Add(child);
            }

            public HierarchyObj GetObj(int index)
            {
                return _hierarchyObjs.ElementAtOrDefault(index);
            }

            public float GetChildrensHeightSum()
            {
                var sum = 0f;

                for (int i = 0; i < _hierarchyObjs.Count; i++)
                {
                    var childHeight = 0f;

                    var parent = _hierarchyObjs[i];

                    if (parent.ShowContent)
                    {
                        childHeight = parent.GetChildrensHeightSum();
                    }

                    sum += parent.Rect.height + _vSpacing + childHeight;
                }

                return sum;
            }
             
            private void RecalculateLayout(int index)
            {
                for (int i = index; i < _hierarchyObjs.Count; i++)
                {
                    if (i > 0)
                    {
                        var prevParent = _hierarchyObjs[i - 1];

                        var parent = _hierarchyObjs[i];

                        if (prevParent.ShowContent)
                        {
                            parent.Rect = new Rect(parent.Rect.x, prevParent.GetChildrensHeightSum(), parent.Rect.width, parent.Rect.height);
                            parent.RecalculateChildren();

                            Debug.Log("Show " + (i - 1));
                        }
                        else
                        {
                            parent.RestartRect();
                            Debug.Log(parent.Name +  ", Hide " + (i - 1));

                            //parent.RecalculateChildren();
                        }
                    }
                   
                    //else if (!parent.FoldOut) 
                    //{

                    //}
                }
            }
        }

        private HierarchyLayout _layout;

        private void HierarchyView(int id, ref Rect hierarchyRect)
        {
            if (_layout == null)
            {
                _layout = new HierarchyLayout();

                _layout.AddObj("ParentObj");
                _layout.AddObj("Second");
                _layout.AddObj("Another");

                var parent = _layout.GetObj(0);
                var parent2 = _layout.GetObj(1);
                var parent3 = _layout.GetObj(2);

                parent.CreateChild("Windmil");
                parent.CreateChild("Windmil2");
                parent.CreateChild("Windmil3");
                parent.CreateChild("Windmil4");

                parent2.CreateChild("House1");
                parent2.CreateChild("House2");
                parent2.CreateChild("House3");

                parent3.CreateChild("Door1");
                parent3.CreateChild("Door2");
                parent3.CreateChild("Door3");

            }

            DrawLayout();
        }

        private void DrawLayout()
        {
            for (int i = 0; i < _layout.HierarchyObjs.Count; i++)
            {
                GameObjectUI(_layout.HierarchyObjs[i]);

                if (_layout.HierarchyObjs[i].ShowContent)
                {
                    for (int j = 0; j < _layout.HierarchyObjs[i].Elements; j++)
                    {
                        GameObjectUI(_layout.HierarchyObjs[i].GetChild(j));
                    }
                }
            }
        }

        private void GameObjectUI(HierarchyObj obj)
        {

            if (obj.Elements > 0)
            {
                obj.ShowContent = EditorGUI.Foldout(obj.Rect, obj.ShowContent, obj.Name);
            }
            else
            {
                EditorGUI.LabelField(obj.Rect, obj.Name);
            }
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

            Event current = Event.current;

            windowRect.x = 0;
            windowRect.y = 0;

            if (!_canDragLine && windowRect.Contains(current.mousePosition))
                MinityScene.SetMouseData(current.mousePosition.x, current.mousePosition.y, current.delta.x, current.delta.y);

            //EditorGUI.DrawRect(windowRect, Color.red);

            // Issue Draw call.
            GL.Viewport(rect);
            GL.IssuePluginEvent(MinityScene.Run(), 0);
            GL.Clear(true, false, default);

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

        private bool _canDragLine;

        private float ResizeControl(Vector2 pos, float width)
        {
            //if(_lineRect == default)
            var lineRect = new Rect(pos.x + width, pos.y, 2, Screen.height);

            EditorGUI.DrawRect(lineRect, Color.black);

            Event current = Event.current;

            //if (current.type == EventType.muse)
            {
                // Debug.Log("Mouse down");

                var testRect = new Rect(lineRect);

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
                    //Debug.Log("Above");
                    DragAndDrop.visualMode = DragAndDropVisualMode.Copy;

                    var minSpace = 50;
                    lineRect.x = Mathf.Clamp(current.mousePosition.x, pos.x + lineRect.width + minSpace, Screen.width - lineRect.width - minSpace);
                }
            }

            return lineRect.x - pos.x;
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
