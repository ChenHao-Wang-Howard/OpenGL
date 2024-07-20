







# Textures
## �ؿ�
1. [���z](#���z)
2. [���z��¶�覡](#���z��¶�覡)
3. [���z�L�o](#���z�L�o)
4. [�[���P�Ыد��z](#�[���P�Ыد��z)
5. [stb_image.h](#stb_image.h)
6. [�ͦ����z](#�ͦ����z)
7. [���ί��z](#���ί��z)
8.[���z�椸](#���z�椸)

##���z

#### �򥻷���
- **���z**�G�@��2D�Ϥ��]�]��1D�M3D�����z�^�A�ΨӬ�����K�[�Ӹ`�A�Ϩ�ݰ_�ӧ�u��C
- �ϥί��z�����ֳ��I�ƶq�A���ɴ�V�Ĳv�C

#### ���z���@��
- **�W�[�Ӹ`**�G�z�L�b�@�i�Ϥ��W�K�[�j�q�Ӹ`�A�Ϫ���ݰ_�Ӻ�ӦӤ��ݭn�W�[�B�~���I�C
- **���z�y��**�G���w�C�ӳ��I�������z�����ӳ����A�i�毾�z�M�g�C

#### ���z�y��
- ���z�y�Цbx�My�b�W�A�d��0��1�����C
- ���z�y�а_�l��(0, 0)�A�Y���z�Ϥ������U���A�פ��(1, 1)�A�Y���z�Ϥ����k�W���C
- ���z�y�ХܨҡG
  ```cpp
  float texCoords[] = {
      0.0f, 0.0f, // ���U��
      1.0f, 0.0f, // �k�U��
      0.5f, 1.0f  // �W��
  };
  ```

#### ���z�M�g
- ���T���Ϊ��C�ӳ��I���w���z�y�СG
  - ���U�����I�������z�����U�� `(0, 0)`
  - �W���I�������z���W����m `(0.5, 1.0)`
  - �k�U�����I�������z���k�U�� `(1, 0)`

#### ���z����
- ����(Sampling)�G�ϥί��z�y��������z�C��C
- ���q�ۦ⾹�|���C�Ӥ��q�i�毾�z�y�Ъ����ȡA������������z�C��C




##���z��¶�覡


#### �򥻷���
- **���z�y�нd��**�G�q�`�O�q(0, 0)��(1, 1)�C
- **�W�X�d��**�GOpenGL�w�]�欰�O���Ư��z�Ϲ��A���]���ѤF��L��ܡC

#### ��¶�覡�ﶵ
- **GL_REPEAT**�G�w�]�欰�A���Ư��z�Ϲ��C
- **GL_MIRRORED_REPEAT**�G���Ư��z�Ϲ��A���C�����ƹϤ��O�蹳��m���C
- **GL_CLAMP_TO_EDGE**�G���z�y�гQ�����b0��1�����A�W�X������������t�C��A������t�Q�Ԧ��ĪG�C
- **GL_CLAMP_TO_BORDER**�G�W�X�d�򪺳����ϥΫ��w����t�C��C

#### �]�m���z��¶�覡
- �ϥ�`glTexParameteri`��ƹ��W�����жb�]�m�G
  ```cpp
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
  ```
  - �Ĥ@�ӰѼơG���z�ؼСA�ϥ�2D���z�ɬ�`GL_TEXTURE_2D`�C
  - �ĤG�ӰѼơG�]�w���ﶵ�P���Ϊ����z�b�]S�BT�b�^�C
  - �ĤT�ӰѼơG��¶�覡�]�p`GL_MIRRORED_REPEAT`�^�C

#### �]�mGL_CLAMP_TO_BORDER�C��
- ����`GL_CLAMP_TO_BORDER`�ﶵ�ɡA�ݫ��w��t�C��G
  ```cpp
  float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
  ```




##���z�L�o


#### �򥻷���
- **���z�y��**�G���̿�ѪR�סA�i�H�O���N�B�I�ƭȡC
- **���z�L�o**�G�i�DOpenGL�p��N���z���������쯾�z�y�СA�S�O�O����ܤj�����z�ѪR�׫ܧC�ɡC

#### ���z�L�o�覡
- **GL_NEAREST**�]�F��L�o�^�G��̱ܳ��񯾲z�y�Ъ������C
  - �w�]�覡�A�������ɪ����ϮסC
  - �Ϥ��ܨҡG
    ![GL_NEAREST�ܨҹ�](https://learnopengl.com/img/getting-started/texture_filter_nearest.png)

- **GL_LINEAR**�]�u�ʹL�o�^�G��󯾲z�y�Ъ��񪺯��z�����i�洡�ȭp��C
  - ���ͧ󥭷ƪ��ϮסC
  - �Ϥ��ܨҡG
    ![GL_LINEAR�ܨҹ�](https://learnopengl.com/img/getting-started/texture_filter_linear.png)

#### �]�w���z�L�o�覡
- �]�w���z�L�o���ﶵ�A�i�H�b��j�M�Y�p�ާ@�ɤ��P�G
  ```cpp
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  ```

