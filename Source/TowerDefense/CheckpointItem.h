// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ParentItem.h"
#include "CheckpointItem.generated.h"

UCLASS()
class TOWERDEFENSE_API ACheckpointItem : public AParentItem
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UStaticMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)
		FColor debugColor = FColor::Black;
	
public:	
	// Sets default values for this actor's properties
	ACheckpointItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Debug();

public:	

};
