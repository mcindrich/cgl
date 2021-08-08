
#include "cgl/image.h"
#include "cgl/object.h"
#include "cgl/texture2D.h"
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

struct Image
{
    int width;
    int height;
    int nrChannels;
    unsigned char *pixels;
};

void ImageInit(struct Image *img)
{
    img->width = img->height = img->nrChannels = 0;
    img->pixels = NULL;
}

int ImageLoad(struct Image *img, const char *path)
{
    int err = 0;
    img->pixels = stbi_load(path, &img->width, &img->height, &img->nrChannels, 0);
    if (!img->pixels)
    {
        err = -1;
    }
    return err;
}

void ImageFree(struct Image *img)
{
    if (img->pixels)
    {
        stbi_image_free(img->pixels);
    }
}

int main()
{
    struct cgl_shader vertexShader;
    struct cgl_shader fragmentShader;
    struct cgl_shader_program shaders;
    struct cgl_vbo vbo;
    struct cgl_ebo ebo;
    struct cgl_vao vao;
    struct cgl_texture2D smileyTex;
    struct cgl_texture2D containerTex;
    struct cgl_image smiley;
    struct cgl_image container;

    int err = 0;
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

    cgl_vbo_init(&vbo);
    cgl_ebo_init(&ebo);
    cgl_vao_init(&vao);

    cgl_shader_init(&vertexShader);
    cgl_shader_init(&fragmentShader);
    cgl_shader_program_init(&shaders);

    cgl_image_init(&smiley);
    cgl_image_init(&container);

    err = cgl_image_load(&smiley, "deps/img/awesomeface.png");
    if (err)
    {
        printf("err\n");
        return -1;
    }
    err = cgl_image_load(&container, "deps/img/container.jpg");
    if (err)
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

    // vao
    cgl_vao_gen(&vao);
    cgl_vao_bind(&vao);

    // vbo
    cgl_vbo_gen(&vbo);
    cgl_vbo_bind(&vbo);
    cgl_buffer_data(cgl_buffer_kind_array, sizeof(vertices), vertices, cgl_draw_kind_static);
    cgl_vertex_attrib_configure(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, 0);
    cgl_vertex_attrib_enable(0);
    cgl_vertex_attrib_configure(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(3 * sizeof(float)));
    cgl_vertex_attrib_enable(1);
    cgl_vertex_attrib_configure(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 8, (void *)(6 * sizeof(float)));
    cgl_vertex_attrib_enable(2);

    // ebo
    cgl_ebo_gen(&ebo);
    cgl_ebo_bind(&ebo);
    cgl_buffer_data(cgl_buffer_kind_element, sizeof(indices), indices, cgl_draw_kind_static);

    // configure textures
    cgl_texture2D_gen(&containerTex, &container, GL_RGB, GL_RGB);
    cgl_texture2D_gen(&smileyTex, &smiley, GL_RGB, GL_RGBA);

    // free after giving data to the texture2D
    cgl_image_delete(&smiley);
    cgl_image_delete(&container);

    // unbind vao
    cgl_vao_unbind();

    err = cgl_shader_load_source(&vertexShader, cgl_shader_kind_vertex, "test/glsl/learnopenglVertexShader.glsl");
    if (err)
    {
        printf("shader load error 1\n");
        return -1;
    }
    err = cgl_shader_load_source(&fragmentShader, cgl_shader_kind_fragment, "test/glsl/learnopenglFragmentShader.glsl");
    if (err)
    {
        printf("shader load error 2\n");
        return -1;
    }

    err = cgl_shader_compile(&vertexShader);
    if (err)
    {
        printf("shader compile error 1\n");
        return -1;
    }
    err = cgl_shader_compile(&fragmentShader);
    if (err)
    {
        printf("shader compile error 2\n");
        return -1;
    }

    cgl_shader_program_set_vertex_shader(&shaders, &vertexShader);
    cgl_shader_program_set_fragment_shader(&shaders, &fragmentShader);

    err = cgl_shader_program_link(&shaders);
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

        cgl_shader_program_use(&shaders);
        const float timeValue = glfwGetTime();
        const float redValue = (cos(timeValue) / 2.0f) + 0.5f;
        const float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        const float blueValue = (cos(timeValue) / 2.0f) + 0.5f;
        const int loc = glGetUniformLocation(cgl_object_get_ID((struct cgl_object *)&shaders), "uColor");
        const int timeLoc = glGetUniformLocation(cgl_object_get_ID((struct cgl_object *)&shaders), "time");
        const int texSampler0Loc =
            glGetUniformLocation(cgl_object_get_ID((struct cgl_object *)&shaders), "texSampler0");
        const int texSampler1Loc =
            glGetUniformLocation(cgl_object_get_ID((struct cgl_object *)&shaders), "texSampler1");
        glUniform4f(loc, redValue, greenValue, blueValue, 1.0f);
        glUniform1f(timeLoc, timeValue);
        glUniform1i(texSampler0Loc, 0);
        glUniform1i(texSampler1Loc, 1);

        // binding appropriate textures
        glActiveTexture(GL_TEXTURE0);
        cgl_texture2D_bind(&containerTex);
        // glBindTexture(GL_TEXTURE_2D, cgl_object_get_ID((struct cgl_object *)&containerTex));
        glActiveTexture(GL_TEXTURE1);
        cgl_texture2D_bind(&smileyTex);
        // glBindTexture(GL_TEXTURE_2D, cgl_object_get_ID((struct cgl_object *)&smileyTex));

        cgl_vao_bind(&vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // unbind for other objects...
        cgl_vao_unbind();
        glBindTexture(GL_TEXTURE_2D, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    cgl_shader_delete(&vertexShader);
    cgl_shader_delete(&fragmentShader);

    // free resources
    cgl_shader_program_delete(&shaders);

    glfwTerminate();
    return 0;
}
