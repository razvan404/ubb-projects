using UnityEngine;


[RequireComponent(typeof(CharacterController))]
public class PlayerController : MonoBehaviour
{
    Vector3[] LEVELS_COORDS = { new(-66, 22, -315), new(-50, 12, -20), new(80, 28, 342), new(-100, 72, 740), new(-100, 3, 1210) };
    Vector3[] LEVELS_ROTATIONS = { new(0, 90, 0), new(0, 90, 0), new(0, -107, 0), new(0, 90, 0), new(0, 90, 0) };

    Vector3[] TOWER_EIFFEL_COORDS = { new(-34, 44, 1210), new(-10, 182, 1210) };

    private Vector3 FINAL_COORDS = new(100, 1, 1010);
    private Vector3 FINAL_ROTATION = new(0, -40, 0);

    public Camera playerCamera;
    public float walkSpeed = 6.0f;
    public float jumpPower = 7.0f;
    public float gravity = 10.0f;

    public float lookSpeed = 4.0f;
    public float lookXLimit = 45.0f;

    Vector3 moveDirection = Vector3.zero;
    float rotationX = 0;

    public bool canMove = true;
    CharacterController characterController;


    //Coins collection
    private int Coin = 0;

    // Number of coins for each level
    private int[] levelCoins = { 6, 5, 7, 12, 9, 1 };

    private int[] towerEiffelLevelsCoins = { 1, 5, 9 };


    private int currentLevel = 1;
    private int currentTowerLevel = 0;

    public SkyManager skyManager;


    public EndScript endScript;


    // Start is called before the first frame update
    void Start()
    {
        characterController = GetComponent<CharacterController>();
        Cursor.lockState = CursorLockMode.Locked;
        Cursor.visible = false;

        TeleportPlayerToLevel(1);
    }

    // Update is called once per frame
    void Update()
    {
        if (!canMove)
        { 
            return;
        }
        
        // Moving
        Vector3 forward = transform.TransformDirection(Vector3.forward);
        Vector3 right = transform.TransformDirection(Vector3.right);

        float currentSpeedX = walkSpeed * Input.GetAxis("Vertical");
        float currentSpeedY = walkSpeed * Input.GetAxis("Horizontal");
        float moveDirectionY = moveDirection.y;

        moveDirection = forward * currentSpeedX + right * currentSpeedY;

        // Jumping / Falling
        if (Input.GetButton("Jump") && characterController.isGrounded)
        {
            moveDirection.y = jumpPower;
        }
        else
        {
            moveDirection.y = moveDirectionY;
        }

        if (!characterController.isGrounded)
        {
            moveDirection.y -= gravity * Time.deltaTime;
        }

        // Rotation
        characterController.Move(moveDirection * Time.deltaTime);
        rotationX += -Input.GetAxis("Mouse Y") * lookSpeed;
        rotationX = Mathf.Clamp(rotationX, -lookXLimit, lookXLimit);
        playerCamera.transform.localRotation = Quaternion.Euler(rotationX, 0, 0);
        transform.rotation *= Quaternion.Euler(0, Input.GetAxis("Mouse X") * lookSpeed, 0);
    }

    private void FixedUpdate()
    {
        // Check if all coins for the current level are collected
        if (Coin >= levelCoins[currentLevel - 1])
        {
            // Check if there is a next level
            if (currentLevel < LEVELS_COORDS.Length)
            {
                TeleportPlayerToLevel(currentLevel + 1);
                Debug.Log("Player moved to Level " + currentLevel);
            }
            else
            {
                Coin = 0;
                Debug.Log("All levels completed!");
                EndSimulation();
            }
        }
        

        if (currentLevel == 5 && currentTowerLevel < 2 && Coin == towerEiffelLevelsCoins[currentTowerLevel])
        {
            TeleportPlayerToLevelEiffel(currentTowerLevel);
            if (currentTowerLevel == 2)
            {
                // When player reaches the top of the Eiffel Tower, move camera lower
                playerCamera.transform.localPosition = new Vector3(0, 0.6f, 0);
            }
        }
        
        // Teleport player to the certain level if key is pressed
        for (int i = 1; i <= LEVELS_COORDS.Length; ++i)
        {
            if (Input.GetKeyDown(KeyCode.Alpha0 + i))
            {
                TeleportPlayerToLevel(i);
            }
        }
    }

    void TeleportPlayerToLevel(int level)
    {
        var coords = LEVELS_COORDS[level - 1];
        var rotation = LEVELS_ROTATIONS[level - 1];
        transform.SetPositionAndRotation(coords, Quaternion.Euler(rotation));
        currentLevel = level;
        currentTowerLevel = 0;
        Coin = 0;
        skyManager.SetSkybox(level - 1);
    }

    void TeleportPlayerToLevelEiffel(int level)
    {
        var coords = TOWER_EIFFEL_COORDS[level];
        Vector3 rotation = new Vector3(0, 90, 0);
        transform.SetPositionAndRotation(coords, Quaternion.Euler(rotation));
        currentTowerLevel = level + 1;
    }

    private void OnTriggerEnter(Collider other)
    {
        if (!other.transform.CompareTag("Coin")) return;
        Coin++;
        Debug.Log($"Collected {Coin} coins!");
        Destroy(other.gameObject);
    }

    public void EndSimulation()
    {
        canMove = false;
        playerCamera.transform.SetPositionAndRotation(FINAL_COORDS, Quaternion.Euler(FINAL_ROTATION));
        endScript.Setup();
    }
}
