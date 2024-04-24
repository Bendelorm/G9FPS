// Fill out your copyright notice in the Description page of Project Settings.


#include "Key_Actor.h"
#include "Key_Door_Actor.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKey_Actor::AKey_Actor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Key = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Key"));

}

//Interacting with key
void AKey_Actor::Interact_Implementation()
{

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), KeyDoor, FoundActors);

	for (int i = 0; i < FoundActors.Num(); i++)
	{
		IFPS_Interact::Execute_Unlock(FoundActors[i], KeyCode);
		//UE_LOG(LogTemp, Display, TEXT("Found a door"));
	}
	Destroy();
}



// Called when the game starts or when spawned
void AKey_Actor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AKey_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

