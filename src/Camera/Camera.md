# Camera
## �ؿ�
1. [�e��](#�e��)
2. [��v��/�[��Ŷ�](#��v��/�[��Ŷ�)
3. [LookAt �x�}](#lookat-�x�})
4. [�ۥѲ���](#�ۥѲ���)
5. [���ʳt�׻PdeltaTime](#���ʳt�׻Pdeltatime)
6. [�������ʻP�ƹ���J](#�������ʻP�ƹ���J)
7. [�Y��](#�Y��)
8. [����](#����)

## �e��
- OpenGL�L��v�������A�i�z�L���ʳ��������C
- FPS������v���]�w�G��L�P�ƹ���J�A�ۭq��v�����O�C

## ��v��/�[��Ŷ�
- �[��x�}�N�@�ɮy���ܴ����[��y�СC
- �w�q��v���ݽT�w��m�B�[���V�B�k���V�q�B�W��V�q�C

### ��v����m
- �w�q��v����m�G
```cpp
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
```
- ��z�b���V�ù��~�C

### ��v����V
- �w�q��v����V�G
```cpp
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
```
- ��V�V�q���Vz�b����V�C

### �k�b
- �w�q�k�V�q�G
```cpp
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
```
- �W�V�q�P��V�V�q�e���A���o�k�V�q�C

### �W�b
- �w�q�W�V�q�G
```cpp
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
```
- �k�V�q�P��V�V�q�e���A���o�W�V�q�C

## LookAt �x�}
- �z�L3�Ӷb�P�����V�q�Ыدx�}�A�ഫ�y�ЪŶ��G
```cpp
glm::mat4 view;
view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
                   glm::vec3(0.0f, 0.0f, 0.0f), 
                   glm::vec3(0.0f, 1.0f, 0.0f));
```

## �ۥѲ���
- �]�w��v���t���ܼơG
```cpp
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
```
- �w�qLookAt��ơG
```cpp
view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
```
- ��L��J������v���G
```cpp
void processInput(GLFWwindow *window) {
    float cameraSpeed = 0.05f;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}
```

## ���ʳt�׻PdeltaTime
- �ϥ�deltaTime�T�O���P�w�鲾�ʳt�פ@�P�G
```cpp
float deltaTime = 0.0f;
float lastFrame = 0.0f;

float currentFrame = glfwGetTime();
deltaTime = currentFrame - lastFrame;
lastFrame = currentFrame;

void processInput(GLFWwindow *window) {
  float cameraSpeed = 2.5f * deltaTime;
  ...
}
```

## �������ʻP�ƹ���J
- �p��������M���訤�A��s��V�V�q�G
```cpp
float lastX = 400, lastY = 300;
float yaw = -90.0f, pitch = 0.0f;

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
```
- ���U�ƹ��^�I��ơG
```cpp
glfwSetCursorPosCallback(window, mouse_callback);
```

## �Y��
- �ƹ��u���Y��G
```cpp
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= yoffset;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}
glfwSetScrollCallback(window, scroll_callback);

projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
```

## ����
- �ϥμکԨ����䭭��A���˨ϥΥ|���ƨӹ�{�󧹵�����v���t�ΡC