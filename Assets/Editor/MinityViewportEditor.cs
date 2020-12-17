﻿using System;
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
            MinityViewport.SetPos(_minity.transform.position.x, _minity.transform.position.y, _minity.transform.position.z);
        }

        public override void OnInspectorGUI()
        {
            //Rect rect = GUILayoutUtility.GetRect(10, 1000, 200, 200);

            Rect rect = GUILayoutUtility.GetRect(Screen.width, 200);
            MinityViewport.SetPos(_minity.transform.position.x, _minity.transform.position.y, _minity.transform.position.z);

            MinityViewport.SetScreenValues(Screen.width, 200f, Screen.width / 200f);

            //Debug.Log((Screen.width, Screen.height));

            if (Event.current.type == EventType.Repaint)
            {
                GUI.BeginClip(rect);
                rect.y = 440;
                GL.Viewport(rect);
                
                GL.IssuePluginEvent(MinityViewport.Run(), 0);

                GUI.EndClip();
            }

            Repaint();
        }
    }
}
