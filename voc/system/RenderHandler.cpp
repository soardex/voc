#include "RenderHandler.h"

CRenderHandler::CRenderHandler()
    : m_psWindow(0)
{

}

CRenderHandler::~CRenderHandler()
{
}

void CRenderHandler::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        exit(1);
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO);

    m_psWindow = SDL_CreateWindow("VOC fizzafruit",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            640,
            480,
            SDL_WINDOW_OPENGL);

    m_sContext = SDL_GL_CreateContext(m_psWindow);
    if (!m_sContext)
        exit(1);

    GLenum status = glewInit();
    if (status != GLEW_OK)
    {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(status));
        exit(1);
    }

    SDL_GL_SetSwapInterval(1);
}

void CRenderHandler::update() 
{
    SDL_GL_SwapWindow(m_psWindow);
    SDL_Delay(10);
}

void CRenderHandler::destroy()
{
    if (m_sContext)
        SDL_GL_DeleteContext(m_sContext);

    SDL_DestroyWindow(m_psWindow);
    SDL_Quit();
}

