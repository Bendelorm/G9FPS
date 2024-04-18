// Fill out your copyright notice in the Description page of Project Settings.


#include "Door_Actor.h"

#include "EngineUtils.h"

// Sets default values
ADoor_Actor::ADoor_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorFrame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrame"));
	DoorFrame->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(DoorFrame);
}

// Called when the game starts or when spawned
void ADoor_Actor::BeginPlay()
{
	Super::BeginPlay();

	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ADoor_Actor::OpenDoor);
		Timeline.AddInterpFloat(CurveFloat, TimelineProgress);

	}

	
}


// Called every frame
void ADoor_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);

}

void ADoor_Actor::Interact_Implementation()
{
	UE_LOG(LogTemp, Display, TEXT("Interacted with Door"));

	if (bIsDoorClosed)
	{
		Timeline.Play();
		UE_LOG(LogTemp, Display, TEXT("Door opened"))
	}
	else
	{
		Timeline.Reverse();
	}
	bIsDoorClosed = !bIsDoorClosed;
}

void ADoor_Actor::OpenDoor(float Value)
{
	FVector Loc = FVector(0.f, DoorMoveDistance*Value, 0.f);

	Door->SetRelativeLocation(Loc);

}