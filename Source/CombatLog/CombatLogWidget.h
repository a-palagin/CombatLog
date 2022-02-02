// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatLogWidget.generated.h"


class UMyVerticalBox;
struct FCombatLogEntryData;
class UCombatLogWidgetDataProxy;
class UCombatLogEntryWidget;
enum class ECombatLogEntryType : uint8;


UCLASS()
class COMBATLOG_API UCombatLogWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetDataProxy(UCombatLogWidgetDataProxy* NewDataProxy);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMyVerticalBox* LogsBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<ECombatLogEntryType, TSubclassOf<UCombatLogEntryWidget>> LogEntryWidgets;

private:
	UPROPERTY(Transient)
	UCombatLogWidgetDataProxy* DataProxy = nullptr;

	void OnNewEntryArrived(const FCombatLogEntryData& EntryData, int32 index);
	void OnEntryExpired(int32 EntryId);
	void RemoveEntryWidget(UCombatLogEntryWidget& EntryWidget);
};
