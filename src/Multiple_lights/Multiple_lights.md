# Multiple_lights
## �ؿ�
1. [�h����](#�h����)
2. [�w�V��](#�w�V��)
3. [�I����](#�I����)
4. [�X�ֵ��G](#�X�ֵ��G)



## �h����
- **�h���������G**
  - �o�ӳ����N�]�t���ӥ����G�@�������Ӷ����w�V���B�|�Ӥ����b���������I�����B�H�Τ@�Ӥ�q���C

- **���������G**
  - **�w�V�� (Directional Light)�G** �����Ӷ������Z�������A���u��V�@�P�C
  - **�I���� (Point Light)�G** �����b�������������A���u�q�I���V�~��g�C
  - **�E�� (Spotlight)�G** ��q���ĪG�A���u�����b�@�ӯS�w����V�C

- **GLSL��ƪ��ϥΡG**
  - ���F�޲z�h�ӥ������p��A�ڭ̱N���ӭp��ʸ˨�GLSL��Ƥ��C
  - �C�إ����������P���p���k�A�]�����C�إ��������Ыؤ@�Ө�Ʀ��U��O���{���X���C

- **GLSL��ƪ����c�G**
  - ��ƻPC�y��������������A�]�t��ƦW�B�^�ǭ��������C
  - �C�ӥ��������]�w�V���B�I�����B�E���^�U�۾֦��@�Ө�ơC

- **���ӭp��y�{�G**
  - �ϥΤ@�ӳ�W���C��V�q�ӥN����q���̲׿�X�C��C
  - �C�ӥ�������q���^�m�C��[���X�C��V�q�W�A�Φ��̲ת���X�C��C

- **�d�ҵ��c�G**

  ```glsl
  out vec4 FragColor;

  void main()
  {
    // �w�q�@�ӿ�X�C���
    vec3 output = vec3(0.0);
    
    // �N�w�V�����^�m�[���X��
    output += calculateDirectionalLight();
    
    // ��Ҧ����I�����]���ۦP���Ʊ�
    for(int i = 0; i < nr_of_point_lights; i++)
      output += calculatePointLight(i);
    
    // �[�W�E�����^�m
    output += calculateSpotLight();

    FragColor = vec4(output, 1.0);
  }
  ```

  - **�����G**
    - `calculateDirectionalLight()`�G�p��w�V������q���v�T�C
    - `calculatePointLight(i)`�G��C���I�����i����ӭp��C
    - `calculateSpotLight()`�G�p��E������q���v�T�C
    - `output`�G�֥[�C�ӥ������^�m�A�Φ��̲��C��C


## �w�V��
- **�w�V����Ʃw�q�G**
  - �b���q�ۦ⾹���A�w�q��ƭp��w�V������q���^�m�C
  - ��Ʊ����@�ǰѼƨíp��X�w�V���Ӫ��C��C

- **�w�V�������n�ܼơG**
  - �N�w�V���һݪ��ܼ��x�s�b `DirLight` ���c�餤�C
  - �N `DirLight` ���c��w�q�� `uniform`�A�b�W�@�`�����йL�G

    ```glsl
    struct DirLight {
        vec3 direction;  // ������V
        vec3 ambient;    // ���ҥ����q
        vec3 diffuse;    // ���Ϯg�����q
        vec3 specular;   // �譱�����q
    };  
    uniform DirLight dirLight;
    ```

- **��ƭ쫬�G**
  - �w�q�@�Ө�ƭ쫬 `CalcDirLight`�A�Ω�p��w�V�������ӮĪG�G

    ```glsl
    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
    ```

  - **�`�N�G** �b�I�s��Ƥ��e�A�ݭn�b `main` ��ƤW��w�q��ƭ쫬�C

- **��ưѼơG**
  - ��Ʊ����H�U�ѼơG
    - `DirLight light`�G�w�V�������c��C
    - `vec3 normal`�G���q���k�V�q�C
    - `vec3 viewDir`�G�[���V�V�q�C

- **�w�V���p��G**
  - ��Ƥ������p��ϥΤF�W�@�`�Ǩ쪺���Ӥ����G

    ```glsl
    vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
    {
        vec3 lightDir = normalize(-light.direction);  // �p�������V�V�q
        // ���Ϯg�ۦ�
        float diff = max(dot(normal, lightDir), 0.0);  // �p�⺩�Ϯg�t��
        // �譱���ۦ�
        vec3 reflectDir = reflect(-lightDir, normal);  // �p��Ϯg����V
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  // �p���譱�Ϯg�t��
        // �X�ֵ��G
        vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));  // ���ҥ��^�m
        vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));  // ���Ϯg�^�m
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));  // �譱���^�m
        return (ambient + diffuse + specular);  // ��^�̲��C��
    }
    ```

  - **�L�{�����G**
    - `lightDir`�G�p���������V�V�q�C
    - `diff`�G�p��k�V�q�M���u��V���I�n�A�o�캩�Ϯg�Y�ơC
    - `reflectDir`�G�p����u���Ϯg��V�C
    - `spec`�G�p����u��V�M�Ϯg��V���I�n�A�o���譱�Ϯg�Y�ơC
    - �p�� `ambient`�B`diffuse`�B`specular` ���q�A�̲ת�^�X�᪺֫�C��C

- **�`���G**
  - �ϥ� `CalcDirLight` ��ƭp��w�V�������ӮĪG�C
  - ���ҥ��B���Ϯg���M�譱�����^�m�X�֬���@�C��V�q�ê�^�C
  - �q�L�o�˪��ʸˡA�����ӭp���[�ҲդƩM�M���C

## �I����
- **�I������Ʃw�q�G**
  - �M�w�V�������A�ڭ̻ݭn�w�q�@�ӥΩ�p���I��������q�^�m����ơC
  - �]�t�I��p��A�H�������j���H�Z������z�C

