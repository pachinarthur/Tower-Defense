// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovementCompo.h"
#include "SpawnedEntity.generated.h"

class AProtoSpawner;
UCLASS()
class TOWERDEFENSE_API ASpawnedEntity : public AActor
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
		UPROPERTY()
			FOnDeath onDeath;
		UPROPERTY(EditAnywhere)
			TObjectPtr<USkeletalMeshComponent> skeleton = nullptr;
		UPROPERTY(EditAnywhere)
			TObjectPtr<UMovementCompo> movement = nullptr;
		UPROPERTY(EditAnywhere)
			int health = 10;
		UPROPERTY(EditAnywhere)
			TObjectPtr<AProtoSpawner> spawnerRef = nullptr;
public:
	FOnDeath& OnDeath() { return onDeath; }
	int GetHealth() const {return health;};
	void SetHealth(const int& _newHealth) { health = _newHealth; };
public:	
	// Sets default values for this actor's properties
	ASpawnedEntity();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void Death();

public:	
	void AddHealth(const int& _valueToAdd);
	void Init(TObjectPtr<AProtoSpawner> _spawner);
	UFUNCTION(BlueprintCallable)
	bool GetcanMove() { return movement->GetCanMove(); }
};
