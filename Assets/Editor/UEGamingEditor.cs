using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UnityEngine;
using UnityEditor;
using System.Diagnostics;

namespace UEGaming_
{
    [CustomEditor(typeof(UEGaming))]
    public class UEGamingEditor : Editor
    {
        private UEGaming _ueGaming;
        private Material _mat;
        Stopwatch _clock;

        private float _elapseTime;
        private float _deltaTime;

        private List<Vector4> _plane;

        private void OnEnable()
        {
            _mat = new Material(Canvas.GetDefaultCanvasMaterial());

            _ueGaming = (target as UEGaming);
            _clock = new Stopwatch();
            _clock.Start();

            _plane = new List<Vector4>();
            CreatePlane();

        }

        public override void OnInspectorGUI()
        {
            _deltaTime = _clock.ElapsedMilliseconds;

            _elapseTime = _clock.ElapsedTicks;

            Rect rect = GUILayoutUtility.GetRect(10, 1000, 200, 200, EditorStyles.helpBox);

            if (Event.current.type == EventType.Repaint)
            {
                GUI.BeginClip(rect);
                GL.Flush();

                GL.PushMatrix();

                GL.Clear(true, false, Color.black);
                _mat.SetPass(0);

                GL.Begin(GL.LINES);

                GL.Color(Color.white);

                DrawPlane();

                GL.End();
                GUI.EndClip();
            }

            Repaint();
        }

        private void CreatePlane()
        {
            _plane.Clear();

            float spacing = 4;

            for (int x = 0; x < 5; x++)
            {
                var pos1 = new Vector4(x * 10 * spacing, 0, 0, 1);
                var pos2 = new Vector4(x * 10 * spacing, 10 * spacing * 4, 0, 1);

                _plane.Add(pos1);
                _plane.Add(pos2);  
            }

            for (int y = 0; y < 5; y++)
            {
                var pos1 = new Vector4( 0, y * 10 * spacing, 0, 1);
                var pos2 = new Vector4(10 * spacing * 4, y * 10 * spacing, 0, 1);

                _plane.Add(pos1);
                _plane.Add(pos2);
            }
        }

        private void DrawPlane() 
        {
            for (int i = 0; i < _plane.Count; i++)
            {
                var vertex = _plane[i];

                var pers = Matrix4x4.Perspective(60, 1000f/200f, 0.1f, 300);

                GL.Vertex(pers * vertex);
            }
        }
    }
}
