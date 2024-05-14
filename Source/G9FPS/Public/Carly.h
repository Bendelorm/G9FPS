// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
#include "G9FPSCameraActor.h"
#include "GameFramework/Character.h"
#include "Carly.generated.h"

struct FInputActionValue;
class UCameraComponent;
class UInputComponent;
class UInputAction;
class UInputMappingContext;

UCLASS()
class G9FPS_API ACarly : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACarly();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//Components

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCameraComponent* FPVCameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* SKFPV;

	//Input Mapping Context and Actions

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputMappingContext* IMC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* CameraSwitchAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	UInputAction* DefaultCameraAction;

	void CameraSwitch(const FInputActionValue& Value);

	void DefaultCamera(const FInputActionValue& Value);

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);


	//Camera System
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ACameraActor> Cameras;

	//Variable for Camera Number
	int32 CameraNumber = 0;

	//Bool to hide player from cameras
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsSecondaryCameraActive;

	//Function for hiding/showing player
	void HidePlayer();

	//Interact System
	UFUNCTION(BlueprintCallable, Category = "Interact")
	void InteractWithObject();

	UPROPERTY(EditAnywhere)
	float InteractLineTraceLength = 350.f;

	//Weapon System
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	bool bHasWeapon = false;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetHasWeapon(bool bHasNewWeapon);

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetHasWeapon();

	USkeletalMeshComponent* GetSKFPV() const;

	UCameraComponent* GetFPVCameraComponent() const;

	//Damage and HP

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health = 60.f;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	)override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth = 60.f;

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
