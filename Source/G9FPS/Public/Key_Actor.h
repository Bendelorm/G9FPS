// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPS_Interact.h"
#include "Key_Actor.generated.h"

UCLASS()
class G9FPS_API AKey_Actor : public AActor, public IFPS_Interact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKey_Actor();

	virtual void Interact_Implementation() override;

	UPROPERTY(EditAnywhere)
	float KeyCode;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* Key;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AActor> KeyDoor;

};
