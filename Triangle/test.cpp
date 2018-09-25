////注意要在包含GLFW的头文件之前包含了GLAD的头文件!
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
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
//    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//"}\n\0";
//
////定义第一个片段着色器的源码
//const char *fragmentShaderSource_1 = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n\0";
//
////定义第二个片段着色器的源码
//const char *fragmentShaderSource_2 = "#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"   FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
//"}\n\0";
//
//
//int main(){
//
//    //初始化GLFW
//    glfwInit();
//
//    //将OpenGL主版本号(Major)和次版本号(Minor)都设为3
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//
//    //使用的是核心模式(Core-profile)
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    //如果是macOS系统，则需要下面这行代码才能让配置起作用
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    //创建一个窗口对象
//    GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello,rectangle", NULL, NULL);
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
//
//    //GLAD是用来管理OpenGL的函数指针的，在调用任何OpenGL的函数之前我们需要初始化GLAD
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
//        cout << "Failed to initialize GLAD" << endl;
//        return -1;
//    }
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
//
//    unsigned int fragmentShaderOrange = glCreateShader(GL_FRAGMENT_SHADER);
//    unsigned int fragmentShaderYellow = glCreateShader(GL_FRAGMENT_SHADER);
//    unsigned int shaderProgramOrange = glCreateProgram();
//    unsigned int shaderProgramYellow = glCreateProgram();
//
//    glShaderSource(fragmentShaderOrange,1,&fragmentShaderSource_1,NULL);
//    glCompileShader(fragmentShaderOrange);
//    glShaderSource(fragmentShaderYellow,1,&fragmentShaderSource_2,NULL);
//    glCompileShader(fragmentShaderYellow);
//
//    glAttachShader(shaderProgramOrange,vertexShader);
//    glAttachShader(shaderProgramOrange,fragmentShaderOrange);
//    glLinkProgram(shaderProgramOrange);
//
//    glAttachShader(shaderProgramYellow,vertexShader);
//    glAttachShader(shaderProgramYellow,fragmentShaderYellow);
//    glLinkProgram(shaderProgramYellow);
//    /*************** over ***************/
//
//
//    /*************** 设置顶点数据与缓冲，并配置顶点属性 *************/
//    //输入一个顶点，分别代表三角形三个顶点的x轴，y轴与z轴坐标
//    float vertices_1[] = {
//        // 第一个三角形
//        0.5f, 0.5f, 0.0f,   // 右上角
//        0.5f, -0.5f, 0.0f,  // 右下角
//        -0.5f, 0.5f, 0.0f,  // 左上角
//    };
//    float vertices_2[] = {
//        // 第二个三角形
//        0.5f, -0.6f, 0.0f,  // 右下角
//        -0.6f, -0.6f, 0.0f, // 左下角
//        -0.6f, 0.5f, 0.0f   // 左上角
//    };
//
//    unsigned int VBO_1,VAO_1;
//    glGenBuffers(1,&VBO_1);
//    glGenVertexArrays(1,&VAO_1);
//    glBindVertexArray(VAO_1);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_1);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_1), vertices_1, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    //glBindBuffer(GL_ARRAY_BUFFER, 0);
//    //glBindVertexArray(0);
//
//    unsigned int VBO_2,VAO_2;
//    glGenBuffers(1,&VBO_2);
//    glGenVertexArrays(1,&VAO_2);
//    glBindVertexArray(VAO_2);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO_2);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_2), vertices_2, GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    //glBindBuffer(GL_ARRAY_BUFFER, 0);
//    //glBindVertexArray(0);
//
//    /*********************** Over ************************/
//
//    //下面这行代码可以用线框模式绘制图形，将参数GL_LINE改为GL_FILL则恢复默认（填充）
//    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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
//        //绘制三角形
//        glUseProgram(shaderProgramOrange);
//        glBindVertexArray(VAO_1);
//        //glDrawArrays函数第一个参数是图元的类型,第二个参数是顶点数组的起始索引，第三个是绘制的顶点个数
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//
//        glUseProgram(shaderProgramYellow);
//        glBindVertexArray(VAO_2);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//    
//        //glfwSwapBuffers函数会交换颜色缓冲
//        glfwSwapBuffers(window);
//        //glfwPollEvents函数检查有没有触发什么事件
//        glfwPollEvents();
//    }
//
//    //释放之前分配的所有资源
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
//
//
