#include "DigDugPCH.h"
#pragma comment(lib,"xinput.lib")

// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "Minigin.h"

#undef main

int __stdcall WinMain(HINSTANCE,HINSTANCE,PSTR,INT) 
{
	cem::Minigin engine;
	engine.Run();
	return 0;
}

