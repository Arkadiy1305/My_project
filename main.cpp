#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

bool is_fullscreen{ false };
GLFWmonitor* monitor;
const GLFWvidmode* mode;

void checkout_fullscreen_mode(GLFWwindow* window);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void window_size_callback(GLFWwindow* window, int width, int height);

float verticies[] = {
    -1.f, -1.f,
    -1.f, 1.f,
    1.f, -1.f,
};

const char* vertex_shader_source =
"#version 460\n"
"layout(location = 0) in vec2 aPos;\n"
"void main(){\n"
"   gl_Position = vec4(aPos, 0.f, 1.f);\n"
"}";

const char* fragment_shader_source =
"#version 460\n"
"out vec4 FragColor;\n"
"void main(){\n"
"   FragColor = vec4(0.f, 1.f, 0.f, 1.f);\n"
"}";

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
    if (!gladLoaderLoadGL())
    {
        glfwTerminate();
        std::cout << "glad not loaded" << "\n";
        return -1;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    unsigned int vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader);

    unsigned int fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader);

    unsigned int shader_program = glCreateProgram();
    glAttachShader(shader_program, vertex_shader);
    glAttachShader(shader_program, fragment_shader);
    glLinkProgram(shader_program);

    glUseProgram(shader_program);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);
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

void window_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}