# Basic Lighting
## �ؿ�
1. [��¦����](#��¦����)
2. [���ҥ���](#���ҥ���)
3. [���Ϯg����](#���Ϯg����)
4. [�k�V�q](#�k�V�q)
5. [�p�⺩�Ϯg����](#�p�⺩�Ϯg����)
6. [�̫�@��ơG�k�V�q�ഫ�P�k�u�x�}](#�̫�@��ơG�k�V�q�ഫ�P�k�u�x�})
7. [�譱����](#�譱����)

## ��¦����
- ���ҥ���(Ambient Lighting)�G�Y�Ϧb�·t�����p�U�A�@�ɤW�q�`���M���@�ǥ��G�]��G�B���B�����^�A�ҥH����X�G�û����|�O�����·t���C���F�����o�ӡA�ڭ̷|�ϥΤ@�����ҥ��ӱ`�ơA���û��|������@���C��C
- ���Ϯg����(Diffuse Lighting)�G���������磌�骺��V�ʼv�T(Directional Impact)�C���O������Ӽҫ�����ı�W����۪����q�C���骺�Y�@�����V�O����ۥ����A���N�|�V�G�C
- �譱����(Specular Lighting)�G���������A����W���X�{���G�I�C�譱���Ӫ��C����骺�C��|����ɦV�����C��C
## ���ҥ���

**�I�������G**
- **�����S��**�G���q�`�Ӧۦh�Ӥ����������A�|�o���äϼu��������I�A�磌�鲣�Ͷ����v�T�C
- **����ө�**�G�o�ئҼ{�Ϯg�M���g���t��k���M��T�A���L������B�귽�ӶO�j�C

**²�Ƽҫ��G���ҥ���**
- �ϥ����ҥ��Ӽ����������g�ĪG�A�@������ө���²�ƪ����C
- �Y�ϳ������S�����������A���ҥ��Ӥ�������ݰ_�Ӧ��ǳ\���G�C

**��@�B�J�G**
1. **�]�w���ҥ��j��**�G
   - �w�q���ҥ��j�ס]`ambientStrength`�^�A�Ψӱ������ҥ����v�T�{�סC

2. **�p�����ҥ�**�G
   - ���ҥ��C��p��G�N�����C�⭼�H���ұj�ױ`�ơC
   - �̲פ��q�C��G�N���ҥ��C��P�����C��ۭ��A�ó]�w�����q�C��C

3. **�ۦ⾹�G**
   ```glsl
   void main()
   {
       float ambientStrength = 0.1; // ���ҥ��j��
       vec3 ambient = ambientStrength * lightColor; // ���ҥ��C��

       vec3 result = ambient * objectColor; // �̲פ��q�C��
       FragColor = vec4(result, 1.0); // �]�w���q�C��
   }
   ```

**���G�G**
- �B��{����A���餣�A�����·t�A�ӬO��ܥX���ҥ��Ӫ��ĪG�C
- **�`�N**�G�����ߤ��餣���v�T�A�]���ϥΤF���P���ۦ⾹�C


## ���Ϯg����
**�p�⺩�Ϯg���ӻݭn����H**
- �k�V�q�G�@�ӫ������I�����V�q�C
- �w�V�����u�G�@����������m�P���q����m�����V�q�t����V�V�q�C���F�p��o�ӥ��u�A�ڭ̻ݭn������m�V�q�M���q����m�V�q�C
## �k�V�q
**�����G**
- **�k�V�q (Normal Vector)**�G�������I�������V�q�C�]����ӳ��I�L�k�w�q���A�ҥH�ϥΩP�򪺳��I�p��X�ӳ��I���k�V�q�C

**��k�G**
- **��ʲK�[�k�V�q**�G���²�檺3D�Ϊ��p�ߤ���A�i�H��ʲK�[�k�V�q�ܳ��I�ƾڤ��C
- **�e���k�p��**�G�]�i�H�ϥΤe���p��C�ӭ����k�V�q�C

**���I�ۦ⾹��s�G**
- ���C�ӳ��I�K�[�k�V�q�A�ç�s���I�ۦ⾹�H�����o�ǼƾڡC

```glsl
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
```

**���I�ݩʫ��Ч�s�G**
- ��s���I�ݩʫ��ХH�A���]�t�k�V�q���s���I�}�C�C

```cpp
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
```

- **�`�N**�G�O���ۦ⾹���ϥΪk�V�q�A���@�ɦP�@���I�ƾڡA�]�����ݭק�O���ۦ⾹���ݩʰt�m�C

**�Ĳv�Ҷq�G**
- ���޿O���ۦ⾹���ϥΪk�V�q�A�����Q�νc�l�����I�ƾڦs�x�bGPU�O���餤����Ƨ󬰰��ġA�קK�B�~��VBO���t�C

**�ǻ��k�V�q����q�ۦ⾹�G**
- �b���I�ۦ⾹���A�ǻ��k�V�q�ܤ��q�ۦ⾹�C

```glsl
out vec3 Normal;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    Normal = aNormal; // �ǻ��k�V�q
}
```

**���q�ۦ⾹�G**
- �w�q��������J�ܼƥH�����k�V�q�C

```glsl
in vec3 Normal;
```

## �p�⺩�Ϯg����
**�ؼСG**
- �ϥΪk�V�q�B������m�M���q��m�p�⪫�骺���Ϯg���ӮĪG�C

**�B�J�G**

1. **������m�G**
   - �b���q�ۦ⾹���ŧi������m�� `uniform` �ܼơG
     ```glsl
     uniform vec3 lightPos;
     ```
   - ��s `uniform`�G
     ```cpp
     lightingShader.setVec3("lightPos", lightPos);
     ```

2. **���q��m�G**
   - �b�@�ɪŶ����i����ӭp��A�ݭn���q���@�ɪŶ���m�C
   - �b���I�ۦ⾹���p�⳻�I���@�ɪŶ��y�СG
     ```glsl
     out vec3 FragPos;  
     out vec3 Normal;

     void main()
     {
         gl_Position = projection * view * model * vec4(aPos, 1.0);
         FragPos = vec3(model * vec4(aPos, 1.0)); // �@�ɪŶ��y��
         Normal = aNormal;
     }
     ```

3. **���q�ۦ⾹��s�G**
   - �b���q�ۦ⾹���[�J��������J�ܼơG
     ```glsl
     in vec3 FragPos;
     in vec3 Normal;
     ```

4. **�p���V�V�q�G**
   - �p������P���q��m��������V�V�q�A�üзǤƦV�q�G
     ```glsl
     vec3 norm = normalize(Normal);
     vec3 lightDir = normalize(lightPos - FragPos);
     ```

5. **�p�⺩�Ϯg���ӡG**
   - �� `norm` �M `lightDir` �i���I���A�p�⺩�Ϯg�v�T�C
   - �ϥ� `max` ����קK�t�ƭȡG
     ```glsl
     float diff = max(dot(norm, lightDir), 0.0);
     vec3 diffuse = diff * lightColor; // ���Ϯg���q
     ```

6. **�p����q�̲��C��G**
   - �N���ҥ��M���Ϯg���ۥ[�A�í��H�����C��G
     ```glsl
     vec3 result = (ambient + diffuse) * objectColor;
     FragColor = vec4(result, 1.0); // �̲פ��q�C��
     ```

**�`�N�ƶ��G**
- **�зǤ�**�G�T�O�Ҧ��A�έp�⪺�V�q�����V�q�A�H²�ƭp��C
- **�קK�t�ƥ���**�G�ϥ� `max` ��ƽT�O���Ϯg���|�ܦ��t�ơA�t���C�⪺���u�O�S���N�q���C

## �̫�@��ơG�k�V�q�ഫ�P�k�u�x�}


**���D�I���G**
- �k�V�q���ഫ��@�ɪŶ��y�ХH�i����ӭp��C
- �k�V�q�u�N���V�A�L�S�w��m�A�����첾�v�T�C
- ����²��a�μҫ��x�}���k�V�q�A�ݥh���첾�����C

**�������Y�񪺼v�T�G**
- �������Y��|�}�a�k�V�q�������ʡA�v�T���ӮĪG�C
- �����Y��ȧ��ܪk�V�q�����סA�q�L�зǤƥi�״_�C

**�ѨM��סG�k�u�x�} (Normal Matrix)**
- **�k�u�x�}�w�q**�G�ҫ��x�}���W��3x3�������f�x�}����m�x�}�C
- **�@��**�G�ץ��������Y���k�V�q���v�T�C

**�b���I�ۦ⾹���p��k�u�x�}�G**

```glsl
Normal = mat3(transpose(inverse(model))) * aNormal;
```

- **��Ƹ����G**
  - `inverse(matrix)`�G�p��x�}���f�x�}�C
  - `transpose(matrix)`�G�p��x�}����m�x�}�C
  - `mat3()`�G�N4x4�x�}�j���ഫ��3x3�x�}�A�h���첾�ݩʡC

**�`�N�ƶ��G**
- **�ʯ�Ҷq**�G�x�}�D�f�B��b�ۦ⾹���}�P���j�C
  - **��ĳ**�G�bCPU�W�p��k�u�x�}�A�M��q�L `uniform` �ǻ����ۦ⾹�C
  
**��@�B�J�G**

1. **�b���I�ۦ⾹���p��k�V�q���@�ɪŶ��y�СG**

   ```glsl
   out vec3 Normal;

   void main()
   {
       gl_Position = projection * view * model * vec4(aPos, 1.0);
       FragPos = vec3(model * vec4(aPos, 1.0));
       Normal = mat3(transpose(inverse(model))) * aNormal; // �ϥΪk�u�x�}
   }
   ```

2. **�b���q�ۦ⾹�������k�V�q�G**

   ```glsl
   in vec3 Normal;
   ```

**�ϥΪk�u�x�}�����n�ʡG**
- ��磌��i�椣�����Y��ɡA�����ϥΪk�u�x�}�ӫO���k�V�q�����T�ʡC
- ��S���Y��Υu�������Y��ɡA�ϥμҫ��x�}���H�k�u�O�i�檺�A���b�������Y�񱡪p�U�ݨϥΪk�u�x�}�C


## �譱����

**�ؼСG**
- ����������Ӽҫ�����{�A�q�L�ޤJ�譱���� (Specular Highlight) �Ӵ��ɥ��ӮĪG�C

**�����G**
- **�譱����**�G�P���Ϯg���������A�����٨̿���[���V�A�M�w������Ϯg�S�ʡC
- **�Ϯg�V�q**�G�q�L�k�V�q½��J�g������V�ӭp��A�譱�����b�[���V�P�Ϯg�V�q�����̤p�ɮĪG�̱j�C

**�[��V�q�G**
- �ϥ��[��̪��@�ɪŶ���m�]��v����m�^�M���q����m�ӭp���[��V�q�C

**�B�J�G**

1. **�b���q�ۦ⾹���ޤJ�[��̦�m�G**
   - �w�q�@�� `uniform` �ܼƨ���o�[��̡]��v���^���@�ɪŶ���m�G
     ```glsl
     uniform vec3 viewPos;
     ```

   - �b��V�`�����ǻ���v������m�V�q�G
     ```cpp
     lightingShader.setVec3("viewPos", camera.Position);
     ```

2. **�w�q�譱�j�סG**
   - �]�w�譱�j�ץH�����譱�������v�T�G
     ```glsl
     float specularStrength = 0.5;
     ```

3. **�p����u�M�Ϯg��V�V�q�G**
   - �p����u��V�V�q�M�Ϯg��V�V�q�G
     ```glsl
     vec3 viewDir = normalize(viewPos - FragPos);
     vec3 reflectDir = reflect(-lightDir, norm);
     ```

   - **�`�N**�G`reflect` ��ƭn�D�J�g����V�O�q�������V���q��m�A�]���ݭn���� `lightDir`�C

4. **�p���譱���ӡG**
   - �p����u��V�P�Ϯg��V���I���A�è��侭����o���譱�j�סG
     ```glsl
     float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
     vec3 specular = specularStrength * spec * lightColor;
     ```

   - **�������ϥ��� (Shininess)**�G�]��32�A����Ϯg���j�שM�����I���j�p�C

5. **�p��̲פ��q�C��G**
   - �N���ҥ��B���Ϯg���M�譱���ۥ[�A�í��H�����C��o��̲��C��G
     ```glsl
     vec3 result = (ambient + diffuse + specular) * objectColor;
     FragColor = vec4(result, 1.0);
     ```

**�`�N�ƶ��G**
- **���u�M�Ϯg��V���I��**�G�Ω�T�w�[��̵����U���譱�����j�סA�T�O�ȫD�t�C
- **�ϥ��׳]�w**�G�ϥ��׶V���A�Ϯg���V�����A�����I�V�p�C




