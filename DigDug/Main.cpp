#include "DigDugPCH.h"
#pragma comment(lib,"xinput.lib")

// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "Minigin.h"
#pragma warning( push )  
#pragma warning( disable : 4100 )  
#undef main

	int main(int argc, char* argv[]) 
{
#pragma warning( pop )

		cem::Minigin engine;
		engine.Run();
		return 0;
	}

