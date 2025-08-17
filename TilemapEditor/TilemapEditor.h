#ifndef TILEMAP_EDITOR_H
#define TILEMAP_EDITOR_H
class TextureRenderer;
namespace TilemapEditor
{
	void OnTilemapButtonPress(int index);

	void AddTextureRenderer(TextureRenderer* renderer, int index);

	void Savemap();
	void Loadmap();
}
#endif //TILEMAP_EDITOR_H


