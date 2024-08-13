# Mesh
## �ؿ�
1. [����](#����)
2. [��l��](#��l��)
3. [��V](#��V)






## ����
- **�w�q�������O���ت��G**
  - �ϥ� Assimp ���J���ҫ��Q�x�s�� Assimp ����Ƶ��c�A�̲׻ݭn�ഫ�� OpenGL ����z�Ѫ��榡�A�~���V����C
  - ����]Mesh�^�N���@���iø�s����A�ڭ̻ݭn�w�q�@�Ӧۤv���������O�ӳB�z�o�Ǹ�ơC

- **�������O���򥻻ݨD�G**
  - �@�Ӻ���ܤֻݭn�H�U��ơG
    - �@�t�C�����I�A�C�ӳ��I�]�t��m�V�q�B�k�V�q�B���z�y�ЦV�q�C
    - ���ޡA�Ω����ø�s�C
    - ���z��ơ]�p���Ϯg/�譱���K�ϡ^�C

- **���I���c��G**
  - �ϥ� `Vertex` ���c����x�s�C�ӳ��I���ݩʡG
    ```cpp
    struct Vertex {
        glm::vec3 Position;
        glm::vec3 Normal;
        glm::vec2 TexCoords;
    };
    ```

- **���z���c��G**
  - �ϥ� `Texture` ���c����x�s���z����ơG
    ```cpp
    struct Texture {
        unsigned int id;
        string type;
    };
    ```
  - `id` ��ܯ��z�� ID�A`type` ��ܯ��z�������]�Ҧp���Ϯg�K�ϩ��譱���K�ϡ^�C

- **�������O�����c�G**
  - �������O `Mesh` �]�t�H�U�����G
    - ���������G
      - `vertices`�G�x�s���I��ƪ��V�q�C
      - `indices`�G�x�s���޸�ƪ��V�q�C
      - `textures`�G�x�s���z��ƪ��V�q�C
      - �c�y��� `Mesh`�G�Ω��l�ƺ����ơC
      - `Draw` ��ơG�Ω�ø�s����A�����@�� `Shader` �ѼơC
    - �p�������G
      - `VAO`�B`VBO`�B`EBO`�G�Ω��V����ơC
      - `setupMesh` ��ơG�Ω��l�ƽw�ġC

  - �������O�w�q�G
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

- **�c�y��ơG**
  - �c�y��ƥΩ��l�ƺ��檺���I�B���ީM���z��ơA�éI�s `setupMesh` ��ơG
    ```cpp
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
        setupMesh();
    }
    ```

## ��l��

- **��l�ƨB�J�G**
  1. �ͦ�VAO�BVBO�MEBO�C
     ```cpp
     glGenVertexArrays(1, &VAO);
     glGenBuffers(1, &VBO);
     glGenBuffers(1, &EBO);
     ```
  2. �j�wVAO�ó]�mVBO�MEBO���w�ĸ�ơC
     ```cpp
     glBindVertexArray(VAO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
     glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
     ```
  3. �]�m���I�ݩʫ��СG
     - **���I��m**�G`glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);`
     - **���I�k�u**�G`glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));`
     - **���I���z����**�G`glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));`
     ```cpp
     glEnableVertexAttribArray(0);   
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

     glEnableVertexAttribArray(1);   
     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

     glEnableVertexAttribArray(2);   
     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
     ```

- **���c��O����G�����u�I�G**
  - C++ ���c�骺�O����G���O�s�򪺡A�o�N���۵��c�骺�ܼƷ|���ǱƦC�b�O���餤�A�ŦX OpenGL �w�Ļݭn����Ƶ��c�C
  - �i�H�����N�@�C `Vertex` ���c��ǻ��� `glBufferData`�A�]�����̪��O����G���w�g�O���ǱƦC���C
  ```cpp
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
  ```

- **�ϥ� `offsetof` �����G**
  - `offsetof` �����i�H�p�⵲�c�餤�ܼƪ��줸�հ����q�A�Ω�]�m `glVertexAttribPointer` ���������ѼơC
  - �d�ҡG`glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));`
  - `offsetof(Vertex, Normal)` �p�� `Normal` �b `Vertex` ���c�餤�������q�A�Ω�]�m���I�k�u���줸�հ����C


## ��V
- **Mesh ���O�� Draw ��ơG**
  - Draw ��ƭt�d��V����A�æb��V���e�j�w���������z�C

- **���z�B�z�R�W�зǡG**
  - �C�Ӻ��Ϯg���z�R�W�� `texture_diffuseN`�A�C���譱�����z�R�W�� `texture_specularN`�A�䤤 N �O���z���s���C
  - �Ҧp�A�T�Ӻ��Ϯg���z�M����譱�����z���p�U�R�W�G
    - `uniform sampler2D texture_diffuse1;`
    - `uniform sampler2D texture_diffuse2;`
    - `uniform sampler2D texture_diffuse3;`
    - `uniform sampler2D texture_specular1;`
    - `uniform sampler2D texture_specular2;`

- **Draw ��ƪ���@�B�J�G**
  1. �p��C�ӯ��z�������s���]N ���q�^�C
  2. �N�s�������쯾�z�����r��W�A�H���o������ uniform �W�١C
  3. �Ұʹ��������z�椸�øj�w���z�C
  4. �N uniform �W�ٶǻ����ۦ⾹�ó]�w���m�ȡC
  5. �ϥ� `glDrawElements` ��ƶi�����ø�s�C

- **�̲ת� Draw ��ƽd�ҡG**

```cpp
void Draw(Shader shader) 
{
    unsigned int diffuseNr = 1;  // ���Ϯg���z���p�ƾ�
    unsigned int specularNr = 1; // �譱�����z���p�ƾ�

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // �b�j�w���e�Ұʬ��������z�椸

        string number; // �Ψ��x�s���z���s��
        string name = textures[i].type; // ������z������

        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++); // �]�w�û��W���Ϯg���z�p�ƾ�
        else if(name == "texture_specular")
            number = std::to_string(specularNr++); // �]�w�û��W�譱�����z�p�ƾ�

        // �]�w�ۦ⾹�������˾� uniform
        shader.setInt(("material." + name + number).c_str(), i);

        // �j�w���������z
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    glActiveTexture(GL_TEXTURE0); // �]�w�^�w�]�����z�椸

    // ø�s����
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0); // �Ѹj VAO
}
```




- **�`�N�ƶ��G**
  - �b C++ ���A`variable++` �|���Ǧ^�ܼƭȦA���W�A�� `++variable` �h�O�����W�A�Ǧ^�ȡC�b�o�̨ϥ� `variable++`�A�O���F�b `stringstream` �������J��e�ȡA�M��A���W�ѤU�@���`���ϥΡC