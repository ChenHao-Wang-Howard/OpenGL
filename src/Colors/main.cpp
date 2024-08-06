#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader_m.h>
#include <camera.h>

#include <iostream>

using namespace std;

// 回調函數，用於窗口大小變化
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 回調函數，用於滑鼠移動
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
// 回調函數，用於滑鼠滾輪
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// 處理輸入
void processInput(GLFWwindow* window);

// 設定
const unsigned int SCR_WIDTH = 800;  // 視窗寬度
const unsigned int SCR_HEIGHT = 600; // 視窗高度

// 相機設定
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); // 初始化相機位置
float lastX = SCR_WIDTH / 2.0f; // 儲存上次滑鼠x座標
float lastY = SCR_HEIGHT / 2.0f; // 儲存上次滑鼠y座標
bool firstMouse = true; // 是否為第一次使用滑鼠

// 計時
float deltaTime = 0.0f; // 幀間隔
float lastFrame = 0.0f; // 上一幀的時間

// 光源位置
glm::vec3 lightPos(1.2f, 1.0f, 2.0f);

int main()
{
    // 初始化GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    // 創建窗口
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // 註冊回調函數
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // 捕捉滑鼠
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // 初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // 啟用深度測試
    glEnable(GL_DEPTH_TEST);

    // 建立和編譯著色器程序
    Shader lightingShader("C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Colors\\colors.vs", "C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Colors\\colors.fs"); // 物體著色器
    Shader lightCubeShader("C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Colors\\light_cube.vs", "C:\\Users\\RTX2070\\source\\repos\\OpenGL\\src\\Colors\\light_cube.fs"); // 光源著色器

    // 設定頂點數據
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

    // 配置物體的VAO和VBO
    unsigned int VBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cubeVAO);

    // 設定頂點屬性指標
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 配置光源的VAO（VBO不變）
    unsigned int lightCubeVAO;
    glGenVertexArrays(1, &lightCubeVAO);
    glBindVertexArray(lightCubeVAO);

    // 綁定VBO到光源VAO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // 渲染循環
    while (!glfwWindowShouldClose(window))
    {
        // 計算每幀時間
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame; // 幀間隔
        lastFrame = currentFrame;

        // 處理輸入
        processInput(window);

        // 渲染指令
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 激活物體著色器
        lightingShader.use();
        lightingShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f); // 設定物體顏色
        lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);  // 設定光源顏色

        // 設定視圖和投影矩陣
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        lightingShader.setMat4("projection", projection);
        lightingShader.setMat4("view", view);

        // 世界變換
        glm::mat4 model = glm::mat4(1.0f);
        lightingShader.setMat4("model", model);

        // 繪製立方體
        glBindVertexArray(cubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 激活光源著色器並繪製光源立方體
        lightCubeShader.use();
        lightCubeShader.setMat4("projection", projection);
        lightCubeShader.setMat4("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, lightPos); // 移動光源位置
        model = glm::scale(model, glm::vec3(0.2f)); // 縮小光源立方體
        lightCubeShader.setMat4("model", model);

        glBindVertexArray(lightCubeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // 交換緩衝區和輪詢事件
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // 刪除所有資源
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightCubeVAO);
    glDeleteBuffers(1, &VBO);

    // 結束GLFW
    glfwTerminate();
    return 0;
}

// 處理所有輸入
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true); // 按下ESC關閉窗口

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime); // 向前移動
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime); // 向後移動
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime); // 向左移動
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime); // 向右移動
}

// 當窗口大小改變時，調整視口
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height); // 設定新的視口大小
}

// 當滑鼠移動時，更新相機視角
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
    float yoffset = lastY - ypos; // y軸是反轉的

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset); // 更新相機視角
}

// 當滑鼠滾輪滾動時，縮放視角
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
