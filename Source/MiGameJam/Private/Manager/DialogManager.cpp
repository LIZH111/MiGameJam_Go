// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/DialogManager.h"

#include "ExplorerDummies/ExplorerNPC.h"
#include"UI/DialogueWidget.h"
#include"Data/DialogueData.h"

// Sets default values
ADialogManager::ADialogManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CurrentDialogueIndex = 0;
	bIsInDialogue = false;

}

// Called when the game starts or when spawned
void ADialogManager::BeginPlay()
{
	Super::BeginPlay();

	// 创建对话UI
	
	// 创建对话UI
	if (DialogueWidgetClass)
	{
		DialogueWidget = CreateWidget<UDialogueWidget>(GetWorld(), DialogueWidgetClass);
		if (DialogueWidget)
		{
			DialogueWidget->AddToViewport();
			DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
	
}



void ADialogManager::StartDialogue(class UDialogueData* DialogueData)
{
	if (!DialogueData || !DialogueWidget) return;

	CurrentDialogueData = DialogueData;
	CurrentDialogueIndex = 0;
	bIsInDialogue = true;

	// 显示UI
	DialogueWidget->SetVisibility(ESlateVisibility::Visible);
    
	// 显示第一句对话
	DisplayNextDialogueLine();
	
}

void ADialogManager::DisplayNextDialogueLine()
{
	if (!CurrentDialogueData || !DialogueWidget) return;

	if (CurrentDialogueIndex < CurrentDialogueData->DialogueLines.Num())
	{
		// 显示当前对话
		FString DialogueLine = CurrentDialogueData->DialogueLines[CurrentDialogueIndex];
		DialogueWidget->SetDialogueText(DialogueLine, CurrentDialogueData->SpeakerName);
		CurrentDialogueIndex++;
	}
	else
	{
		// 对话结束
		EndDialogue();
	}
	
}

void ADialogManager::EndDialogue()
{
	bIsInDialogue = false;
	CurrentDialogueData = nullptr;
	CurrentDialogueIndex = 0;

	if (DialogueWidget)
	{
		DialogueWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}




