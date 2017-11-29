//
// Created by Mike Smith on 09/10/2017.
//

#ifndef LEARNING_OPENGL_INIT_H
#define LEARNING_OPENGL_INIT_H

#include <GLFW/glfw3.h>
#include <string>

class Window
{
private:
    GLFWwindow *_handle = nullptr;

public:
    Window(const std::string &window_name, int width, int height);
    ~Window() = default;
    GLFWwindow *handle();
    int width();
    int height();
    void swapBuffers();
    bool shouldClose() const;
};

#endif  // LEARNING_OPENGL_INIT_H
