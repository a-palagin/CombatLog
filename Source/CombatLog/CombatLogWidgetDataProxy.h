// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"

#include "CombatLogDataTypes.h"
#include "CombatLogWidgetDataProxy.generated.h"

enum class ECombatLogEntryType : uint8;
struct FCombatLogEntryData;

DECLARE_MULTICAST_DELEGATE_TwoParams(FNewEntryArrivedSignature, const FCombatLogEntryData&, int32 /*entry index*/)
DECLARE_MULTICAST_DELEGATE_OneParam(FEntryExpiredSignature, int32 /*entry ID*/)


UCLASS(BlueprintType)
class COMBATLOG_API UCombatLogWidgetDataProxy : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void StartFlow();

	UFUNCTION(BlueprintCallable)
	void StopFlow();

	UFUNCTION(BlueprintCallable)
	void Burst();

	FNewEntryArrivedSignature NewEntryArrivedDelegate;
	FEntryExpiredSignature EntryExpiredDelegate;

	TArray<FCombatLogEntryData> GenerateCombatLog(int32 Amount) const;

	const TArray<FCombatLogEntryData>& GetCurrentLog() const;
private:
	// current visible combat log
	TArray<FCombatLogEntryData> CurrentLog;
	FTimerHandle FlowHandle;

	void AddEntry(FCombatLogEntryData EntryData);
	void RemoveEntry(int32 EntryId);

	void ProduceFlow();
};
