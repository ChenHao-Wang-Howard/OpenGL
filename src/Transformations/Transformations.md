# Transformations

## 目錄
1. [變換](#變換)
2. [向量](#向量)
3. [向量與標量運算](#向量與標量運算)
4. [向量取反](#向量取反)
5. [向量加減](#向量加減)
6. [長度](#長度)
7. [向量相乘](#向量相乘)
8. [矩陣](#矩陣)
9. [矩陣的加減](#矩陣的加減)
10. [矩陣的數乘](#矩陣的數乘)
11. [矩陣相乘](#矩陣相乘)
12. [矩陣與向量相乘](#矩陣與向量相乘)
13. [單位矩陣](#單位矩陣)
14. [縮放](#縮放)
15. [位移](#位移)
16. [旋轉](#旋轉)
17. [矩陣的組合](#矩陣的組合)
18. [實踐](#實踐)
19. [GLM](#GLM)

## 變換
## 向量
## 向量與標量運算
## 向量取反
## 向量加減

#### 基本概念
- **向量**：一個具有方向和大小（強度或長度）的量。
- **舉例**：藏寶圖的指示「向左走10步」中，「左」是方向，「10步」是向量的長度。
- **維度**：向量可以在任意維度上，通常使用2到4維表示。
- **標量**：標量(Scalar)只是一個數字（或僅有一個分量的向量）

#### 2D 向量
- 向量在2D影像中用箭頭表示，如(x, y)。
- 向量的起始點不同但方向和大小相同，它們是相等的。


#### 向量與位置
- 向量可以從(0, 0, 0)指向某個點，稱為位置向量（Position Vector）。
- 例如：位置向量(3, 5)從(0, 0)指向(3, 5)。

#### 向量運算
- **向量與標量運算**：向量可以與標量進行加減乘除運算，對每個分量分別運算：

  - 注意：標量除向量和標量減向量是未定義的運算。
  - 註：數學上沒有向量與標量相加的運算，但線性代數函式庫（如GLM）支持這種運算。

- **向量取反**：將向量方向逆轉，對每個分量取反：


- **向量加減**：分量相加：

- **向量減法**：等於加上第二個向量的相反向量：
 


## 長度


#### 基本概念
- **向量長度/大小**：可以使用勾股定理（Pythagoras Theorem）計算。
- **向量長度公式**：


#### 單位向量
- **定義**：單位向量的長度為1。
- **標準化**：將任意向量的每個分量除以向量的長度可以得到其單位向量：


## 向量相乘


#### 基本概念
- 向量的普通乘法沒有定義，但有兩種特定的乘法方式：**點乘（Dot Product）** 和 **叉乘（Cross Product）**。

#### 點乘
- **點乘公式**


#### 叉乘
- **定義**：叉乘僅在3D空間中有定義，需要兩個不平行向量作為輸入，產生一個正交於兩個輸入向量的第三個向量。



## 矩陣
## 矩陣的加減
## 矩陣的數乘
## 矩陣相乘
## 矩陣與向量相乘
## 單位矩陣
## 縮放
## 位移
## 旋轉
## 矩陣的組合

## GLM


#### 簡介
- **GLM**：OpenGL Mathematics的縮寫，是一個只需包含頭檔的函式庫，無需連結和編譯。
- **版本注意**：從0.9.9版本起，矩陣類型預設為零矩陣（全0），不是單位矩陣（對角元素為1）。初始化矩陣需使用 `glm::mat4 mat = glm::mat4(1.0f)`。

#### 包含必要的頭檔
```cpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
```

#### 例子 - 向量位移
- **向量位移**：將向量 (1, 0, 0) 位移 (1, 1, 0) 個單位。
```cpp
glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
glm::mat4 trans = glm::mat4(1.0f);
trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
vec = trans * vec;
std::cout << vec.x << vec.y << vec.z << std::endl; // 輸出結果應為 2, 1, 0
```

#### 例子 - 矩形旋轉與縮放
- **矩形旋轉90度和縮放0.5倍**：
```cpp
glm::mat4 trans = glm::mat4(1.0f);
trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
```

#### 將矩陣傳遞給著色器
- **修改頂點著色器**：
```glsl
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}
```

- **在C++程式中傳遞矩陣給著色器**：
```cpp
unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
```
- 這段程式碼首先查詢 `transform` uniform 變數的位址，然後用 `glUniformMatrix4fv` 將矩陣資料傳送給著色器。

#### 旋轉箱子並位移到右下角
- **遊戲循環中的變換更新**：
```cpp
glm::mat4 trans = glm::mat4(1.0f);
trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
```
- 這段程式碼先將箱子圍繞原點旋轉，然後位移到視窗的右下角。


