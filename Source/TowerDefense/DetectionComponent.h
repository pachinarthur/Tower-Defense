// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProtoSpawner.h"
#include "Components/ActorComponent.h"
#include "DetectionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UDetectionComponent : public UActorComponent
{
	GENERATED_BODY()

		DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFirstTargetFound, AActor*, _target);
		UPROPERTY()
			FOnFirstTargetFound onFirstTargetFound;
		UPROPERTY(EditAnywhere)
			float detectionRange = 0;;
		UPROPERTY(EditAnywhere)
			TSubclassOf<AActor> classToDetect = nullptr;
		UPROPERTY(EditAnywhere)
			TArray<TObjectPtr<AActor>> allDetected;
		UPROPERTY(EditAnywhere)
			TObjectPtr<AProtoSpawner> spawnerRef = nullptr;
		UPROPERTY(EditAnywhere)
			TSubclassOf<AProtoSpawner> spawnerClassToFind = nullptr;

public:
	FOnFirstTargetFound& OnFirstTargetFound() {return onFirstTargetFound;}
public:	
	// Sets default values for this component's properties
	UDetectionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Init();
	TArray<AActor*> SortDetectedList(TArray<AActor*> _detectedList);
	void SortTick();
public:
	UFUNCTION()
		void SetDetection(const float& _range);
	UFUNCTION()
		void UpdateDetectedList(TArray<AActor*> _detectedList);
};
