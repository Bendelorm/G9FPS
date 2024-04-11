// Fill out your copyright notice in the Description page of Project Settings.


#include "Door_Actor.h"

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

	
}

// Called every frame
void ADoor_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADoor_Actor::OnInteract()
{
	UE_LOG(LogTemp, Display, TEXT("Interacted with Door"));

}