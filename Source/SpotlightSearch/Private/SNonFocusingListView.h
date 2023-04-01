// Copyright Out-of-the-Box Plugins 2018-2023. All Rights Reserved.

#pragma once

/**
 * @brief ListView which does not focus a widget if we are scrolling to.
 */
template <typename ItemType>
class SNonFocusingListView final : public SListView<ItemType>
{
	// Begin SListView interface
	virtual void NotifyItemScrolledIntoView() override
	{
		// We want to avoid focusing the widget we scrolled to, because the search bar should keep the focus at all times.
		this->bNavigateOnScrollIntoView = false;

		SListView<ItemType>::NotifyItemScrolledIntoView();
	}
	// End SListView interface
};
