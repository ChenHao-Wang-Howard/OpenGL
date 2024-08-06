#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>
#include <camera.h>

#include <iostream>

using namespace std;

// �^�ը�ƫŧi
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// �����]�w
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// �۾���l��
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;  // �]�w�ƹ��_�lX��m
float lastY = SCR_HEIGHT / 2.0f; // �]�w�ƹ��_�lY��m
bool firstMouse = true; // �O�_�O�Ĥ@���ƹ��ƥ�

// �p��
float deltaTime = 0.0f; // ��e�V�P�W�@�V���ɶ��t
float lastFrame = 0.0f; // �W�@�V���ɶ�

// ������m
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    // ��l��GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // �]�wOpenGL������3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    // �Ы�GLFW����
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate(); // �p�G�Ыص������ѫh�פ�
        return -1;
    }
    glfwMakeContextCurrent(window);

    // ���U�^�ը��
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // �����ƹ�
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // ��l��GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // �}�Ҳ`�״���
    glEnable(GL_DEPTH_TEST);

    // �sĶ�ۦ⾹
    Shader lightingShader("C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Materials\\materials.vs", "C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Materials\\materials.fs");
    Shader lightCubeShader("C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Materials\\light_cube.vs", "C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Materials\\light_cube.fs");

    // �]�w���I�ƾکM�t�m���I�ݩ�
    float vertices[] = {
        // ���I��m          // �k�V�q
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
    };

    // �t�m�ߤ��骺VAO�MVBO
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // �]�w���I�ݩʫ��СG��m�ݩ�
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // �]�w���I�ݩʫ��СG�k�V�q�ݩ�
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // �t�m������VAO�]VBO�O�����ܡA�ϥάۦP�����I�ƾڡ^
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // ��s�O�����I�ݩʫ���
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // ��V�`��
    while (!glfwWindowShouldClose(window))
    {
        // �p��C�V���ɶ��t
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // �B�z��J
        processInput(window);

        // �M���w�İ�
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // �E���ۦ⾹
        lightingShader.use();
        lightingShader.setVec3("light.position", lightPos);
        lightingShader.setVec3("viewPos", camera.Position);

        // �]�w�����ݩ�
        glm::vec3 lightColor;
        lightColor.x = static_cast<float>(sin(glfwGetTime() * 2.0)); // �]�w�����C��
        lightColor.y = static_cast<float>(sin(glfwGetTime() * 0.7));
        lightColor.z = static_cast<float>(sin(glfwGetTime() * 1.3));
        glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f); // ��z�����v�T
        glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // ���ҥ�
        lightingShader.setVec3("light.ambient", ambientColor);
        lightingShader.setVec3("light.diffuse", diffuseColor);
        lightingShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);

        // �]�w�����ݩ�
        lightingShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("material.diffuse", 1.0f, 0.5f, 0.31f);
        lightingShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f); // �����j��
        lightingShader.setFloat("material.shininess", 32.0f);

        // �]�w���ϩM��v�ܴ�
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // �]�w�@���ܴ�
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // ��V�ߤ���
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // ø�s�O���ߤ���
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos); // ���ʨ������m
        model = glm::scale(model, glm::vec3(0.2f)); // �Y�p
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // �洫�w�İϩM���ߨƥ�
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // ����귽
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    // ����GLFW
    glfwTerminate();
    return 0;
}

// �B�z�Ҧ���J
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); // ���UESC����������

    // �B�z�۾�����
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// �����j�p�ܧ�ɪ��^�ը��
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); // �վ���f�j�p
}

// �ƹ����ʮɪ��^�ը��
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) // �즸�i�J
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX; // �p�ⰾ���q
    float yoffset = lastY - ypos; // �ϦV�p��y�b����

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset); // ��s�۾�����
}

// �ƹ��u���ɪ��^�ը��
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset)); // ��s�۾��Y��
}
