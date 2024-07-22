#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <shader_s.h>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    // ��l�ƩM�t�m GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // �Ы� GLFW ���f
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ��l�� GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // �c�ةM�sĶ�ۦ⾹�{��
    Shader ourShader("C:\\Users\\RTX2070\\source\\repos\\OpenGL\\resource\\Vertex_shader.vs",
        "C:\\Users\\RTX2070\\source\\repos\\OpenGL\\resource\\Fragment_shader.fs");

    // �]�m���I�ƾکM�t�m���I�ݩ�
    float vertices[] = {
        // ��m              // �C��
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // �k�U
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // ���U
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // �W
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // ��m�ݩ�
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // �C���ݩ�
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // ��V�`��
    while (!glfwWindowShouldClose(window))
    {
        // �B�z��J
        processInput(window);

        // ��V
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // ��V�T����
        ourShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // �洫�w�İϨìd�� IO �ƥ�
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // �i��G�Ѱ����t�Ҧ��귽
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    // �פ� GLFW �òM�z�Ҧ��귽
    glfwTerminate();
    return 0;
}

// �B�z�Ҧ���J
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// ���f�j�p���ܮɽեΦ��^�ը��
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
