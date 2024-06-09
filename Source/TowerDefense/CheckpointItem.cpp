// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckpointItem.h"

// Sets default values
ACheckpointItem::ACheckpointItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACheckpointItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpointItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Debug();

}

void ACheckpointItem::Debug()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), 15, 10, debugColor, false, -1, 0, 2);
}

