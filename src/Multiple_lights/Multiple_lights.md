# Multiple_lights
## 目錄
1. [多光源](#多光源)
2. [定向光](#定向光)
3. [點光源](#點光源)
4. [合併結果](#合併結果)



## 多光源
- **多光源場景：**
  - 這個場景將包含六個光源：一個類似太陽的定向光、四個分散在場景中的點光源、以及一個手電筒。

- **光源類型：**
  - **定向光 (Directional Light)：** 模擬太陽等遠距離光源，光線方向一致。
  - **點光源 (Point Light)：** 分散在場景中的光源，光線從點源向外輻射。
  - **聚光 (Spotlight)：** 手電筒效果，光線集中在一個特定的方向。

- **GLSL函數的使用：**
  - 為了管理多個光源的計算，我們將光照計算封裝到GLSL函數中。
  - 每種光源都有不同的計算方法，因此為每種光源類型創建一個函數有助於保持程式碼整潔。

- **GLSL函數的結構：**
  - 函數與C語言中的函數類似，包含函數名、回傳值類型等。
  - 每個光源類型（定向光、點光源、聚光）各自擁有一個函數。

- **光照計算流程：**
  - 使用一個單獨的顏色向量來代表片段的最終輸出顏色。
  - 每個光源對片段的貢獻顏色加到輸出顏色向量上，形成最終的輸出顏色。

- **範例結構：**

  ```glsl
  out vec4 FragColor;

  void main()
  {
    // 定義一個輸出顏色值
    vec3 output = vec3(0.0);
    
    // 將定向光的貢獻加到輸出中
    output += calculateDirectionalLight();
    
    // 對所有的點光源也做相同的事情
    for(int i = 0; i < nr_of_point_lights; i++)
      output += calculatePointLight(i);
    
    // 加上聚光的貢獻
    output += calculateSpotLight();

    FragColor = vec4(output, 1.0);
  }
  ```

  - **說明：**
    - `calculateDirectionalLight()`：計算定向光對片段的影響。
    - `calculatePointLight(i)`：對每個點光源進行光照計算。
    - `calculateSpotLight()`：計算聚光對片段的影響。
    - `output`：累加每個光源的貢獻，形成最終顏色。


## 定向光
- **定向光函數定義：**
  - 在片段著色器中，定義函數計算定向光對片段的貢獻。
  - 函數接受一些參數並計算出定向光照的顏色。

- **定向光的必要變數：**
  - 將定向光所需的變數儲存在 `DirLight` 結構體中。
  - 將 `DirLight` 結構體定義為 `uniform`，在上一節中介紹過：

    ```glsl
    struct DirLight {
        vec3 direction;  // 光的方向
        vec3 ambient;    // 環境光分量
        vec3 diffuse;    // 漫反射光分量
        vec3 specular;   // 鏡面光分量
    };  
    uniform DirLight dirLight;
    ```

- **函數原型：**
  - 定義一個函數原型 `CalcDirLight`，用於計算定向光的光照效果：

    ```glsl
    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
    ```

  - **注意：** 在呼叫函數之前，需要在 `main` 函數上方定義函數原型。

- **函數參數：**
  - 函數接受以下參數：
    - `DirLight light`：定向光的結構體。
    - `vec3 normal`：片段的法向量。
    - `vec3 viewDir`：觀察方向向量。

- **定向光計算：**
  - 函數內部的計算使用了上一節學到的光照公式：

    ```glsl
    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
    {
        vec3 lightDir = normalize(-light.direction);  // 計算光的方向向量
        // 漫反射著色
        float diff = max(dot(normal, lightDir), 0.0);  // 計算漫反射系數
        // 鏡面光著色
        vec3 reflectDir = reflect(-lightDir, normal);  // 計算反射光方向
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  // 計算鏡面反射系數
        // 合併結果
        vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));  // 環境光貢獻
        vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));  // 漫反射貢獻
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));  // 鏡面光貢獻
        return (ambient + diffuse + specular);  // 返回最終顏色
    }
    ```

  - **過程說明：**
    - `lightDir`：計算光源的方向向量。
    - `diff`：計算法向量和光線方向的點積，得到漫反射係數。
    - `reflectDir`：計算光線的反射方向。
    - `spec`：計算視線方向和反射方向的點積，得到鏡面反射係數。
    - 計算 `ambient`、`diffuse`、`specular` 分量，最終返回合併後的顏色。

- **總結：**
  - 使用 `CalcDirLight` 函數計算定向光的光照效果。
  - 環境光、漫反射光和鏡面光的貢獻合併為單一顏色向量並返回。
  - 通過這樣的封裝，讓光照計算更加模組化和清晰。

## 點光源
- **點光源函數定義：**
  - 和定向光類似，我們需要定義一個用於計算點光源對片段貢獻的函數。
  - 包含衰減計算，以模擬光強度隨距離的減弱。

- **點光源的必要變數：**
  - 定義 `PointLight` 結構體，包含所有點光源所需的變數：

    ```glsl
    struct PointLight {
        vec3 position;    // 光源位置

        float constant;   // 衰減常數項
        float linear;     // 衰減一次項
        float quadratic;  // 衰減二次項

        vec3 ambient;     // 環境光分量
        vec3 diffuse;     // 漫反射光分量
        vec3 specular;    // 鏡面光分量
    };  
    ```

- **多光源設置：**
  - 使用預處理指令定義場景中的點光源數量：

    ```glsl
    #define NR_POINT_LIGHTS 4
    ```

  - 建立一個 `PointLight` 結構體數組：

    ```glsl
    uniform PointLight pointLights[NR_POINT_LIGHTS];
    ```

  - **說明：** 
    - `NR_POINT_LIGHTS` 是場景中點光源的數量。
    - `pointLights` 數組用於儲存每個點光源的屬性。

- **點光源函數原型：**
  - 定義計算點光源光照效果的函數原型：

    ```glsl
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
    ```

  - **參數說明：**
    - `PointLight light`：點光源的結構體。
    - `vec3 normal`：片段的法向量。
    - `vec3 fragPos`：片段的位置。
    - `vec3 viewDir`：觀察方向向量。

- **點光源計算：**
  - 在函數中計算點光源對片段的顏色貢獻：

    ```glsl
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
    {
        vec3 lightDir = normalize(light.position - fragPos);  // 計算光線方向
        // 漫反射著色
        float diff = max(dot(normal, lightDir), 0.0);  // 計算漫反射係數
        // 鏡面光著色
        vec3 reflectDir = reflect(-lightDir, normal);  // 計算反射光方向
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  // 計算鏡面反射係數
        // 衰減
        float distance    = length(light.position - fragPos);  // 計算光源到片段的距離
        float attenuation = 1.0 / (light.constant + light.linear * distance + 
                     light.quadratic * (distance * distance));  // 計算衰減因子
        // 合併結果
        vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));  // 環境光貢獻
        vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));  // 漫反射貢獻
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));  // 鏡面光貢獻
        ambient  *= attenuation;  // 衰減環境光
        diffuse  *= attenuation;  // 衰減漫反射光
        specular *= attenuation;  // 衰減鏡面光
        return (ambient + diffuse + specular);  // 返回最終顏色
    }
    ```

  - **計算步驟：**
    - `lightDir`：計算光源到片段的方向。
    - `diff`：計算法向量和光線方向的點積，得到漫反射係數。
    - `reflectDir`：計算光線的反射方向。
    - `spec`：計算視線方向和反射方向的點積，得到鏡面反射係數。
    - `attenuation`：計算衰減因子，考慮距離的影響。
    - 計算 `ambient`、`diffuse`、`specular` 分量，考慮衰減後合併並返回。

- **使用函數計算多個點光源：**
  - 在 `main` 函數中，使用循環遍歷點光源數組，對每個點光源調用 `CalcPointLight` 函數：

    ```glsl
    vec3 result = vec3(0.0);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLights[i], normal, FragPos, viewDir);
    }
    ```

  - **優點：**
    - 通過封裝計算過程，我們可以輕鬆地處理多個點光源。
    - 避免了重複程式碼。

## 合併結果
- **合併光源計算：**
  - 我們已經定義了計算定向光和點光源的函數，現在可以將它們整合到 `main` 函數中。

- **`main` 函數結構：**
  - 計算法向量和視線方向。
  - 執行三個階段的光照計算：
    1. **定向光照計算**
    2. **點光源計算**
    3. **聚光計算**

    ```glsl
    void main()
    {
        // 屬性
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);

        // 第一階段：定向光照
        vec3 result = CalcDirLight(dirLight, norm, viewDir);

        // 第二階段：點光源
        for(int i = 0; i < NR_POINT_LIGHTS; i++)
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    

        // 第三階段：聚光
        // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    

        FragColor = vec4(result, 1.0);
    }
    ```

  - **說明：**
    - 使用迴圈遍歷所有點光源，計算並累加其對最終顏色的貢獻。
    - 每個光源的貢獻被累加到最終的輸出顏色中。

- **光源函數優化：**
  - 每種光源函數中有許多重複的計算，存在優化空間。
  - 可以將重複計算抽象化，提高效率。

- **設定光源的 `uniform` 值：**
  - 定向光的 `uniform` 設定方法：
    - 直接設定 `DirLight` 結構體的屬性值。

  - 點光源的 `uniform` 設定方法：
    - `pointLights` 是 `PointLight` 的數組，設定 `uniform` 時需指定數組下標。

    ```cpp
    lightingShader.setFloat("pointLights[0].constant", 1.0f);
    ```

    - 每個點光源需手動設定所有 `uniform` 值。

- **點光源位置設定：**
  - 定義一個 `glm::vec3` 陣列來儲存點光源的位置：

    ```cpp
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
    ```

  - 將 `pointLightPositions` 中的位置賦值給 `pointLights` 陣列中的每個 `PointLight` 結構體。

- **多燈光物體渲染：**
  - 確保渲染多個燈光物體，而不是僅僅一個。
  - 為每個燈光物體創建一個不同的模型矩陣，類似於之前處理箱子的方式。



