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
    public class MinityScene : MonoBehaviour
    {
        private const string MinityPluginName = "MinityPlugin";

        [DllImport(MinityPluginName)]
        public static extern IntPtr Run();

        [DllImport(MinityPluginName)]
        public static extern void SetTime(float time, float deltaTime);

        [DllImport(MinityPluginName)]
        public static extern void SetScreenValues(float width, float height, float aspect);

        [SerializeField] private Material _mat;

        private bool _canMove = false;

        //[DllImport(MinityPluginName)]
        //public static extern void SetPos(float x, float y, float z);

        [DllImport(MinityPluginName)]
        public static extern void SetKeyDow(int keyType, int key);

        [DllImport(MinityPluginName)]
        public static extern void SetKeyUp(int keyType);

        [DllImport(MinityPluginName)]
        public static extern void SetMouseData(float xPos, float yPos, float deltaX, float deltaY);

        private void Start()
        {
            //transform.forward
            _prevPos = Input.mousePosition;
        }

        private Vector3 _prevPos;
        private Vector3 _prevDelta;

        private void Update()
        {
            SetTime(Time.time, Time.deltaTime);

            var delta = Input.mousePosition - _prevPos;

            _prevPos = Input.mousePosition;

            if (Input.GetKeyDown(KeyCode.A))
            {
                SetKeyDow(0, 2);
            }
            else if (Input.GetKeyUp(KeyCode.A))
            {
                SetKeyUp(0);
            }

            if (Input.GetKeyDown(KeyCode.Space))
            {
                _canMove = !_canMove;
            }
            
            if (Input.GetKeyDown(KeyCode.A))
            {
                MinityScene.SetKeyDow(0, 2);
            }
            else if (Input.GetKeyDown(KeyCode.D))
            {
                MinityScene.SetKeyDow(0, 4);
            }

            if (Input.GetKeyDown(KeyCode.W))
            {
                MinityScene.SetKeyDow(0, 1);
            }
            else if (Input.GetKeyDown(KeyCode.S))
            {
                MinityScene.SetKeyDow(0, 3);
            }

            if (Input.GetKeyDown(KeyCode.Q))
            {
                MinityScene.SetKeyDow(0, 5);
            }
            else if (Input.GetKeyDown(KeyCode.E))
            {
                MinityScene.SetKeyDow(0, 6);
            }


            if (Input.GetMouseButtonDown(0))
            {
                MinityScene.SetKeyDow(1, 1);
            }
            else if (Input.GetMouseButtonUp(0))
            {
                MinityScene.SetKeyUp(1);
            }

            if (!Input.anyKey)
            {
                MinityScene.SetKeyUp(0);
            }

            _prevDelta = Vector3.Lerp(_prevDelta, delta, Time.deltaTime * 18);

            if(_canMove)
            MinityScene.SetMouseData(Input.mousePosition.x, Input.mousePosition.y, _prevDelta.x, -_prevDelta.y);

        }
    }
}