
#include "cgl/object.h"
#include "cgl/shader.h"
#include "cgl/shader_program.h"
#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include <cgl.h>
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

    struct cgl_shader *vertexShader = cgl_shader_new();
    struct cgl_shader *fragmentShader = cgl_shader_new();
    struct cgl_shader_program *shaders = cgl_shader_program_new();

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

    err = cgl_shader_load_source(vertexShader, cgl_shader_kind_vertex, "test/glsl/learnopenglVertexShader.glsl");
    if (err)
    {
        printf("shader load error 1\n");
        return -1;
    }
    err = cgl_shader_load_source(fragmentShader, cgl_shader_kind_fragment, "test/glsl/learnopenglFragmentShader.glsl");
    if (err)
    {
        printf("shader load error 2\n");
        return -1;
    }

    err = cgl_shader_compile(vertexShader);
    if (err)
    {
        printf("shader compile error 1\n");
        return -1;
    }
    err = cgl_shader_compile(fragmentShader);
    if (err)
    {
        printf("shader compile error 2\n");
        return -1;
    }

    cgl_shader_program_set_vertex_shader(shaders, vertexShader);
    cgl_shader_program_set_fragment_shader(shaders, fragmentShader);

    err = cgl_shader_program_link(shaders);
    if (err)
    {
        printf("shaders link error\n");
        return -1;
    }

    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        cgl_shader_program_use(shaders);
        const float timeValue = glfwGetTime();
        const float redValue = (cos(timeValue) / 2.0f) + 0.5f;
        const float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        const float blueValue = (cos(timeValue) / 2.0f) + 0.5f;
        const int loc = glGetUniformLocation(cgl_object_get_ID((struct cgl_object *)shaders), "uColor");
        const int timeLoc = glGetUniformLocation(cgl_object_get_ID((struct cgl_object *)shaders), "time");
        const int texSampler0Loc = glGetUniformLocation(cgl_object_get_ID((struct cgl_object *)shaders), "texSampler0");
        const int texSampler1Loc = glGetUniformLocation(cgl_object_get_ID((struct cgl_object *)shaders), "texSampler1");
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

    cgl_shader_delete(vertexShader);
    cgl_shader_delete(fragmentShader);

    // free resources
    stbi_image_free(imgData);
    cgl_shader_program_delete(shaders);

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