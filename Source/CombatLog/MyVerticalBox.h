// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/VerticalBox.h"
#include "MyVerticalBox.generated.h"


class UMyVerticalBoxSlot;


UCLASS()
class COMBATLOG_API UMyVerticalBox : public UVerticalBox
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category="Widget|Panel")
	UMyVerticalBoxSlot* AddChildAt(int32 Index, UWidget* Content);

	virtual UClass* GetSlotClass() const override;
protected:
	virtual void OnSlotAdded(UPanelSlot* InSlot) override;
	virtual TSharedRef<SWidget> RebuildWidget() override;
	virtual void OnSlotInserted(int32 Index, UPanelSlot* Slot);
};
