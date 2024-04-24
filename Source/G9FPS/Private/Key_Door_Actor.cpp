// Fill out your copyright notice in the Description page of Project Settings.


#include "Key_Door_Actor.h"

#include "EngineUtils.h"

// Sets default values
AKey_Door_Actor::AKey_Door_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorFrame);
}

// Called when the game starts or when spawned
void AKey_Door_Actor::BeginPlay()
{
	Super::BeginPlay();
	
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &AKey_Door_Actor::OpenDoor);
		Timeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}
}

// Called every frame
void AKey_Door_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

//Interaction with the door
void AKey_Door_Actor::Interact_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("Interacted with Door"));
	if (!Locked)
	{
		if (bIsDoorClosed)
		{
			Timeline.Play();
			//UE_LOG(LogTemp, Display, TEXT("Door opened"))
		}
		else
		{
			Timeline.Reverse();
		}
		bIsDoorClosed = !bIsDoorClosed;
	}
}

//Unlocking the door
void AKey_Door_Actor::Unlock_Implementation(float Value)
{
	if (Value == DoorCode)
	{
		Locked = false;
	}
}

void AKey_Door_Actor::OpenDoor(float Value)
{
	FVector Loc = FVector(0.f, DoorMoveDistance * Value, 0.f);

	Door->SetRelativeLocation(Loc);

}