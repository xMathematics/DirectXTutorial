//
// Created by Dongz on 2022/11/8.
//

#ifndef DIRECTXTUTORIAL_GAMEAPP_H
#define DIRECTXTUTORIAL_GAMEAPP_H

#include "d3dApp.h"
class GameApp : public D3DApp
{
public:
    GameApp(HINSTANCE hInstance, const std::wstring& windowName, int initWidth, int initHeight);
    ~GameApp();

    bool Init();
    void OnResize();
    void UpdateScene(float dt);
    void DrawScene();
};

#endif //DIRECTXTUTORIAL_GAMEAPP_H
