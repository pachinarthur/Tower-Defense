// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileDegats.generated.h"

UCLASS()
class TOWERDEFENSE_API AProjectileDegats : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTargetReach);
	UPROPERTY()
	FOnTargetReach onTargetReach;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)
		float moveSpeed = 600;
	UPROPERTY(EditAnywhere)
		TObjectPtr<AActor> target = nullptr;
	UPROPERTY(EditAnywhere)
		float lifespan = 5;
	UPROPERTY(EditAnywhere)
		int damage = 1;
	UPROPERTY(EditAnywhere)
		bool hadTarget = false;

public:
	FOnTargetReach& OnTargetReach() { return onTargetReach; }

public:
	// Sets default values for this actor's properties
	AProjectileDegats();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Move();
	UFUNCTION()
		void TriggerOverlap(AActor* _overlapped, AActor* _overlap);
public:
	void SetTarget(TObjectPtr<AActor> _target);
};
