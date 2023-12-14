using UnityEngine;

public class RobotArmScript : MonoBehaviour
{
    public float dir = 1.0f;
    public float maxRotation = 30.0f;
    private float _angle;
    private float _velocity = 30.0f;
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        var dt = Time.deltaTime;
        var deltaAngle = _velocity * dt * dir;
        if (Mathf.Abs(_angle + deltaAngle) > maxRotation)
        {
            _velocity *= -1.0f;
            deltaAngle *= -1.0f;
        }
        _angle += deltaAngle;
        transform.Rotate(Vector3.right, deltaAngle);
    }
}
