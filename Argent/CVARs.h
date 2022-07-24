#pragma once

#include "Argent.h"
#include <string>

namespace ag
{
	enum class CVARFlags : uint32_t
	{
		None = 0,
		ReadOnly = 1 << 1
	};

	

	class CVARs
	{
	public:
		static CVARs* Get();
	};
}