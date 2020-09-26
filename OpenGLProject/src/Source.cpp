#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void) {
    GLFWwindow* window;

    if (glfwInit() == GL_FALSE)
        return -1;

    window = glfwCreateWindow(800, 600, "OpenGLProject", NULL, NULL);

    if (window == GL_FALSE) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    while (glfwWindowShouldClose(window) == GL_FALSE) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);

        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}