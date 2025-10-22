// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class MIGAMEJAM_API UDialogueWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void SetDialogueText(const FString& Dialogue, const FString& SpeakerName = "Unknown");
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextSpeaker;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TextDialogue;

	
	
};
