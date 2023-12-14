using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RobotAntennaMovement : MonoBehaviour
{
    public Transform satellite;
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        var satellitePosition = satellite.position;
        transform.LookAt(new Vector3(satellitePosition.x, satellitePosition.y, satellitePosition.z));
    }
}
