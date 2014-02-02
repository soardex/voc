#ifndef _SCENE_HANDLER_H_
#define _SCENE_HANDLER_H_

#include "../Commons.h"

class CSceneHandler
{
public:
    CSceneHandler();
    ~CSceneHandler();
    
    void init();
    void update(float tse, glm::mat4 view);
    void destroy();

protected:
    void push();
    void pop();

private:
    glm::mat4 m_sProjection;
    glm::mat4 m_sView;
    glm::mat4 m_sModel;

    GLuint m_nProgram;
    GLuint m_nVertexArray;
    GLuint m_nArrayBuffer;
    GLuint m_nElementBuffer;

    GLuint m_nCubeVertexArray;
    GLuint m_nCubeArrayBuffer;
    GLuint m_nCubeElementBuffer;

    GLint m_nUniformMVP;
    GLint m_nUniformDiffuse;

    std::stack<glm::mat4, std::vector<glm::mat4> > m_vStack;
    glm::mat4 m_sCurrentMatrix;
};

#endif /* end of include guard: _SCENE_HANDLER_H_ */
