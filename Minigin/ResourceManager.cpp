#include <stdexcept>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include <iostream>

namespace ResourceManager
{
	static std::filesystem::path DataPath{};
	static std::map<std::string, std::unique_ptr<Texture2D>> LoadedTextures{};
	static std::map<std::pair<std::string, uint8_t>, std::unique_ptr<Font>> LoadedFonts{};
	void Initiliaze(const std::filesystem::path& data)
	{
		DataPath = data;

		LoadTexture("Error.png");

		if (TTF_Init() != 0)
		{
			throw std::runtime_error(std::string("Failed to load support for fonts: ") + SDL_GetError());
		}
	}

	std::filesystem::path GetDataPath()
	{
		return DataPath;
	}

	Texture2D* LoadTexture(const std::string& file)
	{
		const auto fullPath = DataPath / file;
		const auto filename = std::filesystem::path(fullPath).filename().string();
		if (LoadedTextures.find(filename) == LoadedTextures.end())
		{
			try
			{
				LoadedTextures.insert(std::pair(filename, std::make_unique<Texture2D>(fullPath.string())));
			}
			catch (std::runtime_error err)
			{
				std::cout << err.what();
				return LoadedTextures.at("Error.png").get();
			}
		}

		return LoadedTextures.at(filename).get();
	}

	Font* LoadFont(const std::string& file, uint8_t size)
	{
		const auto fullPath = DataPath/file;
		const auto filename = std::filesystem::path(fullPath).filename().string();
		const auto key = std::pair<std::string, uint8_t>(filename, size);
		if(LoadedFonts.find(key) == LoadedFonts.end())
			LoadedFonts.insert(std::pair(key,std::make_unique<Font>(fullPath.string(), size)));
		return LoadedFonts.at(key).get();
	}


}


