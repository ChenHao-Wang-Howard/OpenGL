# Hello Triangle
## 目錄
1. [頂點輸入](#頂點輸入)
2. [頂點著色器](#頂點著色器)
3. [編譯著色器](#編譯著色器)
4. [片段著色器](#片段著色器)
5. [連結頂點屬性](#連結頂點屬性)
6. [元素緩衝對象](#元素緩衝對象)

## 前言
**頂點數組物件：Vertex Array Object，VAO**
**頂點緩衝物件：Vertex Buffer Object，VBO**
**元素緩衝物件：Element Buffer Object，EBO 或索引緩衝物件Index Buffer Object，IBO**

1. 圖形渲染管線可以被分割成兩個主要部分
    - 第一部分把你的3D座標轉換成2D座標
    - 第二部分是把2D座標轉換成實際的有顏色的像素。

2. **(著色器)Shader**在GPU上為每一個（**(渲染管線)pipeline**）階段運行各自的小程序，具有**並行執行**的特性。

3. OpenGL著色器是用 **OpenGL著色器語言(OpenGL Shading Language,GLSL)** 寫成的

## 頂點輸入
1. 頂點資料輸入
    - 3D座標範圍： OpenGL 處理 3D 座標範圍在 -1.0 到 1.0 之間，稱為**標準化設備座標（Normalized Device Coordinates, NDC）**。
2. 標準化設備座標 (NDC)
    - 座標範圍：  -1.0 ~ 1.0 
    - 座標系統特點： y軸向上，(0, 0) 為中心。
3. 頂點緩衝對象 (VBO)
    - VBO創建與綁定： 使用 glGenBuffers 和 glBindBuffer 函數創建並綁定VBO。
    - 資料傳輸： 使用 glBufferData 將頂點數據傳輸到緩衝記憶體中。
4. glBufferData數據類型
    - GL_STATIC_DRAW
    - GL_DYNAMIC_DRAW
    - GL_STREAM_DRAW

## 頂點著色器
### 基本概念
- 頂點著色器 (Vertex Shader) 是必需的，用於現代 OpenGL 的基礎渲染，至少要配合一個片段著色器。
- 使用語言： GLSL (OpenGL Shading Language)，語法類似 C 語言。
1. 創建與配置步驟
    - 版本聲明： 開頭用 #version 330 core 表示使用 OpenGL 3.3 的核心模式。
    - 輸入聲明： 用 in 關鍵字宣告輸入頂點屬性，例如位置數據 vec3 aPos。
    - 輸入位置： 透過 layout (location = 0) 設定輸入變量的位置值。
2. 向量的使用
    - 數學概念： 向量用來表達空間中的位置和方向。
    - GLSL 向量： vec3 表示有三個分量的向量，用 .x, .y, .z 訪問。
    - 輸出轉換： 把 vec3 轉換成四分量的 vec4，設定 w 分量為 1.0，賦值給 gl_Position。

## 編譯著色器
### 初始設定
1. 硬編碼著色器源碼：把頂點著色器的 GLSL 源碼放在程式碼頂部的 C 風格字串裡
2. 建立著色器對象：
    - 使用 glCreateShader 建立一個著色器對象，並返回它的 ID。
    - 傳遞參數 GL_VERTEX_SHADER 表示我們要創建一個頂點著色器。
3. 使用 glShaderSource 附加著色器源碼到著色器對象，然後用 glCompileShader 編譯它。
    - 第一個參數是著色器對象的 ID。
    - 第二個參數指定源碼字串數量，這裡只有一個。
    - 第三個參數是實際的頂點著色器源碼。
    - 第四個參數設為 NULL。
4. 編譯錯誤檢測
    - 檢測編譯狀態：使用 glGetShaderiv 檢查是否成功編譯，並使用 glGetShaderInfoLog 獲取錯誤訊息。
    - success 變數用來檢查編譯是否成功。
    - infoLog 容器儲存錯誤訊息（如果有的話）。
    - 如果 success 為 GL_FALSE，表示編譯失敗，列印錯誤訊息。

## 片段著色器
### 片段著色器 (Fragment Shader)
目標：計算像素的最終顏色，這裡設定為橘黃色。
顏色表示：RGBA（紅、綠、藍、透明度），範圍0.0到1.0。
示例：紅色1.0f + 綠色1.0f = 黃色。
```
#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
```
輸出變量：out vec4 FragColor，顏色設置為 vec4(1.0f, 0.5f, 0.2f, 1.0f)。
1. 編譯片段著色器
    - 建立片段著色器對象：
    ```
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    ```
2. 附加源碼並編譯：
    ```
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    ```
### 著色器程式 (Shader Program)
1. 建立程式物件：
```
unsigned int shaderProgram;
shaderProgram = glCreateProgram();
```
2. 附加並連結著色器：
```
glAttachShader(shaderProgram, vertexShader);
glAttachShader(shaderProgram, fragmentShader);
glLinkProgram(shaderProgram);
```
3. 檢查連結狀態
```
int success;
char infoLog[512];
glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
if (!success) {
    glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
}
```
4. 使用程式物件
```
glUseProgram(shaderProgram);
```
5. 刪除著色器對象
```
glDeleteShader(vertexShader);
glDeleteShader(fragmentShader);
```
## 連結頂點屬性


#### 解析頂點緩衝資料
- **位置資料**：32位元浮點值，每個位置有3個值，數組中緊密排列，從緩衝開始處存放。
- **glVertexAttribPointer函數**：
  - `glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);`
  - 參數介紹：
    1. **指定頂點屬性位置**：傳入0，對應layout(location = 0)的position屬性。
    2. **頂點屬性大小**：vec3，有3個值。
    3. **資料類型**：GL_FLOAT。
    4. **標準化**：GL_FALSE（不標準化）。
    5. **步長**：3 * sizeof(float)，緊密排列可設為0。
    6. **偏移量**：位置資料在數組的開頭，所以是0。

#### 綁定頂點屬性
- `glEnableVertexAttribArray(0);`
- 每個頂點屬性從綁定到GL_ARRAY_BUFFER的VBO中獲取數據。

#### 繪製流程
- 初始化頂點數據並配置頂點屬性：
  ```cpp
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  ```
- 使用著色器程序並繪製物體：
  ```cpp
  glUseProgram(shaderProgram);
  someOpenGLFunctionThatDrawsOurTriangle();
  ```

#### 頂點數組對象 (VAO)
- VAO儲存頂點屬性配置，可簡化重複綁定和配置工作。
- 創建和綁定VAO：
  ```cpp
  unsigned int VAO;
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  ```
- 繪製時只需綁定對應的VAO：
  ```cpp
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  someOpenGLFunctionThatDrawsOurTriangle();
  ```

#### 繪製三角形
- 使用`glDrawArrays`函數：
  ```cpp
  glDrawArrays(GL_TRIANGLES, 0, 3);
  ```
- 參數介紹：
  1. 繪製圖元類型：GL_TRIANGLES。
  2. 頂點陣列起始索引：0。
  3. 繪製頂點數量：3。

## 元素緩衝對象
好的，以下是翻譯後的筆記：

#### 基本概念
- **EBO**也稱為**索引緩衝對象**(Index Buffer Object, IBO)。
- 主要用來避免重複頂點，優化繪製效率，特別是在繪製包含多個三角形的複雜模型時。

#### 範例：繪製矩形
- 直接定義頂點時，會出現重複頂點，增加額外開銷：
  ```cpp
  float vertices[] = {
      // 第一個三角形
      0.5f, 0.5f, 0.0f,   // 右上角
      0.5f, -0.5f, 0.0f,  // 右下角
      -0.5f, 0.5f, 0.0f,  // 左上角
      // 第二個三角形
      0.5f, -0.5f, 0.0f,  // 右下角
      -0.5f, -0.5f, 0.0f, // 左下角
      -0.5f, 0.5f, 0.0f   // 左上角
  };
  ```
- 使用索引時，只需定義唯一頂點，然後指定繪製順序：
  ```cpp
  float vertices[] = {
      0.5f, 0.5f, 0.0f,   // 右上角
      0.5f, -0.5f, 0.0f,  // 右下角
      -0.5f, -0.5f, 0.0f, // 左下角
      -0.5f, 0.5f, 0.0f   // 左上角
  };

  unsigned int indices[] = {
      0, 1, 3, // 第一個三角形
      1, 2, 3  // 第二個三角形
  };
  ```

#### 建立和綁定EBO
- 建立EBO：
  ```cpp
  unsigned int EBO;
  glGenBuffers(1, &EBO);
  ```
- 綁定EBO並傳遞索引資料：
  ```cpp
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  ```

#### 使用EBO進行繪製
- 使用`glDrawElements`函數代替`glDrawArrays`：
  ```cpp
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  ```
  - 參數：
    1. **繪製模式**：GL_TRIANGLES。
    2. **繪製頂點數量**：6。
    3. **索引類型**：GL_UNSIGNED_INT。
    4. **EBO中的偏移量**：0。

#### EBO與VAO的結合
- 綁定VAO時，自動綁定EBO：
  ```cpp
  glBindVertexArray(VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  ```
- 繪製時只需綁定VAO：
  ```cpp
  glUseProgram(shaderProgram);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  ```

#### 繪製流程總結
1. **初始化**：
   ```cpp
   glBindVertexArray(VAO);
   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   ```
2. **渲染循環中**：
   ```cpp
   glUseProgram(shaderProgram);
   glBindVertexArray(VAO);
   glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
   glBindVertexArray(0);
   ```

#### 線框模式
- 開啟線框模式：
  ```cpp
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  ```
- 恢復預設模式：
  ```cpp
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  ```

