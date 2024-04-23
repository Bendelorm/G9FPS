// Fill out your copyright notice in the Description page of Project Settings.


#include "Carly.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPS_Interact.h"
#include "InputAction.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ACarly::ACarly()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Camera Component
	FPVCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	FPVCameraComponent->SetupAttachment(GetCapsuleComponent());
	FPVCameraComponent->bUsePawnControlRotation = true;

	//Skeletal Mesh Component
	SKFPV = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPSMesh"));
	SKFPV->SetupAttachment(FPVCameraComponent);
}

// Called when the game starts or when spawned
void ACarly::BeginPlay()
{
	Super::BeginPlay();

	//Adding Input Mapping System
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(IMC, 0);
		}
	}
}


void ACarly::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.X);
		AddMovementInput(GetActorRightVector(), MovementVector.Y);
	}
}

void ACarly::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

//Global Variable for Camera Number
int32 CameraNumber = 0;

void ACarly::CameraSwitch(const FInputActionValue& Value)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		TArray<AActor*> FoundCameras;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Cameras, FoundCameras);
		if (CameraNumber < FoundCameras.Num())
		{
			PlayerController->SetViewTarget(FoundCameras[CameraNumber]);
			CameraNumber++;
			if (CameraNumber == FoundCameras.Num())
			{
				CameraNumber = 0;
			}
		}
	}
}

void ACarly::DefaultCamera(const FInputActionValue& Value)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (PlayerController)
	{
		PlayerController->SetViewTarget(this);
	}
}

//Interaction
void ACarly::InteractWithObject()
{
	if (FPVCameraComponent == nullptr) return;

	FHitResult HitResult;
	FVector Start = FPVCameraComponent->GetComponentLocation();
	FVector End = Start + FPVCameraComponent->GetForwardVector() * InteractLineTraceLength;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());
		if (HitResult.GetActor()->Implements<UFPS_Interact>())
		{
			IFPS_Interact::Execute_Interact(HitResult.GetActor());
		}
	}

	//HelpFul DeDug    Remember to #include "DrawDebugHelpers.h"
	
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 2.f);
	DrawDebugPoint(GetWorld(), End, 20.f, FColor::Red, false, 2.f);
	DrawDebugPoint(GetWorld(), Start, 20.f, FColor::Red, false, 2.f);
	


}

//Weapon System
void ACarly::SetHasWeapon(bool bHasNewWeapon)
{
	bHasWeapon = bHasNewWeapon;
}

bool ACarly::GetHasWeapon()
{
	return bHasWeapon;
}

USkeletalMeshComponent* ACarly::GetSKFPV() const
{
	return SKFPV;
}

UCameraComponent* ACarly::GetFPVCameraComponent() const
{
	return FPVCameraComponent;
}

// Called every frame
void ACarly::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACarly::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACarly::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACarly::Look);

		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &ACarly::InteractWithObject);

		EnhancedInputComponent->BindAction(CameraSwitchAction, ETriggerEvent::Triggered, this, &ACarly::CameraSwitch);
		EnhancedInputComponent->BindAction(DefaultCameraAction, ETriggerEvent::Triggered, this, &ACarly::DefaultCamera);

	}
}