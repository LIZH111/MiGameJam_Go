// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplorerDummies/ExplorerPlayer.h"

#include "PlayerController/MiPlayerController.h"
#include"EnhancedInputComponent.h"
#include"EnhancedInputSubsystems.h"
#include"GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ExplorerDummies/ExplorerNPC.h"
#include"Manager/DialogManager.h"
#include "Utilities/CF_Mi.h"

// Sets default values
AExplorerPlayer::AExplorerPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 350.0F;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom,USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;

}

// Called when the game starts or when spawned
void AExplorerPlayer::BeginPlay()
{
	Super::BeginPlay();
	//获取PC
	PC =Cast<AMiPlayerController>(Controller);
	if (PC == nullptr) return;
	//将控制焦点聚集在游戏中（不要初始游戏时点一次窗口）
	PC->SetInputMode(FInputModeGameOnly());
	//初始化增强型输入系统
	UEnhancedInputLocalPlayerSubsystem* Subsystem
		=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer());
	if(Subsystem==nullptr) return;
	Subsystem->AddMappingContext(IMC_SR,0);
	//获取DM
	GetDM();
}

void AExplorerPlayer::Move_Triggered(const FInputActionValue& val)
{
	if (!bTalk && !bATK)
	{
		//按下方向键触发
		//按Vector2D解析传入的形参
		const FVector2D InputVector =val.Get<FVector2D>();
		float vel_x = InputVector.X;
		float vel_y = InputVector.Y;

		if (PC==nullptr) return;
		//关注水平方向Yaw，点头Pitch摇头Yaw
		const FRotator GroundRotation(0,PC->GetControlRotation().Yaw,0);

		//左右
		const FVector RightDir = FRotationMatrix(GroundRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(RightDir,vel_x);

		//前后
		const FVector ForwardDir = FRotationMatrix(GroundRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(ForwardDir,vel_y);
	}
}

void AExplorerPlayer::Move_Completed(const FInputActionValue& val)
{
	
}

void AExplorerPlayer::Look_Triggered(const FInputActionValue& val)
{
	if (!bTalk && !bATK)
	{
		const FVector2d LookVal =val.Get<FVector2D>();
		if (PC==nullptr) return;

		AddControllerYawInput(LookVal.X);
		AddControllerPitchInput(LookVal.Y);
	}
	
}


void AExplorerPlayer::TryDialog_Started(const FInputActionValue& val)
{
	//检查是否允许对话（未对话，未攻击状态）
	if (!bATK)
	{
		//生成对话UI和文字
		MeleeDetectDialog();
		//判断角色是否在说话来判断移动
		if (DM->bIsInDialogue) bTalk = true;
		else bTalk = false;
		//播放UI动画

		//播放对应的文字
	}
	
}
void AExplorerPlayer::MeleeDetectDialog()
{
	//近战攻击逻辑
	//以角色前方150cm处为球心，生成半径是150cm的球体
	
	TArray<FHitResult> OutRes;
	FVector Start =GetActorLocation()+GetActorForwardVector()*150.0f;
	FCollisionObjectQueryParams ObjectQueryParams;
	ObjectQueryParams.AddObjectTypesToQuery(ECC_Pawn);
	FCollisionShape MySphere =FCollisionShape::MakeSphere(150.f);
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);//忽略自身
	
	
	GetWorld()->SweepMultiByObjectType(OutRes,Start,Start,FQuat(0,0,0,0),ObjectQueryParams,MySphere,Params);

	//显示测试球体
	DrawDebugSphere(GetWorld(),Start,150.0f,12,FColor::White,false,5.0f,0.0f,4.0f);
	//若球体碰到敌人ExplorerEnymies,则立刻进入战斗
	for (auto Elem : OutRes)
	{
		AActor* DetectedActor = Cast<AExplorerNPC>(Elem.GetActor());
		if (DetectedActor != nullptr)
		{
			
			//碎屏效果
			//此处方便测试 直接进入战斗
			FindNPCInfo(DetectedActor);

			
			return;
		}
	}
	
	
	
}

void AExplorerPlayer::FindNPCInfo(AActor* NPC)
{
	AExplorerNPC* hitTarget =Cast<AExplorerNPC>(NPC);
	if (hitTarget == nullptr) return;

	//进入探索状态的敌人类中获取敌人的队伍信息
	hitTarget->EnterDialogueThroughDM(hitTarget);
}

void AExplorerPlayer::GetDM()
{
	DM =UCF_Mi::Flib_GetDM();
}

// Called to bind functionality to input
void AExplorerPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EIComp = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (EIComp == nullptr) return;

	EIComp->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AExplorerPlayer::Move_Triggered);
	EIComp->BindAction(MoveAction,ETriggerEvent::Completed,this,&AExplorerPlayer::Move_Completed);
	EIComp->BindAction(LookAction,ETriggerEvent::Triggered,this,&AExplorerPlayer::Look_Triggered);

	EIComp->BindAction(TryAttackingAction,ETriggerEvent::Started,this,&AExplorerPlayer::TryDialog_Started);

}


