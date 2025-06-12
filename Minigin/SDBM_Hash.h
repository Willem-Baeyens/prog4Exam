#ifndef SDBM_HASH_H
#define SDBM_HASH_H
#include <cstdint>

static consteval std::uint32_t SDBM_Hash(const char* text)
{
	std::uint32_t hash = 0;
	int c;

	while ((c = *text++))
		hash = c + (hash << 6) + (hash << 16) - hash;

	return hash;
}

#endif // !SDBM_HASH_H

