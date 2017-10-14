//
// Created by Mike Smith on 09/10/2017.
//

#include "ThirdParty/GLAD/glad.h"
#include "Window.h"

Window::Window(const std::string &window_name, int width, int height)
{
    glfwInit();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    _handler = glfwCreateWindow(width, height, window_name.c_str(), nullptr, nullptr);
    glfwMakeContextCurrent(_handler);
    
    auto resize_callback = [](GLFWwindow *win, int w, int h) -> void {
        glfwGetFramebufferSize(win, &w, &h);
        glViewport(0, 0, w, h);
    };
    
    glfwGetFramebufferSize(_handler, &width, &height);
    glfwSetWindowSizeCallback(_handler, resize_callback);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

bool Window::shouldClose() const
{
    return static_cast<bool>(glfwWindowShouldClose(_handler));
}

void Window::swapBuffers()
{
    glfwSwapBuffers(_handler);
}

int Window::width()
{
    int width, height;
    glfwGetFramebufferSize(_handler, &width, &height);
    return width;
}

int Window::height()
{
    int width, height;
    glfwGetFramebufferSize(_handler, &width, &height);
    return height;
}

GLFWwindow *Window::handler()
{
    return _handler;
}
