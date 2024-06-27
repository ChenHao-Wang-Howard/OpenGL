# OpenGL Project

This project demonstrates the integration of GLFW and GLAD to create a simple OpenGL application. The application creates a window with a dark gray background and handles basic user input.

## Project Structure
```
OpenGL/
¢u¢w¢w src/
¢x ¢u¢w¢w main.cpp
¢u¢w¢w include/
¢u¢w¢w external/
¢x ¢u¢w¢w glfw/
¢x ¢u¢w¢w glad/
¢u¢w¢w CMakeLists.txt
```

- **src/**: Contains the source files for the project.
- **include/**: Contains the header files for the project.
- **external/**: Contains the external libraries (GLFW and GLAD).
- **CMakeLists.txt**: The CMake build configuration file.

## Prerequisites

- [CMake](https://cmake.org/) 3.10 or higher
- [Visual Studio 2019](https://visualstudio.microsoft.com/vs/)
- [GLFW](https://www.glfw.org/download.html)
- [GLAD](https://glad.dav1d.de/)

## Setup

1. **Clone the repository**:
    ```sh
    git clone https://github.com/yourusername/your-repository.git
    cd your-repository
    ```

2. **Download and configure GLFW**:
    - Download GLFW source code and extract it to the `external/glfw` directory.

3. **Download and configure GLAD**:
    - Use the [GLAD](https://glad.dav1d.de/) online service to generate the OpenGL loader.
    - Download the generated files and place `glad.c` in `external/glad/src`, and the header files in `external/glad/include`.

## Building the Project

1. **Open the project in Visual Studio 2019**:
    - Open Visual Studio 2019.
    - Select `File` -> `Open` -> `Folder...` and choose the project directory.

2. **Configure and build the project**:
    - Visual Studio will automatically detect the `CMakeLists.txt` file and configure the project.
    - In the `Solution Explorer`, right-click on `CMakeLists.txt` and select `Build`.

3. **Run the project**:
    - After building, press `F5` to run the project.
    - A window with a dark gray background should appear.

## main.cpp

Here's a brief overview of what `main.cpp` does:

- Initializes GLFW and creates a window.
- Initializes GLAD to load OpenGL functions.
- Sets a framebuffer size callback to adjust the viewport.
- Contains a render loop that clears the screen with a dark gray color and handles input to close the window when the `ESC` key is pressed.

```cpp
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 600, "Test Window", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set viewport
    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // Clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap the buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW
    glfwTerminate();
    return 0;
}
```