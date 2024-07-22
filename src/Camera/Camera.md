# Camera
## 目錄
1. [前言](#前言)
2. [攝影機/觀察空間](#攝影機/觀察空間)
3. [LookAt 矩陣](#lookat-矩陣)
4. [自由移動](#自由移動)
5. [移動速度與deltaTime](#移動速度與deltatime)
6. [視角移動與滑鼠輸入](#視角移動與滑鼠輸入)
7. [縮放](#縮放)
8. [結論](#結論)

## 前言
- OpenGL無攝影機概念，可透過移動場景模擬。
- FPS風格攝影機設定：鍵盤與滑鼠輸入，自訂攝影機類別。

## 攝影機/觀察空間
- 觀察矩陣將世界座標變換為觀察座標。
- 定義攝影機需確定位置、觀察方向、右側向量、上方向量。

### 攝影機位置
- 定義攝影機位置：
```cpp
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
```
- 正z軸指向螢幕外。

### 攝影機方向
- 定義攝影機方向：
```cpp
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
```
- 方向向量指向z軸正方向。

### 右軸
- 定義右向量：
```cpp
glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
```
- 上向量與方向向量叉乘，取得右向量。

### 上軸
- 定義上向量：
```cpp
glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
```
- 右向量與方向向量叉乘，取得上向量。

## LookAt 矩陣
- 透過3個軸與平移向量創建矩陣，轉換座標空間：
```cpp
glm::mat4 view;
view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
                   glm::vec3(0.0f, 0.0f, 0.0f), 
                   glm::vec3(0.0f, 1.0f, 0.0f));
```

## 自由移動
- 設定攝影機系統變數：
```cpp
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
```
- 定義LookAt函數：
```cpp
view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
```
- 鍵盤輸入移動攝影機：
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

## 移動速度與deltaTime
- 使用deltaTime確保不同硬體移動速度一致：
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

## 視角移動與滑鼠輸入
- 計算俯仰角和偏航角，更新方向向量：
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
- 註冊滑鼠回呼函數：
```cpp
glfwSetCursorPosCallback(window, mouse_callback);
```

## 縮放
- 滑鼠滾輪縮放：
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

## 結論
- 使用歐拉角有其限制，推薦使用四元數來實現更完善的攝影機系統。