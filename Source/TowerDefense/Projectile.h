// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOWERDEFENSE_API AProjectile : public AActor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)
		float moveSpeed = 600;
	UPROPERTY(EditAnywhere)
		TObjectPtr<AActor> target = nullptr;
	UPROPERTY(EditAnywhere)
		float lifespan = 1;

	
public:	
	// Sets default values for this actor's properties
	AProjectile();

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
