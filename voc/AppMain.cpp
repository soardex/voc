#include "AppMain.h"

CEmperorSystem *g_sCES = NULL;

int main()
{
    g_sCES = new CEmperorSystem();
    if (g_sCES)
        g_sCES->run();

    delete g_sCES;
    g_sCES = NULL;

	return 0;
}

