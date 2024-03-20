#include "Shaders/Shader.hpp"

Shader::Shader() {}

Shader::Shader(const char* vertexShaderFile, const char* fragmentShaderFile, float* inputVertices, int verticesLen, unsigned int* inputIndices, int indicesLen) {
    setup(vertexShaderFile, fragmentShaderFile, inputVertices, verticesLen, inputIndices, indicesLen);
}

void Shader::setup(const char* vertexShaderFile, const char* fragmentShaderFile, float* inputVertices, int verticesLen, unsigned int* inputIndices, int indicesLen) {
    error = 0;

    vertices = inputVertices;
    indices = inputIndices;

    verticesLength = verticesLen;
    indicesLength = indicesLen;

            /* 
            
            Vertices Setup
            
            */
   
    // VBO
    glGenBuffers(1, &vbo);

    // VAO
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    // EBO
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength * sizeof(int), indices, GL_STATIC_DRAW);

    // Give GL the vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(float), vertices, GL_STATIC_DRAW); // use GL_DYNAMIC_DRAW if the position data changes a lot

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(0); 
    glEnableVertexAttribArray(1); 

            /*
            
            Vertex Shader Setup 
            
            */

    // Read the vertex shader file
    fInStrm.open(vertexShaderFile, std::ios_base::in);
    if (!fInStrm.is_open()) {
        std::cout << "Failed to open vertex shader file: " << vertexShaderFile << std::endl;

        error = 1;
    }

    fInStrm.seekg(0, std::ios_base::end);
    fileLength = fInStrm.tellg();

    char* vertexShaderSrc = new char[fileLength + 1];

    fInStrm.seekg(0);

    fInStrm.read(vertexShaderSrc, fileLength);

    *(vertexShaderSrc + fileLength) = '\0'; // add a null character, because for whatever reason read() doesn't add one

    fInStrm.close();

    // // Make and compile the shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const char* const*) &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    // Check if it was successfully made
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        error = 2;
    }


            /* 
            
            Fragment Shader Setup 
            
            */

    // Read the fragment shader file
    fInStrm.open(fragmentShaderFile, std::ios_base::in);
    if (!fInStrm.is_open()) {
        std::cout << "Failed to open fragment shader file: " << fragmentShaderFile << std::endl;

        error = 1;
    }

    fInStrm.seekg(0, std::ios_base::end);
    fileLength = fInStrm.tellg();

    char* fragmentShaderSrc = new char[fileLength + 1];

    fInStrm.seekg(0);

    fInStrm.read(fragmentShaderSrc, fileLength);

    *(fragmentShaderSrc + fileLength) = '\0'; // add a null character, because for whatever reason read() doesn't add one

    fInStrm.close();
    // Make and compile the shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const char* const*) &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    // Check if it was successfully made
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        error = 2;
    }


            /* 
            
            Shader Program Creation
            
            */

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // The shaders are linked, now delete them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glLinkProgram(shaderProgram);


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error when creating shader program" << infoLog << std::endl;

        error = 3;
    }
}

void Shader::setupDynamic(const char* vertexShaderFile, const char* fragmentShaderFile, float* inputVertices, int verticesLen, unsigned int* inputIndices, int indicesLen) {
       error = 0;

    vertices = inputVertices;
    indices = inputIndices;

    verticesLength = verticesLen;
    indicesLength = indicesLen;

            /* 
            
            Vertices Setup
            
            */
   
    // VBO
    glGenBuffers(1, &vbo);

    // VAO
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    // EBO
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength * sizeof(int), indices, GL_DYNAMIC_DRAW);

    // Give GL the vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(float), vertices, GL_DYNAMIC_DRAW); // use GL_DYNAMIC_DRAW if the position data changes a lot

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(0); 
    glEnableVertexAttribArray(1); 

            /*
            
            Vertex Shader Setup 
            
            */

    // Read the vertex shader file
    fInStrm.open(vertexShaderFile, std::ios_base::in);
    if (!fInStrm.is_open()) {
        std::cout << "Failed to open vertex shader file: " << vertexShaderFile << std::endl;

        error = 1;
    }

    fInStrm.seekg(0, std::ios_base::end);
    fileLength = fInStrm.tellg();

    char* vertexShaderSrc = new char[fileLength + 1];

    fInStrm.seekg(0);

    fInStrm.read(vertexShaderSrc, fileLength);

    *(vertexShaderSrc + fileLength) = '\0'; // add a null character, because for whatever reason read() doesn't add one

    fInStrm.close();

    // // Make and compile the shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const char* const*) &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    // Check if it was successfully made
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        error = 2;
    }


            /* 
            
            Fragment Shader Setup 
            
            */

    // Read the fragment shader file
    fInStrm.open(fragmentShaderFile, std::ios_base::in);
    if (!fInStrm.is_open()) {
        std::cout << "Failed to open fragment shader file: " << fragmentShaderFile << std::endl;

        error = 1;
    }

    fInStrm.seekg(0, std::ios_base::end);
    fileLength = fInStrm.tellg();

    char* fragmentShaderSrc = new char[fileLength + 1];

    fInStrm.seekg(0);

    fInStrm.read(fragmentShaderSrc, fileLength);

    *(fragmentShaderSrc + fileLength) = '\0'; // add a null character, because for whatever reason read() doesn't add one

    fInStrm.close();
    // Make and compile the shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const char* const*) &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    // Check if it was successfully made
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        error = 2;
    }


            /* 
            
            Shader Program Creation
            
            */

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // The shaders are linked, now delete them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glLinkProgram(shaderProgram);


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error when creating shader program" << infoLog << std::endl;

        error = 3;
    }
}

