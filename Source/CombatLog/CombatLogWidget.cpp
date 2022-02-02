// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatLogWidget.h"

#include "CombatLogEntryWidget.h"
#include "CombatLogWidgetDataProxy.h"
#include "MyVerticalBox.h"
#include "Components/VerticalBox.h"


void UCombatLogWidget::SetDataProxy(UCombatLogWidgetDataProxy* NewDataProxy)
{
	if (DataProxy)
	{
		DataProxy->NewEntryArrivedDelegate.RemoveAll(this);
		DataProxy->EntryExpiredDelegate.RemoveAll(this);
		DataProxy = nullptr;
	}

	// animate disappear for all?
	LogsBox->ClearChildren();

	DataProxy = NewDataProxy;
	DataProxy->NewEntryArrivedDelegate.AddUObject(this, &UCombatLogWidget::OnNewEntryArrived);
	DataProxy->EntryExpiredDelegate.AddUObject(this, &UCombatLogWidget::OnEntryExpired);
}

void UCombatLogWidget::OnNewEntryArrived(const FCombatLogEntryData& EntryData, int32 index)
{
	if (!LogEntryWidgets.Contains(EntryData.Type))
	{
		return;
	}
	auto EntryWidgetClass = LogEntryWidgets[EntryData.Type];
	UCombatLogEntryWidget* Widget = CreateWidget<UCombatLogEntryWidget>(this, EntryWidgetClass);
	Widget->SetData(EntryData);

	LogsBox->AddChildAt(index, Widget);
	Widget->AnimateAppear();
}


void UCombatLogWidget::OnEntryExpired(int32 EntryId)
{
	for (UPanelSlot* EntrySlot : LogsBox->GetSlots())
	{
		UCombatLogEntryWidget* Entry = Cast<UCombatLogEntryWidget>(EntrySlot->Content);
		if (Entry && Entry->GetEntryId() == EntryId)
		{

			Entry->CollapseAnimationFinishedDelegate.AddUObject(this, &UCombatLogWidget::RemoveEntryWidget);
			Entry->AnimateCollapse();
			return;
		}
	}


	//wtf?
	// UPanelSlot* const* EntrySlot = LogsBox->GetSlots().FindByPredicate([EntryId](UPanelSlot* _Slot)
	// {
	// 	return Cast<UCombatLogEntryWidget>(_Slot->Content)->GetEntryId() == EntryId;
	// });
}

void UCombatLogWidget::RemoveEntryWidget(UCombatLogEntryWidget& EntryWidget)
{
	LogsBox->RemoveChild(&EntryWidget);
	// which better ?
	// EntryWidget.RemoveFromParent();
}
