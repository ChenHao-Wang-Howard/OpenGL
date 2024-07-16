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

