#pragma once

// TODO: Decide if we should introduce this include here, maybe we can remove the hard dependency on FQuickCommandEntry
#include "QuickMenuDiscoverySubsystem.h"

class SQuickCommandsListView : public SListView<TSharedRef<FQuickCommandEntry>>
{
protected:
	virtual void NotifyItemScrolledIntoView() override;
};
