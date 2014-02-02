#include "SceneHandler.h"
#include "../utils/Helpers.h"
#include "../utils/GeometryUtils.h"

std::string const vertShaderSource = "/home/pastel/Projects/voc/src/build/assets/shaders/common.vs";
std::string const fragShaderSource = "/home/pastel/Projects/voc/src/build/assets/shaders/common.fs";

GLsizei gridElementCount;
GLsizei cubeElementCount;

CSceneHandler::CSceneHandler()
    : m_sCurrentMatrix(1)
{
    m_nProgram = 0;

    m_nVertexArray = 0;
    m_nArrayBuffer = 0;
    m_nElementBuffer = 0;

    m_nCubeVertexArray = 0;
    m_nCubeArrayBuffer = 0;
    m_nCubeElementBuffer = 0;

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

        glBindAttribLocation(m_nProgram, helpers::semantic::attr::POSITION, "position");
        glLinkProgram(m_nProgram);

        validated = helpers::checkProgram(m_nProgram);
    }

    if (validated)
    {
        m_nUniformMVP = glGetUniformLocation(m_nProgram, "mvp");
        m_nUniformDiffuse = glGetUniformLocation(m_nProgram, "diffuse");
    }

    if (validated)
    {
        glUseProgram(m_nProgram);
        glUniform4fv(m_nUniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);
        glUseProgram(0);
    }
    
    //! Populate Grid VAO
    {
        GLsizeiptr gridElementSize;
        std::vector<glm::uint32> gridElementData;

        GLsizei gridVertexCount;
        GLsizeiptr gridVertexSize;
        std::vector<glm::vec3> gridVertexData;

        float extent = 30.0f, step = 1.0f, h = -0.6f;
        for (int line = -extent; line <= extent; line += step)
        {
            gridVertexData.push_back(glm::vec3(line, h, extent));
            gridVertexData.push_back(glm::vec3(line, h, -extent));

            gridVertexData.push_back(glm::vec3(extent, h, line));
            gridVertexData.push_back(glm::vec3(-extent, h, line));
        }

        gridVertexCount = gridVertexData.size();
        gridVertexSize = gridVertexCount * sizeof(glm::vec3);

        gridElementCount = gridVertexCount;
        gridElementSize = gridElementCount * sizeof(glm::uint32);
        for (int i = 0; i < gridElementCount; i++)
            gridElementData.push_back(i);

        glGenBuffers(1, &m_nArrayBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_nArrayBuffer);
        glBufferData(GL_ARRAY_BUFFER, gridVertexSize, &gridVertexData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &m_nElementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nElementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, gridElementSize, &gridElementData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &m_nVertexArray);
        glBindVertexArray(m_nVertexArray);
            glBindBuffer(GL_ARRAY_BUFFER, m_nArrayBuffer);
            glVertexAttribPointer(helpers::semantic::attr::POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nElementBuffer);
            glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
        glBindVertexArray(0);
    }

    //! Populate Cube Variables
    {
        GLsizei cubeVertexCount = 12;
        GLsizeiptr cubeVertexSize = cubeVertexCount * sizeof(glm::vec3);
        glm::vec3 cubeVertexData[12] = 
        {
            glm::vec3(0, 0, 0),
            glm::vec3(1, 0, 0),
            glm::vec3(1, 1, 0),
            glm::vec3(0, 1, 0),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 1, 1),
            glm::vec3(0, 1, 1),
            glm::vec3(0, 0, 1),
            glm::vec3(0, 1, 1),
            glm::vec3(0, 1, 0),
            glm::vec3(1, 0, 1),
            glm::vec3(1, 0, 0)
        };

        cubeElementCount = 36;
        GLsizeiptr cubeElementSize = cubeElementCount * sizeof(glm::uint32);
        glm::uint32 cubeElementData[36] =
        {
            0, 2, 1,
            0, 3, 2,
            1, 5, 4,
            1, 2, 5,
            4, 6, 7,
            4, 5, 6,
            7, 3, 0,
            7, 6, 3,
            9, 5, 2,
            9, 8, 5,
            0, 11, 10,
            0, 10, 7
        };

        GLsizei cubeNormalsCount = 12;
        GLsizeiptr cubeNormalsSize = cubeNormalsCount * sizeof(glm::vec3);
        glm::vec3 cubeNormalsData[12] = 
        {
            glm::vec3(-1, -1, -1),
            glm::vec3( 1, -1, -1),
            glm::vec3( 1,  1, -1),
            glm::vec3(-1,  1, -1),
            glm::vec3( 1, -1,  1),
            glm::vec3( 1,  1,  1),
            glm::vec3(-1,  1,  1),
            glm::vec3(-1, -1,  1),
            glm::vec3(-1,  1,  1),
            glm::vec3(-1,  1, -1),
            glm::vec3( 1, -1,  1),
            glm::vec3( 1, -1, -1)
        };

        GLsizei cubeTexCoordsCount = 12;
        GLsizeiptr cubeTexCoordsSize = cubeTexCoordsCount * sizeof(glm::vec2);
        glm::vec2 cubeTexCoordsData[12] =
        {
            glm::vec2(0, 1),
            glm::vec2(1, 1),
            glm::vec2(1, 0),
            glm::vec2(0, 0),
            glm::vec2(0, 1),
            glm::vec2(0, 0),
            glm::vec2(1, 0),
            glm::vec2(1, 1),
            glm::vec2(0, 1),
            glm::vec2(1, 1),
            glm::vec2(1, 0),
            glm::vec2(0, 0)
        };

        glGenBuffers(1, &m_nCubeArrayBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_nCubeArrayBuffer);
        glBufferData(GL_ARRAY_BUFFER, cubeVertexSize, cubeVertexData, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glGenBuffers(1, &m_nCubeElementBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nCubeElementBuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeElementSize, cubeElementData, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glGenVertexArrays(1, &m_nCubeVertexArray);
        glBindVertexArray(m_nCubeVertexArray);
            glBindBuffer(GL_ARRAY_BUFFER, m_nCubeArrayBuffer);
            glVertexAttribPointer(helpers::semantic::attr::POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_nCubeElementBuffer);
            glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
        glBindVertexArray(0);
    }

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
    glm::mat4 mvp = m_sProjection * view * m_sModel;
    glUniformMatrix4fv(m_nUniformMVP, 1, GL_FALSE, &mvp[0][0]);

    m_sCurrentMatrix = mvp;

    glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    push();
        glBindVertexArray(m_nVertexArray);
            glDrawElements(GL_LINES, gridElementCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        push();
            glBindVertexArray(m_nCubeVertexArray);
                glDrawElements(GL_TRIANGLES, cubeElementCount, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
        pop();
    pop();
}

void CSceneHandler::destroy()
{
    glUseProgram(0);

    glDeleteBuffers(1, &m_nCubeElementBuffer);
    glDeleteBuffers(1, &m_nCubeArrayBuffer);
    glDeleteVertexArrays(1, &m_nCubeVertexArray);

    glDeleteBuffers(1, &m_nElementBuffer);
    glDeleteBuffers(1, &m_nArrayBuffer);
    glDeleteVertexArrays(1, &m_nVertexArray);
    glDeleteProgram(m_nProgram);
}

void CSceneHandler::push()
{
    m_vStack.push(m_sCurrentMatrix);
}

void CSceneHandler::pop()
{
    m_sCurrentMatrix = m_vStack.top();
    m_vStack.pop();
}

