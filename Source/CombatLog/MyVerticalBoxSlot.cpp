// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVerticalBoxSlot.h"

#include "Components/Widget.h"


UMyVerticalBoxSlot::UMyVerticalBoxSlot()
	: Slot(nullptr)
{
	HorizontalAlignment = HAlign_Fill;
	VerticalAlignment = VAlign_Fill;
	Size = FSlateChildSize(ESlateSizeRule::Automatic);
}

void UMyVerticalBoxSlot::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	Slot = nullptr;
}

void UMyVerticalBoxSlot::BuildSlot(TSharedRef<SVerticalBox> VerticalBox)
{
	Slot = &VerticalBox->AddSlot()
		.Padding(Padding)
		.HAlign(HorizontalAlignment)
		.VAlign(VerticalAlignment)
		[
			Content == nullptr ? SNullWidget::NullWidget : Content->TakeWidget()
		];

	Slot->SizeParam = UWidget::ConvertSerializedSizeParamToRuntime(Size);
}

void UMyVerticalBoxSlot::SetPadding(FMargin InPadding)
{
	Padding = InPadding;
	if ( Slot )
	{
		Slot->Padding(InPadding);
	}
}

void UMyVerticalBoxSlot::SetSize(FSlateChildSize InSize)
{
	Size = InSize;
	if ( Slot )
	{
		Slot->SizeParam = UWidget::ConvertSerializedSizeParamToRuntime(InSize);
	}
}

void UMyVerticalBoxSlot::SetHorizontalAlignment(EHorizontalAlignment InHorizontalAlignment)
{
	HorizontalAlignment = InHorizontalAlignment;
	if ( Slot )
	{
		Slot->HAlign(InHorizontalAlignment);
	}
}

void UMyVerticalBoxSlot::SetVerticalAlignment(EVerticalAlignment InVerticalAlignment)
{
	VerticalAlignment = InVerticalAlignment;
	if ( Slot )
	{
		Slot->VAlign(InVerticalAlignment);
	}
}

void UMyVerticalBoxSlot::SynchronizeProperties()
{
	SetPadding(Padding);
	SetSize(Size);
	SetHorizontalAlignment(HorizontalAlignment);
	SetVerticalAlignment(VerticalAlignment);
}


void UMyVerticalBoxSlot::BuildSlotAt(int32 Index, TSharedRef<SVerticalBox> VerticalBox)
{
	Slot = &VerticalBox->InsertSlot(Index)
		.Padding(Padding)
		.HAlign(HorizontalAlignment)
		.VAlign(VerticalAlignment)
		[
			Content == nullptr ? SNullWidget::NullWidget : Content->TakeWidget()
		];

	Slot->SizeParam = UWidget::ConvertSerializedSizeParamToRuntime(Size);
}
