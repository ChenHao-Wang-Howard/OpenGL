# Basic Lighting
## 目錄
1. [基礎光照](#基礎光照)
2. [環境光照](#環境光照)
3. [漫反射光照](#漫反射光照)
4. [法向量](#法向量)
5. [計算漫反射光照](#計算漫反射光照)
6. [最後一件事：法向量轉換與法線矩陣](#最後一件事：法向量轉換與法線矩陣)
7. [鏡面光照](#鏡面光照)

## 基礎光照
- 環境光照(Ambient Lighting)：即使在黑暗的情況下，世界上通常仍然有一些光亮（月亮、遠處的光），所以物體幾乎永遠不會是完全黑暗的。為了模擬這個，我們會使用一個環境光照常數，它永遠會給物體一些顏色。
- 漫反射光照(Diffuse Lighting)：模擬光源對物體的方向性影響(Directional Impact)。它是風氏光照模型中視覺上最顯著的分量。物體的某一部分越是正對著光源，它就會越亮。
- 鏡面光照(Specular Lighting)：模擬有光澤物體上面出現的亮點。鏡面光照的顏色比物體的顏色會比較傾向光的顏色。
## 環境光照

**背景概念：**
- **光源特性**：光通常來自多個分散的光源，會發散並反彈到較遠的點，對物體產生間接影響。
- **全域照明**：這種考慮反射和散射的演算法雖然精確，但過於複雜且資源耗費大。

**簡化模型：環境光照**
- 使用環境光照模擬光的散射效果，作為全域照明的簡化版本。
- 即使場景中沒有直接光源，環境光照仍讓物體看起來有些許光亮。

**實作步驟：**
1. **設定環境光強度**：
   - 定義環境光強度（`ambientStrength`），用來控制環境光的影響程度。

2. **計算環境光**：
   - 環境光顏色計算：將光源顏色乘以環境強度常數。
   - 最終片段顏色：將環境光顏色與物體顏色相乘，並設定為片段顏色。

3. **著色器：**
   ```glsl
   void main()
   {
       float ambientStrength = 0.1; // 環境光強度
       vec3 ambient = ambientStrength * lightColor; // 環境光顏色

       vec3 result = ambient * objectColor; // 最終片段顏色
       FragColor = vec4(result, 1.0); // 設定片段顏色
   }
   ```

**結果：**
- 運行程式後，物體不再完全黑暗，而是顯示出環境光照的效果。
- **注意**：光源立方體不受影響，因為使用了不同的著色器。


## 漫反射光照
**計算漫反射光照需要什麼？**
- 法向量：一個垂直於頂點表面的向量。
- 定向的光線：作為光源的位置與片段的位置之間向量差的方向向量。為了計算這個光線，我們需要光的位置向量和片段的位置向量。
## 法向量
**概念：**
- **法向量 (Normal Vector)**：垂直於頂點表面的單位向量。因為單個頂點無法定義表面，所以使用周圍的頂點計算出該頂點的法向量。

**方法：**
- **手動添加法向量**：對於簡單的3D形狀如立方體，可以手動添加法向量至頂點數據中。
- **叉乘法計算**：也可以使用叉乘計算每個面的法向量。

**頂點著色器更新：**
- 為每個頂點添加法向量，並更新頂點著色器以接收這些數據。

```glsl
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
```

**頂點屬性指標更新：**
- 更新頂點屬性指標以適應包含法向量的新頂點陣列。

```cpp
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

- **注意**：燈的著色器不使用法向量，但共享同一頂點數據，因此不需修改燈的著色器或屬性配置。

**效率考量：**
- 儘管燈的著色器不使用法向量，直接利用箱子的頂點數據存儲在GPU記憶體中的資料更為高效，避免額外的VBO分配。

**傳遞法向量到片段著色器：**
- 在頂點著色器中，傳遞法向量至片段著色器。

```glsl
out vec3 Normal;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = aNormal; // 傳遞法向量
}
```

**片段著色器：**
- 定義相應的輸入變數以接收法向量。

```glsl
in vec3 Normal;
```

## 計算漫反射光照
**目標：**
- 使用法向量、光源位置和片段位置計算物體的漫反射光照效果。

**步驟：**

1. **光源位置：**
   - 在片段著色器中宣告光源位置為 `uniform` 變數：
     ```glsl
     uniform vec3 lightPos;
     ```
   - 更新 `uniform`：
     ```cpp
     lightingShader.setVec3("lightPos", lightPos);
     ```

2. **片段位置：**
   - 在世界空間中進行光照計算，需要片段的世界空間位置。
   - 在頂點著色器中計算頂點的世界空間座標：
     ```glsl
     out vec3 FragPos;  
     out vec3 Normal;

     void main()
     {
         gl_Position = projection * view * model * vec4(aPos, 1.0);
         FragPos = vec3(model * vec4(aPos, 1.0)); // 世界空間座標
         Normal = aNormal;
     }
     ```

3. **片段著色器更新：**
   - 在片段著色器中加入對應的輸入變數：
     ```glsl
     in vec3 FragPos;
     in vec3 Normal;
     ```

4. **計算方向向量：**
   - 計算光源與片段位置之間的方向向量，並標準化向量：
     ```glsl
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(lightPos - FragPos);
     ```

5. **計算漫反射光照：**
   - 對 `norm` 和 `lightDir` 進行點乘，計算漫反射影響。
   - 使用 `max` 函數避免負數值：
     ```glsl
     float diff = max(dot(norm, lightDir), 0.0);
     vec3 diffuse = diff * lightColor; // 漫反射分量
     ```

6. **計算片段最終顏色：**
   - 將環境光和漫反射光相加，並乘以物體顏色：
     ```glsl
     vec3 result = (ambient + diffuse) * objectColor;
     FragColor = vec4(result, 1.0); // 最終片段顏色
     ```

**注意事項：**
- **標準化**：確保所有涉及計算的向量為單位向量，以簡化計算。
- **避免負數光照**：使用 `max` 函數確保漫反射不會變成負數，負數顏色的光線是沒有意義的。

## 最後一件事：法向量轉換與法線矩陣


**問題背景：**
- 法向量需轉換到世界空間座標以進行光照計算。
- 法向量只代表方向，無特定位置，不受位移影響。
- 不能簡單地用模型矩陣乘法向量，需去除位移部分。

**不等比縮放的影響：**
- 不等比縮放會破壞法向量的垂直性，影響光照效果。
- 等比縮放僅改變法向量的長度，通過標準化可修復。

**解決方案：法線矩陣 (Normal Matrix)**
- **法線矩陣定義**：模型矩陣左上角3x3部分的逆矩陣的轉置矩陣。
- **作用**：修正不等比縮放對法向量的影響。

**在頂點著色器中計算法線矩陣：**

```glsl
Normal = mat3(transpose(inverse(model))) * aNormal;
```

- **函數解釋：**
  - `inverse(matrix)`：計算矩陣的逆矩陣。
  - `transpose(matrix)`：計算矩陣的轉置矩陣。
  - `mat3()`：將4x4矩陣強制轉換為3x3矩陣，去除位移屬性。

**注意事項：**
- **性能考量**：矩陣求逆運算在著色器中開銷較大。
  - **建議**：在CPU上計算法線矩陣，然後通過 `uniform` 傳遞給著色器。
  
**實作步驟：**

1. **在頂點著色器中計算法向量的世界空間座標：**

   ```glsl
   out vec3 Normal;

   void main()
   {
       gl_Position = projection * view * model * vec4(aPos, 1.0);
       FragPos = vec3(model * vec4(aPos, 1.0));
       Normal = mat3(transpose(inverse(model))) * aNormal; // 使用法線矩陣
   }
   ```

2. **在片段著色器中接收法向量：**

   ```glsl
   in vec3 Normal;
   ```

**使用法線矩陣的必要性：**
- 當對物體進行不等比縮放時，必須使用法線矩陣來保持法向量的正確性。
- 當沒有縮放或只有等比縮放時，使用模型矩陣乘以法線是可行的，但在不等比縮放情況下需使用法線矩陣。


## 鏡面光照

**目標：**
- 完成風氏光照模型的實現，通過引入鏡面高光 (Specular Highlight) 來提升光照效果。

**概念：**
- **鏡面光照**：與漫反射光照類似，但它還依賴於觀察方向，決定於表面的反射特性。
- **反射向量**：通過法向量翻折入射光的方向來計算，鏡面高光在觀察方向與反射向量夾角最小時效果最強。

**觀察向量：**
- 使用觀察者的世界空間位置（攝影機位置）和片段的位置來計算觀察向量。

**步驟：**

1. **在片段著色器中引入觀察者位置：**
   - 定義一個 `uniform` 變數來獲得觀察者（攝影機）的世界空間位置：
     ```glsl
     uniform vec3 viewPos;
     ```

   - 在渲染循環中傳遞攝影機的位置向量：
     ```cpp
     lightingShader.setVec3("viewPos", camera.Position);
     ```

2. **定義鏡面強度：**
   - 設定鏡面強度以控制鏡面高光的影響：
     ```glsl
     float specularStrength = 0.5;
     ```

3. **計算視線和反射方向向量：**
   - 計算視線方向向量和反射方向向量：
     ```glsl
     vec3 viewDir = normalize(viewPos - FragPos);
     vec3 reflectDir = reflect(-lightDir, norm);
     ```

   - **注意**：`reflect` 函數要求入射光方向是從光源指向片段位置，因此需要取反 `lightDir`。

4. **計算鏡面光照：**
   - 計算視線方向與反射方向的點乘，並取其冪次方得到鏡面強度：
     ```glsl
     float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
     vec3 specular = specularStrength * spec * lightColor;
     ```

   - **高光的反光度 (Shininess)**：設為32，控制反射的強度和高光點的大小。

5. **計算最終片段顏色：**
   - 將環境光、漫反射光和鏡面光相加，並乘以物體顏色得到最終顏色：
     ```glsl
     vec3 result = (ambient + diffuse + specular) * objectColor;
     FragColor = vec4(result, 1.0);
     ```

**注意事項：**
- **視線和反射方向的點乘**：用於確定觀察者視角下的鏡面高光強度，確保值非負。
- **反光度設定**：反光度越高，反射光越集中，高光點越小。




