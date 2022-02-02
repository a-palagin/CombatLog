// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatLogDataTypes.generated.h"


UENUM()
enum class ECombatLogEntryType : uint8
{
	None UMETA(Hidden),
	Solder,
	Boss,
};


USTRUCT(BlueprintType)
struct FCombatLogEntryData
{
	GENERATED_BODY()
public:
	FCombatLogEntryData();
	FCombatLogEntryData(ECombatLogEntryType Type, const FString& PlayerName, const FString& EnemyName);
	FString ToString() const;
	bool operator<(const FCombatLogEntryData& Rhs) const;
	bool operator==(const FCombatLogEntryData& Rhs) const;
	int32 Id;
	ECombatLogEntryType Type;
	FString PlayerName;
	FString EnemyName;

private:
	static int32 _Id;
};
