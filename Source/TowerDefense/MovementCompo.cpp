// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementCompo.h"
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values for this component's properties
UMovementCompo::UMovementCompo()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMovementCompo::BeginPlay()
{
	Super::BeginPlay();
	Init();
}


// Called every frame
void UMovementCompo::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Move();
	Debug();
	Rotate();
}

void UMovementCompo::FindAllCheckpoints()
{
	TArray<TObjectPtr<AActor>> _actors;
	UGameplayStatics::GetAllActorsOfClass(this, classToFind, _actors);
	const int _size = _actors.Num();
	for (int i = 0; i < _size; i++) {
		allCheckpoints.Add(Cast<ACheckpoint>(_actors[i]));
	}
	SortCheckpoints();
	onPathReceveid.Broadcast(true);

}

void UMovementCompo::SortCheckpoints()
{
	const int _size = allCheckpoints.Num();
	for (int i = 0; i < _size -1; i++) {
		int _smallIndex = i;
		for (int j = 1+1; j < _size; j++) {
			if (allCheckpoints[i]->GetOrder() > allCheckpoints[j]->GetOrder()) {
				if (allCheckpoints[_smallIndex]->GetOrder() > allCheckpoints[j]->GetOrder()) {
					_smallIndex = j;
				}
			}
			
		}
		TObjectPtr<ACheckpoint> _temp = allCheckpoints[i];
		allCheckpoints[i] = allCheckpoints[_smallIndex];
		allCheckpoints[_smallIndex] = _temp;
	}
}

void UMovementCompo::Move()
{
	if (!canMove)return;
	const FVector _loc = UKismetMathLibrary::VInterpTo_Constant(customOwner->GetActorLocation(),allCheckpoints[pathCurrentIndex]->GetActorLocation(),GetWorld()->DeltaTimeSeconds,moveSpeed);
	customOwner->SetActorLocation(_loc);
	if (CheckHasArrived(allCheckpoints[pathCurrentIndex]->GetActorLocation())) {
		IncrementIndex();
	}
}

void UMovementCompo::Init()
{
	customOwner = GetOwner();
	onPathReceveid.AddDynamic(this, &UMovementCompo::SetCanMove);
	FindAllCheckpoints();
}

void UMovementCompo::IncrementIndex()
{
	const int _size = allCheckpoints.Num();
	if (pathCurrentIndex >= _size - 1) {
		canMove = false;
		return;
	}
	pathCurrentIndex++;
}

bool UMovementCompo::CheckHasArrived(const FVector& _targetToCheck)
{
	return FVector::Dist(customOwner->GetActorLocation(), _targetToCheck) <= minDistAllowed;
}

void UMovementCompo::Debug()
{
	const int _size = allCheckpoints.Num();
	if (_size < 1)return;
	for (int i = 0; i < _size; i++){
		FColor _color = i == pathCurrentIndex ? FColor::Magenta :
			i < pathCurrentIndex ? FColor::Green: FColor::Red;
		DrawDebugSphere(GetWorld(), allCheckpoints[i]->GetActorLocation(), 50, 15, _color, false, -1, 0, 2);
		if (i + 1 < _size) {
			DrawDebugLine(GetWorld(), allCheckpoints[i]->GetActorLocation(), allCheckpoints[i +1]->GetActorLocation(), FColor::Black, false, -1, 0, 2);
		}
	}
}

void UMovementCompo::Rotate()
{
	if (!canMove)return;
	const FRotator _newRot = UKismetMathLibrary::FindLookAtRotation(customOwner->GetActorLocation(), allCheckpoints[pathCurrentIndex]->GetActorLocation());
	const FRotator _rot = UKismetMathLibrary::RInterpTo_Constant(customOwner->GetActorRotation(), _newRot, GetWorld()->DeltaTimeSeconds, rotationSpeed);
	customOwner->SetActorRotation(_rot);
}
