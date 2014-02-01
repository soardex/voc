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
private:
    glm::mat4 m_sProjection;
    glm::mat4 m_sView;
    glm::mat4 m_sModel;

    GLuint m_nVertexArray;
    GLuint m_nProgram;
    GLuint m_nArrayBuffer;
    GLuint m_nElementBuffer;

    GLint m_nUniformMVP;
    GLint m_nUniformDiffuse;
};

#endif /* end of include guard: _SCENE_HANDLER_H_ */
