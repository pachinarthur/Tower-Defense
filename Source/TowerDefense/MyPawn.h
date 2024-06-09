// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "ParentItem.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "InputMappingContext.h"
#include "MyPawn.generated.h"
UCLASS()
class TOWERDEFENSE_API AMyPawn : public APawn
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		TObjectPtr<USkeletalMeshComponent> mesh = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<USpringArmComponent> springArm = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UCameraComponent> camera = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UFloatingPawnMovement> movement = nullptr;

	UPROPERTY(EditAnywhere)
		TObjectPtr<UInputMappingContext> mappingContext = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr <UInputAction> inputMovement = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr <UInputAction> inputCamera = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr <UInputAction> inputSprint = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr <UInputAction> inputCrounch = nullptr;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)		//BluePrintReadOnly si on veut juste Get et pas Set
		float moveSpeed = 600;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		float rotationSpeed = 300;

	UPROPERTY(EditAnywhere)
		float sprintSpeed = 1200;
	UPROPERTY(EditAnywhere)
		float crounchSpeed = 300;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		float forwardAnim = 0;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		float rightAnim = 0;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		bool isCrounching = false;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		bool isSprinting = false;
	UPROPERTY(VisibleAnywhere)
		TArray<AActor*> FoundActors;
	UPROPERTY(EditAnywhere)
		TObjectPtr<UClass> ClassToFind = AParentItem::StaticClass();
	UPROPERTY(EditAnywhere)
		float NearDist = FLT_MAX;
	UPROPERTY(EditAnywhere)
		TObjectPtr<AActor> NearestActor = nullptr;
	UPROPERTY(EditAnywhere)
		float minDistance = 100;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> CheckPointArrived;
	UPROPERTY(EditAnywhere)
		FVector LocationCheck = FVector(0);

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Init();
	void Move(const FInputActionValue& _value);
	void RotateCamera(const FInputActionValue& _value);
	void Sprint();
	void Crounch(const FInputActionValue& _value);
	void UpdateSpeed(const float& _value);
	void GetAllActor();
	void IfCheckpointPassed();
	void MoveToCheckpoint(const TObjectPtr<AActor> _checkpoint);
	TObjectPtr<AActor> GetNearestActor(const TArray<AActor*>& _foundActors);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
