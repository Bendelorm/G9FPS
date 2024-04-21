// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputSubsystemInterface.h"
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

	void CameraSwitch(const FInputActionValue& Value);

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);


	//Camera System
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ACameraActor> Cameras;

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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
