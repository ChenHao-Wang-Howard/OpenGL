







# Textures
## 目錄
1. [紋理](#紋理)
2. [紋理環繞方式](#紋理環繞方式)
3. [紋理過濾](#紋理過濾)
4. [加載與創建紋理](#加載與創建紋理)
5. [stb_image.h](#stb_image.h)
6. [生成紋理](#生成紋理)
7. [應用紋理](#應用紋理)
8.[紋理單元](#紋理單元)

##紋理

#### 基本概念
- **紋理**：一個2D圖片（也有1D和3D的紋理），用來為物體添加細節，使其看起來更真實。
- 使用紋理能夠減少頂點數量，提升渲染效率。

#### 紋理的作用
- **增加細節**：透過在一張圖片上添加大量細節，使物體看起來精細而不需要增加額外頂點。
- **紋理座標**：指定每個頂點對應紋理的哪個部分，進行紋理映射。

#### 紋理座標
- 紋理座標在x和y軸上，範圍為0到1之間。
- 紋理座標起始於(0, 0)，即紋理圖片的左下角，終止於(1, 1)，即紋理圖片的右上角。
- 紋理座標示例：
  ```cpp
  float texCoords[] = {
      0.0f, 0.0f, // 左下角
      1.0f, 0.0f, // 右下角
      0.5f, 1.0f  // 上中
  };
  ```

#### 紋理映射
- 為三角形的每個頂點指定紋理座標：
  - 左下角頂點對應紋理的左下角 `(0, 0)`
  - 上頂點對應紋理的上中位置 `(0.5, 1.0)`
  - 右下角頂點對應紋理的右下角 `(1, 0)`

#### 紋理取樣
- 取樣(Sampling)：使用紋理座標獲取紋理顏色。
- 片段著色器會為每個片段進行紋理座標的插值，獲取對應的紋理顏色。




##紋理環繞方式


#### 基本概念
- **紋理座標範圍**：通常是從(0, 0)到(1, 1)。
- **超出範圍**：OpenGL預設行為是重複紋理圖像，但也提供了其他選擇。

#### 環繞方式選項
- **GL_REPEAT**：預設行為，重複紋理圖像。
- **GL_MIRRORED_REPEAT**：重複紋理圖像，但每次重複圖片是鏡像放置的。
- **GL_CLAMP_TO_EDGE**：紋理座標被約束在0到1之間，超出的部分重複邊緣顏色，產生邊緣被拉伸效果。
- **GL_CLAMP_TO_BORDER**：超出範圍的部分使用指定的邊緣顏色。

#### 設置紋理環繞方式
- 使用`glTexParameteri`函數對單獨的坐標軸設置：
  ```cpp
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  ```
  - 第一個參數：紋理目標，使用2D紋理時為`GL_TEXTURE_2D`。
  - 第二個參數：設定的選項與應用的紋理軸（S、T軸）。
  - 第三個參數：環繞方式（如`GL_MIRRORED_REPEAT`）。

#### 設置GL_CLAMP_TO_BORDER顏色
- 當選擇`GL_CLAMP_TO_BORDER`選項時，需指定邊緣顏色：
  ```cpp
  float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
  ```




##紋理過濾


#### 基本概念
- **紋理座標**：不依賴解析度，可以是任意浮點數值。
- **紋理過濾**：告訴OpenGL如何將紋理像素對應到紋理座標，特別是當物體很大但紋理解析度很低時。

#### 紋理過濾方式
- **GL_NEAREST**（鄰近過濾）：選擇最接近紋理座標的像素。
  - 預設方式，產生顆粒狀的圖案。
  - 圖片示例：
    ![GL_NEAREST示例圖](https://learnopengl.com/img/getting-started/texture_filter_nearest.png)

- **GL_LINEAR**（線性過濾）：基於紋理座標附近的紋理像素進行插值計算。
  - 產生更平滑的圖案。
  - 圖片示例：
    ![GL_LINEAR示例圖](https://learnopengl.com/img/getting-started/texture_filter_linear.png)

#### 設定紋理過濾方式
- 設定紋理過濾的選項，可以在放大和縮小操作時不同：
  ```cpp
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  ```

#### 多級漸遠紋理 (Mipmap)
- **多級漸遠紋理**：一系列紋理影像，每個影像是前一個影像的二分之一。
- 解決遠處物體使用高解析度紋理的問題，提高性能和真實感。
- OpenGL自動生成多級漸遠紋理：
  ```cpp
  glGenerateMipmap(GL_TEXTURE_2D);
  ```

#### 多級漸遠紋理過濾方式
- **過濾方式**：
  - **GL_NEAREST_MIPMAP_NEAREST**：使用最鄰近的多級漸遠紋理並進行鄰近插值。
  - **GL_LINEAR_MIPMAP_NEAREST**：使用最鄰近的多級漸遠紋理並進行線性內插。
  - **GL_NEAREST_MIPMAP_LINEAR**：在兩個最匹配像素大小的多級漸遠紋理之間進行線性內插，並使用鄰近插值進行取樣。
  - **GL_LINEAR_MIPMAP_LINEAR**：在兩個鄰近的多級漸遠紋理之間進行線性插值，並使用線性插值進行取樣。

- 設定多級漸遠紋理過濾方式：
  ```cpp
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  ```
- **注意**：多級漸遠紋理主要用於縮小過濾，不能用於放大過濾，否則會產生GL_INVALID_ENUM錯誤。

##加載與創建紋理



#### 解決方案
1. **自己寫圖像載入器**：
   - 為特定格式（例如.PNG）寫一個載入器，將圖像轉換為位元組序列。
   - 雖然不難，但非常麻煩，且需要為每種支援的格式寫載入器。

2. **使用圖像載入庫**：
   - 支援多種流行格式的圖像載入庫是一種更好的選擇。
   - **stb_image.h**：一個流行的圖像載入庫，支援多種圖像格式。

#### 使用stb_image.h載入紋理
- **stb_image.h**函式庫能夠簡化圖像載入過程，支援多種格式。



##stb_image.h


#### 基本概念
- **stb_image.h**：Sean Barrett開發的單頭文件圖像加載庫，能夠加載大部分流行的文件格式。
- **優點**：簡單易用，方便整合到你的工程中。

#### 安裝和使用stb_image.h
1. **下載stb_image.h**：
   - 可以在[stb_image.h官方網站](https://github.com/nothings/stb)下載。

2. **包含stb_image.h**：
   - 將下載的頭文件命名為`stb_image.h`並加入你的工程。
   - 創建一個新的C++文件，輸入以下程式碼：
     ```cpp
     #define STB_IMAGE_IMPLEMENTATION
     #include "stb_image.h"
     ```
   - 定義`STB_IMAGE_IMPLEMENTATION`會讓預處理器修改頭文件，包含相關的函數定義原始碼。

3. **在程式中包含stb_image.h**：
   - 在你的主程式文件中包含`stb_image.h`：
     ```cpp
     #include "stb_image.h"
     ```

#### 使用stb_image.h載入圖像
- 使用`stbi_load`函數加載圖像：
  ```cpp
  int width, height, nrChannels;
  unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
  ```
  - **參數**：
    - 第一個參數：影像檔案的位置。
    - 第二、第三和第四個參數：影像的寬度、高度和顏色通道數量，stb_image.h會填入這三個變數。

#### 生成紋理
- 使用加載的圖像數據生成紋理：
  ```cpp
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data); // 釋放圖像數據
  ```

#### 設置紋理參數
- 設置紋理環繞方式和過濾方式：
  ```cpp
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  ```


##生成紋理


#### 基本概念
- **紋理ID**：紋理和之前的OpenGL物件一樣，使用ID來引用。
- **綁定紋理**：需要綁定紋理，以便後續指令能夠配置當前綁定的紋理。

#### 生成紋理
- 創建紋理ID：
  ```cpp
  unsigned int texture;
  glGenTextures(1, &texture);
  ```
  - 第一個參數：生成的紋理數量。
  - 第二個參數：儲存生成紋理ID的unsigned int陣列。

- 綁定紋理：
  ```cpp
  glBindTexture(GL_TEXTURE_2D, texture);
  ```
  - 指定紋理目標為`GL_TEXTURE_2D`。

#### 設置紋理參數
- 設置紋理環繞方式和過濾方式：
  ```cpp
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  ```

#### 加載並生成紋理
- 使用`stbi_load`加載圖像：
  ```cpp
  int width, height, nrChannels;
  unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
  ```

- 使用`glTexImage2D`生成紋理：
  ```cpp
  if (data)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
      std::cout << "Failed to load texture" << std::endl;
  }
  ```
  - **參數**：
    - `GL_TEXTURE_2D`：紋理目標。
    - `0`：多級漸遠紋理的級別，0是基本級別。
    - `GL_RGB`：紋理儲存的格式。
    - `width`和`height`：紋理的寬度和高度。
    - `0`：歷史遺留參數，設置為0。
    - `GL_RGB`：來源圖像的格式。
    - `GL_UNSIGNED_BYTE`：來源圖像資料的類型。
    - `data`：圖像資料。

- 釋放圖像的記憶體：
  ```cpp
  stbi_image_free(data);
  ```

#### 完整生成紋理過程
```cpp
unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);

// 為當前綁定的紋理對象設置環繞和過濾方式
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// 加載並生成紋理
int width, height, nrChannels;
unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
if (data)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
    std::cout << "Failed to load texture" << std::endl;
}
stbi_image_free(data);
```


##應用紋理

#### 基本概念
- **紋理座標**：需要更新頂點資料，告訴OpenGL如何取樣紋理。

#### 更新頂點資料
- 新的頂點資料包含位置、顏色和紋理座標：
  ```cpp
  float vertices[] = {
      // ---- 位置 ----       ---- 顏色 ----     - 紋理座標 -
       0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
       0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
  };
  ```

#### 配置頂點屬性指標
- 新增紋理座標屬性，並更新步長參數：
  ```cpp
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // 更新位置和顏色屬性的步長參數
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  ```

#### 更新頂點著色器
- 接收並傳遞紋理座標：
  ```cpp
  #version 330 core
  layout (location = 0) in vec3 aPos;
  layout (location = 1) in vec3 aColor;
  layout (location = 2) in vec2 aTexCoord;

  out vec3 ourColor;
  out vec2 TexCoord;

  void main()
  {
      gl_Position = vec4(aPos, 1.0);
      ourColor = aColor;
      TexCoord = aTexCoord;
  }
  ```

#### 更新片段著色器
- 接收並使用紋理座標，並宣告uniform sampler2D：
  ```cpp
  #version 330 core
  out vec4 FragColor;

  in vec3 ourColor;
  in vec2 TexCoord;

  uniform sampler2D ourTexture;

  void main()
  {
      FragColor = texture(ourTexture, TexCoord);
  }
  ```

#### 綁定紋理並繪製
- 在`glDrawElements`之前綁定紋理：
  ```cpp
  glBindTexture(GL_TEXTURE_2D, texture);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  ```

#### 混合紋理和頂點顏色
- 在片段著色器中混合紋理顏色和頂點顏色：
  ```cpp
  FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
  ```

#### 完整的應用紋理代碼示例
```cpp
// Vertex data including position, color, and texture coordinates
float vertices[] = {
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

// Configure vertex attributes
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

// Updated vertex shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}

// Updated fragment shader
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}

// Binding texture and drawing
glBindTexture(GL_TEXTURE_2D, texture);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

// Mixing texture and vertex color
FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
```


##紋理單元


#### 基本概念
- **sampler2D**變數是uniform類型，需要使用`glUniform`為其賦值。
- **紋理單元**：允許在片段著色器中使用多個紋理。
- 預設紋理單元是0，但可以使用多個紋理單元來綁定多個紋理。

#### 使用紋理單元
- 使用`glUniform1i`為紋理採樣器分配一個位置值，以設定多個紋理。
- 使用`glActiveTexture`激活紋理單元，並綁定紋理到該單元。

#### 激活紋理單元並綁定紋理
- 激活紋理單元並綁定紋理：
  ```cpp
  glActiveTexture(GL_TEXTURE0); // 在綁定紋理之前先激活紋理單元
  glBindTexture(GL_TEXTURE_2D, texture1);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);
  ```

#### 修改片段著色器
- 片段著色器接收多個sampler2D：
  ```cpp
  #version 330 core
  out vec4 FragColor;

  in vec2 TexCoord;

  uniform sampler2D texture1;
  uniform sampler2D texture2;

  void main()
  {
      FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
  }
  ```

- **mix函數**：對兩個紋理進行線性插值，參數0.2代表80%的第一個紋理顏色和20%的第二個紋理顏色。

#### 載入和創建第二個紋理
- 載入第二個紋理（OpenGL學習臉部表情圖片）。

#### 綁定紋理並設置uniform
- 綁定兩個紋理到對應的紋理單元：
  ```cpp
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  ```

- 設置每個採樣器的uniform變數：
  ```cpp
  ourShader.use(); // 在設定uniform變數之前激活著色器程序
  glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // 手動設定
  ourShader.setInt("texture2", 1); // 使用著色器類設定
  ```

#### 翻轉y軸
- 使用`stbi_set_flip_vertically_on_load(true)`在加載圖像時翻轉y軸：
  ```cpp
  stbi_set_flip_vertically_on_load(true);
  ```

#### 完整代碼示例
```cpp
// 頂點數據，包括位置、顏色和紋理座標
float vertices[] = {
    // ---- 位置 ----       ---- 顏色 ----     - 紋理座標 -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
};

// 配置頂點屬性指標
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

// 修改頂點著色器
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}

// 修改片段著色器
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}

// 設置uniform變數
ourShader.use();
glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
ourShader.setInt("texture2", 1);

// 加載圖像時翻轉y軸
stbi_set_flip_vertically_on_load(true);

// 綁定紋理並繪製
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);

glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, texture2);

glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```






