#include "SceneHandler.h"
#include "../utils/Helpers.h"
#include "../utils/GeometryUtils.h"

std::string const vertShaderSource = "/home/pastel/Projects/voc/src/build/assets/shaders/common.vs";
std::string const fragShaderSource = "/home/pastel/Projects/voc/src/build/assets/shaders/common.fs";

//GLsizei const elementCount = 6;
//GLsizeiptr const elementSize = elementCount * sizeof(glm::uint32);
//glm::uint32 const elementData[elementCount] =
//{
//    0, 1, 2,
//    0, 2, 3
//};
//
//GLsizei const vertexCount = 4;
//GLsizeiptr const vertexSize = vertexCount * sizeof(glm::vec2);
//glm::vec2 const vertexData[vertexCount] = 
//{
//    glm::vec2(-1.0f, -1.0f),
//    glm::vec2( 1.0f, -1.0f),
//    glm::vec2( 1.0f,  1.0f),
//    glm::vec2(-1.0f,  1.0f)
//};

GLsizei elementCount;
GLsizeiptr elementSize;
std::vector<glm::uint32> elementData;

GLsizei vertexCount;
GLsizeiptr vertexSize;
std::vector<glm::vec3> vertexData;

CSceneHandler::CSceneHandler()
{
    m_nVertexArray = 0;
    m_nProgram = 0;
    m_nArrayBuffer = 0;
    m_nElementBuffer = 0;

    m_nUniformMVP = 0;
    m_nUniformDiffuse = 0;
}

CSceneHandler::~CSceneHandler()
{
}

void CSceneHandler::init()
{
    bool validated = true;

    helpers::checkGLVersion();
    if (validated)
    {
        GLuint vertShader = helpers::createShader(GL_VERTEX_SHADER, vertShaderSource);
        GLuint fragShader = helpers::createShader(GL_FRAGMENT_SHADER, fragShaderSource);

        validated = validated && helpers::checkShader(vertShader, vertShaderSource);
        validated = validated && helpers::checkShader(fragShader, fragShaderSource);

        m_nProgram = glCreateProgram();
        glAttachShader(m_nProgram, vertShader);
        glAttachShader(m_nProgram, fragShader);

        glDeleteShader(vertShader);
        glDeleteShader(fragShader);

        glBindAttribLocation(m_nProgram, helpers::semantic::attr::POSITION, "Position");
        glLinkProgram(m_nProgram);

        validated = helpers::checkProgram(m_nProgram);
    }

    if (validated)
    {
        m_nUniformMVP = glGetUniformLocation(m_nProgram, "MVP");
        m_nUniformDiffuse = glGetUniformLocation(m_nProgram, "Diffuse");
    }

    if (validated)
    {
        glUseProgram(m_nProgram);
        glUniform4fv(m_nUniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);
        glUseProgram(0);
    }
    
    float extent = 30.0f, step = 1.0f, h = -0.6f;
    for (int line = -extent; line <= extent; line += step)
    {
        vertexData.push_back(glm::vec3(line, h, extent));
        vertexData.push_back(glm::vec3(line, h, -extent));

        vertexData.push_back(glm::vec3(extent, h, line));
        vertexData.push_back(glm::vec3(-extent, h, line));
    }

    vertexCount = vertexData.size();
    vertexSize = vertexCount * sizeof(glm::vec3);

    elementCount = vertexCount;
    elementSize = elementCount * sizeof(glm::uint32);
    for (int i = 0; i < elementCount; i++)
        elementData.push_back(i);


    printf("sizeof grid: %lu", sizeof(glm::vec3));

    glGenBuffers(1, &m_nArrayBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, m_nArrayBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexSize, &vertexData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &m_nElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementSize, &elementData[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glViewport(0, 0, 640, 480);

    m_sProjection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 750.0f);
    m_sModel = glm::mat4(1.0f);
    m_sView = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 3.0f),
            glm::vec3(0.0f, 0.0f, -5.0f),
            glm::vec3(0.0f, 1.0f, 0.0f));

    glm::mat4 mvp = m_sProjection * m_sView * m_sModel;

    glUseProgram(m_nProgram);
    glUniformMatrix4fv(m_nUniformMVP, 1, GL_FALSE, &mvp[0][0]);
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

    glm::mat4 mvp = m_sProjection * view * m_sModel;
    glUniformMatrix4fv(m_nUniformMVP, 1, GL_FALSE, &mvp[0][0]);

    glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindBuffer(GL_ARRAY_BUFFER, m_nArrayBuffer);
    glVertexAttribPointer(helpers::semantic::attr::POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nElementBuffer);

    glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
    glDrawElements(GL_LINES, elementCount, GL_UNSIGNED_INT, 0);
    glDisableVertexAttribArray(helpers::semantic::attr::POSITION);
}

void CSceneHandler::destroy()
{
    glUseProgram(0);

    glDeleteBuffers(1, &m_nArrayBuffer);
    glDeleteBuffers(1, &m_nElementBuffer);
    glDeleteProgram(m_nProgram);
}

