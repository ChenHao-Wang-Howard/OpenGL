# Lighting_casters
## 目錄
1. [投光物](#投光物)
2. [平行光](#平行光)
3. [點光源](#點光源)
4. [衰減](#衰減)
5. [聚光](#聚光)
6. [手電筒](#手電筒)
7. [平滑/軟化邊緣](#平滑/軟化邊緣)

## 投光物
- **投光物 (Light Casters)：**
  - 投光物是將光投射到物體上的光源。
  - 現實世界中有多種類型的光源，並且每種類型都有不同的表現。

- **光源類型：**
  1. **定向光 (Directional Light)：**
     - 模擬遠處照射來的光源，光線方向平行且均勻。
     - 類似於太陽光，適用於需要均勻光照的場景。
     - 定向光不會隨距離衰減。

  2. **點光源 (Point Light)：**
     - 光源從一個點向四周發射光線，強度隨距離增加而衰減。
     - 常用於模擬燈泡、火炬等點狀光源。
     - 是之前學習的光源的一種擴展形式。

  3. **聚光 (Spotlight)：**
     - 光源形成一個圓錐形的光束，光線集中在特定方向。
     - 適合模擬手電筒、聚光燈等光源。
     - 強度隨距離和角度增大而衰減。

## 平行光
- **定向光 (Directional Light)：**
  - 當光源處於非常遠的位置時，來自光源的光線可以近似為互相平行。
  - 不考慮光源的位置，只考慮光線的方向。

- **定向光的例子：**
  - **太陽**：雖然不是無限遠，但在光照計算中可以視作無限遠，光線近似平行。

- **定向光的特性：**
  - 光線平行，場景中每個物體受到的光照方向一致。
  - 不考慮物體與光源的相對位置。

- **定向光的實現：**
  1. **使用光線方向向量而非位置向量：**
     - 定向光不需要光源位置向量，只需定義光線的方向向量。

     ```glsl
     struct Light {
         vec3 direction;
         vec3 ambient;
         vec3 diffuse;
         vec3 specular;
     };
     ```

  2. **計算光線方向：**
     - 使用光線方向向量計算 `lightDir`，並在計算前對方向向量取反和標準化：

     ```glsl
     vec3 lightDir = normalize(-light.direction);
     ```

     - 注意對方向向量取反，因為計算需要從片段到光源的光線方向。

  3. **光照計算：**
     - `lightDir` 向量可以用於漫反射和鏡面光的計算，其他光照計算保持不變。

- **應用範例：**
  - 使用定向光對多個物體進行光照計算，確保每個物體受到相同方向的光照影響。
  - 使用之前的場景來展示定向光效果。

  ```cpp
  for(unsigned int i = 0; i < 10; i++)
  {
      glm::mat4 model;
      model = glm::translate(model, cubePositions[i]);
      float angle = 20.0f * i;
      model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
      lightingShader.setMat4("model", model);

      glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  ```

  - 設定光源的方向：

  ```cpp
  lightingShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
  ```

- **方向向量的表示：**
  - 使用 `vec4` 表示方向向量時，`w` 分量設為 `0.0`，表示為方向向量。
  - 使用 `vec4` 表示位置向量時，`w` 分量設為 `1.0`，表示為位置向量。

  ```glsl
  vec4 directionVector = vec4(0.2f, 1.0f, 0.3f, 0.0f);
  ```

- **光照類型判斷：**
  - 根據 `w` 分量判斷光照類型，並調整計算方法：

  ```cpp
  if(lightVector.w == 0.0) 
      // 執行定向光照計算

  else if(lightVector.w == 1.0)
      // 根據光源的位置做光照計算

  ```

- **舊版 OpenGL 的光照類型決定：**
  - 舊版 OpenGL 使用 `w` 分量來判斷光源類型（定向光或位置光源），並相應調整光照計算。

## 點光源
- **點光源 (Point Light)：**
  - 點光源是位於場景中某一個位置的光源。
  - 點光源會朝著所有方向發射光線。
  - 光線強度隨著距離增加而衰減。

- **點光源的特性：**
  - 模擬燈泡、火把等點狀光源。
  - 照亮光源附近的區域，而不是整個場景。

- **簡化的點光源問題：**
  - 先前的點光源模擬中，光線沒有衰減，導致整個場景被均勻照亮。
  - 後排物體和前排物體受到同樣強度的光照，缺乏真實感。

- **點光源的衰減：**
  - 在真實場景中，點光源的光線隨距離衰減。
  - 我們希望點光源只照亮附近區域，而不是整個場景。

- **改進點光源的模擬：**
  - 定義一個公式來使光線隨距離衰減。
  - 確保後排物體比前排物體受到的光照更弱。

### 實現點光源的光線衰減

在實現點光源時，我們需要考慮光線隨距離衰減的公式，以模擬更真實的光照效果。

#### 1. 點光源結構體設計

首先，我們設計一個 `Light` 結構體來表示點光源：

```glsl
struct Light {
    vec3 position;  // 點光源的位置
    vec3 ambient;   // 環境光分量
    vec3 diffuse;   // 漫反射光分量
    vec3 specular;  // 鏡面光分量

    float constant; // 常數衰減係數
    float linear;   // 線性衰減係數
    float quadratic;// 二次衰減係數
};
```

- `position`：光源的位置。
- `ambient`、`diffuse`、`specular`：分別控制環境光、漫反射光和鏡面光的影響。
- `constant`、`linear`、`quadratic`：分別是常數、線性和二次衰減係數，用於控制光線的衰減程度。

#### 2. 光照計算中引入衰減公式

在光照計算中，我們需要考慮點光源的衰減：

```glsl
// 計算光線方向
vec3 lightDir = normalize(light.position - FragPos);

// 計算光線距離
float distance = length(light.position - FragPos);

// 計算衰減
float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

// 計算光照分量
vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

// 應用衰減
ambient *= attenuation;
diffuse *= attenuation;
specular *= attenuation;

// 最終顏色
FragColor = vec4(ambient + diffuse + specular, 1.0);
```

- **衰減公式**：使用常數、線性和二次衰減係數計算光線的衰減。
- **應用衰減**：在計算環境光、漫反射光和鏡面光分量後，將它們乘以衰減因子。

#### 3. 在應用中設置點光源

在應用中，我們需要為點光源設置適當的衰減係數和光照屬性：

```cpp
lightingShader.setVec3("light.position", lightPosition);
lightingShader.setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
lightingShader.setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

// 設置衰減係數
lightingShader.setFloat("light.constant", 1.0f);
lightingShader.setFloat("light.linear", 0.09f);
lightingShader.setFloat("light.quadratic", 0.032f);
```



## 衰減
- **光衰減 (Attenuation)：**
  - 隨著光線距離的增加，光的強度逐漸減弱，稱為光衰減。
  - 實現衰減的方法是使用數學公式來計算光強度隨距離的變化。

- **線性衰減的問題：**
  - 簡單的線性衰減公式看起來不夠真實。
  - 在現實世界中，光在近距離時亮度很高，然後迅速衰減，最後逐漸變弱。

- **使用更真實的衰減公式：**


- **衰減效果的描述：**
  - 近距離時，光線明亮且衰減迅速。
  - 隨著距離增加，光強度逐漸變弱。
  - 在遠距離時，光強度幾乎不再變化。

- **衰減參數的選擇：**
  - 根據場景和需求選擇適當的衰減參數。
  - 下表顯示了不同距離下的衰減參數，提供了常數項、線性項和二次項的建議值：

  | 距離 | 常數項  | 一次項  | 二次項  |
  |---|---|---|---|
  | 7 | 1.0 | 0.7 | 1.8 |
  | 13 | 1.0 | 0.35 | 0.44 |
  | 20 | 1.0 | 0.22 | 0.20 |
  | 32 | 1.0 | 0.14 | 0.07 |
  | 50 | 1.0 | 0.09 | 0.032 |
  | 65 | 1.0 | 0.07 | 0.017 |
  | 100 | 1.0 | 0.045 | 0.0075 |
  | 160 | 1.0 | 0.027 | 0.0028 |
  | 200 | 1.0 | 0.022 | 0.0019 |
  | 325 | 1.0 | 0.014 | 0.0007 |
  | 600 | 1.0 | 0.007 | 0.0002 |
  | 3250 | 1.0 | 0.0014 | 0.000007 |

- **衰減的實現：**
  1. **定義光源結構體：**
     - 在 `Light` 結構體中添加常數項、線性項和二次項。

     ```glsl
     struct Light {
         vec3 position;
         vec3 ambient;
         vec3 diffuse;
         vec3 specular;

         float constant;
         float linear;
         float quadratic;
     };
     ```

  2. **設置衰減參數：**
     - 在應用中設置光源的衰減參數，根據場景需求選擇合適的值。

     ```cpp
     lightingShader.setFloat("light.constant", 1.0f);
     lightingShader.setFloat("light.linear", 0.09f);
     lightingShader.setFloat("light.quadratic", 0.032f);
     ```

  3. **計算衰減值：**
     - 在片段著色器中計算衰減值，將其應用到光照計算中。

     ```glsl
     float distance    = length(light.position - FragPos);
     float attenuation = 1.0 / (light.constant + light.linear * distance + 
                                light.quadratic * (distance * distance));
     ```

  4. **應用衰減到光照分量：**
     - 將衰減值乘以環境光、漫反射光和鏡面光的顏色。

     ```glsl
     ambient  *= attenuation; 
     diffuse  *= attenuation;
     specular *= attenuation;
     ```




## 聚光
## 手電筒

### 概念
- **聚光 (Spotlight)：** 
  - 是一種光束形狀的光源，光線集中在一個特定的方向。
  - 典型應用是手電筒，位於觀察者位置，並指向玩家視角的正前方。
  - 聚光需要持續更新其位置和方向，以保持與玩家視角一致。

### 所需的屬性
- **聚光的必要屬性：**
  - **位置向量 (Position Vector)：** 用於計算光的方向。
  - **方向向量 (Direction Vector)：** 聚光指向的方向。
  - **切光角 (Cut-Off Angle)：** 決定光束的範圍。

### 實現步驟
1. **定義 `Light` 結構體：**
   - 在 `Light` 結構體中包含聚光需要的屬性：

   ```glsl
   struct Light {
       vec3  position;   // 聚光的位置
       vec3  direction;  // 聚光的方向
       float cutOff;     // 聚光的切光角
       ...
   };
   ```

2. **設置聚光屬性：**
   - 在應用程序中，設置聚光的位置、方向和切光角：

   ```cpp
   lightingShader.setVec3("light.position", camera.Position);  // 聚光的位置為玩家的位置
   lightingShader.setVec3("light.direction", camera.Front);    // 聚光的方向為玩家視角的方向
   lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));  // 使用切光角的餘弦值
   ```

   - **注意：** 使用 `glm::cos(glm::radians(12.5f))` 將切光角轉換為餘弦值，避免在著色器中進行昂貴的反餘弦計算。

3. **計算光照範圍：**
   - 在片段著色器中，計算光線方向和聚光方向之間的角度（使用點積）：

   ```glsl
   float theta = dot(lightDir, normalize(-light.direction));  // 計算光線與聚光方向的夾角
   ```

   - **解釋：**
     - `lightDir` 是從片段到光源的方向向量。
     - `-light.direction` 是從光源指向片段的方向向量。
     - 需要對向量進行標準化以確保點積結果正確。

4. **判斷片段是否在聚光內部：**
   - 使用條件判斷片段是否在聚光的光束內：

   ```glsl
   if(theta > light.cutOff) 
   {       
       // 執行光照計算
   }
   else  
   {
       // 否則，使用環境光，讓場景在聚光之外時不至於完全黑暗
       color = vec4(light.ambient * vec3(texture(material.diffuse, TexCoords)), 1.0);
   }
   ```

   - **注意：** 使用 `>` 符號而非 `<` 符號，因為餘弦值越大，角度越小。
     - 0度的餘弦值為 1.0。
     - 90度的餘弦值為 0.0。

5. **解釋餘弦值比較：**
   - 切光角設置為 `12.5` 的餘弦值，約等於 `0.9978`。
   - 當 `theta` 大於切光值時，片段位於聚光內部，光照生效。

### 小結
- 聚光是一種特殊的光源，通過方向和切光角來控制光照範圍。
- 使用餘弦值進行角度比較，避免昂貴的反餘弦計算。
- 實現手電筒效果需要持續更新聚光的位置和方向，以保持與玩家視角一致。

## 平滑/軟化邊緣


為了使聚光看起來更加自然和逼真，我們可以通過引入內圓錐和外圓錐來平滑聚光的邊緣。

- **內圓錐 (Inner Cone)：**
  - 是聚光的核心部分，光線在此範圍內保持最大強度。
  - 在內圓錐內的光線會以滿強度照亮物體。

- **外圓錐 (Outer Cone)：**
  - 是聚光的擴展部分，光線在此範圍內逐漸減弱，直到外圓錐的邊界。
  - 在內圓錐和外圓錐之間，光強度根據距離進行插值。



### 實現步驟

1. **定義 `Light` 結構體：**
   - 在 `Light` 結構體中添加外切光角的屬性：

   ```glsl
   struct Light {
       vec3  position;   // 聚光的位置
       vec3  direction;  // 聚光的方向
       float cutOff;     // 內圓錐切光角
       float outerCutOff; // 外圓錐切光角
       ...
   };
   ```

2. **設置聚光屬性：**
   - 在應用程序中，設置聚光的內外切光角：

   ```cpp
   lightingShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
   lightingShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
   ```

   - 使用餘弦值進行比較，可以避免昂貴的反餘弦計算。

3. **計算光強度：**
   - 在片段著色器中，計算光強度 \(I\)：

   ```glsl
   float theta     = dot(lightDir, normalize(-light.direction));
   float epsilon   = light.cutOff - light.outerCutOff;
   float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
   ```

   - **說明：**
     - `lightDir` 是從片段到光源的方向向量。
     - `-light.direction` 是從光源指向片段的方向向量。
     - 使用 `clamp` 函數將強度約束在 [0.0, 1.0] 之間。

4. **應用光強度：**
   - 使用計算出的強度值來調整光照效果：

   ```glsl
   diffuse  *= intensity;  // 調整漫反射光強度
   specular *= intensity;  // 調整鏡面光強度
   ```

   - 不影響環境光，使場景始終保持一點光照。

### 小結

- 透過引入內外圓錐和強度插值，我們可以實現聚光的平滑邊緣效果。
- 使用餘弦值進行角度比較，避免了昂貴的反餘弦計算。
- 實現了更自然的光照效果，使得聚光在場景中更加真實。
