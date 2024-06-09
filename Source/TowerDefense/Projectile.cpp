// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "SpawnedEntity.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(lifespan);
	OnActorBeginOverlap.AddDynamic(this, &AProjectile::TriggerOverlap);
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();
}

void AProjectile::Move()
{
	if (!target)return;
	const FVector _newLoc = FMath::VInterpConstantTo(GetActorLocation(), target->GetActorLocation(), GetWorld()->DeltaTimeSeconds, moveSpeed);
	SetActorLocation(_newLoc);
}

void AProjectile::TriggerOverlap(AActor* _overlapped, AActor* _overlap)
{
	TObjectPtr<ASpawnedEntity> _entity = Cast<ASpawnedEntity>(_overlap);

	if (!_entity) {
		UE_LOG(LogTemp, Warning, TEXT("Not _overlap"));
	}
}

void AProjectile::SetTarget(TObjectPtr<AActor> _target)
{
	target = _target;
}

