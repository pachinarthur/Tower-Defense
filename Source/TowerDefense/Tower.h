// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AttackComponent.h"
#include "DetectionComponent.h"
#include "Tower.generated.h"

UCLASS()
class TOWERDEFENSE_API ATower : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UAttackComponent> attack = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UDetectionComponent> detection = nullptr;


	
public:	
	// Sets default values for this actor's properties
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
