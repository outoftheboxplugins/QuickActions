#include "SQuickCommandsListView.h"

void SQuickCommandsListView::NotifyItemScrolledIntoView()
{
	// We want to avoid focusing the widget we scrolled to, because the search bar should keep the focus at all times.
	bNavigateOnScrollIntoView = false;

	SListView::NotifyItemScrolledIntoView();
}
