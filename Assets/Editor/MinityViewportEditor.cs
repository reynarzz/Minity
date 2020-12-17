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

            MinityViewport.SetScreenValues(Screen.width, Screen.height, Screen.width / Screen.height);
        }

        public override void OnInspectorGUI()
        {
            //Rect rect = GUILayoutUtility.GetRect(10, 1000, 200, 200);

            Rect rect = GUILayoutUtility.GetRect(Screen.width, Screen.height);


            //Debug.Log((Screen.width, Screen.height));

            if (Event.current.type == EventType.Repaint)
            {
                GUI.BeginClip(rect);
                GL.Viewport(new Rect(0, 0, Screen.width, Screen.height));

                GL.IssuePluginEvent(MinityViewport.Run(), 0);

                GUI.EndClip();
            }

            Repaint();
        }
    }
}
