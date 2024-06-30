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
## 元素緩衝對象