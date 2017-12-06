#include "ThirdParty/GLAD/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

//#pragma comment (lib, "glfw3.lib")
//#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "opengl32.lib")

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    GLFWwindow *window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    while (!glfwWindowShouldClose(window)) {
        // 检查事件
        glfwPollEvents();
        
        // 在这里执行各种渲染操作
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        //交换缓冲区
        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}