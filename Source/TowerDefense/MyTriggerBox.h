// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSE_API AMyTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
public:

	// constructor sets default values for this actor's properties
	AMyTriggerBox();
	//créer des fonctions pour les événements de début et de fin de chevauchement
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);
	UFUNCTION()
		void OnOverlapEnd(class AActor* OverlappedActor, class AActor* OtherActor);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
