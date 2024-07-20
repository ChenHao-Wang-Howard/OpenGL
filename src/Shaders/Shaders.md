# Shaders
## �ؿ�
1. [GLSL](#GLSL)
2. [�������](#�������)
3. [��J�P��X](#��J�P��X)
4. [Uniform](#Uniform)
5. [��h�ݩ�](#��h�ݩ�)
6. [�ڭ̦ۤv���ۦ⾹��](#�ڭ̦ۤv���ۦ⾹��)
7. [�q�ɮׯ���](#�q�ɮׯ���)

## GLSL
#### �򥻷���
- **GLSL**�G�@������C�y�����ۦ⾹�y���A�M���ϧέp��]�p�C
- **�D�n�S��**�G�]�t�w��V�q�M�x�}�ާ@�����ίS�ʡC
- **���c**�G�ۦ⾹�}�Y�ŧi�����A���۬O��J/��X�ܼơBuniform�Mmain��ơC

#### �嫬�ۦ⾹���c
```cpp
#version version_number
in type in_variable_name;
in type in_variable_name;

out type out_variable_name;

uniform type uniform_name;

void main()
{
    // �B�z��J�öi��@�ǹϧξާ@
    ...
    // �N�B�z�L�����G��X���X�ܼ�
    out_variable_name = weird_stuff_we_processed;
}
```

#### ���I�ۦ⾹
- **��J�ܼ�**�G���I�ݩ� (Vertex Attribute)�C
- **�W��**�G�ѵw��M�w�AOpenGL�ܤ֫O��16�ӥ]�t4���q�����I�ݩʡC
- **�d�ߤ�k**�G�ϥ�`GL_MAX_VERTEX_ATTRIBS`�d�ߤW���C

```cpp
int nrAttributes;
glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
std::cout << "Maximum number of vertex attributes supported: " << nrAttributes << std::endl;
```



## �������


#### �򥻷���
- **GLSL��ƫ��O**�G����C�y���A�]�tint�Bfloat�Bdouble�Buint�Mbool�C
- **�e������**�G�V�q(Vector)�M�x�}(Matrix)�A�x�}�|�b���᪺�е{���Q�סC

#### �V�q
- �V�q�O�@�ӥ]�t2�B3��4�Ӥ��q���e���A���q�����i�H�O���@��¦�����C
- �`�Ϊ��V�q�����G
  - `vecn`�G�]�tn��float���q���w�]�V�q
  - `bvecn`�G�]�tn��bool���q���V�q
  - `ivecn`�G�]�tn��int���q���V�q
  - `uvecn`�G�]�tn��unsigned int���q���V�q
  - `dvecn`�G�]�tn��double���q���V�q
- **�`�Ϊ�float�V�q**�G`vecn`�A�����j�h�ƻݨD�C

#### ����V�q���q
- �ϥ�`.x`�B`.y`�B`.z`�M`.w`�����1���4�Ӥ��q�C
- �i��`rgba`����C����q�A��`stpq`������z�y�Ф��q�C

#### ���� (Swizzling)
- **����**�G�F����ܩM�զX�V�q���q���s�覡�C
  ```cpp
  vec2 someVec;
  vec4 differentVec = someVec.xyxx;
  vec3 anotherVec = differentVec.zyw;
  vec4 otherVec = someVec.xxxx + anotherVec.yxzy;
  ```
- **����**�G����bvec2�����`.z`�����C

#### �V�q�غc���
- �ϥΦV�q�@���ѼơA��ֻݨD�Ѽƪ��ƶq�C
  ```cpp
  vec2 vect = vec2(0.5, 0.7);
  vec4 result = vec4(vect, 0.0, 0.0);
  vec4 otherResult = vec4(result.xyz, 1.0);
  ```
## ��J�P��X
### ��J�P��X - ���O

#### �򥻷���
- **GLSL**�ϥ�`in`�M`out`����r�ӳ]�w�ۦ⾹����J�M��X�A�i���ƶǻ��C
- �C�ӵۦ⾹����X�ܼƷ|�ǻ����U�@�ӵۦ⾹���q����J�ܼơC

