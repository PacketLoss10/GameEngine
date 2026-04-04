#pragma once

#include <type_traits>
#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
#include <functional>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#include <ws2tcpip.h>

using ByteBuffer = std::vector<char>;

class ByteArray
{
private:
	ByteBuffer buffer;
	size_t cursor = 0;

	template<typename T>
	T endianness_check(T val)
	{
		if constexpr (sizeof(T) == 2)
			return ntohs(val);
		else if constexpr (sizeof(T) == 4)
			return ntohl(val);
		else if constexpr (sizeof(T) == 8)
		{
			uint64_t tmp;
			std::memcpy(&tmp, &val, 8);
			tmp = ((tmp & 0x00000000000000FFULL) << 56) |
				((tmp & 0x000000000000FF00ULL) << 40) |
				((tmp & 0x0000000000FF0000ULL) << 24) |
				((tmp & 0x00000000FF000000ULL) << 8) |
				((tmp & 0x000000FF00000000ULL) >> 8) |
				((tmp & 0x0000FF0000000000ULL) >> 24) |
				((tmp & 0x00FF000000000000ULL) >> 40) |
				((tmp & 0xFF00000000000000ULL) >> 56);
			std::memcpy(&val, &tmp, 8);
			return val;
		}
		return val;
	}
public:
	ByteArray() = default;
	ByteArray(const ByteBuffer& buffer) :buffer(buffer) {}

	const char* data() const { return buffer.data(); }
	size_t size() const { return buffer.size(); }

	void reset()
	{
		cursor = 0;
		buffer.clear();
	}
	void reset_read()
	{
		cursor = 0;
	}

	template<typename T>
	void put(const T& val)
	{
		const char* ptr = reinterpret_cast<const char*>(&val);
		buffer.insert(buffer.end(), ptr, ptr + sizeof(T));
	}

	template<typename T>
	void put(const T* val, size_t count)
	{
		const char* ptr = reinterpret_cast<const char*>(val);
		buffer.insert(buffer.end(), ptr, ptr + sizeof(T) * count);
	}

	template<typename T>
	T get()
	{
		if (cursor + sizeof(T) > buffer.size())
		{
			throw std::runtime_error("ByteArray read overflow");
		}

		T val;
		std::memcpy(&val, buffer.data() + cursor, sizeof(T));
		cursor += sizeof(T);

		return endianness_check(val);
	}

	template<typename T>
	const T* get(size_t count)
	{
		size_t size = sizeof(T) * count;
		if (cursor + size > buffer.size())
		{
			throw std::runtime_error("ByteArray read overflow");
		}

		const T* ptr = reinterpret_cast<const T*>(buffer.data() + cursor);
		cursor += size;
		
		return ptr;
	}
};