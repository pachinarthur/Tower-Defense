// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

// Sets default values
ATower::ATower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	attack = CreateDefaultSubobject<UAttackComponent>("Attack");
	detection = CreateDefaultSubobject<UDetectionComponent>("Detection");
	mesh->SetupAttachment(RootComponent);
	AddOwnedComponent(attack);
	AddOwnedComponent(detection);
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
	detection->OnFirstTargetFound().AddDynamic(attack, &UAttackComponent::SetTarget);
}

// Called every frame
void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

