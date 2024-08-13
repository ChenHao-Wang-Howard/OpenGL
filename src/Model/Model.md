# Model
## 目錄
1. [模型](#模型)
2. [導入3D模型到OpenGL](#導入3D模型到OpenGL)
3. [重大優化](#重大優化)









## 模型
- **Model 類別結構**
  - 私有變數：
    - `vector<Mesh> meshes`：儲存模型的所有網格。
    - `string directory`：儲存模型檔案的目錄，後續載入紋理時使用。
  - 私有函數：
    - `void loadModel(string path)`：載入模型檔案。
    - `void processNode(aiNode *node, const aiScene *scene)`：遞迴處理每個節點，提取網格資料。
    - `Mesh processMesh(aiMesh *mesh, const aiScene *scene)`：處理每個網格，將 Assimp 資料結構轉換為 `Mesh` 物件。
    - `vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)`：載入材質的紋理，並儲存為 `Texture` 結構體。

- **Model 類別程式碼**
  - **構造函數 `Model(char *path)`**
    - 透過傳入的檔案路徑，呼叫 `loadModel` 函數來載入模型。
    - ```cpp
      Model(char *path)
      {
          loadModel(path);
      }
      ```
    
  - **Draw 函數**
    - 遍歷 `meshes` 向量中的每個 `Mesh`，呼叫它們的 `Draw` 函數來渲染模型。
    - ```cpp
      void Draw(Shader &shader)
      {
          for(unsigned int i = 0; i < meshes.size(); i++)
              meshes[i].Draw(shader);
      }
      ```

## 導入3D模型到OpenGL
- **導入3D模型到OpenGL的過程**
  - **包含Assimp頭檔**
    ```cpp
    #include <assimp/Importer.hpp>
    #include <assimp/scene.h>
    #include <assimp/postprocess.h>
    ```

  - **使用Assimp載入模型**
    - 定義`Importer`物件，使用`ReadFile`函數載入模型：
      ```cpp
      Assimp::Importer importer;
      const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
      ```
    - `ReadFile`函數的第二個參數可以設定後製處理選項：
      - `aiProcess_Triangulate`：將所有圖元轉換為三角形。
      - `aiProcess_FlipUVs`：翻轉紋理座標的Y軸。

  - **其他常見的後製處理選項**
    - `aiProcess_GenNormals`：為每個頂點生成法線。
    - `aiProcess_SplitLargeMeshes`：將大網格分割成小網格。
    - `aiProcess_OptimizeMeshes`：將小網格合併為大網格以減少繪製呼叫。

  - **完整的`loadModel`函數**
    ```cpp
    void loadModel(string path)
    {
        Assimp::Importer import;
        const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
            return;
        }
        directory = path.substr(0, path.find_last_of('/'));

        processNode(scene->mRootNode, scene);
    }
    ```
    - 檢查載入的場景和根節點是否為`null`或不完整。
    - 若無錯誤，處理場景中的所有節點，呼叫`processNode`函數。

  - **`processNode`函數的工作流程**
    ```cpp
    void processNode(aiNode *node, const aiScene *scene)
    {
        // 處理節點的所有網格（如果有的話）
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }

        // 接下來對它的子節點重複這個過程
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }
    ```
    - 處理節點的所有網格，將網格加入到`meshes`列表。
    - 遞歸處理子節點，直到所有節點都被處理完畢。

  - **`processMesh`函數的結構**
    ```cpp
    Mesh processMesh(aiMesh *mesh, const aiScene *scene)
    {
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        // 取得所有的頂點資料
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            // 處理頂點位置、法線和紋理座標
            glm::vec3 vector;
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;

            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoords = vec;
            }
            else
                vertex.TexCoords = glm::vec2(0.0f, 0.0f);

            vertices.push_back(vertex);
        }

        // 取得索引
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // 處理材質
        if (mesh->mMaterialIndex >= 0)
        {
            aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
            vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
            textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
            vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
            textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }
    ```
    - **處理步驟**
      - 取得所有的頂點資料。
      - 取得網格索引。
      - 取得材質資料，並將其加入`textures`列表。

  - **`loadMaterialTextures`函數**
    ```cpp
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
    {
        vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            texture.path = str;
            textures.push_back(texture);
        }
        return textures;
    }
    ```
    - 透過`GetTextureCount`函數檢查材質中包含的紋理數量。
    - 使用`GetTexture`函數取得每個紋理的檔案位置。
    - 使用`TextureFromFile`函數載入紋理並取得其ID，將紋理加入`textures`列表。

  - **載入紋理檔案**
    - 假設模型檔案中的紋理路徑是相對路徑，可以將紋理位置字串拼接到目錄字串上以取得完整的紋理路徑。

  - **處理絕對路徑紋理**
    - 如果模型中的紋理路徑是絕對路徑，可能需要手動修改檔案來使用相對路徑。

  - **完成導入過程**
    - 使用Assimp導入模型並將資料轉換為自定義的Mesh物件，整合頂點、索引和材質資料。
## 重大優化
- **優化模型載入過程**
  - **避免重複載入紋理**
    - 在多個網格中重複使用相同紋理的情況下，避免重複載入紋理來提高效能。
    - 每次載入紋理前，先檢查該紋理是否已經載入過，若已載入過則直接使用，跳過重新加載的步驟。

  - **儲存紋理路徑**
    - 定義`Texture`結構體來儲存紋理資訊，其中包括紋理的路徑，用於比較紋理是否已載入過：
      ```cpp
      struct Texture {
          unsigned int id;
          string type;
          aiString path;  // 儲存紋理的路徑，用於與其它紋理進行比較
      };
      ```

  - **儲存已載入的紋理**
    - 在模型類別的頂部宣告一個私有變數`textures_loaded`，用來儲存所有已經載入過的紋理：
      ```cpp
      vector<Texture> textures_loaded;
      ```

  - **更新`loadMaterialTextures`函數**
    - 在載入紋理前，檢查紋理路徑是否已存在於`textures_loaded`中，如果存在則直接使用該紋理，否則載入新的紋理並儲存到`textures_loaded`中：
      ```cpp
      vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
      {
          vector<Texture> textures;
          for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
          {
              aiString str;
              mat->GetTexture(type, i, &str);
              bool skip = false;
              for(unsigned int j = 0; j < textures_loaded.size(); j++)
              {
                  if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
                  {
                      textures.push_back(textures_loaded[j]);
                      skip = true; 
                      break;
                  }
              }
              if(!skip)
              {   // 如果紋理還沒有被加載，則加載它
                  Texture texture;
                  texture.id = TextureFromFile(str.C_Str(), directory);
                  texture.type = typeName;
                  texture.path = str.C_Str();
                  textures.push_back(texture);
                  textures_loaded.push_back(texture); // 添加到已載入的紋理中
              }
          }
          return textures;
      }
      ```

