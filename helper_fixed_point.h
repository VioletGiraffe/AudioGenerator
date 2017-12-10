#pragma once

#include <stdint.h>

namespace detail {

template <typename T>
struct expand_type
{};

template<>
struct expand_type<uint8_t>
{
	using type = uint16_t;
};

template<>
struct expand_type<uint16_t>
{
	using type = uint32_t;
};

template<>
struct expand_type<uint32_t>
{
	using type = uint64_t;
};

template<>
struct expand_type<int8_t>
{
	using type = int16_t;
};

template<>
struct expand_type<int16_t>
{
	using type = int32_t;
};

template<>
struct expand_type<int32_t>
{
	using type = int64_t;
};

}