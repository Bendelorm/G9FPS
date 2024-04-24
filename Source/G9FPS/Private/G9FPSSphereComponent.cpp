// Fill out your copyright notice in the Description page of Project Settings.


#include "G9FPSSphereComponent.h"

#include "Kismet/GameplayStatics.h"

UG9FPSSphereComponent::UG9FPSSphereComponent()
{
	SphereRadius = 30.f;
}

void UG9FPSSphereComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UG9FPSSphereComponent::OnSphereBeginOverlap);
}

void UG9FPSSphereComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACarly* Character = Cast<ACarly>(OtherActor);
	if (Character != nullptr)
	{
		OnPickUp.Broadcast(Character);
		OnComponentBeginOverlap.RemoveAll(this);
	}
}