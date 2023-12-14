using UnityEngine;

public class SatelliteController : MonoBehaviour
{
    private float _initY;
    private float _radius;
    private float _speed = 0.7f;
    // Start is called before the first frame update
    void Start()
    {
        var position = transform.position;
        _initY = position.y;
        _radius = Mathf.Sqrt(position.x * position.x + position.z * position.z);
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        var time = Time.time * _speed;
        var x = _radius * Mathf.Sin(time);
        var z = _radius * Mathf.Cos(time);

        // Set the new position
        var transform1 = transform;
        var position = new Vector3(x, _initY, z);
        transform1.position = position;

        // Rotate to face the center (0, 0, 0)
        var lookAtPosition = new Vector3(0f, _initY, 0f);
        transform.LookAt(lookAtPosition);
    }
}
