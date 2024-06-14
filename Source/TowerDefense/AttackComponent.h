// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttackComponent.generated.h"

class AProjectile;
class AProjectileDegats;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSE_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectileDegats> projectileDegatsToShoot = nullptr;
		UPROPERTY(EditAnywhere)
			TObjectPtr<AActor> target = nullptr;

		UPROPERTY(EditAnywhere)
			float attackRange = 500;

		UPROPERTY(EditAnywhere)
			bool canAttack = true;

		UPROPERTY(EditAnywhere)
			float currentTime = 0;

		UPROPERTY(EditAnywhere)
			float maxTime = 2;


public:	
	// Sets default values for this component's properties
	UAttackComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Attack();
	void CoolDownTime(float& _current,const float& _max);
public:	
	void Fire();
	UFUNCTION()
		void SetTarget(AActor* _newTarget);
		
};
