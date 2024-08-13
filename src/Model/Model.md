# Model
## �ؿ�
1. [�ҫ�](#�ҫ�)
2. [�ɤJ3D�ҫ���OpenGL](#�ɤJ3D�ҫ���OpenGL)
3. [���j�u��](#���j�u��)









## �ҫ�
- **Model ���O���c**
  - �p���ܼơG
    - `vector<Mesh> meshes`�G�x�s�ҫ����Ҧ�����C
    - `string directory`�G�x�s�ҫ��ɮת��ؿ��A������J���z�ɨϥΡC
  - �p����ơG
    - `void loadModel(string path)`�G���J�ҫ��ɮסC
    - `void processNode(aiNode *node, const aiScene *scene)`�G���j�B�z�C�Ӹ`�I�A���������ơC
    - `Mesh processMesh(aiMesh *mesh, const aiScene *scene)`�G�B�z�C�Ӻ���A�N Assimp ��Ƶ��c�ഫ�� `Mesh` ����C
    - `vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)`�G���J���誺���z�A���x�s�� `Texture` ���c��C

- **Model ���O�{���X**
  - **�c�y��� `Model(char *path)`**
    - �z�L�ǤJ���ɮ׸��|�A�I�s `loadModel` ��ƨӸ��J�ҫ��C
    - ```cpp
      Model(char *path)
      {
          loadModel(path);
      }
      ```
    
  - **Draw ���**
    - �M�� `meshes` �V�q�����C�� `Mesh`�A�I�s���̪� `Draw` ��ƨӴ�V�ҫ��C
    - ```cpp
      void Draw(Shader &shader)
      {
          for(unsigned int i = 0; i < meshes.size(); i++)
              meshes[i].Draw(shader);
      }
      ```

## �ɤJ3D�ҫ���OpenGL
- **�ɤJ3D�ҫ���OpenGL���L�{**
  - **�]�tAssimp�Y��**
    ```cpp
    #include <assimp/Importer.hpp>
    #include <assimp/scene.h>
    #include <assimp/postprocess.h>
    ```

  - **�ϥ�Assimp���J�ҫ�**
    - �w�q`Importer`����A�ϥ�`ReadFile`��Ƹ��J�ҫ��G
      ```cpp
      Assimp::Importer importer;
      const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
      ```
    - `ReadFile`��ƪ��ĤG�ӰѼƥi�H�]�w��s�B�z�ﶵ�G
      - `aiProcess_Triangulate`�G�N�Ҧ��Ϥ��ഫ���T���ΡC
      - `aiProcess_FlipUVs`�G½�௾�z�y�Ъ�Y�b�C

  - **��L�`������s�B�z�ﶵ**
    - `aiProcess_GenNormals`�G���C�ӳ��I�ͦ��k�u�C
    - `aiProcess_SplitLargeMeshes`�G�N�j������Φ��p����C
    - `aiProcess_OptimizeMeshes`�G�N�p����X�֬��j����H���ø�s�I�s�C

  - **���㪺`loadModel`���**
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
    - �ˬd���J�������M�ڸ`�I�O�_��`null`�Τ�����C
    - �Y�L���~�A�B�z���������Ҧ��`�I�A�I�s`processNode`��ơC

  - **`processNode`��ƪ��u�@�y�{**
    ```cpp
    void processNode(aiNode *node, const aiScene *scene)
    {
        // �B�z�`�I���Ҧ�����]�p�G�����ܡ^
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(processMesh(mesh, scene));
        }

        // ���U�ӹ復���l�`�I���Ƴo�ӹL�{
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            processNode(node->mChildren[i], scene);
        }
    }
    ```
    - �B�z�`�I���Ҧ�����A�N����[�J��`meshes`�C��C
    - ���k�B�z�l�`�I�A����Ҧ��`�I���Q�B�z�����C

  - **`processMesh`��ƪ����c**
    ```cpp
    Mesh processMesh(aiMesh *mesh, const aiScene *scene)
    {
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<Texture> textures;

        // ���o�Ҧ������I���
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            // �B�z���I��m�B�k�u�M���z�y��
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

        // ���o����
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
                indices.push_back(face.mIndices[j]);
        }

        // �B�z����
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
    - **�B�z�B�J**
      - ���o�Ҧ������I��ơC
      - ���o������ޡC
      - ���o�����ơA�ñN��[�J`textures`�C��C

  - **`loadMaterialTextures`���**
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
    - �z�L`GetTextureCount`����ˬd���褤�]�t�����z�ƶq�C
    - �ϥ�`GetTexture`��ƨ��o�C�ӯ��z���ɮצ�m�C
    - �ϥ�`TextureFromFile`��Ƹ��J���z�è��o��ID�A�N���z�[�J`textures`�C��C

  - **���J���z�ɮ�**
    - ���]�ҫ��ɮפ������z���|�O�۹���|�A�i�H�N���z��m�r�������ؿ��r��W�H���o���㪺���z���|�C

  - **�B�z������|���z**
    - �p�G�ҫ��������z���|�O������|�A�i��ݭn��ʭק��ɮרӨϥά۹���|�C

  - **�����ɤJ�L�{**
    - �ϥ�Assimp�ɤJ�ҫ��ñN����ഫ���۩w�q��Mesh����A��X���I�B���ީM�����ơC
## ���j�u��
- **�u�Ƽҫ����J�L�{**
  - **�קK���Ƹ��J���z**
    - �b�h�Ӻ��椤���ƨϥάۦP���z�����p�U�A�קK���Ƹ��J���z�Ӵ����į�C
    - �C�����J���z�e�A���ˬd�ӯ��z�O�_�w�g���J�L�A�Y�w���J�L�h�����ϥΡA���L���s�[�����B�J�C

  - **�x�s���z���|**
    - �w�q`Texture`���c����x�s���z��T�A�䤤�]�A���z�����|�A�Ω������z�O�_�w���J�L�G
      ```cpp
      struct Texture {
          unsigned int id;
          string type;
          aiString path;  // �x�s���z�����|�A�Ω�P�䥦���z�i����
      };
      ```

  - **�x�s�w���J�����z**
    - �b�ҫ����O�������ŧi�@�Өp���ܼ�`textures_loaded`�A�Ψ��x�s�Ҧ��w�g���J�L�����z�G
      ```cpp
      vector<Texture> textures_loaded;
      ```

  - **��s`loadMaterialTextures`���**
    - �b���J���z�e�A�ˬd���z���|�O�_�w�s�b��`textures_loaded`���A�p�G�s�b�h�����ϥθӯ��z�A�_�h���J�s�����z���x�s��`textures_loaded`���G
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
              {   // �p�G���z�٨S���Q�[���A�h�[����
                  Texture texture;
                  texture.id = TextureFromFile(str.C_Str(), directory);
                  texture.type = typeName;
                  texture.path = str.C_Str();
                  textures.push_back(texture);
                  textures_loaded.push_back(texture); // �K�[��w���J�����z��
              }
          }
          return textures;
      }
      ```

