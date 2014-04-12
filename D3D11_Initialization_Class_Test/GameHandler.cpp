#include "GameHandler.h"


GameHandler::GameHandler(HINSTANCE hInstance, int nCmdShow){
	

	mWinInit = new WindowInitializer(hInstance, nCmdShow);
	mD3DInit = new D3DInitializer(mWinInit->g_hWnd);
	mTRenderer = new ToshRenderer(mD3DInit);
}