# Lighting_maps
## 目錄
1. [光照貼圖](#光照貼圖)
2. [漫反射貼圖](#漫反射貼圖)
3. [鏡面光貼圖](#鏡面光貼圖)
4. [採樣鏡面光貼圖](#採樣鏡面光貼圖)






## 光照貼圖

- **引入光照貼圖 (Lighting Maps)：**
  - **漫反射貼圖 (Diffuse Map)：** 控制物體的漫反射分量。
  - **鏡面光貼圖 (Specular Map)：** 控制物體的鏡面光分量。



## 漫反射貼圖
- **漫反射貼圖的概念：**
  - 我們希望為每個片段單獨設定漫反射顏色。
  - 漫反射貼圖 (Diffuse Map) 是一張覆蓋物體的圖像，表現了物體所有的漫反射顏色。
  - 漫反射貼圖類似於紋理，允許我們根據片段位置取得顏色值。

- **使用漫反射貼圖的步驟：**
  1. **準備貼圖：**
     - 使用紋理圖像表示物體的漫反射顏色，例如有鋼邊框的木箱圖像。

  2. **修改 `Material` 結構體：**
     - 將漫反射顏色向量替換為 `sampler2D`。
     - 移除環境光材質顏色向量，因為它通常等於漫反射顏色。

     ```glsl
     struct Material {
         sampler2D diffuse; // 漫反射貼圖
         vec3      specular;
         float     shininess;
     }; 
     ```

  3. **更新片段著色器：**
     - 添加紋理座標的輸入變數。

     ```glsl
     in vec2 TexCoords;
     ```

     - 從紋理中取樣漫反射顏色值。

     ```glsl
     vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
     ```

     - 將環境光材質顏色設定為漫反射材質顏色相同的值。

     ```glsl
     vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
     ```

  4. **更新頂點數據：**
     - 頂點數據現在包含了頂點位置、法向量和紋理座標。

     ```glsl
     layout (location = 0) in vec3 aPos;
     layout (location = 1) in vec3 aNormal;
     layout (location = 2) in vec2 aTexCoords;

     out vec2 TexCoords;

     void main()
     {
         ...
         TexCoords = aTexCoords;
     }
     ```

  5. **更新 VAO 的頂點屬性指針：**
     - 確保頂點屬性指針匹配更新後的頂點數據。

  6. **載入和綁定紋理：**
     - 載入箱子圖像為一個紋理。
     - 將紋理單元賦值到 `material.diffuse` 的 uniform 取樣器。
     - 綁定箱子的紋理到適當的紋理單元。

     ```cpp
     lightingShader.setInt("material.diffuse", 0);
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, diffuseMap);
     ```


## 鏡面光貼圖
- **問題：鏡面高光的表現不正確**
  - 木製物體不應該有強烈的鏡面高光。
  - 鋼製邊框需要顯示適當的鏡面高光。
  - 需要控制不同部分的鏡面光強度。

- **鏡面光貼圖 (Specular Map)：**
  - 使用紋理貼圖來表示物體不同部分的鏡面光強度。
  - 鏡面光貼圖是黑白（或彩色）的紋理，定義了每部分的鏡面光強度。

- **範例與原理：**
  - 鏡面光貼圖的每個像素顏色對應著鏡面光強度。
    - **黑色**表示無鏡面光（`vec3(0.0)`）。
    - **灰色**表示中等鏡面光（`vec3(0.5)`）。
    - **白色**表示強烈鏡面光。
  - 片段著色器中從貼圖取樣顏色值，並乘以光源的鏡面強度來計算鏡面光分量。

- **貼圖內容：**
  - 木頭部分顯示為黑色，代表沒有鏡面高光。
  - 鋼製邊框顯示不同灰度，顯示鏡面光強度的變化。
  - 實際上，木頭有鏡面光，但影響很小，反光度小。


- **實現過程：**
  1. **更新 `Material` 結構體：**
     - 將鏡面光顏色向量替換為 `sampler2D`：

       ```glsl
       struct Material {
           sampler2D diffuse;  // 漫反射貼圖
           sampler2D specular; // 鏡面光貼圖
           float     shininess;
       };
       ```

  2. **片段著色器中取樣鏡面光：**
     - 使用鏡面光貼圖來計算鏡面光分量：

       ```glsl
       vec3 specularColor = texture(material.specular, TexCoords).rgb;
       vec3 specular = light.specular * specularColor * spec;
       ```

  3. **更新頂點數據：**
     - 確保頂點數據包含頂點位置、法向量和紋理座標。

  4. **載入和綁定鏡面光紋理：**
     - 載入鏡面光紋理並綁定到適當的紋理單元：

       ```cpp
       lightingShader.setInt("material.specular", 1);
       glActiveTexture(GL_TEXTURE1);
       glBindTexture(GL_TEXTURE_2D, specularMap);
       ```


## 採樣鏡面光貼圖
- **鏡面光貼圖 (Specular Map)：**
  - 與其他紋理類似，程式碼與漫反射貼圖相似。
  - 正確載入圖像並產生紋理物件。
  - 使用不同的紋理單元來綁定鏡面光貼圖。

- **紋理單元綁定：**
  - 使用 `GL_TEXTURE1` 綁定鏡面光貼圖：

    ```cpp
    lightingShader.setInt("material.specular", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);
    ```

- **更新材質結構體：**
  - 修改 `Material` 結構體，使其接受 `sampler2D` 作為鏡面光分量：

    ```glsl
    struct Material {
        sampler2D diffuse;   // 漫反射貼圖
        sampler2D specular;  // 鏡面光貼圖
        float     shininess;
    };
    ```

- **採樣鏡面光貼圖：**
  - 使用 `texture()` 函數從鏡面光貼圖中取樣：

    ```glsl
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));  
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    FragColor = vec4(ambient + diffuse + specular, 1.0);
    ```

- **控制細節：**
  - 使用鏡面光貼圖可設定物體表面的細節：
    - 哪些部分需要鏡面高光。
    - 不同部位的鏡面光強度。

- **鏡面光貼圖的顏色：**
  - 可使用真正的顏色來設定鏡面光貼圖，不僅控制強度還控制顏色。
  - **注意**：鏡面高光的顏色通常由光源決定，使用顏色可能不夠真實，通常採用黑白貼圖。

