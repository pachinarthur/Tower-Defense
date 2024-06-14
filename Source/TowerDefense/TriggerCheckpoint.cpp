// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerCheckpoint.h"
#include "SpawnedEntity.h"

void ATriggerCheckpoint::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ATriggerCheckpoint::OnOverlapBegin);
}

void ATriggerCheckpoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}




ATriggerCheckpoint::ATriggerCheckpoint()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATriggerCheckpoint::OnOverlapBegin(AActor* _overlapped, AActor* _overlap)
{
	TObjectPtr<ASpawnedEntity> _entity = Cast<ASpawnedEntity>(_overlap);
	if (!_entity)return;
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	_entity->Destroy();
	
}
