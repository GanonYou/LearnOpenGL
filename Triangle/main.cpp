//注意要在包含GLFW的头文件之前包含了GLAD的头文件!
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

//当用户改变窗口的大小的时候，视口也应该被调整，需要一个回调函数
void framebuffer_size_callback(GLFWwindow * window,int width,int height);
//声明一个函数用来检测特定的键是否被按下
void processInput(GLFWwindow * window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

//定义一个顶点着色器的源码
const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\n\0";

//定义一个片段着色器的源码
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


int main(){
    
    //初始化GLFW
    glfwInit();
    
    //将OpenGL主版本号(Major)和次版本号(Minor)都设为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    //使用的是核心模式(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //如果是macOS系统，则需要下面这行代码才能让配置起作用
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    //创建一个窗口对象
    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    
    //通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);
    //注册定义好的回调函数，告诉GLFW每当窗口调整大小的时候调用这个函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
    //GLAD是用来管理OpenGL的函数指针的，在调用任何OpenGL的函数之前我们需要初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    
    /*************** 设置顶点数据与缓冲，并配置顶点属性 *************/
    //输入一个顶点，分别代表三角形三个顶点的x轴，y轴与z轴坐标
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    
    unsigned int VBO,VAO;
    //使用glGenBuffers函数和一个缓冲ID生成一个VBO顶点缓冲对象
    glGenBuffers(1,&VBO);
    //使用glGenVertexArrays函数和一个缓冲ID生成一个VAO顶点数组对象
    glGenVertexArrays(1,&VAO);
    
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    //首先绑定VAO
    glBindVertexArray(VAO);
    //然后绑定并设置VBO，使用glBindBuffer函数把新创建的缓冲绑定到GL_ARRAY_BUFFER目标上
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //调用glBufferData函数，它会把之前定义的顶点数据复制到缓冲的内存中
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    //链接顶点属性
    //下面这个函数的参数依次为顶点属性，顶点属性的大小，数据的类型，是否希望数据被标准化以及步长
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    //启用顶点属性
    glEnableVertexAttribArray(0);
    
    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    /*********************** Over ************************/
   
    
    
    
    //渲染循环(Render Loop)
    while (!glfwWindowShouldClose(window)) {
        
        //检测特定的键是否被按下，并在每一帧做出处理
        processInput(window);
        
        //glClearColor函数是一个状态设置函数，用来设置清空屏幕所用的颜色
        glClearColor(0.2f,0.3f,0.3f,1.0f);
        //glClear函数是一个状态使用函数，它使用当前的状态来用指定颜色清空屏幕
        glClear(GL_COLOR_BUFFER_BIT);
        
        //glfwSwapBuffers函数会交换颜色缓冲
        glfwSwapBuffers(window);
        //glfwPollEvents函数检查有没有触发什么事件
        glfwPollEvents();
    }
    
    //释放之前分配的所有资源
    glfwTerminate();
    
    return 0;
}

void framebuffer_size_callback(GLFWwindow * window,int width,int height){
    //glViewport函数前两个参数控制窗口左下角的位置，第三个和第四个参数控制渲染窗口的宽度和高度
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow * window){
    //检查用户是否按下了返回键(Esc)（如果没有按下，glfwGetKey将会返回GLFW_RELEASE，按下则为GLFW_PRESS)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}







