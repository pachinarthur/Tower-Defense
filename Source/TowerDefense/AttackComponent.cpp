// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include "ProjectileDegats.h"

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!canAttack)
		CoolDownTime(currentTime, maxTime);
	Attack();
	// ...
}

void UAttackComponent::Attack()
{
	if (!canAttack || !target)return;
	if (FVector::Dist(GetOwner()->GetActorLocation(), target->GetActorLocation()) > attackRange)return;
	const FVector _spawnLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorUpVector() * 100;
	TObjectPtr<AProjectileDegats> _projectile = GetWorld()->SpawnActor<AProjectileDegats>(projectileDegatsToShoot,_spawnLocation,FRotator::ZeroRotator);
	if (!_projectile)return;
	//if(!IsValid(_projectile))return;
	_projectile->SetTarget(target);
	canAttack = false;
}

void UAttackComponent::CoolDownTime(float& _current, const float& _max)
{
	_current += GetWorld()->DeltaTimeSeconds;
	if (_current >= _max) {
		canAttack = true;
		_current = 0;
	}

}

void UAttackComponent::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("PEEW PEEW"));
}

void UAttackComponent::SetTarget(AActor* _newTarget)
{
	if (!_newTarget) {
		target = nullptr;
		return;
	}
	if (FVector::Dist(_newTarget->GetActorLocation(), GetOwner()->GetActorLocation()) <= attackRange) {
		target = _newTarget;
		return;
	}
	target = nullptr;
}

