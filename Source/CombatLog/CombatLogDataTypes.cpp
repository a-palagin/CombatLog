#include "CombatLogDataTypes.h"


int32 FCombatLogEntryData::_Id = 0;


FCombatLogEntryData::FCombatLogEntryData(): Id(++_Id), Type(ECombatLogEntryType::None)
{
	UE_LOG(LogTemp, Warning, TEXT("Default ctor: %s"), *ToString());
}


FCombatLogEntryData::FCombatLogEntryData(ECombatLogEntryType Type, const FString& PlayerName, const FString& EnemyName):
	Id(++_Id),
	Type(Type),
	PlayerName(PlayerName),
	EnemyName(EnemyName)
{
}


FString FCombatLogEntryData::ToString() const
{
	return FString::Printf(TEXT("%i: [%s] %s->%s"), Id, *StaticEnum<ECombatLogEntryType>()->GetValueAsString(Type), *PlayerName, *EnemyName);
}


bool FCombatLogEntryData::operator < (const FCombatLogEntryData& Rhs) const
{
	return PlayerName + EnemyName < Rhs.PlayerName + Rhs.EnemyName;
}

bool FCombatLogEntryData::operator==(const FCombatLogEntryData& Rhs) const
{
	return Id == Rhs.Id;
}
