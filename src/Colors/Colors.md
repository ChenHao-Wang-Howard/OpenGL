# Colors
## 目錄
1. [顏色](#顏色)
2. [創建一個光照場景](#創建一個光照場景)
## 顏色

### 顏色由R, G, B組成
EX:要取得一個珊瑚紅(Coral)色
```cpp
glm::vec3 coral(1.0f, 0.5f, 0.31f);
```

### 定義：物體的顏色為物體從一個光源反射各個顏色分量的大小
將兩個顏色向量作分量相乘，結果就是最終的顏色向量
EX: 
```cpp
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor; // = (1.0f, 0.5f, 0.31f);
```
## 創建一個光照場景


1. **選擇物體：**
   - 使用立方體作為光照對象（即立方體箱子）。
   - 使用另一個立方體表示光源的位置。

2. **頂點緩衝物件(VBO)：**
   - 填充頂點緩衝物件並設置頂點屬性指針。

3. **頂點著色器：**
   - 繪製箱子的簡化版頂點著色器代碼：
     ```glsl
     #version 330 core
     layout (location = 0) in vec3 aPos;

     uniform mat4 model;
     uniform mat4 view;
     uniform mat4 projection;

     void main()
     {
         gl_Position = projection * view * model * vec4(aPos, 1.0);
     }
     ```
   - 確保頂點資料與屬性指標與著色器一致。

4. **創建燈的VAO：**
   - 創建一個專用的VAO給光源，以避免頻繁修改頂點數據影響燈的位置。
   - 代碼範例：
     ```cpp
     unsigned int lightVAO;
     glGenVertexArrays(1, &lightVAO);
     glBindVertexArray(lightVAO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);
     ```

5. **片段著色器：**
   - 定義物體和光源顏色的片段著色器：
     ```glsl
     #version 330 core
     out vec4 FragColor;

     uniform vec3 objectColor;
     uniform vec3 lightColor;

     void main()
     {
         FragColor = vec4(lightColor * objectColor, 1.0);
     }
     ```
   - 設置顏色：
     ```cpp
     lightingShader.use();
     lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
     lightingShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
     ```

6. **燈的著色器：**
   - 創建一個專用的片段著色器，確保燈的顏色不受影響：
     ```glsl
     #version 330 core
     out vec4 FragColor;

     void main()
     {
         FragColor = vec4(1.0); // 常量白色
     }
     ```

7. **燈的位置：**
   - 設置光源位置和縮放：
     ```cpp
     glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
     model = glm::mat4();
     model = glm::translate(model, lightPos);
     model = glm::scale(model, glm::vec3(0.2f));
     ```

8. **繪製燈立方體：**
   - 使用燈的著色器繪製：
     ```cpp
     lampShader.use();
     // 設置模型、視圖和投影矩陣
     ...
     glBindVertexArray(lightVAO);
     glDrawArrays(GL_TRIANGLES, 0, 36);
     ```
