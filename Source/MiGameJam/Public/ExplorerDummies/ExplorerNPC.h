// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExplorerNPC.generated.h"

class UDialogueData;
class ADialogManager;
UCLASS()
class MIGAMEJAM_API AExplorerNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExplorerNPC();

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	bool CanInteract() const { return bCanInteract && DialogueData != nullptr; }

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	UDialogueData* GetDialogueData() const { return DialogueData; }

	UFUNCTION(BlueprintCallable, Category = "Interaction")
	FText GetInteractText() const { return InteractText; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void EnterDialogueThroughDM(AExplorerNPC* NPC);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	UDialogueData* DialogueData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	FText InteractText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bCanInteract;

	// 组件
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* MeshComponent;
	
	

	
};
