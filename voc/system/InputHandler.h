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

    enum SPECKEY
    {
        E_SK_UP = 0,
        E_SK_DN,
        E_SK_LT,
        E_SK_RT,

        E_SK_W,
        E_SK_S,
        E_SK_A,
        E_SK_D,

        E_SK_MAX
    };

    bool getSpectatorKeyState(SPECKEY key) { return m_bSpectatorKeys[key]; }

private:
    SDL_Event m_sEvent;
    int m_nClose;
    int m_nStickyKeys;
    bool m_bSpectatorKeys[E_SK_MAX];
};

#endif /* end of include guard: _INPUT_HANDLER_H_ */
