#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    //环境光照
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;
    
    //漫反射
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    //使用max函数保证漫反射分量不会变成负数
    float diff = max(dot(norm,lightDir),0.0);
    //得到最终的漫反射分量
    vec3 diffuse = diff * lightColor;
    
    //镜面光照
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir,norm);
    float spec = pow(max(dot(viewDir,reflectDir),0.0),32);
    vec3 specular = specularStrength * spec * lightColor;
    
    //冯氏光照三分量：环境(Ambient)、漫反射(Diffuse)和镜面(Specular)光照
    vec3 result = (ambient + diffuse + specular) * objectColor;
    FragColor = vec4(result, 1.0);  
}
