// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Checkpoint.h"
#include "MovementCompo.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UMovementCompo : public UActorComponent
{
	GENERATED_BODY()
		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPathReceveid, bool, _value);
	UPROPERTY(EditAnywhere)
		FOnPathReceveid onPathReceveid;
protected:
	UPROPERTY(EditAnywhere)
		TObjectPtr<AActor> customOwner = nullptr;
	UPROPERTY(EditAnywhere)
		TArray<TObjectPtr<ACheckpoint>> allCheckpoints;
	UPROPERTY(EditAnywhere)
		TSubclassOf<ACheckpoint> classToFind = nullptr;
	UPROPERTY(EditAnywhere)
		int pathCurrentIndex = 0;
	UPROPERTY(EditAnywhere)
		float moveSpeed = 300;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool canMove = false;
	UPROPERTY(EditAnywhere)
		float minDistAllowed = 100;
	UPROPERTY(EditAnywhere)
		float rotationSpeed = 300;

public:
	UFUNCTION()
		void SetCanMove(bool _value) { canMove = _value; }
public:	
	// Sets default values for this component's properties
	UMovementCompo();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void FindAllCheckpoints();
	void SortCheckpoints();
	void Move();
	void Init();
	void IncrementIndex();
	bool CheckHasArrived(const FVector& _targetToCheck);
	void Debug();
	void Rotate();
public:	
	bool GetCanMove() { return canMove; }
		
};
