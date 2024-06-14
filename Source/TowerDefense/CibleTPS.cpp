// Fill out your copyright notice in the Description page of Project Settings.


#include "CibleTPS.h"

// Sets default values
ACibleTPS::ACibleTPS()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACibleTPS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACibleTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACibleTPS::Death()
{
	Destroy();
}