#include "SceneHandler.h"
#include "../utils/Helpers.h"
#include "../utils/GeometryUtils.h"

std::string const vertShaderSource = "/home/pastel/Projects/voc/src/build/assets/shaders/image-2d.vs";
std::string const fragShaderSource = "/home/pastel/Projects/voc/src/build/assets/shaders/image-2d.fs";

std::string const textureSampler = "/home/pastel/Projects/voc/src/build/assets/textures/water.jpg";

GLsizei gridElementCount;
GLsizei cubeElementCount;

GLuint locType;

CSceneHandler::CSceneHandler()
    : m_vVertexArray(OBJECT::O_MAX),
    m_vGridBuffer(BUFFER::B_MAX),
    m_vCubeBuffer(BUFFER::B_MAX),
    m_sCurrentMatrix(1)
{
    m_nProgram = 0;

    m_nUniformMVP = 0;
    m_nUniformDiffuse = 0;
}

CSceneHandler::~CSceneHandler()
{
}

void CSceneHandler::init()
{
    m_sTexture = CTextureManager::inst();
    m_sTexture->load(textureSampler.c_str(), 1);

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
        glBindAttribLocation(m_nProgram, helpers::semantic::attr::TEXCOORD, "texcoord");
        glLinkProgram(m_nProgram);

        validated = helpers::checkProgram(m_nProgram);
    }

    if (validated)
    {
        m_nUniformMVP = glGetUniformLocation(m_nProgram, "mvp");
        m_nUniformDiffuse = glGetUniformLocation(m_nProgram, "diffuse");

        locType = glGetUniformLocation(m_nProgram, "type");
    }

    if (validated)
    {
        glUseProgram(m_nProgram);
        glUniform4fv(m_nUniformDiffuse, 1, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);
        glUseProgram(0);
    }
    
    glGenVertexArrays(OBJECT::O_MAX, &m_vVertexArray[0]);

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

        glGenBuffers(BUFFER::B_MAX, &m_vGridBuffer[0]);

        glBindBuffer(GL_ARRAY_BUFFER, m_vGridBuffer[BUFFER::B_VERTEX]);
        glBufferData(GL_ARRAY_BUFFER, gridVertexSize, &gridVertexData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vGridBuffer[BUFFER::B_ELEMENT]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, gridElementSize, &gridElementData[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(m_vVertexArray[OBJECT::O_GRID]);
            glBindBuffer(GL_ARRAY_BUFFER, m_vGridBuffer[BUFFER::B_VERTEX]);
            glVertexAttribPointer(helpers::semantic::attr::POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vGridBuffer[BUFFER::B_ELEMENT]);
            glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
        glBindVertexArray(0);
    }

    //! Populate Cube Variables
    {
        GLsizei cubeVertexCount = 12;
        struct vertv3v2
        {
            vertv3v2(glm::vec3 const &pos, glm::vec2 const &tc)
                : position(pos),
                texcoord(tc)
            {
            }

            glm::vec3 position;
            glm::vec2 texcoord;
        };

        GLsizeiptr cubeVertexSize = cubeVertexCount * sizeof(vertv3v2);
        vertv3v2 cubeVertexData[12] = 
        {
            vertv3v2(glm::vec3(0, 0, 0), glm::vec2(0, 1)),
            vertv3v2(glm::vec3(1, 0, 0), glm::vec2(1, 1)),
            vertv3v2(glm::vec3(1, 1, 0), glm::vec2(1, 0)),
            vertv3v2(glm::vec3(0, 1, 0), glm::vec2(0, 0)),
            vertv3v2(glm::vec3(1, 0, 1), glm::vec2(0, 1)),
            vertv3v2(glm::vec3(1, 1, 1), glm::vec2(0, 0)),
            vertv3v2(glm::vec3(0, 1, 1), glm::vec2(1, 0)),
            vertv3v2(glm::vec3(0, 0, 1), glm::vec2(1, 1)),
            vertv3v2(glm::vec3(0, 1, 1), glm::vec2(0, 1)),
            vertv3v2(glm::vec3(0, 1, 0), glm::vec2(1, 1)),
            vertv3v2(glm::vec3(1, 0, 1), glm::vec2(1, 0)),
            vertv3v2(glm::vec3(1, 0, 0), glm::vec2(0, 0))
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

        //GLsizei cubeNormalsCount = 12;
        //GLsizeiptr cubeNormalsSize = cubeNormalsCount * sizeof(glm::vec3);
        //glm::vec3 cubeNormalsData[12] = 
        //{
        //    glm::vec3(-1, -1, -1),
        //    glm::vec3( 1, -1, -1),
        //    glm::vec3( 1,  1, -1),
        //    glm::vec3(-1,  1, -1),
        //    glm::vec3( 1, -1,  1),
        //    glm::vec3( 1,  1,  1),
        //    glm::vec3(-1,  1,  1),
        //    glm::vec3(-1, -1,  1),
        //    glm::vec3(-1,  1,  1),
        //    glm::vec3(-1,  1, -1),
        //    glm::vec3( 1, -1,  1),
        //    glm::vec3( 1, -1, -1)
        //};

        glGenBuffers(BUFFER::B_MAX, &m_vCubeBuffer[0]);

        glBindBuffer(GL_ARRAY_BUFFER, m_vCubeBuffer[BUFFER::B_VERTEX]);
        glBufferData(GL_ARRAY_BUFFER, cubeVertexSize, cubeVertexData, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vCubeBuffer[BUFFER::B_ELEMENT]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeElementSize, cubeElementData, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindVertexArray(m_vVertexArray[OBJECT::O_CUBE]);
            glBindBuffer(GL_ARRAY_BUFFER, m_vCubeBuffer[BUFFER::B_VERTEX]);
            glVertexAttribPointer(helpers::semantic::attr::POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(vertv3v2), BUFFER_OFFSET(0));
            glVertexAttribPointer(helpers::semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(vertv3v2), BUFFER_OFFSET(sizeof(glm::vec2)));
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vCubeBuffer[BUFFER::B_ELEMENT]);
            glEnableVertexAttribArray(helpers::semantic::attr::POSITION);
            glEnableVertexAttribArray(helpers::semantic::attr::TEXCOORD);
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

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glFrontFace(GL_CCW);

    glUseProgram(m_nProgram);
    glUniformMatrix4fv(m_nUniformMVP, 1, GL_FALSE, &mvp[0][0]);
    glUseProgram(0);
}

void CSceneHandler::update(float tse, glm::mat4 view)
{
    glm::mat4 mvp = m_sProjection * view * m_sModel;

    glUseProgram(m_nProgram);
    glUniformMatrix4fv(m_nUniformMVP, 1, GL_FALSE, &mvp[0][0]);
    glUseProgram(0);

    m_sCurrentMatrix = mvp;

    glClearColor(0.0f, 0.7f, 0.7f, 1.0f);
    glClearDepth(1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(m_nProgram);
    push();
        glBindVertexArray(m_vVertexArray[OBJECT::O_GRID]);
            glDrawElements(GL_LINES, gridElementCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        push();
            glUniform1i(locType, 1);
            glEnable(GL_TEXTURE_2D);
            m_sTexture->bindTexture(1);
            glBindVertexArray(m_vVertexArray[OBJECT::O_CUBE]);
                glDrawElements(GL_TRIANGLES, cubeElementCount, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
            glDisable(GL_TEXTURE_2D);
            glUniform1i(locType, 0);
        pop();
    pop();
    glUseProgram(0);
}

void CSceneHandler::destroy()
{
    glDeleteBuffers(BUFFER::B_MAX, &m_vCubeBuffer[0]);
    glDeleteBuffers(BUFFER::B_MAX, &m_vGridBuffer[0]);
    glDeleteVertexArrays(OBJECT::O_MAX, &m_vVertexArray[0]);
    glDeleteProgram(m_nProgram);

    m_sTexture->unloadTexture(1);
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

