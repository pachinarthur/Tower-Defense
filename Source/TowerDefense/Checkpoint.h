// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "Checkpoint.generated.h"

UCLASS()
class TOWERDEFENSE_API ACheckpoint : public AActor
{
	GENERATED_BODY()
		UPROPERTY(EditAnywhere)
		TObjectPtr<UBillboardComponent> billboard = nullptr;
		UPROPERTY(EditAnywhere)
			int order = 0;
public:
	int GetOrder() const { return order; }
public:	
	// Sets default values for this actor's properties
	ACheckpoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	

	void Debug();
};
