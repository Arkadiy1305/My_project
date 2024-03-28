#include <GLFW/glfw3.h>

bool is_fullscreen{ false };
GLFWmonitor* monitor;
const GLFWvidmode* mode;

void checkout_fullscreen_mode(GLFWwindow* window);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    monitor = glfwGetPrimaryMonitor();
    mode = glfwGetVideoMode(monitor);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        //glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void checkout_fullscreen_mode(GLFWwindow* window)
{
    if (is_fullscreen)
    {
        glfwSetWindowMonitor(window, nullptr, 100, 100, 640, 480, mode->refreshRate);
        is_fullscreen = false;
    }
    else
    {
        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        is_fullscreen = true;
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if (key == GLFW_KEY_I && action == GLFW_PRESS)
        checkout_fullscreen_mode(window);
}