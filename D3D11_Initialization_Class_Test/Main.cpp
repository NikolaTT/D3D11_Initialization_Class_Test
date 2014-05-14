#include <windows.h>
#include <vector>
#include <fstream>
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