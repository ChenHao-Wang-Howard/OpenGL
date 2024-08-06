# Materials
## 目錄
1. [材質](#材質)
2. [設定材質](#設定材質)
3. [光的屬性](#光的屬性)
4. [不同的光源顏色](#不同的光源顏色)






## 材質

- **材質屬性 (Material Properties)：**
  - 定義物體和光的顏色。
  - 結合環境光、漫反射光和鏡面光來決定物體的視覺效果。
  - 材質顏色 (Material Color) 分為三個光照分量：
    - **環境光照 (Ambient Lighting)：** 定義表面在環境光下反射的顏色，通常與表面顏色相同。
    - **漫反射光照 (Diffuse Lighting)：** 定義表面在漫反射光下的顏色。
    - **鏡面光照 (Specular Lighting)：** 定義表面的鏡面高光顏色，可能反映特定表面的顏色。
  - **反光度 (Shininess)：** 影響鏡面高光的散射/半徑。

- **材質結構體 (Material Struct)：**
  - 在片段著色器中使用結構體來儲存物體的材質屬性。
  - 結構體定義：
    ```glsl
    #version 330 core
    struct Material {
        vec3 ambient;   // 環境光照顏色
        vec3 diffuse;   // 漫反射光照顏色
        vec3 specular;  // 鏡面光照顏色
        float shininess; // 反光度
    };

    uniform Material material;
    ```


## 設定材質

在片段著色器中，我們建立了一個 `Material` 結構體的 `uniform`，並更新了光照計算以使用新的材質屬性。

#### 更新片段著色器的光照計算

- **環境光照 (Ambient Lighting)：**
  ```glsl
  vec3 ambient = lightColor * material.ambient;
  ```
  - 使用材質的 `ambient` 屬性計算環境光顏色。

- **漫反射光照 (Diffuse Lighting)：**
  ```glsl
  vec3 norm = normalize(Normal);
  vec3 lightDir = normalize(lightPos - FragPos);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = lightColor * (diff * material.diffuse);
  ```
  - 計算法向量與光源方向的點乘。
  - 使用材質的 `diffuse` 屬性計算漫反射顏色。

- **鏡面光照 (Specular Lighting)：**
  ```glsl
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
  vec3 specular = lightColor * (spec * material.specular);
  ```
  - 計算反射方向和視線方向的點乘。
  - 使用材質的 `specular` 屬性和 `shininess` 屬性計算鏡面光顏色。

- **總合結果：**
  ```glsl
  vec3 result = ambient + diffuse + specular;
  FragColor = vec4(result, 1.0);
  ```

#### 設定材質屬性

透過設定適當的 `uniform`，我們可以在應用中控制物體的材質。`GLSL` 中的結構體只是充當 `uniform` 變數的命名空間，所以需要逐一設定結構體中的每個屬性：

```cpp
lightingShader.setVec3("material.ambient",  1.0f, 0.5f, 0.31f);
lightingShader.setVec3("material.diffuse",  1.0f, 0.5f, 0.31f);
lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
lightingShader.setFloat("material.shininess", 32.0f);
```

- **設定解釋：**
  - 將 **環境光** 和 **漫反射** 分量設為物體的目標顏色。
  - **鏡面分量** 設為中等亮度，不過於強烈。
  - **反光度** 設定為 32，控制高光的散射範圍。


## 光的屬性
- **物體過亮原因：**
  - 環境光、漫反射光、鏡面光對所有光源均完全反射。
  - 需對每種光照分量單獨設置強度。

- **設定光照分量強度：**
  - 每個光照分量（環境光、漫反射、鏡面光）需單獨指定強度向量。
  - 例：假設 `lightColor = vec3(1.0)`：
    ```glsl
    vec3 ambient  = vec3(1.0) * material.ambient;
    vec3 diffuse  = vec3(1.0) * (diff * material.diffuse);
    vec3 specular = vec3(1.0) * (spec * material.specular);
    ```

- **調整環境光強度：**
  - 環境光不應該對顏色有過大影響，需降低環境光強度。
  - 設定環境光強度為較小值：
    ```glsl
    vec3 ambient = vec3(0.1) * material.ambient;
    ```

- **光源結構體：**
  - 創建光源結構體，儲存光照屬性。
  - 包含光源位置及各光照分量的強度。
  - 結構體定義：
    ```glsl
    struct Light {
        vec3 position;
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
    };
    
    uniform Light light;
    ```

- **設定光照屬性：**
  - 環境光：通常設為較低強度，以免過度主導顏色。
  - 漫反射光：設為希望的光源顏色，通常較亮。
  - 鏡面光：設為 `vec3(1.0)`，以最大強度發光。

- **更新片段著色器：**
  - 使用光源結構體中的屬性來計算光照：
    ```glsl
    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse  = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    ```

- **在應用中設定光照強度：**
  ```cpp
  lightingShader.setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
  lightingShader.setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); // 调暗光照以搭配场景
  lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
  ```

- **總結：**
  - 為光照分量單獨設置強度，可以有效控制物體的光照效果，避免過亮或不自然的結果。


## 不同的光源顏色
- **光源顏色影響：**
  - 不同光源顏色影響物體的最終顏色輸出。
  - 光照顏色直接影響物體能反射的顏色。

- **動態改變光源顏色：**
  - 可以通過調整光源顏色來產生有趣的效果。
  - 利用 `sin` 函數和 `glfwGetTime` 改變光源顏色，讓其隨時間變化。

- **程式碼示例：**
  ```cpp
  glm::vec3 lightColor;
  lightColor.x = sin(glfwGetTime() * 2.0f);
  lightColor.y = sin(glfwGetTime() * 0.7f);
  lightColor.z = sin(glfwGetTime() * 1.3f);

  glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // 降低影响
  glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响

  lightingShader.setVec3("light.ambient", ambientColor);
  lightingShader.setVec3("light.diffuse", diffuseColor);
  ```

- **程式碼說明：**
  - **光源顏色**：使用 `sin` 函數讓 `x`, `y`, `z` 分量隨時間波動。
  - **漫反射顏色**：將光源顏色乘以 `0.5f`，降低影響。
  - **環境光顏色**：將漫反射顏色乘以 `0.2f`，進一步降低影響。
