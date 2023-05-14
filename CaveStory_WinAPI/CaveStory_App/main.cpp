#include <iostream>
#include<GameEngineCore/GameEngineCore.h>
#include<CaveStory_Contents/ContentsCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{

    // CallBack 방식이라고 합니다.
    GameEngineCore::EngineStart<ContentsCore>("WinAPI_Cave_Story", hInstance);
    return 0;

}