#include <windows.h>
#include "WindowInitialization.h"
#include "D3DInitializer.h"
#include "ToshRenderer.h"
#include <vector>
#include "VertexTypes.h"
#include "ObjModelParser.h"
#include <fstream>
#include "RenderStates.h"
#include "AlphaBlendSorter.h"
#include "GeometryLoader.h"
#include "BasicLevel.h"
#include "GameHandler.h"

//changed VertexBasic Position to XMFLOAT4

using namespace DirectX; using std::vector; using std::ofstream;

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	GameHandler* mTGameHandler = new GameHandler(hInstance, nCmdShow);

	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			mTGameHandler->update();
			mTGameHandler->render();
		}
	}


	return (int)msg.wParam;
}