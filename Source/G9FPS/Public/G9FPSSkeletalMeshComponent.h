// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Carly.h"
#include "Components/SkeletalMeshComponent.h"
#include "G9FPSSkeletalMeshComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, meta = (BlueprintSpawnableComponent))
class G9FPS_API UG9FPSSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	UG9FPSSkeletalMeshComponent();

	ACarly* Character;

	UFUNCTION(Blueprintable, BlueprintCallable, Category = "Object")
	void AttachComponentToPlayer(ACarly* TargetCharacter);

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponSettings")
	FVector GuntipOffset;


	// IMC and actions for gun

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* FireIMC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ReloadAction;

	UFUNCTION(BlueprintCallable, Category = "Input")
	void Fire();

	void Reload();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float AmmoCount = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	float MaxAmmo = 6;

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	float GetAmmoCount();

	UFUNCTION(BlueprintCallable, Category = "Ammo")
	float GetMaxAmmo();

	//Animation and sound for gun

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation and Sound")
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation and Sound")
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation and Sound")
	UAnimMontage* ReloadAnimation;


	//Projectile
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<AActor> ProjectileToSpawn;
};
