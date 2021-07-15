
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <stdio.h>
#include <math.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

char *loadShaderSource(const char *filename);
int checkCompiledShader(unsigned int shader);
int checkLinkedProgram(unsigned int program);

int main()
{
    int error = 0;

    float vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
        0.5f,  -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f, 0.5f,  0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };

    unsigned int indices[] = {
        // note that we start from 0!
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    int err = 0;

    // shaders
    unsigned int vShader;
    char *vShaderSource = NULL;
    unsigned int fShader;
    char *fShaderSource = NULL;
    unsigned int shaderProgram;

    // texture 1
    int imgWidth, imgHeight, nrChannels;
    unsigned char *imgData = NULL;

    // texture 2
    int imgWidth2, imgHeight2, nrChannels2;
    unsigned char *imgData2 = NULL;

    // vertex objects
    unsigned int EBO;
    unsigned int VBO;
    unsigned int VAO;
    unsigned int textureID;
    unsigned int texture2ID;

    // loading resources
    vShaderSource = loadShaderSource("test/glsl/learnopenglVertexShader.glsl");
    fShaderSource = loadShaderSource("test/glsl/learnopenglFragmentShader.glsl");
    imgData = stbi_load("deps/img/container.jpg", &imgWidth, &imgHeight, &nrChannels, 0);
    imgData2 = stbi_load("deps/img/awesomeface.png", &imgWidth2, &imgHeight2, &nrChannels2, 0);

    if (!imgData2)
    {
        return -1;
    }

    // init GLFW window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "learnopengl", NULL, NULL);
    if (window == NULL)
    {
        // std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // setup GLEW -> after this all opengl is available
    GLint glewStatus = glewInit();
    if (glewStatus != GLEW_OK)
    {
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!vShaderSource || !fShaderSource)
    {
        glfwTerminate();
        return -1;
    }

    // configure texture sampling and filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // configure VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // configure textures
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, (void *)imgData);
    glGenerateMipmap(GL_TEXTURE_2D);
    // texture #2
    glGenTextures(1, &texture2ID);
    glBindTexture(GL_TEXTURE_2D, texture2ID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth2, imgHeight2, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void *)imgData2);
    glGenerateMipmap(GL_TEXTURE_2D);
    // configure VBO and attribute pointers
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(3 * sizeof(float)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(6 * sizeof(float)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    // configure EBO
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // unbind VAO for later use
    glBindVertexArray(0);

    // vertex shader
    vShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vShader, 1, (const char **)&vShaderSource, NULL);
    glCompileShader(vShader);
    error = checkCompiledShader(vShader);
    if (error)
    {
        glfwTerminate();
        return -1;
    }

    // fragment shader
    fShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShader, 1, (const char **)&fShaderSource, NULL);
    glCompileShader(fShader);
    error = checkCompiledShader(fShader);
    if (error)
    {
        glfwTerminate();
        return -1;
    }

    // shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);
    error = checkLinkedProgram(shaderProgram);

    if (error)
    {
        // cout << "Unable to link shaders... quitting" << endl;
        glfwTerminate();
        return -1;
    }

    glDeleteShader(vShader);
    glDeleteShader(fShader);

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        const float timeValue = glfwGetTime();
        const float redValue = (cos(timeValue) / 2.0f) + 0.5f;
        const float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        const float blueValue = (cos(timeValue) / 2.0f) + 0.5f;
        const int loc = glGetUniformLocation(shaderProgram, "uColor");
        const int timeLoc = glGetUniformLocation(shaderProgram, "time");
        const int texSampler0Loc = glGetUniformLocation(shaderProgram, "texSampler0");
        const int texSampler1Loc = glGetUniformLocation(shaderProgram, "texSampler1");
        glUniform4f(loc, redValue, greenValue, blueValue, 1.0f);
        glUniform1f(timeLoc, timeValue);
        glUniform1i(texSampler0Loc, 0);
        glUniform1i(texSampler1Loc, 1);

        // binding appropriate textures
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2ID);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // unbind for other objects...
        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // free resources
    free(vShaderSource);
    free(fShaderSource);
    stbi_image_free(imgData);

    glfwTerminate();
    return 0;
}

char *loadShaderSource(const char *filename)
{
    char *buffer = 0;
    long length;
    FILE *f = fopen(filename, "rb");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        buffer = (char *)malloc(sizeof(char) * (length + 1));
        if (buffer)
        {
            fread(buffer, sizeof(char), length, f);
            buffer[length] = 0;
        }
        fclose(f);
    }
    return buffer;
}

int checkCompiledShader(unsigned int shader)
{
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        // std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 1;
    }

    return 0;
}

int checkLinkedProgram(unsigned int program)
{
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success)
    {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        // std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        return 1;
    }

    return 0;
}