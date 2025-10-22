// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerDummies/ExplorerNPC.h"
#include "Data/DialogueData.h"
#include "Manager/DialogManager.h"
#include"Utilities/CF_Mi.h"

// Sets default values
AExplorerNPC::AExplorerNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(RootComponent);

	bCanInteract = true;
	InteractText = FText::FromString("Press Left Mouse to Interact");

}

// Called when the game starts or when spawned
void AExplorerNPC::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called to bind functionality to input
void AExplorerNPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AExplorerNPC::EnterDialogueThroughDM(AExplorerNPC* NPC)
{
	//将敌人参考，玩家队伍管理器参考都传入战斗管理器
	ADialogManager* BMRef = UCF_Mi::Flib_GetDM();

	if (BMRef == nullptr) return;
	if (BMRef->bIsInDialogue)
	{
		// 在对话中，显示下一句
		BMRef->DisplayNextDialogueLine();
	}
	else
	{
		BMRef->StartDialogue(NPC->DialogueData);
	}
	
	
}

