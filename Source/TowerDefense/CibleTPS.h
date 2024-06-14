// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CibleTPS.generated.h"

UCLASS()
class TOWERDEFENSE_API ACibleTPS : public AActor
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
	UPROPERTY()
		FOnDeath onDeath;
public:	
	FOnDeath& OnDeath() { return onDeath; }

	// Sets default values for this actor's properties
	ACibleTPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void Death();
};
