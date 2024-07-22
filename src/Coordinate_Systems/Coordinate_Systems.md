### 座標系統 - 筆記

#### 概述
- **標準化設備座標 (NDC)**：OpenGL希望每個頂點的x, y, z座標都在-1.0到1.0之間，超出範圍的頂點將不可見。
- **轉換過程**：局部空間 -> 世界空間 -> 觀察空間 -> 裁剪空間 -> 螢幕空間。

#### 座標系統
1. **局部空間 (Local Space/物件空間)**：物體相對於自己的原點的座標。
2. **世界空間 (World Space)**：物體相對於世界原點的座標，經由模型矩陣轉換。
3. **觀察空間 (View Space/視覺空間)**：從攝影機的角度來觀察物體的座標，經由觀察矩陣轉換。
4. **裁剪空間 (Clip Space)**：將座標轉換到-1.0到1.0範圍內，經由投影矩陣轉換。
5. **螢幕空間 (Screen Space)**：最終映射到螢幕上的座標。

#### 轉換矩陣
- **模型矩陣 (Model Matrix)**：將局部座標轉換為世界座標。
- **觀察矩陣 (View Matrix)**：將世界座標轉換為觀察空間座標。
- **投影矩陣 (Projection Matrix)**：將觀察座標轉換為裁剪空間座標。

#### 投影矩陣
1. **正射投影 (Orthographic Projection)**：定義一個立方體的平截頭箱，適用於2D渲染和工程應用。
   ```cpp
   glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
   ```
2. **透視投影 (Perspective Projection)**：模擬真實世界中的透視效果，遠處物體看起來更小。
   ```cpp
   glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
   ```

#### 右手座標系
- OpenGL使用右手座標系：正x軸在右，正y軸向上，正z軸朝向後方。

#### 例子 - 3D繪圖
- **模型矩陣**：將平面旋轉，使其放在地板上。
  ```cpp
  glm::mat4 model;
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  ```

- **觀察矩陣**：將攝影機向後移動，以便看到物體。
  ```cpp
  glm::mat4 view;
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  ```

- **投影矩陣**：定義透視投影。
  ```cpp
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
  ```

- **頂點著色器**：宣告變換矩陣並應用。
  ```glsl
  #version 330 core
  layout (location = 0) in vec3 aPos;
  ...
  uniform mat4 model;
  uniform mat4 view;
  uniform mat4 projection;

  void main()
  {
      gl_Position = projection * view * model * vec4(aPos, 1.0);
      ...
  }
  ```

- **C++ 程式碼**：傳遞矩陣給著色器。
  ```cpp
  int modelLoc = glGetUniformLocation(ourShader.ID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  // 觀察矩陣和投影矩陣類似
  ```

#### Z緩衝
- **啟用深度測試**：
  ```cpp
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ```

#### 更多的立方體
- **定義多個立方體位置**：
  ```cpp
  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
  };
  ```

- **渲染多個立方體**：
  ```cpp
  glBindVertexArray(VAO);
  for(unsigned int i = 0; i < 10; i++)
  {
    glm::mat4 model;
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i; 
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    ourShader.setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  ```