#### �h�ź������z (Mipmap)
- **�h�ź������z**�G�@�t�C���z�v���A�C�Ӽv���O�e�@�Ӽv�����G�����@�C
- �ѨM���B����ϥΰ��ѪR�ׯ��z�����D�A�����ʯ�M�u��P�C
- OpenGL�۰ʥͦ��h�ź������z�G
  ```cpp
  glGenerateMipmap(GL_TEXTURE_2D);
  ```

#### �h�ź������z�L�o�覡
- **�L�o�覡**�G
  - **GL_NEAREST_MIPMAP_NEAREST**�G�ϥγ̾F�񪺦h�ź������z�öi��F�񴡭ȡC
  - **GL_LINEAR_MIPMAP_NEAREST**�G�ϥγ̾F�񪺦h�ź������z�öi��u�ʤ����C
  - **GL_NEAREST_MIPMAP_LINEAR**�G�b��ӳ̤ǰt�����j�p���h�ź������z�����i��u�ʤ����A�èϥξF�񴡭ȶi����ˡC
  - **GL_LINEAR_MIPMAP_LINEAR**�G�b��ӾF�񪺦h�ź������z�����i��u�ʴ��ȡA�èϥνu�ʴ��ȶi����ˡC

- �]�w�h�ź������z�L�o�覡�G
  ```cpp
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  ```
- **�`�N**�G�h�ź������z�D�n�Ω��Y�p�L�o�A����Ω��j�L�o�A�_�h�|����GL_INVALID_ENUM���~�C

##�[���P�Ыد��z



#### �ѨM���
1. **�ۤv�g�Ϲ����J��**�G
   - ���S�w�榡�]�Ҧp.PNG�^�g�@�Ӹ��J���A�N�Ϲ��ഫ���줸�էǦC�C
   - ���M�����A���D�`�·СA�B�ݭn���C�ؤ䴩���榡�g���J���C

2. **�ϥιϹ����J�w**�G
   - �䴩�h�جy��榡���Ϲ����J�w�O�@�ا�n����ܡC
   - **stb_image.h**�G�@�Ӭy�檺�Ϲ����J�w�A�䴩�h�عϹ��榡�C

