#include "MiniginPCH.h"
#pragma comment(lib,"xinput.lib")

// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#include "SDL.h"
#include "Minigin.h"
int playDIGDUG;
#pragma warning( push )  
#pragma warning( disable : 4100 )  
int main(int argc, char* argv[]) {
#pragma warning( pop )

	Minigin engine;
	engine.Run();
	playDIGDUG;
    return 0;
}

