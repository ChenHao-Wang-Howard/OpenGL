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