#### �ϥ�stb_image.h���J���z
- **stb_image.h**�禡�w���²�ƹϹ����J�L�{�A�䴩�h�خ榡�C



##stb_image.h


#### �򥻷���
- **stb_image.h**�GSean Barrett�}�o�����Y���Ϲ��[���w�A����[���j�����y�檺���榡�C
- **�u�I**�G²����ΡA��K��X��A���u�{���C

#### �w�˩M�ϥ�stb_image.h
1. **�U��stb_image.h**�G
   - �i�H�b[stb_image.h�x�����](https://github.com/nothings/stb)�U���C

2. **�]�tstb_image.h**�G
   - �N�U�����Y���R�W��`stb_image.h`�å[�J�A���u�{�C
   - �Ыؤ@�ӷs��C++���A��J�H�U�{���X�G
     ```cpp
     #define STB_IMAGE_IMPLEMENTATION
     #include "stb_image.h"
     ```
   - �w�q`STB_IMAGE_IMPLEMENTATION`�|���w�B�z���ק��Y���A�]�t��������Ʃw�q��l�X�C

3. **�b�{�����]�tstb_image.h**�G
   - �b�A���D�{����󤤥]�t`stb_image.h`�G
     ```cpp
     #include "stb_image.h"
     ```

#### �ϥ�stb_image.h���J�Ϲ�
- �ϥ�`stbi_load`��ƥ[���Ϲ��G
  ```cpp
  int width, height, nrChannels;
  unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
  ```
  - **�Ѽ�**�G
    - �Ĥ@�ӰѼơG�v���ɮת���m�C
    - �ĤG�B�ĤT�M�ĥ|�ӰѼơG�v�����e�סB���שM�C��q�D�ƶq�Astb_image.h�|��J�o�T���ܼơC

#### �ͦ����z
- �ϥΥ[�����Ϲ��ƾڥͦ����z�G
  ```cpp
  unsigned int texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data); // ����Ϲ��ƾ�
  ```

#### �]�m���z�Ѽ�
- �]�m���z��¶�覡�M�L�o�覡�G
  ```cpp
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  ```


##�ͦ����z


#### �򥻷���
- **���zID**�G���z�M���e��OpenGL����@�ˡA�ϥ�ID�ӤޥΡC
- **�j�w���z**�G�ݭn�j�w���z�A�H�K������O����t�m��e�j�w�����z�C

#### �ͦ����z
- �Ыد��zID�G
  ```cpp
  unsigned int texture;
  glGenTextures(1, &texture);
  ```
  - �Ĥ@�ӰѼơG�ͦ������z�ƶq�C
  - �ĤG�ӰѼơG�x�s�ͦ����zID��unsigned int�}�C�C

- �j�w���z�G
  ```cpp
  glBindTexture(GL_TEXTURE_2D, texture);
  ```
  - ���w���z�ؼЬ�`GL_TEXTURE_2D`�C

#### �]�m���z�Ѽ�
- �]�m���z��¶�覡�M�L�o�覡�G
  ```cpp
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  ```

#### �[���åͦ����z
- �ϥ�`stbi_load`�[���Ϲ��G
  ```cpp
  int width, height, nrChannels;
  unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
  ```

- �ϥ�`glTexImage2D`�ͦ����z�G
  ```cpp
  if (data)
  {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
      glGenerateMipmap(GL_TEXTURE_2D);
  }
  else
  {
      std::cout << "Failed to load texture" << std::endl;
  }
  ```
  - **�Ѽ�**�G
    - `GL_TEXTURE_2D`�G���z�ؼСC
    - `0`�G�h�ź������z���ŧO�A0�O�򥻯ŧO�C
    - `GL_RGB`�G���z�x�s���榡�C
    - `width`�M`height`�G���z���e�שM���סC
    - `0`�G���v��d�ѼơA�]�m��0�C
    - `GL_RGB`�G�ӷ��Ϲ����榡�C
    - `GL_UNSIGNED_BYTE`�G�ӷ��Ϲ���ƪ������C
    - `data`�G�Ϲ���ơC

- ����Ϲ����O����G
  ```cpp
  stbi_image_free(data);
  ```

#### ����ͦ����z�L�{
```cpp
unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);

// ����e�j�w�����z��H�]�m��¶�M�L�o�覡
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);   
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

// �[���åͦ����z
int width, height, nrChannels;
unsigned char *data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
if (data)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
    std::cout << "Failed to load texture" << std::endl;
}
stbi_image_free(data);
```


##���ί��z

#### �򥻷���
- **���z�y��**�G�ݭn��s���I��ơA�i�DOpenGL�p����˯��z�C

#### ��s���I���
- �s�����I��ƥ]�t��m�B�C��M���z�y�СG
  ```cpp
  float vertices[] = {
      // ---- ��m ----       ---- �C�� ----     - ���z�y�� -
       0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // �k�W
       0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // �k�U
      -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ���U
      -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ���W
  };
  ```

#### �t�m���I�ݩʫ���
- �s�W���z�y���ݩʡA�ç�s�B���ѼơG
  ```cpp
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  // ��s��m�M�C���ݩʪ��B���Ѽ�
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  ```

#### ��s���I�ۦ⾹
- �����öǻ����z�y�СG
  ```cpp
  #version 330 core
  layout (location = 0) in vec3 aPos;
  layout (location = 1) in vec3 aColor;
  layout (location = 2) in vec2 aTexCoord;

  out vec3 ourColor;
  out vec2 TexCoord;

  void main()
  {
      gl_Position = vec4(aPos, 1.0);
      ourColor = aColor;
      TexCoord = aTexCoord;
  }
  ```

#### ��s���q�ۦ⾹
- �����èϥί��z�y�СA�ëŧiuniform sampler2D�G
  ```cpp
  #version 330 core
  out vec4 FragColor;

  in vec3 ourColor;
  in vec2 TexCoord;

  uniform sampler2D ourTexture;

  void main()
  {
      FragColor = texture(ourTexture, TexCoord);
  }
  ```

#### �j�w���z��ø�s
- �b`glDrawElements`���e�j�w���z�G
  ```cpp
  glBindTexture(GL_TEXTURE_2D, texture);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  ```

#### �V�X���z�M���I�C��
- �b���q�ۦ⾹���V�X���z�C��M���I�C��G
  ```cpp
  FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
  ```

#### ���㪺���ί��z�N�X�ܨ�
```cpp
// Vertex data including position, color, and texture coordinates
float vertices[] = {
    0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // �k�W
    0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // �k�U
   -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ���U
   -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ���W
};

// Configure vertex attributes
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

// Updated vertex shader
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}

// Updated fragment shader
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
}

// Binding texture and drawing
glBindTexture(GL_TEXTURE_2D, texture);
glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

// Mixing texture and vertex color
FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
```


##���z�椸


#### �򥻷���
- **sampler2D**�ܼƬOuniform�����A�ݭn�ϥ�`glUniform`�����ȡC
- **���z�椸**�G���\�b���q�ۦ⾹���ϥΦh�ӯ��z�C
- �w�]���z�椸�O0�A���i�H�ϥΦh�ӯ��z�椸�Ӹj�w�h�ӯ��z�C

#### �ϥί��z�椸
- �ϥ�`glUniform1i`�����z�ļ˾����t�@�Ӧ�m�ȡA�H�]�w�h�ӯ��z�C
- �ϥ�`glActiveTexture`�E�����z�椸�A�øj�w���z��ӳ椸�C

#### �E�����z�椸�øj�w���z
- �E�����z�椸�øj�w���z�G
  ```cpp
  glActiveTexture(GL_TEXTURE0); // �b�j�w���z���e���E�����z�椸
  glBindTexture(GL_TEXTURE_2D, texture1);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);
  ```

#### �ק���q�ۦ⾹
- ���q�ۦ⾹�����h��sampler2D�G
  ```cpp
  #version 330 core
  out vec4 FragColor;

  in vec2 TexCoord;

  uniform sampler2D texture1;
  uniform sampler2D texture2;

  void main()
  {
      FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
  }
  ```

- **mix���**�G���ӯ��z�i��u�ʴ��ȡA�Ѽ�0.2�N��80%���Ĥ@�ӯ��z�C��M20%���ĤG�ӯ��z�C��C

#### ���J�M�ЫزĤG�ӯ��z
- ���J�ĤG�ӯ��z�]OpenGL�ǲ��y�����Ϥ��^�C

