// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatLogEntryWidget.h"

#include "Animation/UMGSequencePlayer.h"
#include "Components/TextBlock.h"

void UCombatLogEntryWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// SetVisibility(ESlateVisibility::Collapsed);
}

void UCombatLogEntryWidget::SetData(const FCombatLogEntryData& LogEntryData)
{
	PlayerName->SetText(FText::FromString(LogEntryData.PlayerName));
	EnemyName->SetText(FText::FromString(LogEntryData.EnemyName));
	EntryId = LogEntryData.Id;
}

void UCombatLogEntryWidget::AnimateAppear()
{
	// stop current running anim?

	RunningAnimation = PlayAnimation(AppearAnim);
	RunningAnimation->OnSequenceFinishedPlaying().AddUObject(this, &UCombatLogEntryWidget::OnAnimationAppearFinished);
}

void UCombatLogEntryWidget::AnimateCollapse()
{
	// stop current running anim?
	SetVisibility(ESlateVisibility::HitTestInvisible);
	RunningAnimation = PlayAnimation(CollapseAnim);
	RunningAnimation->OnSequenceFinishedPlaying().AddUObject(this, &UCombatLogEntryWidget::OnAnimationCollapseFinished);
}

void UCombatLogEntryWidget::OnAnimationAppearFinished(UUMGSequencePlayer& Player)
{
	RunningAnimation = nullptr;
	AppearAnimationFinishedDelegate.Broadcast(*this);
}

void UCombatLogEntryWidget::OnAnimationCollapseFinished(UUMGSequencePlayer& Player)
{
	SetVisibility(ESlateVisibility::Collapsed);
	RunningAnimation = nullptr;
	CollapseAnimationFinishedDelegate.Broadcast(*this);
}
