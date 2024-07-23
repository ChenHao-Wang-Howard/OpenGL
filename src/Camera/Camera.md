# Camera
## 目錄
1. [前言](#前言)
2. [攝影機/觀察空間](#攝影機/觀察空間)
3. [LookAt 矩陣](#lookat-矩陣)
4. [自由移動](#自由移動)
5. [移動速度與deltaTime](#移動速度與deltatime)
6. [視角移動與滑鼠輸入](#視角移動與滑鼠輸入)
7. [縮放](#縮放)

## 前言
- OpenGL無攝影機概念，可透過移動場景模擬。
- FPS風格攝影機設定：鍵盤與滑鼠輸入，自訂攝影機類別。

## 攝影機/觀察空間
- 觀察矩陣將世界座標變換為觀察座標。
- 定義攝影機需確定位置、觀察方向、右側向量、上方向量。

#### 概念
- 討論攝影機/觀察空間時，指的是以攝影機視角作為場景原點時，場景中所有頂點的座標。
- 觀察矩陣：將所有世界座標變換為相對於攝影機位置與方向的觀察座標。

#### 攝影機定義
- 需要的元素：
  1. 世界空間中的位置
  2. 觀察方向
  3. 右側的向量
  4. 上方的向量

- 基本構建：創建一個三個單位軸相互垂直、以攝影機位置為原點的座標系。



### 攝影機位置
- 定義攝影機位置：
  ```cpp
  glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
  ```
- 注意：正z軸是從螢幕指向觀察者。希望攝影機向後移動，就沿著z軸的正方向移動。

### 攝影機方向
- 攝影機指向場景原點 `(0, 0, 0)`：
  ```cpp
  glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
  glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
  ```
- 說明：方向向量（Direction Vector）其實是從攝影機指向目標的反方向。

### 右軸
- 取得右邊向量需要定義一個上向量，並進行叉乘：
  ```cpp
  glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
  glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
  ```

### 上軸
- 取得指向攝影機正y軸向量：
  ```cpp
  glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
  ```

### 總結
- 在線性代數中，這個過程稱為格拉姆—施密特正交化(Gram-Schmidt Process)。


## LookAt 矩陣

### 矩陣公式
- 矩陣形式：
  ```
  LookAt = [ Rx Ux Dx 0 ]
           [ Ry Uy Dy 0 ]
           [ Rz Uz Dz 0 ]
           [ 0  0  0  1 ] *
           [ 1  0  0  -Px ]
           [ 0  1  0  -Py ]
           [ 0  0  1  -Pz ]
           [ 0  0  0   1 ]
  ```
  - R: 右向量
  - U: 上向量
  - D: 方向向量
  - P: 攝影機位置向量（位置向量是相反的，因為希望將世界平移到與自身移動相反的方向）

### 觀察矩陣
- LookAt 矩陣：作為觀察矩陣，可以有效地將所有世界座標變換到觀察空間。

### 使用 GLM
- GLM 已經提供支援，只需定義攝影機位置、目標位置和上向量即可：
  ```cpp
  glm::mat4 view;
  view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f), 
                     glm::vec3(0.0f, 0.0f, 0.0f), 
                     glm::vec3(0.0f, 1.0f, 0.0f));
  ```

### 攝影機旋轉
- 攝影機注視點保持在 `(0, 0, 0)`，透過每一幀重新計算 x 和 z 座標，使攝影機繞著場景旋轉：
  ```cpp
  float radius = 10.0f;
  float camX = sin(glfwGetTime()) * radius;
  float camZ = cos(glfwGetTime()) * radius;
  glm::mat4 view;
  view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
  ```



## 自由移動
### 設定攝影機系統
- 定義攝影機變數：
  ```cpp
  glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
  glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
  glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);
  ```

### 更新 LookAt 函數
- 攝影機位置設為 `cameraPos`
- 方向為目前位置加上方向向量：
  ```cpp
  view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
  ```

### 鍵盤輸入控制
- 定義 `processInput` 函數：
  ```cpp
  void processInput(GLFWwindow *window)
  {
      float cameraSpeed = 0.05f; // 調整速度
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

### 移動控制細節
- WASD 控制前後左右移動
- 使用叉乘計算右向量，並沿著右向量移動，實現橫移效果 (Strafe)
- 右向量需標準化，確保移動速度一致，不受攝影機朝向影響



## 移動速度與deltaTime

### 速度問題
- 移動速度目前是常數。
- 不同處理器性能會導致不同的渲染幀率，影響攝影機移動速度。
- 發布程式時，需確保各硬體上移動速度一致。

### 解決方案：使用時間差
- 使用 `deltaTime` 變量，記錄渲染每幀所需時間。
- 移動速度乘以 `deltaTime`，確保速度隨時間調整，平衡不同幀率下的移動速度。

### 追蹤 `deltaTime`
- 定義兩個全域變數：
  ```cpp
  float deltaTime = 0.0f; // 當前幀與上一幀的時間差
  float lastFrame = 0.0f; // 上一幀的時間
  ```
- 每幀計算新的 `deltaTime`：
  ```cpp
  float currentFrame = glfwGetTime();
  deltaTime = currentFrame - lastFrame;
  lastFrame = currentFrame;
  ```

### 更新 `processInput`
- 使用 `deltaTime` 計算攝影機速度：
  ```cpp
  void processInput(GLFWwindow *window)
  {
    float cameraSpeed = 2.5f * deltaTime;
    // 其他按鍵控制
  }
  ```



## 視角移動與滑鼠輸入
### 歐拉角 筆記
### 基本概念
- **歐拉角(Euler Angle)**: 表示3D空間中旋轉的三個值。
- 由萊昂哈德·歐拉提出，包含：
  - **俯仰角(Pitch)**: 往上或往下看的角度。
  - **偏航角(Yaw)**: 往左或往右看的角度。
  - **滾轉角(Roll)**: 攝影機的翻滾角度（通常用於太空船攝影機）。

### 用途
- 我們的攝影機系統主要關心俯仰角和偏航角，不考慮滾轉角。

### 轉換過程
1. **俯仰角**和**偏航角**轉換為方向向量需要一些三角學知識：
   - 斜邊邊長定義為1，鄰邊的長度是 `cos(角度)`，對邊是 `sin(角度)`

2. **俯仰角計算**:
   - \( y \) 分量: `sin(俯仰角)`
     ```cpp
     direction.y = sin(glm::radians(pitch));
     ```
   - \( x \) 和 \( z \) 分量也被俯仰角影響:
     ```cpp
     direction.x = cos(glm::radians(pitch));
     direction.z = cos(glm::radians(pitch));
     ```

3. **偏航角計算**:
   - \( x \) 分量: `cos(偏航角)`
   - \( z \) 分量: `sin(偏航角)`
     ```cpp
     direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
     direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
     ```

### 結果
- 得到基於俯仰角和偏航角的方向向量:
  ```cpp
  direction.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
  direction.y = sin(glm::radians(pitch));
  direction.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
  ```

### 滑鼠輸入 筆記

### 目的
- 利用滑鼠移動來調整偏航角和俯仰角，實現攝影機在3D場景中的自由移動。

### 原理
- 水平移動影響偏航角，垂直移動影響俯仰角。
- 計算滑鼠位置與上一幀的位置差異來確定偏移量，調整角度。

### 設置步驟
1. **隱藏並捕捉滑鼠**
   ```cpp
   glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
   ```
   - 隱藏滑鼠，防止它離開視窗，適合FPS風格的攝影機系統。

2. **監聽滑鼠移動事件**
   ```cpp
   void mouse_callback(GLFWwindow* window, double xpos, double ypos);
   glfwSetCursorPosCallback(window, mouse_callback);
   ```
   - 設置滑鼠移動回調函數`mouse_callback`。

3. **計算滑鼠偏移量**
   - 儲存上一幀滑鼠位置（初始為螢幕中心：`800x600`）。
     ```cpp
     float lastX = 400, lastY = 300;
     ```
   - 計算偏移量：
     ```cpp
     float xoffset = xpos - lastX;
     float yoffset = lastY - ypos; // 注意 y 坐标反向
     lastX = xpos;
     lastY = ypos;
     ```
   - 調整靈敏度：
     ```cpp
     float sensitivity = 0.05f;
     xoffset *= sensitivity;
     yoffset *= sensitivity;
     ```

4. **更新俯仰角和偏航角**
   ```cpp
   yaw   += xoffset;
   pitch += yoffset;
   ```

5. **限制俯仰角範圍**
   - 避免視角逆轉：
     ```cpp
     if(pitch > 89.0f)
         pitch = 89.0f;
     if(pitch < -89.0f)
         pitch = -89.0f;
     ```

6. **計算方向向量**
   ```cpp
   glm::vec3 front;
   front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
   front.y = sin(glm::radians(pitch));
   front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
   cameraFront = glm::normalize(front);
   ```

### 解決攝影機跳躍問題
- 初次進入視窗時滑鼠位置不對，導致攝影機跳躍。
- 用`bool`變數檢查是否第一次輸入：
  ```cpp
  if(firstMouse) 
  {
      lastX = xpos;
      lastY = ypos;
      firstMouse = false;
  }
  ```

### 最終程式碼
```cpp
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; 
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}
```


## 縮放

#### 目的
- 實作一個縮放(Zoom)功能，調整視野(Field of View, FOV)來改變場景顯示的範圍。

#### 原理
- 視野變小時，場景看起來會被放大(Zoom In)。
- 使用滑鼠滾輪來調整視野範圍。

#### 步驟

1. **定義滑鼠滾輪回呼函數**
   - 監聽滑鼠滾輪滾動，調整視野(FOV)。
   ```cpp
   void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
   {
     if(fov >= 1.0f && fov <= 45.0f)
       fov -= yoffset;
     if(fov <= 1.0f)
       fov = 1.0f;
     if(fov >= 45.0f)
       fov = 45.0f;
   }
   ```
   - `yoffset`代表垂直滾動的大小。
   - 將`fov`限制在`1.0f`到`45.0f`之間。

2. **更新投影矩陣**
   - 在每幀中上傳投影矩陣到GPU，使用`fov`變數來設定視野。
   ```cpp
   projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
   ```

3. **註冊回呼函數**
   - 註冊滑鼠滾輪回呼函數，使其在滑鼠滾輪滾動時被調用。
   ```cpp
   glfwSetScrollCallback(window, scroll_callback);
   ```



#### 附註
- 使用歐拉角的攝影機系統並不完美，可能會引入萬向節死鎖問題。
- 更好的攝影機系統是使用四元數(Quaternions)，會在後續討論。