# Shaders
## 目錄
1. [GLSL](#GLSL)
2. [資料類型](#資料類型)
3. [輸入與輸出](#輸入與輸出)
4. [Uniform](#Uniform)
5. [更多屬性](#更多屬性)
6. [我們自己的著色器類](#我們自己的著色器類)
7. [從檔案索取](#從檔案索取)

## GLSL
#### 基本概念
- **GLSL**：一種類似C語言的著色器語言，專為圖形計算設計。
- **主要特性**：包含針對向量和矩陣操作的有用特性。
- **結構**：著色器開頭宣告版本，接著是輸入/輸出變數、uniform和main函數。

#### 典型著色器結構
```cpp
#version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;

uniform type uniform_name;

void main()
{
    // 處理輸入並進行一些圖形操作
    ...
    // 將處理過的結果輸出到輸出變數
    out_variable_name = weird_stuff_we_processed;
}
```

#### 頂點著色器
- **輸入變數**：頂點屬性 (Vertex Attribute)。
- **上限**：由硬體決定，OpenGL至少保證16個包含4分量的頂點屬性。
- **查詢方法**：使用`GL_MAX_VERTEX_ATTRIBS`查詢上限。

```cpp
int nrAttributes;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;
```



## 資料類型


#### 基本概念
- **GLSL資料型別**：類似C語言，包含int、float、double、uint和bool。
- **容器類型**：向量(Vector)和矩陣(Matrix)，矩陣會在之後的教程中討論。

#### 向量
- 向量是一個包含2、3或4個分量的容器，分量類型可以是任一基礎類型。
- 常用的向量類型：
  - `vecn`：包含n個float分量的預設向量
  - `bvecn`：包含n個bool分量的向量
  - `ivecn`：包含n個int分量的向量
  - `uvecn`：包含n個unsigned int分量的向量
  - `dvecn`：包含n個double分量的向量
- **常用的float向量**：`vecn`，滿足大多數需求。

#### 獲取向量分量
- 使用`.x`、`.y`、`.z`和`.w`獲取第1到第4個分量。
- 可用`rgba`獲取顏色分量，用`stpq`獲取紋理座標分量。

#### 重組 (Swizzling)
- **重組**：靈活選擇和組合向量分量的新方式。
  ```cpp
  vec2 someVec;
  vec4 differentVec = someVec.xyxx;
  vec3 anotherVec = differentVec.zyw;
  vec4 otherVec = someVec.xxxx + anotherVec.yxzy;
  ```
- **限制**：不能在vec2中獲取`.z`元素。

#### 向量建構函數
- 使用向量作為參數，減少需求參數的數量。
  ```cpp
  vec2 vect = vec2(0.5, 0.7);
  vec4 result = vec4(vect, 0.0, 0.0);
  vec4 otherResult = vec4(result.xyz, 1.0);
  ```
## 輸入與輸出
### 輸入與輸出 - 筆記

#### 基本概念
- **GLSL**使用`in`和`out`關鍵字來設定著色器的輸入和輸出，進行資料傳遞。
- 每個著色器的輸出變數會傳遞給下一個著色器階段的輸入變數。

#### 頂點著色器
- **輸入變數**：直接從頂點資料接收輸入，需使用`layout (location = 0)`指定位置。
- 可以使用`glGetAttribLocation`查詢屬性位置值，但在著色器中設定更簡潔易懂。

#### 片段著色器
- 必須定義一個`vec4`類型的顏色輸出變數，否則OpenGL會將物體渲染為黑色或白色。

#### 傳遞數據
- 要從一個著色器向另一個著色器傳遞數據，需要在發送方聲明輸出變數，在接收方聲明相同名稱和類型的輸入變數。
- OpenGL會在連結程序物件時將這些變數連結起來。

#### 範例：從頂點著色器向片段著色器傳遞顏色
- **頂點著色器**：
  ```cpp
  #version 330 core
  layout (location = 0) in vec3 aPos;

  out vec4 vertexColor;

  void main()
  {
      gl_Position = vec4(aPos, 1.0);
      vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // 暗紅色
  }
  ```
- **片段著色器**：
  ```cpp
  #version 330 core
  out vec4 FragColor;

  in vec4 vertexColor;

  void main()
  {
      FragColor = vertexColor;
  }
  ```
- **結果**：片段著色器接收到頂點著色器傳來的深紅色，並輸出該顏色。

## Uniform


#### 基本概念
- **Uniform**：從應用程式(CPU)傳遞數據到著色器(GPU)的一種方式。
- **特性**：
  1. 全域性(Global)：每個著色器程序中的uniform變量都是獨一無二的，可以在任何著色器階段訪問。
  2. 持久性：uniform值會一直保存，直到被重置或更新。

#### 宣告與使用
- 在GLSL中宣告uniform：
  ```cpp
  #version 330 core
  out vec4 FragColor;

  uniform vec4 ourColor;

  void main()
  {
      FragColor = ourColor;
  }
  ```
- 在片段著色器中宣告一個`uniform vec4`的`ourColor`，並將片段著色器的輸出顏色設為uniform值。

#### 設置Uniform值
- 查找著色器中uniform屬性的索引/位置值：
  ```cpp
  int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
  ```
- 更新uniform值：
  ```cpp
  glUseProgram(shaderProgram);
  glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
  ```

#### 實現顏色隨時間變化
- 獲取運行時間，計算綠色值並更新uniform：
  ```cpp
  float timeValue = glfwGetTime();
  float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
  int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
  glUseProgram(shaderProgram);
  glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
  ```

#### OpenGL中的glUniform函數
- OpenGL不支持類型重載，所以glUniform函數有多個後綴標識不同類型：
  - `f`：float
  - `i`：int
  - `ui`：unsigned int
  - `3f`：3個float
  - `fv`：float向量/數組

#### 在渲染迴圈中更新Uniform
- 每次迭代中更新uniform值，實現顏色變化：
  ```cpp
  while(!glfwWindowShouldClose(window))
  {
      processInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shaderProgram);

      float timeValue = glfwGetTime();
      float greenValue = sin(timeValue) / 2.0f + 0.5f;
      int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
      glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glfwSwapBuffers(window);
      glfwPollEvents();
  }
  ```

#### 小結
- Uniform變量用於在應用程式和著色器之間傳遞數據，並且在渲染迭代中可以隨時更新。
- Uniform是一個全域變數，在著色器程序的任何階段都可以訪問。
- 在頂點屬性無法滿足需求時，使用Uniform是一個有效的解決方案。

## 更多屬性


#### 基本概念
- 增加顏色資料到頂點資料中，每個頂點有3個float值表示顏色（RGB）。
- 更新頂點著色器以接收顏色作為頂點屬性輸入。

#### 新增顏色資料的頂點數組
```cpp
float vertices[] = {
    // 位置              // 顏色
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 右下
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 左下
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 頂部
};
```

#### 更新頂點著色器
- 接收顏色並輸出到片段著色器
```cpp
#version 330 core
layout (location = 0) in vec3 aPos;   
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}
```

#### 更新片段著色器
- 接收並使用頂點著色器傳來的顏色
```cpp
#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
```

#### 配置頂點屬性指標
- 更新`glVertexAttribPointer`函數以處理新的頂點數據佈局
```cpp
// 位置屬性
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// 顏色屬性
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
```
- 新的步長值為`6 * sizeof(float)`（3個位置值 + 3個顏色值）。
- 顏色屬性的偏移量為`3 * sizeof(float)`。

#### 顏色插值
- 渲染三角形時，光柵化階段會生成比頂點更多的片段，進行顏色插值。
- 片段顏色根據頂點顏色和位置進行線性插值，實現顏色過渡。

#### 結果
- 運行程式應該看到三個頂點分別為紅、綠、藍色的三角形，並在三角形內部呈現顏色漸變效果。

---

這些筆記涵蓋了在頂點資料中添加更多屬性（如顏色）的過程，並展示了如何更新著色器和頂點屬性指標以處理新的頂點數據佈局，幫助你快速理解和回顧相關內容。
## 我們自己的著色器類


#### 基本概念
- 寫、編譯和管理著色器是一件麻煩事，我們會創建一個類別來簡化這個過程。
- 這個類別可以從硬碟讀取著色器，編譯並連結它們，並對它們進行錯誤檢測。

#### 類別結構
- 我們會將著色器類別全部放在頭檔裡，方便學習和移植。

#### 頭檔內容
- 包含必要的include，並定義類別結構：
```cpp
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // 包含glad來獲取所有必需的OpenGL頭文件

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // 程序ID
    unsigned int ID;

    // 建構子，讀取並構建著色器
    Shader(const char* vertexPath, const char* fragmentPath);
    // 使用/激活程序
    void use();
    // uniform工具函數
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
};

#endif
```

#### 說明
- 使用預處理指令防止重複包含：
  ```cpp
  #ifndef SHADER_H
  #define SHADER_H
  ```
- 預處理指令告知編譯器在文件未被包含過的情況下才包含和編譯這個頭文件，防止連結衝突。
- 類別`Shader`儲存了著色器程式的ID。
- 建構子需要頂點和片段著色器原始碼的檔案路徑，允許從硬碟讀取原始碼文字檔案。
- 工具函數：
  - `use`：激活著色器程序。
  - `setBool`、`setInt`、`setFloat`：查詢uniform位置並設定其值。


## 從檔案索取


#### 基本概念
- 使用C++檔案流讀取著色器內容，將其存儲到string物件中。
- 編譯和連結著色器，並檢查編譯/連結過程中的錯誤。

#### 讀取檔案內容
- 使用C++檔案流從指定路徑讀取頂點和片段著色器的內容。
- 將檔案內容存儲到string物件中：
  ```cpp
  Shader(const char* vertexPath, const char* fragmentPath)
  {
      // 1. 從文件路徑中獲取頂點/片段著色器
      std::string vertexCode;
      std::string fragmentCode;
      std::ifstream vShaderFile;
      std::ifstream fShaderFile;
      // 保證ifstream對象可以拋出異常：
      vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      try 
      {
          // 打開文件
          vShaderFile.open(vertexPath);
          fShaderFile.open(fragmentPath);
          std::stringstream vShaderStream, fShaderStream;
          // 讀取文件的緩衝內容到數據流中
          vShaderStream << vShaderFile.rdbuf();
          fShaderStream << fShaderFile.rdbuf();       
          // 關閉文件處理器
          vShaderFile.close();
          fShaderFile.close();
          // 轉換數據流到string
          vertexCode = vShaderStream.str();
          fragmentCode = fShaderStream.str();     
      }
      catch (std::ifstream::failure e)
      {
          std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
      }
      const char* vShaderCode = vertexCode.c_str();
      const char* fShaderCode = fragmentCode.c_str();
  }
  ```

#### 編譯和連結著色器
- 編譯頂點和片段著色器，檢查編譯錯誤：
  ```cpp
  // 2. 編譯著色器
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  // 頂點著色器
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // 打印編譯錯誤（如果有的話）
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  };

  // 片段著色器也類似
  [...]

  // 著色器程序
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  // 打印連接錯誤（如果有的話）
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success)
  {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  // 刪除著色器，它們已經連接到我們的程序中了，已經不再需要了
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  ```

#### 使用函數
- 簡單的使用函數`use`：
  ```cpp
  void use() 
  { 
      glUseProgram(ID);
  }
  ```

#### Uniform設置函數
- 設置uniform變數的值：
  ```cpp
  void setBool(const std::string &name, bool value) const
  {
      glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
  }
  void setInt(const std::string &name, int value) const
  { 
      glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
  }
  void setFloat(const std::string &name, float value) const
  { 
      glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
  } 
  ```

#### 使用著色器類別
- 創建一個著色器對象並使用它：
  ```cpp
  Shader ourShader("path/to/shaders/shader.vs", "path/to/shaders/shader.fs");
  ...
  while(...)
  {
      ourShader.use();
      ourShader.setFloat("someUniform", 1.0f);
      DrawStuff();
  }
  ```

#### 小結
- 讀取頂點和片段著色器的內容，編譯並連結，並檢查錯誤。
- 使用簡單的`use`函數來激活著色器程序。
- 設置uniform變數值的函數，方便在渲染循環中動態更新uniform。


