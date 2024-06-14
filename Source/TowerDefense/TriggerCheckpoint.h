// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "ATrap.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API ATrap : public ATriggerBox
{
	GENERATED_BODY()
protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


public:

	// constructor sets default values for this actor's properties
	ATrap();

	// declare overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class AActor* _overlapped, class AActor* _overlap);

};
