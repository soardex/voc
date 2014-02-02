#ifndef _SCENE_HANDLER_H_
#define _SCENE_HANDLER_H_

#include "../Commons.h"
#include "AssetsHandler.h"

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
    CTextureManager *m_sTexture;

    glm::mat4 m_sProjection;
    glm::mat4 m_sView;
    glm::mat4 m_sModel;

    enum OBJECT
    {
        O_GRID,
        O_CUBE,

        O_MAX
    };

    enum BUFFER
    {
        B_VERTEX,
        B_ELEMENT,

        B_MAX
    };

    GLuint m_nProgram;

    std::vector<GLuint> m_vVertexArray;
    std::vector<GLuint> m_vGridBuffer;
    std::vector<GLuint> m_vCubeBuffer;

    GLint m_nUniformMVP;
    GLint m_nUniformDiffuse;

    std::stack<glm::mat4, std::vector<glm::mat4> > m_vStack;
    glm::mat4 m_sCurrentMatrix;
};

#endif /* end of include guard: _SCENE_HANDLER_H_ */
