using JetBrains.Annotations;
using UnityEngine;

public class RobotLegScript : MonoBehaviour
{
    public float dir = 1.0f;
    public float maxRotation = 20.0f;
    public Rigidbody robot;
    
    private float _angle;
    private float _velocity = 35.0f;
    private bool _containsRobot;


    // Start is called before the first frame update
    void Start()
    {
        _containsRobot = robot != null;
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

        if (_angle > 0)
        {
            transform.Rotate(Vector3.right, deltaAngle);
            if (!_containsRobot) return;
            var forwardMovement = -robot.transform.forward * (Mathf.Pow(_angle, 0.2f) * 1.5f * dt);
            robot.MovePosition(robot.position + forwardMovement);
        }
        else
        {
            transform.Rotate(Vector3.right, deltaAngle / 2);
        }
    }
}
