// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVerticalBox.h"

#include "MyVerticalBoxSlot.h"
#include "Components/VerticalBoxSlot.h"

UMyVerticalBoxSlot* UMyVerticalBox::AddChildAt(int32 Index, UWidget* Content)
{
	if(!Content)
	{
		return nullptr;
	}

	if ( !bCanHaveMultipleChildren && GetChildrenCount() > 0 )
	{
		return nullptr;
	}

	if (Index < 0 && Index > GetChildrenCount())
	{
		return nullptr;
	}

	Content->RemoveFromParent();

	EObjectFlags NewObjectFlags = RF_Transactional;
	if (HasAnyFlags(RF_Transient))
	{
		NewObjectFlags |= RF_Transient;
	}

	UPanelSlot* PanelSlot = NewObject<UPanelSlot>(this, GetSlotClass(), NAME_None, NewObjectFlags);
	PanelSlot->Content = Content;
	PanelSlot->Parent = this;

	Content->Slot = PanelSlot;

	Slots.Insert(PanelSlot, Index);

	OnSlotInserted(Index, PanelSlot);

	InvalidateLayoutAndVolatility();

	return Cast<UMyVerticalBoxSlot>(PanelSlot);
}

UClass* UMyVerticalBox::GetSlotClass() const
{
	return UMyVerticalBoxSlot::StaticClass();
}

void UMyVerticalBox::OnSlotAdded(UPanelSlot* InSlot)
{
	// Add the child to the live canvas if it already exists
	if ( MyVerticalBox.IsValid() )
	{
		CastChecked<UMyVerticalBoxSlot>(InSlot)->BuildSlot(MyVerticalBox.ToSharedRef());
	}
}

TSharedRef<SWidget> UMyVerticalBox::RebuildWidget()
{
	MyVerticalBox = SNew(SVerticalBox);

	for ( UPanelSlot* PanelSlot : Slots )
	{
		if ( UMyVerticalBoxSlot* TypedSlot = Cast<UMyVerticalBoxSlot>(PanelSlot) )
		{
			TypedSlot->Parent = this;
			TypedSlot->BuildSlot(MyVerticalBox.ToSharedRef());
		}
	}

	return MyVerticalBox.ToSharedRef();
}


void UMyVerticalBox::OnSlotInserted(int32 Index, UPanelSlot* InSlot)
{
	if ( MyVerticalBox.IsValid() )
	{
		CastChecked<UMyVerticalBoxSlot>(InSlot)->BuildSlotAt(Index, MyVerticalBox.ToSharedRef());
	}

}
