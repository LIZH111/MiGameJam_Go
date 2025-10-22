// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ExplorerPlayer.generated.h"

class AMiPlayerController;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;
class ADialogManager;



UCLASS()
class MIGAMEJAM_API AExplorerPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExplorerPlayer();

	AMiPlayerController* PC = nullptr;
	ADialogManager* DM = nullptr;

	UPROPERTY(EditAnywhere,Category="Components")
	UCameraComponent* FollowCamera ;

	UPROPERTY(EditAnywhere,Category="Components")
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(EditAnywhere,Category="Input")
	UInputMappingContext* IMC_SR;
	
	bool bATK = false;
	bool bTalk = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

#pragma region InputEvents
	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* MoveAction; 
	
	UFUNCTION()
	void Move_Triggered(const FInputActionValue& val);

	UFUNCTION()
	void Move_Completed(const FInputActionValue& val);

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* LookAction; 
	
	UFUNCTION()
	void Look_Triggered(const FInputActionValue& val);

	UPROPERTY(EditAnywhere,Category="Input")
	UInputAction* TryAttackingAction; 
	
	UFUNCTION()
	void TryDialog_Started(const FInputActionValue& val);

	
#pragma endregion


public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	void MeleeDetectDialog();
	void FindNPCInfo(AActor* NPC);
	void GetDM();

};
