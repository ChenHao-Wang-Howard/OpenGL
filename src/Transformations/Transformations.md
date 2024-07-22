# Transformations

## �ؿ�
1. [�ܴ�](#�ܴ�)
2. [�V�q](#�V�q)
3. [�V�q�P�жq�B��](#�V�q�P�жq�B��)
4. [�V�q����](#�V�q����)
5. [�V�q�[��](#�V�q�[��)
6. [����](#����)
7. [�V�q�ۭ�](#�V�q�ۭ�)
8. [�x�}](#�x�})
9. [�x�}���[��](#�x�}���[��)
10. [�x�}���ƭ�](#�x�}���ƭ�)
11. [�x�}�ۭ�](#�x�}�ۭ�)
12. [�x�}�P�V�q�ۭ�](#�x�}�P�V�q�ۭ�)
13. [���x�}](#���x�})
14. [�Y��](#�Y��)
15. [�첾](#�첾)
16. [����](#����)
17. [�x�}���զX](#�x�}���զX)
18. [���](#���)
19. [GLM](#GLM)

## �ܴ�
## �V�q
## �V�q�P�жq�B��
## �V�q����
## �V�q�[��

#### �򥻷���
- **�V�q**�G�@�Ө㦳��V�M�j�p�]�j�שΪ��ס^���q�C
- **�|��**�G���_�Ϫ����ܡu�V����10�B�v���A�u���v�O��V�A�u10�B�v�O�V�q�����סC
- **����**�G�V�q�i�H�b���N���פW�A�q�`�ϥ�2��4����ܡC
- **�жq**�G�жq(Scalar)�u�O�@�ӼƦr�]�ζȦ��@�Ӥ��q���V�q�^

#### 2D �V�q
- �V�q�b2D�v�����νb�Y��ܡA�p(x, y)�C
- �V�q���_�l�I���P����V�M�j�p�ۦP�A���̬O�۵����C


#### �V�q�P��m
- �V�q�i�H�q(0, 0, 0)���V�Y���I�A�٬���m�V�q�]Position Vector�^�C
- �Ҧp�G��m�V�q(3, 5)�q(0, 0)���V(3, 5)�C

#### �V�q�B��
- **�V�q�P�жq�B��**�G�V�q�i�H�P�жq�i��[����B��A��C�Ӥ��q���O�B��G

  - �`�N�G�жq���V�q�M�жq��V�q�O���w�q���B��C
  - ���G�ƾǤW�S���V�q�P�жq�ۥ[���B��A���u�ʥN�ƨ禡�w�]�pGLM�^����o�عB��C

- **�V�q����**�G�N�V�q��V�f��A��C�Ӥ��q���ϡG


- **�V�q�[��**�G���q�ۥ[�G

- **�V�q��k**�G����[�W�ĤG�ӦV�q���ۤϦV�q�G
 


## ����


#### �򥻷���
- **�V�q����/�j�p**�G�i�H�ϥΤĪѩw�z�]Pythagoras Theorem�^�p��C
- **�V�q���פ���**�G


#### ���V�q
- **�w�q**�G���V�q�����׬�1�C
- **�зǤ�**�G�N���N�V�q���C�Ӥ��q���H�V�q�����ץi�H�o�����V�q�G


## �V�q�ۭ�


#### �򥻷���
- �V�q�����q���k�S���w�q�A������دS�w�����k�覡�G**�I���]Dot Product�^** �M **�e���]Cross Product�^**�C

#### �I��
- **�I������**


#### �e��
- **�w�q**�G�e���Ȧb3D�Ŷ������w�q�A�ݭn��Ӥ�����V�q�@����J�A���ͤ@�ӥ�����ӿ�J�V�q���ĤT�ӦV�q�C



## �x�}
## �x�}���[��
## �x�}���ƭ�
## �x�}�ۭ�
## �x�}�P�V�q�ۭ�
## ���x�}
## �Y��
## �첾
## ����
## �x�}���զX

## GLM


#### ²��
- **GLM**�GOpenGL Mathematics���Y�g�A�O�@�ӥu�ݥ]�t�Y�ɪ��禡�w�A�L�ݳs���M�sĶ�C
- **�����`�N**�G�q0.9.9�����_�A�x�}�����w�]���s�x�}�]��0�^�A���O���x�}�]�﨤������1�^�C��l�Ưx�}�ݨϥ� `glm::mat4 mat = glm::mat4(1.0f)`�C

#### �]�t���n���Y��
```cpp
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
```

#### �Ҥl - �V�q�첾
- **�V�q�첾**�G�N�V�q (1, 0, 0) �첾 (1, 1, 0) �ӳ��C
```cpp
glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
glm::mat4 trans = glm::mat4(1.0f);
trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
vec = trans * vec;
std::cout << vec.x << vec.y << vec.z << std::endl; // ��X���G���� 2, 1, 0
```

#### �Ҥl - �x�α���P�Y��
- **�x�α���90�שM�Y��0.5��**�G
```cpp
glm::mat4 trans = glm::mat4(1.0f);
trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
trans = glm::scale(trans, glm::vec3(0.5, 0.5, 0.5));
```

#### �N�x�}�ǻ����ۦ⾹
- **�קﳻ�I�ۦ⾹**�G
```glsl
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);
}
```

- **�bC++�{�����ǻ��x�}���ۦ⾹**�G
```cpp
unsigned int transformLoc = glGetUniformLocation(ourShader.ID, "transform");
glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
```
- �o�q�{���X�����d�� `transform` uniform �ܼƪ���}�A�M��� `glUniformMatrix4fv` �N�x�}��ƶǰe���ۦ⾹�C

#### ����c�l�æ첾��k�U��
- **�C���`�������ܴ���s**�G
```cpp
glm::mat4 trans = glm::mat4(1.0f);
trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
```
- �o�q�{���X���N�c�l��¶���I����A�M��첾��������k�U���C


