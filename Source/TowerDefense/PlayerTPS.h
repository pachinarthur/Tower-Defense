// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "InputMappingContext.h"
#include "PlayerTPS.generated.h"

UCLASS()
class TOWERDEFENSE_API APlayerTPS : public APawn
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
		TObjectPtr<UAttackComponent> attack = nullptr;

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
	UPROPERTY(EditAnywhere)
		TObjectPtr <UInputAction> inputShoot = nullptr;
	UPROPERTY(EditAnywhere)
		TObjectPtr <UInputAction> inputReload = nullptr;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)		//BluePrintReadOnly si on veut juste Get et pas Set
		float moveSpeed = 600;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		float rotationSpeed = 300;

	UPROPERTY(EditAnywhere)
		float sprintSpeed = 1200;
	UPROPERTY(EditAnywhere)
		float crounchSpeed = 300;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		int currentMunition = 10;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		int MaxMunition = 10;

	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		float forwardAnim = 0;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		float rightAnim = 0;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		bool isCrounching = false;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		bool isSprinting = false;
public:
	// Sets default values for this pawn's properties
	APlayerTPS();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Init();
	void Move(const FInputActionValue& _value);
	void RotateCamera(const FInputActionValue& _value);
	void Sprint();
	void Crounch(const FInputActionValue& _value);
	void UpdateSpeed(const float& _value);
	void Shoot();
	void Reload();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
