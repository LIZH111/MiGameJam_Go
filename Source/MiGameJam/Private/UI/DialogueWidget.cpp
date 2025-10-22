// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DialogueWidget.h"

#include "Components/TextBlock.h"

void UDialogueWidget::SetDialogueText(const FString& Dialogue, const FString& SpeakerName)
{
	if (TextSpeaker)
	{
		TextSpeaker->SetText(FText::FromString(SpeakerName + ":"));
	}

	if (TextDialogue)
	{
		TextDialogue->SetText(FText::FromString(Dialogue));
	}


}