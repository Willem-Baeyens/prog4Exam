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
#include "Rotator.h"
#include "TrashTheCache.h"


void load()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	Font* LinguaFontPtr = ResourceManager::GetInstance().LoadFont("Lingua.otf", 24);
	auto fpsCounter = std::make_unique<GameObject>();
	
	fpsCounter->AddComponent<TextRenderer>("",LinguaFontPtr);
	fpsCounter->AddComponent<Fps>();
	fpsCounter->SetWorldPosition(0, 20, 0);

	auto backGround = std::make_unique<GameObject>();
	backGround->AddComponent<TextureRenderer>(ResourceManager::GetInstance().LoadTexture("background.tga"));

	auto daeLogo = std::make_unique<GameObject>();
	daeLogo->AddComponent<TextureRenderer>(ResourceManager::GetInstance().LoadTexture("logo.tga"));
	daeLogo->SetWorldPosition(216, 180, 0);
	
	auto title = std::make_unique<GameObject>();
	title->AddComponent<TextRenderer>("Programming 4 Assignment", LinguaFontPtr);
	title->SetWorldPosition(160, 20, 0);

	auto pivot = std::make_unique<GameObject>();
	pivot->SetWorldPosition(300, 400, 0);
	
	auto bubble = std::make_unique<GameObject>();
	bubble->AddComponent<TextureRenderer>(ResourceManager::GetInstance().LoadTexture("bubble.png"));
	bubble->AddComponent<Rotator>(25.f,.66f,pivot.get());

	auto bobble = std::make_unique<GameObject>();
	bobble->AddComponent<TextureRenderer>(ResourceManager::GetInstance().LoadTexture("bobble.png"));
	bobble->AddComponent<Rotator>(25.f, 2.f, bubble.get());

	auto TrashTheCacheObject = std::make_unique<GameObject>();
	TrashTheCacheObject->AddComponent<TrashTheCache>();


	scene.Add(std::move(backGround));
	//scene.Add(std::move(fpsCounter));
	//scene.Add(std::move(daeLogo));
	//scene.Add(std::move(title));
	//scene.Add(std::move(pivot));
	//scene.Add(std::move(bubble));
	//scene.Add(std::move(bobble));
	scene.Add(std::move(TrashTheCacheObject));
}

int main(int, char*[]) {
	Minigin engine("../Data/");
	engine.Run(load);
    return 0;
}