// Fill out your copyright notice in the Description page of Project Settings.


#include "G9FPSSkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

UG9FPSSkeletalMeshComponent::UG9FPSSkeletalMeshComponent()
{
	GuntipOffset = FVector(100.0f, 0.0f, 10.0f);
}

void UG9FPSSkeletalMeshComponent::AttachComponentToPlayer(ACarly* TargetCharacter)
{
	Character = TargetCharacter;

	if(Character == nullptr || Character->GetHasWeapon())
	{
		return;
	}

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

	AttachToComponent(Character->GetSKFPV(), AttachmentRules, FName(TEXT("AttachSocket")));

	Character->SetHasWeapon(true);

	//Adding IMC to player on weapon pickup
	APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
	if(PlayerController)
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(FireIMC, 1);
		}

		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);

		if(EnhancedInputComponent)
		{
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &UG9FPSSkeletalMeshComponent::Fire);
			EnhancedInputComponent->BindAction(ReloadAction, ETriggerEvent::Triggered, this, &UG9FPSSkeletalMeshComponent::Reload);

		}
	}
}

void UG9FPSSkeletalMeshComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if(Character == nullptr)
	{
		return;
	}
}

void UG9FPSSkeletalMeshComponent::Fire()
{
	if(ProjectileToSpawn != nullptr)
	{
		UWorld* World = GetWorld();
		if(World != nullptr)
		{
			if (AmmoCount > 0 && bIsReloading == false)
			{
				APlayerController* PlayerController = Cast<APlayerController>(Character->GetController());
				FRotator SpawnRotation = PlayerController->PlayerCameraManager->GetCameraRotation();
				FVector SpawnLocation = GetOwner()->GetActorLocation() + SpawnRotation.RotateVector(GuntipOffset);

				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				World->SpawnActor<AActor>(ProjectileToSpawn, SpawnLocation, SpawnRotation, ActorSpawnParams);

				AmmoCount--;
				if(FireSound != nullptr)
				{
					//Shooting sound
					UGameplayStatics::PlaySoundAtLocation(this, FireSound, Character->GetActorLocation());
				}
			}
		}
	}
}


//Function for reloading and playing reload animation
void UG9FPSSkeletalMeshComponent::Reload()
{
	if (ProjectileToSpawn != nullptr)
	{
		UWorld* World = GetWorld();
		if (World != nullptr && bIsReloading == false)
		{
			bIsReloading = true;
			if (ReloadSound != nullptr)
			{
				//Reload sound
				UGameplayStatics::PlaySoundAtLocation(this, ReloadSound, Character->GetActorLocation());
			}
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]() //reload timer
				{
					AmmoCount = 6;
					bIsReloading = false;
				}, 2.3, false);
		}
	}
}

float UG9FPSSkeletalMeshComponent::GetAmmoCount()
{
	return AmmoCount;
}

float UG9FPSSkeletalMeshComponent::GetMaxAmmo()
{
	return MaxAmmo;
}
