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
private:
    CModelLoader *m_psModel;

    glm::mat4 m_sProjection;
    glm::mat4 m_sView;
    glm::mat4 m_sModel;
};

#endif /* end of include guard: _SCENE_HANDLER_H_ */
