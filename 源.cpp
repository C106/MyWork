#include<GL/glew.h>
#include <GLFW\glfw3.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<time.h>
#include"shader.h"
#include"GPUprogram.h"
#include"stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
float lastX = 640, lastY = 480;
std::ostream& operator<<(std::ostream& os, const glm::vec3& vec) {
    os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
    return os;
}
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
Camera camera1(glm::vec3(0.0, 0.0, 3.0), glm::vec3(0.0, 0.0, -1.0));
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{


    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;
    camera1.MouseMove(xoffset, yoffset);
}
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    else
    {
        std::cout << "glfw initialized" << std::endl;
    }
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Kobe", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    if (glewInit()!=GLEW_OK)
    {
        std::cout << "Error" << std::endl;
    }
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init();
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,0.0f,-1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,0.0f,-1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,0.0f,-1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,0.0f,-1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,0.0f,1.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,0.0f,1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f,1.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,0.0f,1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,0.0f,1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,0.0f,1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,0.0f,0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,0.0f,0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,0.0f,0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,0.0f,0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,0.0f,0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,0.0f,0.0f,

     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,0.0f,0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,0.0f,0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,0.0f,0.0f,
     0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,0.0f,0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,0.0f,0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,0.0f,0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,-1.0f,0.0f,
     0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f,-1.0f,0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,-1.0f,0.0f,
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,-1.0f,0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,-1.0f,0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,-1.0f,0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,1.0f,0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,0.0f,
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,1.0f,0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,1.0f,0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,1.0f,0.0f
    };
    //创建顶点数组
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    //创建顶点缓冲
    unsigned int Vbo;
    glGenBuffers(1, &Vbo);
    glBindBuffer(GL_ARRAY_BUFFER, Vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
    //顶点属性
    
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    //顶点属性——纹理
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //顶点属性——法向量
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);
    //创建元素缓冲

    unsigned int elements[8] = {
        3,2,0,
        2,1,0
    };
    unsigned int index_buffer;
    glGenBuffers(1,&index_buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), elements,GL_DYNAMIC_DRAW);

    //着色器
    shader vertex(".\\Res\\Shader\\Header.glsl",GL_VERTEX_SHADER);
    shader fragment(".\\Res\\Shader\\fs.glsl", GL_FRAGMENT_SHADER);
    program shader1;
    shader1.link(vertex.ID, fragment.ID);
    //着色器2
    shader fragment2(".\\Res\\Shader\\fs2.glsl", GL_FRAGMENT_SHADER);
    program shader2;
    shader2.link(vertex.ID, fragment2.ID);


    
    //纹理
    glActiveTexture(GL_TEXTURE0);
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(".\\Res\\kobe.png", &width, &height, &nrChannels, 0);
    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB,GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    unsigned char* data2 = stbi_load(".\\Res\\Glass.png", &width, &height, &nrChannels, 0);

    unsigned int texture2;
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
    glGenerateMipmap(GL_TEXTURE_2D);

    shader1.use();
    shader1.setInt("tex", 0);
    shader1.setInt("tex2", 1);
    float mix = 0,x=0;
    //进入3D
    glm::mat4 model;
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0,1.0, 0.0));
    glm::mat4 view;
    view = glm::translate(view, glm::vec3(0.0, 0.0, -3.0));
    glm::mat4 projection;
    float screenWidth = 1280;
    float screenHeight = 720;
    
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  0.0f),
        glm::vec3(2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3(2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3(1.3f, -2.0f, -2.5f),
        glm::vec3(1.5f,  2.0f, -2.5f),
        glm::vec3(1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    shader1.use();
    glEnable(GL_DEPTH_TEST);
    //摄像机
    //glm::vec3 Camera=glm::vec3(0.0,0.0,3.0);
    //glm::vec3 Target = glm::vec3(0.0, 0.0, 0.0);
    //glm::vec3 Direction = glm::normalize(Camera - Target);
    //glm::vec3 UP = glm::vec3(0.0, 1.0, 0.0);
    //glm::vec3 cRight = glm::normalize(glm::cross(Direction,UP));
    //glm::vec3 cUp = glm::cross(cRight, Direction);
    //glm::mat4 view2; 
    //view2 = glm::lookAt(Camera, Target, cUp);

    //光照
    unsigned int vao1;
    glGenVertexArrays(1, &vao1);
    glBindVertexArray(vao1);
    glBindBuffer(GL_ARRAY_BUFFER, Vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glm::vec3 lightcolor(1.0f, 1.0f, 1.0f);
    glm::vec3 lightpos(2.2f, 2.0f, 3.0f);
    glm::mat4 model2;
    model2 = glm::translate(model2, lightpos);

    //法向量


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // feed inputs to dear imgui, start new frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();


        // render your GUI
        ImGui::Begin("Camera");
        ImGui::SliderFloat("yaw", &camera1.yaw, -180, 180);
        camera1.setFront();
        ImGui::SliderFloat("pitch", &camera1.pitch, -90, 90);
        camera1.setFront();
        ImGui::SliderFloat("roll", &camera1.roll, -180, 180);
        camera1.changeRoll(camera1.roll);
        ImGui::SliderFloat("fov", &camera1.fov, 42, 48);
        ImGui::End();


        ImGui::Begin("lightPos");
        ImGui::SliderFloat("x", &lightpos.x, -50, 50);
        ImGui::SliderFloat("y", &lightpos.y, -50, 50);
        ImGui::SliderFloat("z", &lightpos.z, -50, 50);
        ImGui::End();

        ImGui::Begin("lightColor");
        ImGui::ColorEdit3("lightColor", &lightcolor.x);
        ImGui::End();

        glBindVertexArray(VAO);
        shader1.use();
        shader1.setInt("tex", 0);
        shader1.setInt("tex2", 1);
        camera1.Keyboard(window);
        shader1.setMat4("model", model);
        shader1.setMat4("view", camera1.Getview());
        projection = glm::perspective(camera1.fov, screenWidth / screenHeight, 0.1f, 100.0f);
        shader1.setMat4("projection", projection);
        shader1.setVec3("lightColor", lightcolor);
        shader1.setVec3("viewPos", camera1.location);
        shader1.setMat4("trs", model2);
        shader1.setVec3("Lightpos", lightpos);
        for (int i = 0; i < 10; i++)
        {
            glm::mat4 model;
            float angle = 20.f * i;
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model, glm::radians(angle), glm::vec3(0.3f, 0.1f, 0.0f));
            shader1.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 360);
        }
        shader2.use();
        shader2.setMat4("model", model2);
        shader2.setMat4("view", camera1.Getview());
        shader2.setMat4("projection", projection);
        shader2.setVec3("lightColor", lightcolor);
        model2 = glm::translate(glm::mat4(1.0), lightpos);
        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        // Render dear imgui into screen
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //glfwSetCursorPosCallback(window,mouse_callback);

    }

    glfwTerminate();
    return 0;
}