- **�I���������n�ܼơG**
  - �w�q `PointLight` ���c��A�]�t�Ҧ��I�����һݪ��ܼơG

    ```glsl
    struct PointLight {
        vec3 position;    // ������m

        float constant;   // �I��`�ƶ�
        float linear;     // �I��@����
        float quadratic;  // �I��G����

        vec3 ambient;     // ���ҥ����q
        vec3 diffuse;     // ���Ϯg�����q
        vec3 specular;    // �譱�����q
    };  
    ```

- **�h�����]�m�G**
  - �ϥιw�B�z���O�w�q���������I�����ƶq�G

    ```glsl
    #define NR_POINT_LIGHTS 4
    ```

  - �إߤ@�� `PointLight` ���c��ƲաG

    ```glsl
    uniform PointLight pointLights[NR_POINT_LIGHTS];
    ```

  - **�����G** 
    - `NR_POINT_LIGHTS` �O�������I�������ƶq�C
    - `pointLights` �ƲեΩ��x�s�C���I�������ݩʡC

- **�I������ƭ쫬�G**
  - �w�q�p���I�������ӮĪG����ƭ쫬�G

    ```glsl
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
    ```

  - **�Ѽƻ����G**
    - `PointLight light`�G�I���������c��C
    - `vec3 normal`�G���q���k�V�q�C
    - `vec3 fragPos`�G���q����m�C
    - `vec3 viewDir`�G�[���V�V�q�C

- **�I�����p��G**
  - �b��Ƥ��p���I��������q���C��^�m�G

    ```glsl
    vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
    {
        vec3 lightDir = normalize(light.position - fragPos);  // �p����u��V
        // ���Ϯg�ۦ�
        float diff = max(dot(normal, lightDir), 0.0);  // �p�⺩�Ϯg�Y��
        // �譱���ۦ�
        vec3 reflectDir = reflect(-lightDir, normal);  // �p��Ϯg����V
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);  // �p���譱�Ϯg�Y��
        // �I��
        float distance    = length(light.position - fragPos);  // �p���������q���Z��
        float attenuation = 1.0 / (light.constant + light.linear * distance + 
                     light.quadratic * (distance * distance));  // �p��I��]�l
        // �X�ֵ��G
        vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, TexCoords));  // ���ҥ��^�m
        vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, TexCoords));  // ���Ϯg�^�m
        vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));  // �譱���^�m
        ambient  *= attenuation;  // �I�����ҥ�
        diffuse  *= attenuation;  // �I��Ϯg��
        specular *= attenuation;  // �I���譱��
        return (ambient + diffuse + specular);  // ��^�̲��C��
    }
    ```

  - **�p��B�J�G**
    - `lightDir`�G�p���������q����V�C
    - `diff`�G�p��k�V�q�M���u��V���I�n�A�o�캩�Ϯg�Y�ơC
    - `reflectDir`�G�p����u���Ϯg��V�C
    - `spec`�G�p����u��V�M�Ϯg��V���I�n�A�o���譱�Ϯg�Y�ơC
    - `attenuation`�G�p��I��]�l�A�Ҽ{�Z�����v�T�C
    - �p�� `ambient`�B`diffuse`�B`specular` ���q�A�Ҽ{�I���X�֨ê�^�C

- **�ϥΨ�ƭp��h���I�����G**
  - �b `main` ��Ƥ��A�ϥδ`���M���I�����ƲաA��C���I�����ե� `CalcPointLight` ��ơG

    ```glsl
    vec3 result = vec3(0.0);
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLights[i], normal, FragPos, viewDir);
    }
    ```

  - **�u�I�G**
    - �q�L�ʸ˭p��L�{�A�ڭ̥i�H���P�a�B�z�h���I�����C
    - �קK�F���Ƶ{���X�C

## �X�ֵ��G
- **�X�֥����p��G**
  - �ڭ̤w�g�w�q�F�p��w�V���M�I��������ơA�{�b�i�H�N���̾�X�� `main` ��Ƥ��C

- **`main` ��Ƶ��c�G**
  - �p��k�V�q�M���u��V�C
  - ����T�Ӷ��q�����ӭp��G
    1. **�w�V���ӭp��**
    2. **�I�����p��**
    3. **�E���p��**

    ```glsl
    void main()
    {
        // �ݩ�
        vec3 norm = normalize(Normal);
        vec3 viewDir = normalize(viewPos - FragPos);

        // �Ĥ@���q�G�w�V����
        vec3 result = CalcDirLight(dirLight, norm, viewDir);

        // �ĤG���q�G�I����
        for(int i = 0; i < NR_POINT_LIGHTS; i++)
            result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);    

        // �ĤT���q�G�E��
        // result += CalcSpotLight(spotLight, norm, FragPos, viewDir);    

        FragColor = vec4(result, 1.0);
    }
    ```

  - **�����G**
    - �ϥΰj��M���Ҧ��I�����A�p��ò֥[���̲��C�⪺�^�m�C
    - �C�ӥ������^�m�Q�֥[��̲ת���X�C�⤤�C

- **��������u�ơG**
  - �C�إ�����Ƥ����\�h���ƪ��p��A�s�b�u�ƪŶ��C
  - �i�H�N���ƭp���H�ơA�����Ĳv�C

- **�]�w������ `uniform` �ȡG**
  - �w�V���� `uniform` �]�w��k�G
    - �����]�w `DirLight` ���c�骺�ݩʭȡC

  - �I������ `uniform` �]�w��k�G
    - `pointLights` �O `PointLight` ���ƲաA�]�w `uniform` �ɻݫ��w�ƲդU�СC

    ```cpp
    lightingShader.setFloat("pointLights[0].constant", 1.0f);
    ```

    - �C���I�����ݤ�ʳ]�w�Ҧ� `uniform` �ȡC

- **�I������m�]�w�G**
  - �w�q�@�� `glm::vec3` �}�C���x�s�I��������m�G

    ```cpp
    glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
    ```

  - �N `pointLightPositions` ������m��ȵ� `pointLights` �}�C�����C�� `PointLight` ���c��C

- **�h�O�������V�G**
  - �T�O��V�h�ӿO������A�Ӥ��O�ȶȤ@�ӡC
  - ���C�ӿO������Ыؤ@�Ӥ��P���ҫ��x�}�A�����󤧫e�B�z�c�l���覡�C



