//注意要在包含GLFW的头文件之前包含了GLAD的头文件!
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;

//当用户改变窗口的大小的时候，视口也应该被调整，需要一个回调函数
void framebuffer_size_callback(GLFWwindow * window,int width,int height);
//声明一个函数用来检测特定的键是否被按下
void processInput(GLFWwindow * window);

int main(){
    
    //初始化GLFW
    glfwInit();
    
    //将OpenGL主版本号(Major)和次版本号(Minor)都设为3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    
    //使用的是核心模式(Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    //如果是macOS系统，则需要下面这行代码才能让配置起作用
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    //创建一个窗口对象
    GLFWwindow * window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL){
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    //通知GLFW将我们窗口的上下文设置为当前线程的主上下文
    glfwMakeContextCurrent(window);
    
    //GLAD是用来管理OpenGL的函数指针的，在调用任何OpenGL的函数之前我们需要初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }
    
    //注册定义好的回调函数，告诉GLFW每当窗口调整大小的时候调用这个函数
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    
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







