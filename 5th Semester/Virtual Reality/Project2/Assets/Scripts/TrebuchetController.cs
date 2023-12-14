using UnityEngine;

public class TrebuchetController : MonoBehaviour
{
    public Rigidbody weight;
    public GameObject rockConnector;
    public HingeJoint _hingeToDestroy;
    private bool _launched;
    public float limitX = 10f;
    private readonly float _speed = 5f;
    private float _orientation = 1f;

    // Start is called before the first frame update
    void Start()
    {
        _hingeToDestroy = rockConnector.GetComponent<HingeJoint>();
        _launched = false;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (Input.GetKey(KeyCode.Space) && !_launched)
        {
            // Starts the trebuchet
            weight.isKinematic = false;
            _launched = true;
            return;
        }

        if (Input.GetKey(KeyCode.X) && _launched)
        {
             // Launch the object
             Destroy(_hingeToDestroy);
        }
        
        var dt = Time.deltaTime;
        var position = transform.position;
        position.x += dt * _orientation * _speed;
        if (Mathf.Abs(position.x) > limitX)
        {
            _orientation *= -1f;
        }
        transform.position = position;
    }
}
