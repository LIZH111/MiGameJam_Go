// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilities/CF_Mi.h"
#include"Kismet/GameplayStatics.h"
#include "Manager/DialogManager.h"

ADialogManager* UCF_Mi::Flib_GetDM()
{
	//获取场景中的BattleManager
	AActor* targetRef = UGameplayStatics::GetActorOfClass(GEngine->GameViewport->GetWorld(),ADialogManager::StaticClass());
	ADialogManager* DMRef = Cast<ADialogManager>(targetRef);
	
	return DMRef;
}
