// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DialogueData.generated.h"

/**
 * 
 */
UCLASS()
class MIGAMEJAM_API UDialogueData : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	TArray<FString> DialogueLines;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString SpeakerName;
	
};
