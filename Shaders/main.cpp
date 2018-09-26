////
////  main.cpp
////  Shaders
////
////  Created by 游文彦 on 2018/9/26.
////  Copyright © 2018 Swallow. All rights reserved.
////
//
////注意要在包含GLFW的头文件之前包含了GLAD的头文件!
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include <cmath>
//using namespace std;
//
////当用户改变窗口的大小的时候，视口也应该被调整，需要一个回调函数
//void framebuffer_size_callback(GLFWwindow * window,int width,int height);
////声明一个函数用来检测特定的键是否被按下
//void processInput(GLFWwindow * window);
//
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
////定义一个顶点着色器的源码
//const char *vertexShaderSource = "#version 330 core\n"
//"layout (location = 0) in vec3 aPos;\n"
//"void main()\n"
//"{\n"
//"   gl_Position = vec4(aPos, 1.0);\n"
//"}\n\0";
//
////定义一个片段着色器的源码
////在OpenGL程序代码中会设定uniform变量
//const char *fragmentShaderSource = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"uniform vec4 ourColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = ourColor;\n"
//"}\n\0";
//
//
//int main(){
//
//    //初始化GLFW
//    glfwInit();
//    //将OpenGL主版本号(Major)和次版本号(Minor)都设为3
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    //使用的是核心模式(Core-profile)
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //如果是macOS系统，则需要下面这行代码才能让配置起作用
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    //创建一个窗口对象
//    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello,shaders", NULL, NULL);
//    if (window == NULL){
//        cout << "Failed to create GLFW window" << endl;
//        glfwTerminate();
//        return -1;
//    }
//
//    //通知GLFW将我们窗口的上下文设置为当前线程的主上下文
//    glfwMakeContextCurrent(window);
//    //注册定义好的回调函数，告诉GLFW每当窗口调整大小的时候调用这个函数
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    //GLAD是用来管理OpenGL的函数指针的，在调用任何OpenGL的函数之前我们需要初始化GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//        cout << "Failed to initialize GLAD" << endl;
//        return -1;
//    }
//
//
//    /*************** 建立并编译着色器程序 *************/
//    //1.编译顶点着色器
//    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
//    //glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。
//    //第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL
//    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//    glCompileShader(vertexShader);
//    //下面这段代码用来检测编译是否成功
//    int success;
//    char infoLog[512];
//    //用glGetShaderiv来检查是否编译成功
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//
//    //2.编译片段着色器
//    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    //glShaderSource函数把要编译的着色器对象作为第一个参数。第二参数指定了传递的源码字符串数量，这里只有一个。
//    //第三个参数是顶点着色器真正的源码，第四个参数我们先设置为NULL
//    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//    glCompileShader(fragmentShader);
//    //下面这段代码用来检测编译是否成功
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
//
//    //3.用glCreateProgram函数创建一个程序
//    int shaderProgram = glCreateProgram();
//    //将顶点着色器和片段着色器附加到程序对象上
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    //链接它们
//    glLinkProgram(shaderProgram);
//    //检测链接着色器程序是否失败
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//    }
//    //着色器对象链接完之后就可以删除了
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//    /*************** over ***************/
//
//    /*************** 设置顶点数据与缓冲，并配置顶点属性 *************/
//    //输入一个顶点，分别代表三角形三个顶点的x轴，y轴与z轴坐标
//    float vertices[] = {
//        0.5f, -0.5f, 0.0f,
//        -0.5f, -0.5f, 0.0f,
//        0.0f,  0.5f, 0.0f
//    };
//
//    unsigned int VBO,VAO;
//    //使用glGenBuffers函数和一个缓冲ID生成一个VBO顶点缓冲对象
//    glGenBuffers(1,&VBO);
//    //使用glGenVertexArrays函数和一个缓冲ID生成一个VAO顶点数组对象
//    glGenVertexArrays(1,&VAO);
//
//    //首先绑定VAO
//    glBindVertexArray(VAO);
//    //然后绑定并设置VBO，使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    //调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    //链接顶点属性
//    //下面这个函数的参数依次为顶点属性，顶点属性的大小，数据的类型，是否希望数据被标准化、步长以及偏移量
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    //启用顶点属性
//    glEnableVertexAttribArray(0);
//
//    //glBindVertexArray(VAO);
//    /*********************** Over ************************/
//
//
//    //渲染循环(Render Loop)
//    while (!glfwWindowShouldClose(window)) {
//
//        //检测特定的键是否被按下，并在每一帧做出处理
//        processInput(window);
//
//        //glClearColor函数是一个状态设置函数，用来设置清空屏幕所用的颜色
//        glClearColor(0.2f,0.3f,0.3f,1.0f);
//        //glClear函数是一个状态使用函数，它使用当前的状态来用指定颜色清空屏幕
//        glClear(GL_COLOR_BUFFER_BIT);
//
//        //激活着色器
//        glUseProgram(shaderProgram);
//
//        //更新uniform颜色
//        float timeValue = glfwGetTime();
//        float greenValue = sin(timeValue) / 2.0f + 0.5f;
//        //用glGetUniformLocation查询uniform ourColor的位置值
//        int vertexColorLocation = glGetUniformLocation(shaderProgram,"ourColor");
//        //glUniform4f 代表设定uniform的4个float值,分别是R,G,B,A
//        glUniform4f(vertexColorLocation,0.0f,greenValue,0.0f,1.0f);
//
//        //glDrawArrays函数第一个参数是图元的类型,第二个参数是顶点数组的起始索引，第三个是绘制的顶点个数
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        //交换缓冲并查询IO事件
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    //释放之前分配的所有资源
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    glfwTerminate();
//
//    return 0;
//}
//
//void framebuffer_size_callback(GLFWwindow * window,int width,int height){
//    //glViewport函数前两个参数控制窗口左下角的位置，第三个和第四个参数控制渲染窗口的宽度和高度
//    glViewport(0,0,width,height);
//}
//
//void processInput(GLFWwindow * window){
//    //检查用户是否按下了返回键(Esc)（如果没有按下，glfwGetKey将会返回GLFW_RELEASE，按下则为GLFW_PRESS)
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//        glfwSetWindowShouldClose(window, true);
//    }
//}
//
//
//
//
//
