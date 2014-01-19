#ifndef _INPUT_HANDLER_H_
#define _INPUT_HANDLER_H_

#include "../Commons.h"

class CInputHandler
{
public:
    CInputHandler();
    ~CInputHandler();

    void update();
    bool isRunning() { return (m_nClose) ? false : true; }

private:
    SDL_Event m_sEvent;
    int m_nClose;
};

#endif /* end of include guard: _INPUT_HANDLER_H_ */
