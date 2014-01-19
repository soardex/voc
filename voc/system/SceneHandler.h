#ifndef _SCENE_HANDLER_H_
#define _SCENE_HANDLER_H_

#include "../Commons.h"

class CSceneHandler
{
public:
    CSceneHandler();
    ~CSceneHandler();
    
    void init();
    void update(float tse);
    void destroy();
private:

};

#endif /* end of include guard: _SCENE_HANDLER_H_ */
