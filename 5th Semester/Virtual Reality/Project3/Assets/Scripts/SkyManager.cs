using System.Collections.Generic;
using UnityEngine;

public class SkyManager : MonoBehaviour
{
    public float speed = 0.5f;
    private static readonly int Rotation = Shader.PropertyToID("_Rotation");
    public List<Material> skyboxes = new List<Material>();
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        RenderSettings.skybox.SetFloat(Rotation, Time.time * speed);
    }

    public void SetSkybox(int index)
    {
        RenderSettings.skybox = skyboxes[index];
    }
}