void Shader::fileSetup(const char* vertexShaderFile, const char* fragmentShaderFile) { // for use if the vertices will be changed every time something is rendered
    error = 0;

            /*  
            
            Vertices Setup
            
            */
   
    // VBO
    glGenBuffers(1, &vbo);

    // VAO
    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    // EBO
    glGenBuffers(1, &ebo);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Give GL the vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // use GL_DYNAMIC_DRAW if the position data changes a lot

    // Set the vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(0); 
    glEnableVertexAttribArray(1); 

            /*
            
            Vertex Shader Setup 
            
            */

    // Read the vertex shader file
    fInStrm.open(vertexShaderFile, std::ios_base::in);
    if (!fInStrm.is_open()) {
        std::cout << "Failed to open vertex shader file: " << vertexShaderFile << std::endl;

        error = 1;
    }

    fInStrm.seekg(0, std::ios_base::end);
    fileLength = fInStrm.tellg();

    char* vertexShaderSrc = new char[fileLength + 1];

    fInStrm.seekg(0);

    fInStrm.read(vertexShaderSrc, fileLength);

    *(vertexShaderSrc + fileLength) = '\0'; // add a null character, because for whatever reason read() doesn't add one

    fInStrm.close();

    // // Make and compile the shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const char* const*) &vertexShaderSrc, NULL);
    glCompileShader(vertexShader);

    // Check if it was successfully made
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        error = 2;
    }


            /* 
            
            Fragment Shader Setup 
            
            */

    // Read the fragment shader file
    fInStrm.open(fragmentShaderFile, std::ios_base::in);
    if (!fInStrm.is_open()) {
        std::cout << "Failed to open fragment shader file: " << fragmentShaderFile << std::endl;

        error = 1;
    }

    fInStrm.seekg(0, std::ios_base::end);
    fileLength = fInStrm.tellg();

    char* fragmentShaderSrc = new char[fileLength + 1];

    fInStrm.seekg(0);

    fInStrm.read(fragmentShaderSrc, fileLength);

    *(fragmentShaderSrc + fileLength) = '\0'; // add a null character, because for whatever reason read() doesn't add one

    fInStrm.close();
    // Make and compile the shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const char* const*) &fragmentShaderSrc, NULL);
    glCompileShader(fragmentShader);

    // Check if it was successfully made
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);


    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;

        error = 2;
    }


            /* 
            
            Shader Program Creation
            
            */

    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    // The shaders are linked, now delete them
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glLinkProgram(shaderProgram);


    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "Error when creating shader program" << infoLog << std::endl;

        error = 3;
    }
}

void Shader::setVertices(float* inputVertices, int verticesLen, unsigned int* inputIndices, int indicesLen) {
    vertices = inputVertices;
    indices = inputIndices;
    
    verticesLength = verticesLen;
    indicesLength = indicesLen;

    glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength * sizeof(int), indices, GL_STATIC_DRAW);

    // Give GL the vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(float), vertices, GL_STATIC_DRAW); // use GL_DYNAMIC_DRAW if the position data changes a lot

    return;
}

void Shader::updateVertices(float* inputVertices, int verticesLen, unsigned int* inputIndices, int indicesLen) {
    vertices = inputVertices;
    indices = inputIndices;

    verticesLength = verticesLen;
    indicesLength = indicesLen;

    glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesLength * sizeof(int), indices, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verticesLength * sizeof(float), vertices, GL_DYNAMIC_DRAW); // use GL_DYNAMIC_DRAW if the position data changes a lot
}

int Shader::getErrorCode() {
    return error;
}

void Shader::activate() {
    // Use the shader program
    glUseProgram(shaderProgram);

    // Bind the vaos
    glBindVertexArray(vao);


    return;
}

void Shader::draw() {
    // Draw the object
    set2f("screenDimensions", windowWidth, windowHeight);
    glDrawElements(GL_LINES, indicesLength, GL_UNSIGNED_INT, 0);

    return;
}

        /*
        
        Float Setting
        
        */

void Shader::set1f(const char* varName, float arg1) {
    glUniform1f(glGetUniformLocation(shaderProgram, varName), arg1);

    return;
}

void Shader::set2f(const char* varName, float arg1, float arg2) {
    glUniform2f(glGetUniformLocation(shaderProgram, varName), arg1, arg2);

    return;
}

void Shader::set3f(const char* varName, float arg1, float arg2, float arg3) {
    glUniform3f(glGetUniformLocation(shaderProgram, varName), arg1, arg2, arg3);

    return;
}

void Shader::set4f(const char* varName, float arg1, float arg2, float arg3, float arg4) {
    glUniform4f(glGetUniformLocation(shaderProgram, varName), arg1, arg2, arg3, arg4);

    return;
}


        /*
        
        Int Setting
        
        */

void Shader::set1i(const char* varName, int arg1) {
    glUniform1i(glGetUniformLocation(shaderProgram, varName), arg1);

    return;
}

void Shader::set2i(const char* varName, int arg1, int arg2) {
    glUniform2i(glGetUniformLocation(shaderProgram, varName), arg1, arg2);

    return;
}

void Shader::set3i(const char* varName, int arg1, int arg2, int arg3) {
    glUniform3i(glGetUniformLocation(shaderProgram, varName), arg1, arg2, arg3);

    return;
}

void Shader::set4i(const char* varName, int arg1, int arg2, int arg3, int arg4) {
    glUniform4i(glGetUniformLocation(shaderProgram, varName), arg1, arg2, arg3, arg4);

    return;
}
