// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Manager/DialogManager.h"
#include "CF_Mi.generated.h"

class ADialogManager;
/**
 * 
 */
UCLASS()
class MIGAMEJAM_API UCF_Mi : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static ADialogManager* Flib_GetDM();
	
};
