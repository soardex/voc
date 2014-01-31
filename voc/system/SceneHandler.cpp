#include "SceneHandler.h"
#include "../utils/Helpers.h"
#include "../utils/GeometryUtils.h"

std::string const vertShaderSource = "/home/pastel/Projects/voc/src/build/assets/shaders/common.vs";
std::string const fragShaderSource = "/home/pastel/Projects/voc/src/build/assets/shaders/common.fs";

GLsizei const elementCount = 6;
GLsizeiptr const elementSize = elementCount * sizeof(glm::uint32);
glm::uint32 const elementData[elementCount] =
{
    0, 1, 2,
    0, 2, 3
};

GLsizei const vertexCount = 4;
GLsizeiptr const vertexSize = vertexCount * sizeof(glm::vec2);
glm::vec2 const vertexData[vertexCount] = 
{
    glm::vec2(-1.0f, -1.0f),
    glm::vec2( 1.0f, -1.0f),
    glm::vec2( 1.0f,  1.0f),
    glm::vec2(-1.0f,  1.0f)
};

GLuint vertexArray = 0;
GLuint program = 0;
GLuint arrayBuffer = 0;
GLuint elementBuffer = 0;
GLint uniformMVP = 0;
GLint uniformDiffuse = 0;

CSceneHandler::CSceneHandler()
{
}

CSceneHandler::~CSceneHandler()
{
}

void CSceneHandler::init()
{
    bool validated = true;

    if (validated)
    {
        GLuint vertShader = helpers::createShader(GL_VERTEX_SHADER, vertShaderSource);
        GLuint fragShader = helpers::createShader(GL_FRAGMENT_SHADER, fragShaderSource);

        validated = validated && helpers::checkShader(vertShader, vertShaderSource);
        validated = validated && helpers::checkShader(fragShader, fragShaderSource);

        program = glCreateProgram();
        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        glBindAttribLocation(program, helpers::semantic::attr::POSITION, "Position");
        glLinkProgram(program);

        validated = helpers::checkProgram(program);
    }

    if (validated)
    {
        uniformMVP = glGetUniformLocation(program, "MVP");
        uniformDiffuse = glGetUniformLocation(program, "Diffuse");
    }

    if (validated)
    {
        glUseProgram(program);
        glUniform4fv(uniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);
        glUseProgram(0);
    }
    
    glGenBuffers(1, &arrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexData, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &elementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize, elementData, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CSceneHandler::update(float tse, glm::mat4 view)
{
    glViewport(0, 0, 640, 480);

    m_sProjection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 750.0f);
    m_sModel = glm::mat4(1.0f);
    m_sView = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, -5.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 mvp = m_sProjection * m_sView * m_sModel;

    glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(program);
    glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, &mvp[0][0]);

    glBindBuffer(GL_ARRAY_BUFFER, arrayBuffer);
    glVertexAttribPointer(helpers::semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBuffer);

    glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
    glDrawRangeElements(GL_TRIANGLES, 0, vertexCount, elementCount, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(helpers::semantic::attr::POSITION);

    glUseProgram(0);
}

void CSceneHandler::destroy()
{
    glDeleteBuffers(1, &arrayBuffer);
    glDeleteBuffers(1, &elementBuffer);
    glDeleteProgram(program);
}