#### ���I�ۦ⾹
- **��J�ܼ�**�G�����q���I��Ʊ�����J�A�ݨϥ�`layout (location = 0)`���w��m�C
- �i�H�ϥ�`glGetAttribLocation`�d���ݩʦ�m�ȡA���b�ۦ⾹���]�w��²������C

#### ���q�ۦ⾹
- �����w�q�@��`vec4`�������C���X�ܼơA�_�hOpenGL�|�N�����V���¦�Υզ�C

#### �ǻ��ƾ�
- �n�q�@�ӵۦ⾹�V�t�@�ӵۦ⾹�ǻ��ƾڡA�ݭn�b�o�e���n����X�ܼơA�b�������n���ۦP�W�٩M��������J�ܼơC
- OpenGL�|�b�s���{�Ǫ���ɱN�o���ܼƳs���_�ӡC

#### �d�ҡG�q���I�ۦ⾹�V���q�ۦ⾹�ǻ��C��
- **���I�ۦ⾹**�G
  ```cpp
  #version 330 core
  layout (location = 0) in vec3 aPos;

  out vec4 vertexColor;

  void main()
  {
      gl_Position = vec4(aPos, 1.0);
      vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // �t����
  }
  ```
- **���q�ۦ⾹**�G
  ```cpp
  #version 330 core
  out vec4 FragColor;

  in vec4 vertexColor;

  void main()
  {
      FragColor = vertexColor;
  }
  ```
- **���G**�G���q�ۦ⾹�����쳻�I�ۦ⾹�ǨӪ��`����A�ÿ�X���C��C

## Uniform


#### �򥻷���
- **Uniform**�G�q���ε{��(CPU)�ǻ��ƾڨ�ۦ⾹(GPU)���@�ؤ覡�C
- **�S��**�G
  1. �����(Global)�G�C�ӵۦ⾹�{�Ǥ���uniform�ܶq���O�W�@�L�G���A�i�H�b����ۦ⾹���q�X�ݡC
  2. ���[�ʡGuniform�ȷ|�@���O�s�A����Q���m�Χ�s�C

#### �ŧi�P�ϥ�
- �bGLSL���ŧiuniform�G
  ```cpp
  #version 330 core
  out vec4 FragColor;

  uniform vec4 ourColor;

  void main()
  {
      FragColor = ourColor;
  }
  ```
- �b���q�ۦ⾹���ŧi�@��`uniform vec4`��`ourColor`�A�ñN���q�ۦ⾹����X�C��]��uniform�ȡC

#### �]�mUniform��
- �d��ۦ⾹��uniform�ݩʪ�����/��m�ȡG
  ```cpp
  int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
  ```
- ��suniform�ȡG
  ```cpp
  glUseProgram(shaderProgram);
  glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
  ```

#### ��{�C���H�ɶ��ܤ�
- ����B��ɶ��A�p����Ȩç�suniform�G
  ```cpp
  float timeValue = glfwGetTime();
  float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
  int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
  glUseProgram(shaderProgram);
  glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
  ```

#### OpenGL����glUniform���
- OpenGL��������������A�ҥHglUniform��Ʀ��h�ӫ����Ѥ��P�����G
  - `f`�Gfloat
  - `i`�Gint
  - `ui`�Gunsigned int
  - `3f`�G3��float
  - `fv`�Gfloat�V�q/�Ʋ�

#### �b��V�j�餤��sUniform
- �C�����N����suniform�ȡA��{�C���ܤơG
  ```cpp
  while(!glfwWindowShouldClose(window))
  {
      processInput(window);

      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT);

      glUseProgram(shaderProgram);

      float timeValue = glfwGetTime();
      float greenValue = sin(timeValue) / 2.0f + 0.5f;
      int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
      glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

      glBindVertexArray(VAO);
      glDrawArrays(GL_TRIANGLES, 0, 3);

      glfwSwapBuffers(window);
      glfwPollEvents();
  }
  ```

#### �p��
- Uniform�ܶq�Ω�b���ε{���M�ۦ⾹�����ǻ��ƾڡA�åB�b��V���N���i�H�H�ɧ�s�C
- Uniform�O�@�ӥ����ܼơA�b�ۦ⾹�{�Ǫ����󶥬q���i�H�X�ݡC
- �b���I�ݩʵL�k�����ݨD�ɡA�ϥ�Uniform�O�@�Ӧ��Ī��ѨM��סC

## ��h�ݩ�


#### �򥻷���
- �W�[�C���ƨ쳻�I��Ƥ��A�C�ӳ��I��3��float�Ȫ���C��]RGB�^�C
- ��s���I�ۦ⾹�H�����C��@�����I�ݩʿ�J�C

#### �s�W�C���ƪ����I�Ʋ�
```cpp
float vertices[] = {
    // ��m              // �C��
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // �k�U
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ���U
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // ����
};
```

#### ��s���I�ۦ⾹
- �����C��ÿ�X����q�ۦ⾹
```cpp
#version 330 core
layout (location = 0) in vec3 aPos;   
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(aPos, 1.0);
    ourColor = aColor;
}
```

#### ��s���q�ۦ⾹
- �����èϥγ��I�ۦ⾹�ǨӪ��C��
```cpp
#version 330 core
out vec4 FragColor;  
in vec3 ourColor;

