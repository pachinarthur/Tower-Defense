// Fill out your copyright notice in the Description page of Project Settings.


#include "Checkpoint.h"

// Sets default values
ACheckpoint::ACheckpoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	billboard = CreateDefaultSubobject<UBillboardComponent>("Billboard");
	billboard->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Debug();
}

void ACheckpoint::Debug()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), 15, 10, FColor::Black, false, -1, 0, 2);
}