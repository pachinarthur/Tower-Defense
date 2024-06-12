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
	//cr�er des fonctions pour les �v�nements de d�but et de fin de chevauchement
	UFUNCTION()
		void OnOverlapBegin(AActor* _overlapped, AActor* _overlap);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
