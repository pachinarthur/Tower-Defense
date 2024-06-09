// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtoSpawner.h"
#include "SpawnedEntity.h"

// Sets default values
AProtoSpawner::AProtoSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	billboardComponent = CreateDefaultSubobject<UBillboardComponent>("BillBoard");
	billboardComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProtoSpawner::BeginPlay()
{
	Super::BeginPlay();
	Init();
	
}

// Called every frame
void AProtoSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Debug();
	IncreaseTime(currentTime,maxTime);
}

void AProtoSpawner::Spawn()
{
	if (currentSpawnNumber >= maxCount)return;
	TObjectPtr<AActor> _spawned = GetWorld()->SpawnActor<AActor>(entityToSpawn, GetActorLocation(), FRotator::ZeroRotator);
	if (!_spawned)return;
	TObjectPtr<ASpawnedEntity> _entity = Cast<ASpawnedEntity>(_spawned);
	_entity->Init(this);

	currentSpawnNumber++;
	allEntities.Add(_spawned);
	onEntitySpawned.Broadcast(_spawned.Get());
	onEntityListUpdated.Broadcast(allEntities);
	/*if (currentSpawnNumber && timerRate > minTimeValue)
		UpdateTimerRate();*/
}

void AProtoSpawner::Init()
{
	//GetWorld()->GetTimerManager().SetTimer(spawnTimer, this, &AProtoSpawner::Spawn, 1, true);
	onTimerElapsed.AddDynamic(this, &AProtoSpawner::Spawn);
}

void AProtoSpawner::Debug()
{
	DrawDebugBox(GetWorld(), GetActorLocation(), FVector::OneVector * 100, debugColor, false, -1, 0, 2);
	if (!useSpawnerLocation)
		DrawDebugSphere(GetWorld(), customLocation, 15,10,debugColor,false,-1,0,2);
}

void AProtoSpawner::UpdateTimerRate()
{
	timerRate -= decrementValue;
	timerRate = timerRate > minTimeValue ? timerRate : minTimeValue;
	const float _remainingTime = GetWorld()->GetTimerManager().GetTimerElapsed(spawnTimer);
	GetWorld()->GetTimerManager().ClearTimer(spawnTimer);
	GetWorld()->GetTimerManager().SetTimer(spawnTimer,this,&AProtoSpawner::Spawn,timerRate,true, _remainingTime);
}

FVector AProtoSpawner::SelectSpawnLocation()
{
	return useSpawnerLocation ? GetActorLocation() : customLocation;
}

void AProtoSpawner::IncreaseTime(float& _current, float& _maxTime)
{
	_current += GetWorld()->DeltaTimeSeconds;
	if (_current >= _maxTime)
	{
		_current = 0;
		if (canReduceSpawnTime) {
			_maxTime -= decrementValue;
			_maxTime = _maxTime > minTimeValue ? _maxTime : minTimeValue;
		}
		onTimerElapsed.Broadcast();
		//Spawn();
	}
}

void AProtoSpawner::RemoveEntity(TObjectPtr<ASpawnedEntity> _toRemove)
{
	allEntities.Remove(_toRemove);
	onEntityListUpdated.Broadcast(allEntities);
}

