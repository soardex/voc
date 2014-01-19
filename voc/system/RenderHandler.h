#ifndef _RENDER_HANDLER_H_
#define _RENDER_HANDLER_H_

#include "../Commons.h"

class CRenderHandler
{
public:
    explicit CRenderHandler();
    ~CRenderHandler();

    void init();
    void update();
    void destroy();

    SDL_Window &getWindow() const { return *m_psWindow; }
    SDL_GLContext getGLContext() const { return m_sContext; }

private:
    SDL_Window *m_psWindow;
    SDL_GLContext m_sContext;
};

#endif /* end of include guard: _RENDER_HANDLER_H_ */
