using UnityEngine;

public class RobotHeadMovement : MonoBehaviour
{
    public float maxRotation = 15.0f;
    private float _angle;
    private float _velocity = 20.0f;
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        var dt = Time.deltaTime; //seconds
        var deltaAngle = _velocity * dt;
        if (Mathf.Abs(_angle + deltaAngle) > maxRotation)
        {
            _velocity *= -1.0f;
            deltaAngle *= -1.0f;
        }
        _angle += deltaAngle;


        transform.Rotate(Vector3.right, deltaAngle);

    }
}
