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
        }

        public override void OnInspectorGUI()
        {
            Rect rect = GUILayoutUtility.GetRect(10, 1000, 200, 200);

            if (Event.current.type == EventType.Repaint)
            {
                GUI.BeginClip(rect);
                GL.Viewport(new Rect(0, 75, 1000, 200));

                GL.IssuePluginEvent(MinityViewport.Run(), 0);

                GUI.EndClip();
            }

            Repaint();
        }
    }
}
