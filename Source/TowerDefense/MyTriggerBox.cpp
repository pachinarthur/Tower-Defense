// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTriggerBox.h"
#include "SpawnedEntity.h"

AMyTriggerBox::AMyTriggerBox()
{
	
}

void AMyTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapBegin);
}

void AMyTriggerBox::Tick(float DeltaTime)
{
	PrimaryActorTick.bCanEverTick = true;

}

void AMyTriggerBox::OnOverlapBegin(AActor* _overlapped, AActor* _overlap)
{
	TObjectPtr<ASpawnedEntity> _entity = Cast<ASpawnedEntity>(_overlap);
	if (!_entity)return;
	UE_LOG(LogTemp, Warning, TEXT("Overlap"));
	_entity->Destroy();
}


