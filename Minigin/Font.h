#ifndef FONT_H
#define FONT_H
#include <string>

struct _TTF_Font;
/**
 * Simple RAII wrapper for a _TTF_Font
 */
class Font final
{
public:
	_TTF_Font* GetFont() const;
	explicit Font(const std::string& fullPath, int size);
	~Font();

	Font(const Font&) = delete;
	Font(Font&&) = delete;
	Font& operator= (const Font&) = delete;
	Font& operator= (const Font&&) = delete;
private:
	_TTF_Font* m_font;
};
#endif // !FONT_H


