// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatLogWidgetDataProxy.h"

#include "CombatLogDataTypes.h"

float SolderEntryLifetime = 10.f;
float BossEntryLifetime = 30.f;


void UCombatLogWidgetDataProxy::StartFlow()
{
	StopFlow();
	ProduceFlow();
}

void UCombatLogWidgetDataProxy::StopFlow()
{
	GetWorld()->GetTimerManager().ClearTimer(FlowHandle);
}

void UCombatLogWidgetDataProxy::Burst()
{
	TArray<FCombatLogEntryData> Log = GenerateCombatLog(10);
	for (FCombatLogEntryData& Entry : Log)
	{
		AddEntry(Entry);
	}
}


TArray<FCombatLogEntryData> UCombatLogWidgetDataProxy::GenerateCombatLog(int32 Amount) const
{
	static FString Letters(TEXT("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
	TArray<FCombatLogEntryData> Log;
	// Log.SetNumUninitialized(Amount);
	for (int i = 0; i < Amount; ++i)
	{
		ECombatLogEntryType Type = FMath::RandBool() ? ECombatLogEntryType::Solder : ECombatLogEntryType::Boss;
		FString Player(1, &Letters[FMath::RandRange(0, Letters.Len() - 1)]);
		FString Enemy(1, &Letters[FMath::RandRange(0, Letters.Len() - 1)]);
		Log.Emplace(FCombatLogEntryData(Type, Player, Enemy));
		// Log[i] = FCombatLogEntryData(Type, Player, Enemy);
	}
	return Log;
}

const TArray<FCombatLogEntryData>& UCombatLogWidgetDataProxy::GetCurrentLog() const
{
	return CurrentLog;
}

void UCombatLogWidgetDataProxy::AddEntry(FCombatLogEntryData EntryData)
{
	UE_LOG(LogTemp, Warning, TEXT("Adding entry: %s"), *EntryData.ToString());
	int32 lo, hi, mid;
	lo = 0;
	hi = CurrentLog.Num();
	while (lo < hi)
	{
		mid = (lo + hi) / 2;
		if (CurrentLog[mid] < EntryData)
		{
			lo = mid + 1;
		}
		else
		{
			hi = mid;
		}
	}
	CurrentLog.EmplaceAt(lo, EntryData);
	UWorld* World = GetWorld();
	FTimerHandle Handle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &UCombatLogWidgetDataProxy::RemoveEntry, EntryData.Id);
	float Lifetime = EntryData.Type == ECombatLogEntryType::Solder ? SolderEntryLifetime : BossEntryLifetime;
	World->GetTimerManager().SetTimer(Handle, TimerDelegate, Lifetime, false);
	NewEntryArrivedDelegate.Broadcast(EntryData, lo);
}

void UCombatLogWidgetDataProxy::RemoveEntry(int32 EntryId)
{
	int32 EntryIndex = INDEX_NONE;
	for (int Index = 0; Index < CurrentLog.Num(); ++Index)
	{
		if (CurrentLog[Index].Id == EntryId)
		{
			EntryIndex = Index;
			UE_LOG(LogTemp, Warning, TEXT("Removing: %s at %i"), *CurrentLog[EntryIndex].ToString(), Index);
			CurrentLog.RemoveAt(EntryIndex);
			EntryExpiredDelegate.Broadcast(EntryId);
			return;;
		}
	}
}

void UCombatLogWidgetDataProxy::ProduceFlow()
{
	TArray<FCombatLogEntryData> Entries = GenerateCombatLog(FMath::RandRange(1, 3));
	for (FCombatLogEntryData& Entry : Entries)
	{
		AddEntry(Entry);
	}
	GetWorld()->GetTimerManager().SetTimer(FlowHandle, this, &UCombatLogWidgetDataProxy::ProduceFlow, FMath::RandRange(5, 15));
}
