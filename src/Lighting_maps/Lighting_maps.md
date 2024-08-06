# Lighting_maps
## �ؿ�
1. [���ӶK��](#���ӶK��)
2. [���Ϯg�K��](#���Ϯg�K��)
3. [�譱���K��](#�譱���K��)
4. [�ļ��譱���K��](#�ļ��譱���K��)






## ���ӶK��

- **�ޤJ���ӶK�� (Lighting Maps)�G**
  - **���Ϯg�K�� (Diffuse Map)�G** ����骺���Ϯg���q�C
  - **�譱���K�� (Specular Map)�G** ����骺�譱�����q�C



## ���Ϯg�K��
- **���Ϯg�K�Ϫ������G**
  - �ڭ̧Ʊ欰�C�Ӥ��q��W�]�w���Ϯg�C��C
  - ���Ϯg�K�� (Diffuse Map) �O�@�i�л\���骺�Ϲ��A��{�F����Ҧ������Ϯg�C��C
  - ���Ϯg�K�������󯾲z�A���\�ڭ̮ھڤ��q��m���o�C��ȡC

- **�ϥκ��Ϯg�K�Ϫ��B�J�G**
  1. **�ǳƶK�ϡG**
     - �ϥί��z�Ϲ���ܪ��骺���Ϯg�C��A�Ҧp������ت���c�Ϲ��C

  2. **�ק� `Material` ���c��G**
     - �N���Ϯg�C��V�q������ `sampler2D`�C
     - �������ҥ������C��V�q�A�]�����q�`���󺩤Ϯg�C��C

     ```glsl
     struct Material {
         sampler2D diffuse; // ���Ϯg�K��
         vec3      specular;
         float     shininess;
     }; 
     ```

  3. **��s���q�ۦ⾹�G**
     - �K�[���z�y�Ъ���J�ܼơC

     ```glsl
     in vec2 TexCoords;
     ```

     - �q���z�����˺��Ϯg�C��ȡC

     ```glsl
     vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
     ```

     - �N���ҥ������C��]�w�����Ϯg�����C��ۦP���ȡC

     ```glsl
     vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
     ```

  4. **��s���I�ƾڡG**
     - ���I�ƾڲ{�b�]�t�F���I��m�B�k�V�q�M���z�y�СC

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

  5. **��s VAO �����I�ݩʫ��w�G**
     - �T�O���I�ݩʫ��w�ǰt��s�᪺���I�ƾڡC

  6. **���J�M�j�w���z�G**
     - ���J�c�l�Ϲ����@�ӯ��z�C
     - �N���z�椸��Ȩ� `material.diffuse` �� uniform ���˾��C
     - �j�w�c�l�����z��A�����z�椸�C

     ```cpp
     lightingShader.setInt("material.diffuse", 0);
     glActiveTexture(GL_TEXTURE0);
     glBindTexture(GL_TEXTURE_2D, diffuseMap);
     ```


## �譱���K��
- **���D�G�譱��������{�����T**
  - ��s���餣���Ӧ��j�P���譱�����C
  - ���s��ػݭn��ܾA���譱�����C
  - �ݭn����P�������譱���j�סC

- **�譱���K�� (Specular Map)�G**
  - �ϥί��z�K�ϨӪ�ܪ��餣�P�������譱���j�סC
  - �譱���K�ϬO�¥ա]�αm��^�����z�A�w�q�F�C�������譱���j�סC

- **�d�һP��z�G**
  - �譱���K�Ϫ��C�ӹ����C��������譱���j�סC
    - **�¦�**��ܵL�譱���]`vec3(0.0)`�^�C
    - **�Ǧ�**��ܤ����譱���]`vec3(0.5)`�^�C
    - **�զ�**��ܱj�P�譱���C
  - ���q�ۦ⾹���q�K�Ϩ����C��ȡA�í��H�������譱�j�רӭp���譱�����q�C

- **�K�Ϥ��e�G**
  - ���Y������ܬ��¦�A�N��S���譱�����C
  - ���s�����ܤ��P�ǫסA����譱���j�ת��ܤơC
  - ��ڤW�A���Y���譱���A���v�T�ܤp�A�ϥ��פp�C


- **��{�L�{�G**
  1. **��s `Material` ���c��G**
     - �N�譱���C��V�q������ `sampler2D`�G

       ```glsl
       struct Material {
           sampler2D diffuse;  // ���Ϯg�K��
           sampler2D specular; // �譱���K��
           float     shininess;
       };
       ```

  2. **���q�ۦ⾹�������譱���G**
     - �ϥ��譱���K�Ϩӭp���譱�����q�G

       ```glsl
       vec3 specularColor = texture(material.specular, TexCoords).rgb;
       vec3 specular = light.specular * specularColor * spec;
       ```

  3. **��s���I�ƾڡG**
     - �T�O���I�ƾڥ]�t���I��m�B�k�V�q�M���z�y�СC

  4. **���J�M�j�w�譱�����z�G**
     - ���J�譱�����z�øj�w��A�����z�椸�G

       ```cpp
       lightingShader.setInt("material.specular", 1);
       glActiveTexture(GL_TEXTURE1);
       glBindTexture(GL_TEXTURE_2D, specularMap);
       ```


## �ļ��譱���K��
- **�譱���K�� (Specular Map)�G**
  - �P��L���z�����A�{���X�P���Ϯg�K�Ϭۦ��C
  - ���T���J�Ϲ��ò��ͯ��z����C
  - �ϥΤ��P�����z�椸�Ӹj�w�譱���K�ϡC

- **���z�椸�j�w�G**
  - �ϥ� `GL_TEXTURE1` �j�w�譱���K�ϡG

    ```cpp
    lightingShader.setInt("material.specular", 1);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, specularMap);
    ```

- **��s���赲�c��G**
  - �ק� `Material` ���c��A�Ϩ䱵�� `sampler2D` �@���譱�����q�G

    ```glsl
    struct Material {
        sampler2D diffuse;   // ���Ϯg�K��
        sampler2D specular;  // �譱���K��
        float     shininess;
    };
    ```

- **�ļ��譱���K�ϡG**
  - �ϥ� `texture()` ��Ʊq�譱���K�Ϥ����ˡG

    ```glsl
    vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));  
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    FragColor = vec4(ambient + diffuse + specular, 1.0);
    ```

- **����Ӹ`�G**
  - �ϥ��譱���K�ϥi�]�w��������Ӹ`�G
    - ���ǳ����ݭn�譱�����C
    - ���P���쪺�譱���j�סC

- **�譱���K�Ϫ��C��G**
  - �i�ϥίu�����C��ӳ]�w�譱���K�ϡA���ȱ���j���ٱ����C��C
  - **�`�N**�G�譱�������C��q�`�ѥ����M�w�A�ϥ��C��i�ण���u��A�q�`�ĥζ¥նK�ϡC

