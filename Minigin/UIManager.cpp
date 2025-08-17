#include "UIManager.h"
#include <vector>
#include "UI.h"

namespace UIManager
{
	std::vector<std::unique_ptr<UI>> UIS{};

	UI* ActiveUI{ nullptr };

	UI* GetActiveUI()
	{
		return ActiveUI;
	}

	UI* GetUI(size_t id)
	{
		return UIS[id].get();
	}

	size_t CreateUI()
	{
		UIS.push_back(std::make_unique<UI>());
		return UIS.size() - 1;
	}

	void SetActiveUI(size_t id)
	{
		ActiveUI = UIS[id].get();
	}
	void DisableUI()
	{
		ActiveUI = nullptr;
	}
}

