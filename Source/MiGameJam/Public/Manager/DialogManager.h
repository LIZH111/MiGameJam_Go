// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DialogManager.generated.h"
class AExplorerNPC;
class UDialogueWidget;
class UDialogueData;


UCLASS()
class MIGAMEJAM_API ADialogManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADialogManager();
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Dialog")
	UDialogueWidget* DialogueWidget;
	
	// 添加 DialogueWidgetClass 声明
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDialogueWidget> DialogueWidgetClass;

	bool bIsInDialogue;
	
private:
	UPROPERTY()
	UDialogueData* CurrentDialogueData;

	int32 CurrentDialogueIndex;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	// 对话系统
	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void StartDialogue(class UDialogueData* DialogueData);

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void DisplayNextDialogueLine();

	UFUNCTION(BlueprintCallable, Category = "Dialogue")
	void EndDialogue();


};
