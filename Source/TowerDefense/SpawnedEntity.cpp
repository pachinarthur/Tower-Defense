
// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnedEntity.h"
#include "DetectionComponent.h"

// Sets default values
ASpawnedEntity::ASpawnedEntity()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	skeleton = CreateDefaultSubobject<USkeletalMeshComponent>("Skeleton");
	movement = CreateDefaultSubobject<UMovementCompo>("Movement");

	skeleton->SetupAttachment(RootComponent);
	AddOwnedComponent(movement);
}

// Called when the game starts or when spawned
void ASpawnedEntity::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpawnedEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASpawnedEntity::AddHealth(const int& _valueToAdd)
{
	health += _valueToAdd;
	health = health < 0 ? 0 : health;
	if (health <= 0) {
		onDeath.Broadcast();
	}
}

void ASpawnedEntity::Init(TObjectPtr<AProtoSpawner> _spawner)
{
	if (!_spawner)return;
	spawnerRef = _spawner;
	onDeath.AddDynamic(this, &ASpawnedEntity::Death);
}


void ASpawnedEntity::Death()
{
	spawnerRef->RemoveEntity(this);
	Destroy();
}