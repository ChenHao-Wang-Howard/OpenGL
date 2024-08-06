# Colors
## �ؿ�
1. [�C��](#�C��)
2. [�Ыؤ@�ӥ��ӳ���](#�Ыؤ@�ӥ��ӳ���)
## �C��

### �C���R, G, B�զ�
EX:�n���o�@�Ӭ����(Coral)��
```cpp
glm::vec3 coral(1.0f, 0.5f, 0.31f);
```

### �w�q�G���骺�C�⬰����q�@�ӥ����Ϯg�U���C����q���j�p
�N����C��V�q�@���q�ۭ��A���G�N�O�̲ת��C��V�q
EX: 
```cpp
glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
glm::vec3 result = lightColor * toyColor; // = (1.0f, 0.5f, 0.31f);
```
## �Ыؤ@�ӥ��ӳ���


1. **��ܪ���G**
   - �ϥΥߤ���@�����ӹ�H�]�Y�ߤ���c�l�^�C
   - �ϥΥt�@�ӥߤ����ܥ�������m�C

2. **���I�w�Ī���(VBO)�G**
   - ��R���I�w�Ī���ó]�m���I�ݩʫ��w�C

3. **���I�ۦ⾹�G**
   - ø�s�c�l��²�ƪ����I�ۦ⾹�N�X�G
     ```glsl
     #version 330 core
     layout (location = 0) in vec3 aPos;

     uniform mat4 model;
     uniform mat4 view;
     uniform mat4 projection;

     void main()
     {
         gl_Position = projection * view * model * vec4(aPos, 1.0);
     }
     ```
   - �T�O���I��ƻP�ݩʫ��лP�ۦ⾹�@�P�C

4. **�ЫؿO��VAO�G**
   - �Ыؤ@�ӱM�Ϊ�VAO�������A�H�קK�W�c�קﳻ�I�ƾڼv�T�O����m�C
   - �N�X�d�ҡG
     ```cpp
     unsigned int lightVAO;
     glGenVertexArrays(1, &lightVAO);
     glBindVertexArray(lightVAO);
     glBindBuffer(GL_ARRAY_BUFFER, VBO);
     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
     glEnableVertexAttribArray(0);
     ```

5. **���q�ۦ⾹�G**
   - �w�q����M�����C�⪺���q�ۦ⾹�G
     ```glsl
     #version 330 core
     out vec4 FragColor;

     uniform vec3 objectColor;
     uniform vec3 lightColor;

     void main()
     {
         FragColor = vec4(lightColor * objectColor, 1.0);
     }
     ```
   - �]�m�C��G
     ```cpp
     lightingShader.use();
     lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
     lightingShader.setVec3("lightColor",  1.0f, 1.0f, 1.0f);
     ```

6. **�O���ۦ⾹�G**
   - �Ыؤ@�ӱM�Ϊ����q�ۦ⾹�A�T�O�O���C�⤣���v�T�G
     ```glsl
     #version 330 core
     out vec4 FragColor;

     void main()
     {
         FragColor = vec4(1.0); // �`�q�զ�
     }
     ```

7. **�O����m�G**
   - �]�m������m�M�Y��G
     ```cpp
     glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
     model = glm::mat4();
     model = glm::translate(model, lightPos);
     model = glm::scale(model, glm::vec3(0.2f));
     ```

8. **ø�s�O�ߤ���G**
   - �ϥοO���ۦ⾹ø�s�G
     ```cpp
     lampShader.use();
     // �]�m�ҫ��B���ϩM��v�x�}
     ...
     glBindVertexArray(lightVAO);
     glDrawArrays(GL_TRIANGLES, 0, 36);
     ```
