#include "CVARs.h"

// CVAR implementation from github.com/vblanco20-1

namespace ag
{
	class CVARSystem : public CVARs
	{

	};

	enum class CVARType : char
	{
		Bool,
		Int,
		Float,
		String
	};

	class CVAR
	{
	public:
		friend class CVARSystem;
		
		int32_t arrIndex;

		CVARType type;
		CVARFlags flags;
		std::string name;
		std::string desc;
	};

	template<typename T>
	struct CVARStorage
	{
		T initial;
		T current;
		CVAR* var;
	};

	template<typename T>
	struct CVARArray
	{
		CVARStorage<T>* vars;
		int32_t last{ 0 };

		CVARArray(size_t size)
		{
			vars = new CVARStorage<t>[size]();
		}

		~CVARArray()
		{
			delete vars;
		}

		T GetValue(int32_t index)
		{
			return vars[index].current;
		}
		void SetValue(const T& val, int32_t index)
		{
			vars[index].current = val;
		}

		int Add(const& val, CVAR* var)
		{
			int index = last;
			vars[index].current = value;
			vars[index].initial = value;
			vars[index].var = var;

			var->arrIndex = index;
			last++;
			return index;
		}
	};
}

ag::CVARs* ag::CVARs::Get()
{
	static CVARSystem cv{};
	return &cv;
}