void main()
{
    FragColor = vec4(ourColor, 1.0);
}
```

#### �t�m���I�ݩʫ���
- ��s`glVertexAttribPointer`��ƥH�B�z�s�����I�ƾڧG��
```cpp
// ��m�ݩ�
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// �C���ݩ�
glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);
```
- �s���B���Ȭ�`6 * sizeof(float)`�]3�Ӧ�m�� + 3���C��ȡ^�C
- �C���ݩʪ������q��`3 * sizeof(float)`�C

#### �C�ⴡ��
- ��V�T���ήɡA���]�ƶ��q�|�ͦ����I��h�����q�A�i���C�ⴡ�ȡC
- ���q�C��ھڳ��I�C��M��m�i��u�ʴ��ȡA��{�C��L��C

#### ���G
- �B��{�����Ӭݨ�T�ӳ��I���O�����B��B�Ŧ⪺�T���ΡA�æb�T���Τ����e�{�C�⺥�ܮĪG�C

---

�o�ǵ��O�[�\�F�b���I��Ƥ��K�[��h�ݩʡ]�p�C��^���L�{�A�îi�ܤF�p���s�ۦ⾹�M���I�ݩʫ��ХH�B�z�s�����I�ƾڧG���A���U�A�ֳt�z�ѩM�^�U�������e�C
## �ڭ̦ۤv���ۦ⾹��


#### �򥻷���
- �g�B�sĶ�M�޲z�ۦ⾹�O�@��·ШơA�ڭ̷|�Ыؤ@�����O��²�Ƴo�ӹL�{�C
- �o�����O�i�H�q�w��Ū���ۦ⾹�A�sĶ�ós�����̡A�ù復�̶i����~�˴��C

#### ���O���c
- �ڭ̷|�N�ۦ⾹���O������b�Y�ɸ̡A��K�ǲߩM���ӡC

#### �Y�ɤ��e
- �]�t���n��include�A�éw�q���O���c�G
```cpp
#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // �]�tglad������Ҧ����ݪ�OpenGL�Y���

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    // �{��ID
    unsigned int ID;

    // �غc�l�AŪ���úc�صۦ⾹
    Shader(const char* vertexPath, const char* fragmentPath);
    // �ϥ�/�E���{��
    void use();
    // uniform�u����
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
};

