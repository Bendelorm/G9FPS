// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "FPS_Interact.h"
#include "Door_Actor.generated.h"

UCLASS()
class G9FPS_API ADoor_Actor : public AActor, public IFPS_Interact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor_Actor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Door;

};
