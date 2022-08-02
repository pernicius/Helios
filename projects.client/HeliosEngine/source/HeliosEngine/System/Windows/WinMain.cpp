#include "pch_engine.h"
#ifdef HE_SYSTEM_WINDOWS

#include "HeliosEngine/Core/Application.h"
#include <Windows.h>


#ifdef HE_BUILD_DEBUG
// ConsoleApp for stdout debuging
int main(int argc, char** argv)
#else
// WindowedApp
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
#endif
{
	return HeliosEngine::AppMain(__argc, __argv);
}


#endif // HE_SYSTEM_WINDOWS
