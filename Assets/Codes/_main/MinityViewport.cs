using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Runtime.InteropServices;
/// <summary>
/// Unity Editor Gaming Entry point.
/// </summary>
namespace MinityEngine
{
    public class MinityViewport : MonoBehaviour
    {
        private const string MinityPluginName = "MinityPlugin";

        [DllImport(MinityPluginName)]
        public static extern IntPtr Run();

        [DllImport(MinityPluginName)]
        public static extern void SetTime(float time, float deltaTime);

        [DllImport(MinityPluginName)]
        public static extern void SetScreenValues(float width, float height, float aspect);

        [SerializeField] private Material _mat;

        [DllImport(MinityPluginName)]
        public static extern void SetPos(float x, float y, float z);

        [DllImport(MinityPluginName)]
        public static extern void SetKeyDow(int keyType, int key);

        [DllImport(MinityPluginName)]
        public static extern void SetKeyUp(int keyType);

        [DllImport(MinityPluginName)]
        public static extern void SetMouseData(float xPos, float yPos, float deltaX, float deltaY);

        private void Start()
        {
            //transform.forward
        }

        private void Update()
        {
            SetTime(Time.time, Time.deltaTime);

            if (Input.GetKeyDown(KeyCode.A))
            {
                SetKeyDow(0, 2);
            }
            else if (Input.GetKeyUp(KeyCode.A))
            {
                SetKeyUp(0);
            }
        }
    }
}