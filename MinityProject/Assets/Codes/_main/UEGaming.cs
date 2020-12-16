using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

/// <summary>
/// Unity Editor Gaming Entry point.
/// </summary>
public class UEGaming : MonoBehaviour
{
    public event Action<float> OnUpdate;
    public event Action OnStart;

    private void Start()
    {
        //OnStart.Invoke();
    }

    private void Update()
    {
        //OnUpdate.Invoke(Time.deltaTime);
    }
}
