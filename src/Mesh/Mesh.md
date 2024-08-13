# Mesh
## 目錄
1. [網格](#網格)
2. [初始化](#初始化)
3. [渲染](#渲染)






## 網格
- **定義網格類別的目的：**
  - 使用 Assimp 載入的模型被儲存為 Assimp 的資料結構，最終需要轉換為 OpenGL 能夠理解的格式，才能渲染物體。
  - 網格（Mesh）代表單一的可繪製實體，我們需要定義一個自己的網格類別來處理這些資料。

- **網格類別的基本需求：**
  - 一個網格至少需要以下資料：
    - 一系列的頂點，每個頂點包含位置向量、法向量、紋理座標向量。
    - 索引，用於索引繪製。
    - 紋理資料（如漫反射/鏡面光貼圖）。

- **頂點結構體：**
  - 使用 `Vertex` 結構體來儲存每個頂點的屬性：
    ```cpp
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };
    ```

- **紋理結構體：**
  - 使用 `Texture` 結構體來儲存紋理的資料：
    ```cpp
    struct Texture {
        unsigned int id;
        string type;
    };
    ```
  - `id` 表示紋理的 ID，`type` 表示紋理的類型（例如漫反射貼圖或鏡面光貼圖）。

- **網格類別的結構：**
  - 網格類別 `Mesh` 包含以下成員：
    - 公有成員：
      - `vertices`：儲存頂點資料的向量。
      - `indices`：儲存索引資料的向量。
      - `textures`：儲存紋理資料的向量。
      - 構造函數 `Mesh`：用於初始化網格資料。
      - `Draw` 函數：用於繪製網格，接收一個 `Shader` 參數。
    - 私有成員：
      - `VAO`、`VBO`、`EBO`：用於渲染的資料。
      - `setupMesh` 函數：用於初始化緩衝。

  - 網格類別定義：
    ```cpp
    class Mesh {
    public:
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;
        
        Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
        void Draw(Shader shader);
    
    private:
        unsigned int VAO, VBO, EBO;
        void setupMesh();
    };
    ```

- **構造函數：**
  - 構造函數用於初始化網格的頂點、索引和紋理資料，並呼叫 `setupMesh` 函數：
    ```cpp
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        setupMesh();
    }
    ```

## 初始化

- **初始化步驟：**
  1. 生成VAO、VBO和EBO。
     ```cpp
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glGenBuffers(1, &EBO);
     ```
  2. 綁定VAO並設置VBO和EBO的緩衝資料。
     ```cpp
     glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
     ```
  3. 設置頂點屬性指標：
     - **頂點位置**：`glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);`
     - **頂點法線**：`glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));`
     - **頂點紋理坐標**：`glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));`
     ```cpp
     glEnableVertexAttribArray(0);   
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

     glEnableVertexAttribArray(1);   
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

     glEnableVertexAttribArray(2);   
     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
     ```

- **結構體記憶體佈局的優點：**
  - C++ 結構體的記憶體佈局是連續的，這意味著結構體的變數會順序排列在記憶體中，符合 OpenGL 緩衝需要的資料結構。
  - 可以直接將一列 `Vertex` 結構體傳遞給 `glBufferData`，因為它們的記憶體佈局已經是順序排列的。
  ```cpp
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
  ```

- **使用 `offsetof` 巨集：**
  - `offsetof` 巨集可以計算結構體中變數的位元組偏移量，用於設置 `glVertexAttribPointer` 中的偏移參數。
  - 範例：`glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));`
  - `offsetof(Vertex, Normal)` 計算 `Normal` 在 `Vertex` 結構體中的偏移量，用於設置頂點法線的位元組偏移。


## 渲染
- **Mesh 類別的 Draw 函數：**
  - Draw 函數負責渲染網格，並在渲染之前綁定對應的紋理。

- **紋理處理命名標準：**
  - 每個漫反射紋理命名為 `texture_diffuseN`，每個鏡面光紋理命名為 `texture_specularN`，其中 N 是紋理的編號。
  - 例如，三個漫反射紋理和兩個鏡面光紋理應如下命名：
    - `uniform sampler2D texture_diffuse1;`
    - `uniform sampler2D texture_diffuse2;`
    - `uniform sampler2D texture_diffuse3;`
    - `uniform sampler2D texture_specular1;`
    - `uniform sampler2D texture_specular2;`

- **Draw 函數的實作步驟：**
  1. 計算每個紋理類型的編號（N 分量）。
  2. 將編號拼接到紋理類型字串上，以取得對應的 uniform 名稱。
  3. 啟動對應的紋理單元並綁定紋理。
  4. 將 uniform 名稱傳遞給著色器並設定其位置值。
  5. 使用 `glDrawElements` 函數進行網格繪製。

- **最終的 Draw 函數範例：**

```cpp
void Draw(Shader shader) 
{
    unsigned int diffuseNr = 1;  // 漫反射紋理的計數器
    unsigned int specularNr = 1; // 鏡面光紋理的計數器

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // 在綁定之前啟動相應的紋理單元

        string number; // 用來儲存紋理的編號
        string name = textures[i].type; // 獲取紋理的類型

        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++); // 設定並遞增漫反射紋理計數器
        else if(name == "texture_specular")
            number = std::to_string(specularNr++); // 設定並遞增鏡面光紋理計數器

        // 設定著色器中的取樣器 uniform
        shader.setInt(("material." + name + number).c_str(), i);

        // 綁定對應的紋理
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0); // 設定回預設的紋理單元

    // 繪製網格
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // 解綁 VAO
}
```




- **注意事項：**
  - 在 C++ 中，`variable++` 會先傳回變數值再遞增，而 `++variable` 則是先遞增再傳回值。在這裡使用 `variable++`，是為了在 `stringstream` 中先插入當前值，然後再遞增供下一次循環使用。