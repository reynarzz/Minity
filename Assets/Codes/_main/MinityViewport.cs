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

        [SerializeField] private Material _mat;

        private void Start()
        {
        }

        private void Update()
        {
            SetTime(Time.time, Time.deltaTime);
        }
    }
}