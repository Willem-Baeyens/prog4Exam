#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <filesystem>
#include <string>
#include <memory>
#include <map>

class Texture2D;
class Font;

namespace ResourceManager
{
	void Initiliaze(const std::filesystem::path& data);

	Texture2D* LoadTexture(const std::string& file);
	Font* LoadFont(const std::string& file, uint8_t size);
}
#endif // !RESOURCEMANAGER_H