#### �j�w���z�ó]�muniform
- �j�w��ӯ��z����������z�椸�G
  ```cpp
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture1);

  glActiveTexture(GL_TEXTURE1);
  glBindTexture(GL_TEXTURE_2D, texture2);

  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  ```

- �]�m�C�ӱļ˾���uniform�ܼơG
  ```cpp
  ourShader.use(); // �b�]�wuniform�ܼƤ��e�E���ۦ⾹�{��
  glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // ��ʳ]�w
  ourShader.setInt("texture2", 1); // �ϥεۦ⾹���]�w
  ```

#### ½��y�b
- �ϥ�`stbi_set_flip_vertically_on_load(true)`�b�[���Ϲ���½��y�b�G
  ```cpp
  stbi_set_flip_vertically_on_load(true);
  ```

#### ����N�X�ܨ�
```cpp
// ���I�ƾڡA�]�A��m�B�C��M���z�y��
float vertices[] = {
    // ---- ��m ----       ---- �C�� ----     - ���z�y�� -
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // �k�W
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // �k�U
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // ���U
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // ���W
};

// �t�m���I�ݩʫ���
glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
glEnableVertexAttribArray(2);

// �קﳻ�I�ۦ⾹
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
    TexCoord = aTexCoord;
}

// �ק���q�ۦ⾹
#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
}

// �]�muniform�ܼ�
ourShader.use();
glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0);
ourShader.setInt("texture2", 1);

// �[���Ϲ���½��y�b
stbi_set_flip_vertically_on_load(true);

// �j�w���z��ø�s
glActiveTexture(GL_TEXTURE0);
glBindTexture(GL_TEXTURE_2D, texture1);

glActiveTexture(GL_TEXTURE1);
glBindTexture(GL_TEXTURE_2D, texture2);

glBindVertexArray(VAO);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
```






