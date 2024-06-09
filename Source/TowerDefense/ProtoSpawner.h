// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "ProtoSpawner.generated.h"

class ASpawnedEntity;
UCLASS()
class TOWERDEFENSE_API AProtoSpawner : public AActor
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTimerElapsed);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEntitySpawned, AActor*, _spawned);
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEntityListUpdated, TArray<AActor*>, _allSpawned);
		UPROPERTY(EditAnywhere)
			FOnTimerElapsed onTimerElapsed;
		UPROPERTY(EditAnywhere)
			FOnEntitySpawned onEntitySpawned;
		UPROPERTY(EditAnywhere)
			FOnEntityListUpdated onEntityListUpdated;



#pragma region Components
		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Components")
			TObjectPtr<UBillboardComponent> billboardComponent = nullptr;
#pragma endregion

		UPROPERTY(EditAnywhere, Category = "ProtoSpawner")
			TArray<TObjectPtr<AActor>> allEntities;
		UPROPERTY(EditAnywhere, Category = "ProtoSpawner")
			float currentSpawnNumber = 0;
#pragma region Settings
		UPROPERTY(EditAnywhere,Category="ProtoSpawner|Settings")
			TSubclassOf<AActor> entityToSpawn = nullptr;
		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Settings")
			int maxCount = 10;
		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Settings")
			float currentTime = 0;
		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Settings")
			float maxTime = 5;

		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Settings|Timer")
			bool canReduceSpawnTime = false;
		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Settings|Timer")
			float timerRate = 1;
		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Settings|Timer")
			float decrementValue = 0.1f;
		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Settings|Timer")
			float minTimeValue = 0.1f;

		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Settings|Location")
			bool useSpawnerLocation = true;
		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Settings|Location")
			FVector customLocation = FVector(0);

#pragma endregion

		UPROPERTY(EditAnywhere, Category = "ProtoSpawner|Debugs")
			FColor debugColor = FColor::Black;
		
		UPROPERTY(EditAnywhere)
			FTimerHandle spawnTimer;

public:
	FVector GetSpawnLocation() { return  useSpawnerLocation ? GetActorLocation() : customLocation; }
	TObjectPtr<UBillboardComponent> GetBillboardCompo() {return	billboardComponent;}
	FOnTimerElapsed& OnTimerElapsed() { return onTimerElapsed; }
	FOnEntitySpawned& OnEntitySpawned() { return onEntitySpawned; }
	FOnEntityListUpdated& OnEntityListUpdated() { return onEntityListUpdated; }

	void SetCustomLocation(const FVector& _newLoc) { customLocation = _newLoc; }
public:	
	// Sets default values for this actor's properties
	AProtoSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void Spawn();
	void Init();
	void Debug();
	void UpdateTimerRate();
	FVector SelectSpawnLocation();
	void IncreaseTime(float& _current, float& _maxTime);

public:	
	// Called every frame
	void RemoveEntity(TObjectPtr<ASpawnedEntity> _toRemove);
};
