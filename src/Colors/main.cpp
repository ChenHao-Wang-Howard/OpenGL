#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>
#include <camera.h>

#include <iostream>

using namespace std;

// �^�ը�ơA�Ω󵡤f�j�p�ܤ�
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// �^�ը�ơA�Ω�ƹ�����
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// �^�ը�ơA�Ω�ƹ��u��
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// �B�z��J
void processInput(GLFWwindow* window);

// �]�w
const unsigned int SCR_WIDTH = 800;  // �����e��
const unsigned int SCR_HEIGHT = 600; // ��������

// �۾��]�w
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); // ��l�Ƭ۾���m
float lastX = SCR_WIDTH / 2.0f; // �x�s�W���ƹ�x�y��
float lastY = SCR_HEIGHT / 2.0f; // �x�s�W���ƹ�y�y��
bool firstMouse = true; // �O�_���Ĥ@���ϥηƹ�

// �p��
float deltaTime = 0.0f; // �V���j
float lastFrame = 0.0f; // �W�@�V���ɶ�

// ������m
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    // ��l��GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    // �Ыص��f
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
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

    // �ҥβ`�״���
    glEnable(GL_DEPTH_TEST);

    // �إߩM�sĶ�ۦ⾹�{��
    Shader lightingShader("C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Colors\\colors.vs", "C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Colors\\colors.fs"); // ����ۦ⾹
    Shader lightCubeShader("C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Colors\\light_cube.vs", "C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Colors\\light_cube.fs"); // �����ۦ⾹

    // �]�w���I�ƾ�
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    // �t�m���骺VAO�MVBO
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // �]�w���I�ݩʫ���
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // �t�m������VAO�]VBO���ܡ^
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // �j�wVBO�����VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // ��V�`��
    while (!glfwWindowShouldClose(window))
    {
        // �p��C�V�ɶ�
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame; // �V���j
        lastFrame = currentFrame;

        // �B�z��J
        processInput(window);

        // ��V���O
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // �E������ۦ⾹
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f); // �]�w�����C��
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);  // �]�w�����C��

        // �]�w���ϩM��v�x�}
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // �@���ܴ�
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // ø�s�ߤ���
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // �E�������ۦ⾹��ø�s�����ߤ���
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos); // ���ʥ�����m
        model = glm::scale(model, glm::vec3(0.2f)); // �Y�p�����ߤ���
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // �洫�w�İϩM���ߨƥ�
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // �R���Ҧ��귽
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
        glfwSetWindowShouldClose(window, true); // ���UESC�������f

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime); // �V�e����
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime); // �V�Ჾ��
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime); // �V������
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime); // �V�k����
}

// ���f�j�p���ܮɡA�վ���f
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); // �]�w�s�����f�j�p
}

// ��ƹ����ʮɡA��s�۾�����
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // y�b�O���઺

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset); // ��s�۾�����
}

// ��ƹ��u���u�ʮɡA�Y�����
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
