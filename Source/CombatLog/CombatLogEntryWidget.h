// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatLogDataTypes.h"
#include "CombatLogEntryWidget.generated.h"


struct FCombatLogEntryData;
class UTextBlock;
class UCombatLogEntryWidget;


DECLARE_MULTICAST_DELEGATE_OneParam(FWidgetAnimationFinishedSignature, UCombatLogEntryWidget&);


UCLASS(Abstract)
class COMBATLOG_API UCombatLogEntryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	FWidgetAnimationFinishedSignature AppearAnimationFinishedDelegate;
	FWidgetAnimationFinishedSignature CollapseAnimationFinishedDelegate;

	virtual void NativeConstruct() override;

	void SetData(const FCombatLogEntryData& LogEntryData);

	UFUNCTION(BlueprintCallable)
	void AnimateAppear();
	UFUNCTION(BlueprintCallable)
	void AnimateCollapse();

	int32 GetEntryId() const { return EntryId; }
	bool IsAnimating() const { return RunningAnimation != nullptr; }
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* PlayerName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* EnemyName;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* AppearAnim;

	UPROPERTY(Transient, meta=(BindWidgetAnim))
	UWidgetAnimation* CollapseAnim;
private:
	int32 EntryId = -1;

	UPROPERTY(Transient)
	UUMGSequencePlayer* RunningAnimation = nullptr;

	void OnAnimationAppearFinished(UUMGSequencePlayer& Player);
	void OnAnimationCollapseFinished(UUMGSequencePlayer& Player);
};
