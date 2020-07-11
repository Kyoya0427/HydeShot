//======================================================
// File Name	: Utilities.h
// Summary		: ï÷óòä÷êî
// Date			: 2020/5/12
// Author		: Kyoya  Sakamoto
//======================================================
#pragma once

#include <algorithm>

template<class T>
inline constexpr const T& Clamp(const T& v, const T& low, const T& high)
{
	return std::min(std::max(v, low), high);
}

