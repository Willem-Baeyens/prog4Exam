#ifndef UI_MANAGER_H
#define UI_MANAGER_H
#include <memory>
class UI;
namespace UIManager
{
	[[nodiscard]] UI* GetActiveUI();
	[[nodiscard]] UI* GetUI(size_t index);

	size_t CreateUI();//returns index of UI
	void SetActiveUI(size_t index);
	void DisableUI();
}
#endif //UI_MANAGER_H


