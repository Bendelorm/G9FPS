// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "FPS_Interact.h"
#include "Key_Door_Actor.generated.h"

UCLASS()
class G9FPS_API AKey_Door_Actor : public AActor, public IFPS_Interact
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKey_Door_Actor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact_Implementation() override;

	virtual void Unlock_Implementation(float Value) override;



private:

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* DoorFrame;
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	UStaticMeshComponent* Door;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimeline Timeline;
	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;

	bool bIsDoorClosed = true;

	UPROPERTY(EditAnywhere)
	float DoorMoveDistance = 10.f;

	UFUNCTION()
	void OpenDoor(float Value);

	UPROPERTY(EditAnywhere)
	bool Locked = true; 

	UPROPERTY(EditAnywhere)
	float DoorCode;


};
