#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Vertex shader code
const GLchar* vertexSource = R"glsl(
    #version 150 core
    in vec2 position;
    in vec3 color;
    out vec3 Color;
    void main() {
        Color = color;
        gl_Position = vec4(position.x, position.y, 0.0, 1.0);
    }
    )glsl";

// Fragment shagder code
const GLchar* fragmentSource = R"glsl(
    #version 150 core
    in vec3 Color;
    out vec4 outColor;
    uniform vec3 triangleColor;
    void main() {
        outColor = vec4(Color, 1.0);
    }
    )glsl";

int main(void) {
    // Create a window object 
    GLFWwindow* window;

    // Error check
    if (glfwInit() == GL_FALSE)
        return -1;

    // Give properties to that window object
    window = glfwCreateWindow(800, 600, "OpenGLProject", NULL, NULL);

    // Error check
    if (window == GL_FALSE) {
        glfwTerminate();
        return -1;
    }
    
    // Make a context using this windows so OpenGL knows where to draw to
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    glewInit();

    // Vertex array to store links between vertex buffers and attributes
    GLuint vertexArray;
    glGenVertexArrays(1, &vertexArray);
    glBindVertexArray(vertexArray);

    // Vertex buffer to store vertices and colors
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);

    GLfloat vertices[] = {
        -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // Top-left:     Red
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // Top-right:    Green
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-right: Blue
        -0.5f, -0.5f, 1.0f, 1.0f, 1.0f  // Bottom-left:  White
    };

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Element buffer to access vertices in the vertex buffer, to reuse vertices
    GLuint elementBuffer;
    glGenBuffers(1, &elementBuffer);
    
    GLuint elements[] = {
        0, 1, 2,
        2, 3, 0
    };

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    // Vertex shader object to hold the vertex shader code
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);
    
    // Fragment shader object to hold the fragment shader code
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // A shader program to connect the vertex shader with the fragment shader
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Grab the position attribute from the shader program
    GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
    glEnableVertexAttribArray(posAttrib);
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

    // Grab the color attribute from the shader program
    GLint colAttrib = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(colAttrib);
    glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));

    // Window loop
    while (glfwWindowShouldClose(window) == GL_FALSE) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
        
        // Clear screen
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwPollEvents();

        // Draw the vertices in the vertex buffer based on the indices specified by the element buffer
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Swap front and back buffer
        glfwSwapBuffers(window);
    }

    // Clean-up
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteVertexArrays(1, &vertexArray);

    // Exit
    glfwTerminate();

    return 0;
}