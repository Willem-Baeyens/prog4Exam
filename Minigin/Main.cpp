#pragma once
#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <iostream>

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "TextRenderer.h"
#include "TextureRenderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "Fps.h"


void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	Font* LinguaFontPtr = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fpsCounter = std::make_unique<GameObject>();
	
	fpsCounter->AddComponent<TextRenderer>("",LinguaFontPtr);
	fpsCounter->AddComponent<Fps>();
	fpsCounter->m_Transform.SetPosition(0, 20, 0);

	auto backGround = std::make_unique<GameObject>();
	backGround->AddComponent<TextureRenderer>(ResourceManager::GetInstance().LoadTexture("background.tga"));

	auto daeLogo = std::make_unique<GameObject>();
	daeLogo->AddComponent<TextureRenderer>(ResourceManager::GetInstance().LoadTexture("logo.tga"));
	daeLogo->m_Transform.SetPosition(216, 180, 0);
	
	auto title = std::make_unique<GameObject>();
	title->AddComponent<TextRenderer>("Programming 4 Assignment", LinguaFontPtr);
	title->m_Transform.SetPosition(160, 20, 0);
	
	//fpsCounter->RemoveComponent(fpsCounter->GetComponent<Fps>());
	
	if(fpsCounter->HasComponent<TextRenderer>())
		std::cout << "TextRenderer has Fps Component\n";

	scene.Add(std::move(backGround));
	scene.Add(std::move(fpsCounter));
	scene.Add(std::move(daeLogo));
	scene.Add(std::move(title));
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}