#endif
```

#### ����
- �ϥιw�B�z���O����ƥ]�t�G
  ```cpp
  #ifndef SHADER_H
  #define SHADER_H
  ```
- �w�B�z���O�i���sĶ���b��󥼳Q�]�t�L�����p�U�~�]�t�M�sĶ�o���Y���A����s���Ĭ�C
- ���O`Shader`�x�s�F�ۦ⾹�{����ID�C
- �غc�l�ݭn���I�M���q�ۦ⾹��l�X���ɮ׸��|�A���\�q�w��Ū����l�X��r�ɮסC
- �u���ơG
  - `use`�G�E���ۦ⾹�{�ǡC
  - `setBool`�B`setInt`�B`setFloat`�G�d��uniform��m�ó]�w��ȡC


## �q�ɮׯ���


#### �򥻷���
- �ϥ�C++�ɮ׬yŪ���ۦ⾹���e�A�N��s�x��string���󤤡C
- �sĶ�M�s���ۦ⾹�A���ˬd�sĶ/�s���L�{�������~�C

#### Ū���ɮפ��e
- �ϥ�C++�ɮ׬y�q���w���|Ū�����I�M���q�ۦ⾹�����e�C
- �N�ɮפ��e�s�x��string���󤤡G
  ```cpp
  Shader(const char* vertexPath, const char* fragmentPath)
  {
      // 1. �q�����|��������I/���q�ۦ⾹
      std::string vertexCode;
      std::string fragmentCode;
      std::ifstream vShaderFile;
      std::ifstream fShaderFile;
      // �O��ifstream��H�i�H�ߥX���`�G
      vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
      try 
      {
          // ���}���
          vShaderFile.open(vertexPath);
          fShaderFile.open(fragmentPath);
          std::stringstream vShaderStream, fShaderStream;
          // Ū����󪺽w�Ĥ��e��ƾڬy��
          vShaderStream << vShaderFile.rdbuf();
          fShaderStream << fShaderFile.rdbuf();       
          // �������B�z��
          vShaderFile.close();
          fShaderFile.close();
          // �ഫ�ƾڬy��string
          vertexCode = vShaderStream.str();
          fragmentCode = fShaderStream.str();     
      }
      catch (std::ifstream::failure e)
      {
          std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
      }
      const char* vShaderCode = vertexCode.c_str();
      const char* fShaderCode = fragmentCode.c_str();
  }
  ```

#### �sĶ�M�s���ۦ⾹
- �sĶ���I�M���q�ۦ⾹�A�ˬd�sĶ���~�G
  ```cpp
  // 2. �sĶ�ۦ⾹
  unsigned int vertex, fragment;
  int success;
  char infoLog[512];

  // ���I�ۦ⾹
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  // ���L�sĶ���~�]�p�G�����ܡ^
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success)
  {
      glGetShaderInfoLog(vertex, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
  };

  // ���q�ۦ⾹�]����
  [...]

  // �ۦ⾹�{��
  ID = glCreateProgram();
  glAttachShader(ID, vertex);
  glAttachShader(ID, fragment);
  glLinkProgram(ID);
  // ���L�s�����~�]�p�G�����ܡ^
  glGetProgramiv(ID, GL_LINK_STATUS, &success);
  if (!success)
  {
      glGetProgramInfoLog(ID, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
  }

  // �R���ۦ⾹�A���̤w�g�s����ڭ̪��{�Ǥ��F�A�w�g���A�ݭn�F
  glDeleteShader(vertex);
  glDeleteShader(fragment);
  ```

#### �ϥΨ��
- ²�檺�ϥΨ��`use`�G
  ```cpp
  void use() 
  { 
      glUseProgram(ID);
  }
  ```

#### Uniform�]�m���
- �]�muniform�ܼƪ��ȡG
  ```cpp
  void setBool(const std::string &name, bool value) const
  {
      glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value); 
  }
  void setInt(const std::string &name, int value) const
  { 
      glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
  }
  void setFloat(const std::string &name, float value) const
  { 
      glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
  } 
  ```

#### �ϥεۦ⾹���O
- �Ыؤ@�ӵۦ⾹��H�èϥΥ��G
  ```cpp
  Shader ourShader("path/to/shaders/shader.vs", "path/to/shaders/shader.fs");
  ...
  while(...)
  {
      ourShader.use();
      ourShader.setFloat("someUniform", 1.0f);
      DrawStuff();
  }
  ```

#### �p��
- Ū�����I�M���q�ۦ⾹�����e�A�sĶ�ós���A���ˬd���~�C
- �ϥ�²�檺`use`��ƨӿE���ۦ⾹�{�ǡC
- �]�muniform�ܼƭȪ���ơA��K�b��V�`�����ʺA��suniform�C


