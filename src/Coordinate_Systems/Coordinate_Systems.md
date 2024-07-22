### �y�Шt�� - ���O

#### ���z
- **�зǤƳ]�Ʈy�� (NDC)**�GOpenGL�Ʊ�C�ӳ��I��x, y, z�y�г��b-1.0��1.0�����A�W�X�d�򪺳��I�N���i���C
- **�ഫ�L�{**�G�����Ŷ� -> �@�ɪŶ� -> �[��Ŷ� -> ���ŪŶ� -> �ù��Ŷ��C

#### �y�Шt��
1. **�����Ŷ� (Local Space/����Ŷ�)**�G����۹��ۤv�����I���y�СC
2. **�@�ɪŶ� (World Space)**�G����۹��@�ɭ��I���y�СA�g�Ѽҫ��x�}�ഫ�C
3. **�[��Ŷ� (View Space/��ı�Ŷ�)**�G�q��v�������ר��[��骺�y�СA�g���[��x�}�ഫ�C
4. **���ŪŶ� (Clip Space)**�G�N�y���ഫ��-1.0��1.0�d�򤺡A�g�ѧ�v�x�}�ഫ�C
5. **�ù��Ŷ� (Screen Space)**�G�̲׬M�g��ù��W���y�СC

#### �ഫ�x�}
- **�ҫ��x�} (Model Matrix)**�G�N�����y���ഫ���@�ɮy�СC
- **�[��x�} (View Matrix)**�G�N�@�ɮy���ഫ���[��Ŷ��y�СC
- **��v�x�} (Projection Matrix)**�G�N�[��y���ഫ�����ŪŶ��y�СC

#### ��v�x�}
1. **���g��v (Orthographic Projection)**�G�w�q�@�ӥߤ��骺���I�Y�c�A�A�Ω�2D��V�M�u�{���ΡC
   ```cpp
   glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);
   ```
2. **�z����v (Perspective Projection)**�G�����u��@�ɤ����z���ĪG�A���B����ݰ_�ӧ�p�C
   ```cpp
   glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
   ```

#### �k��y�Шt
- OpenGL�ϥΥk��y�Шt�G��x�b�b�k�A��y�b�V�W�A��z�b�¦V���C

#### �Ҥl - 3Dø��
- **�ҫ��x�}**�G�N��������A�Ϩ��b�a�O�W�C
  ```cpp
  glm::mat4 model;
  model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  ```

- **�[��x�}**�G�N��v���V�Ჾ�ʡA�H�K�ݨ쪫��C
  ```cpp
  glm::mat4 view;
  view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
  ```

- **��v�x�}**�G�w�q�z����v�C
  ```cpp
  glm::mat4 projection;
  projection = glm::perspective(glm::radians(45.0f), screenWidth / screenHeight, 0.1f, 100.0f);
  ```

- **���I�ۦ⾹**�G�ŧi�ܴ��x�}�����ΡC
  ```glsl
  #version 330 core
  layout (location = 0) in vec3 aPos;
  ...
  uniform mat4 model;
  uniform mat4 view;
  uniform mat4 projection;

  void main()
  {
      gl_Position = projection * view * model * vec4(aPos, 1.0);
      ...
  }
  ```

- **C++ �{���X**�G�ǻ��x�}���ۦ⾹�C
  ```cpp
  int modelLoc = glGetUniformLocation(ourShader.ID, "model");
  glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
  // �[��x�}�M��v�x�}����
  ```

#### Z�w��
- **�ҥβ`�״���**�G
  ```cpp
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  ```

#### ��h���ߤ���
- **�w�q�h�ӥߤ����m**�G
  ```cpp
  glm::vec3 cubePositions[] = {
    glm::vec3( 0.0f,  0.0f,  0.0f), 
    glm::vec3( 2.0f,  5.0f, -15.0f), 
    glm::vec3(-1.5f, -2.2f, -2.5f),  
    glm::vec3(-3.8f, -2.0f, -12.3f),  
    glm::vec3( 2.4f, -0.4f, -3.5f),  
    glm::vec3(-1.7f,  3.0f, -7.5f),  
    glm::vec3( 1.3f, -2.0f, -2.5f),  
    glm::vec3( 1.5f,  2.0f, -2.5f), 
    glm::vec3( 1.5f,  0.2f, -1.5f), 
    glm::vec3(-1.3f,  1.0f, -1.5f)  
  };
  ```

- **��V�h�ӥߤ���**�G
  ```cpp
  glBindVertexArray(VAO);
  for(unsigned int i = 0; i < 10; i++)
  {
    glm::mat4 model;
    model = glm::translate(model, cubePositions[i]);
    float angle = 20.0f * i; 
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    ourShader.setMat4("model", model);

    glDrawArrays(GL_TRIANGLES, 0, 36);
  }
  ```

