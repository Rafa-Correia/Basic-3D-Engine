#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <conio.h>
#include "basic_graphics.hpp"
#include "shader.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int create_win() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.x
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW!" << std::endl;
        std::cin.get();
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Game Engine", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        std::cout << "Press any key to continue..." << std::endl;
        _getch();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        std::cout << "Press any key to continue..." << std::endl;
        _getch();
        return -1;
    }

    //triangle stuff
    float vertices[] = {
        // Positions (x, y, z)
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom-left
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Bottom-right
         0.0f,  0.5f, 0.0f, 0.5f, 1.0f   // Top-center
    };

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    //tex setup

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    stbi_set_flip_vertically_on_load(true);

    int width, height, nrChannels;
    unsigned char* data = stbi_load("../assets/textures/container.jpg", &width, &height, &nrChannels, 0);

    unsigned int texture1;
    glGenTextures(1, &texture1);

    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);





    //create our shader
    Shader s = Shader("..\\assets\\shaders\\vertex.glsl", "..\\assets\\shaders\\fragment.glsl");
    //s.use();
    s.setInt("container.jpg", 0);
    
    glClearColor(0.1f, 0.1f, 0.2f, 1.0f);

    while (!glfwWindowShouldClose(window)) {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
            glfwSetWindowShouldClose(window, true);
        glClear(GL_COLOR_BUFFER_BIT);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        s.use();
        // Render here
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    std::cout << "Press any key to continue..." << std::endl;
    _getch();
    return 0;
}
