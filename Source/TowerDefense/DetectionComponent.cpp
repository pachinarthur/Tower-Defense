// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectionComponent.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UDetectionComponent::UDetectionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDetectionComponent::BeginPlay()
{
	Super::BeginPlay();
	Init();
	// ...
	
}


// Called every frame
void UDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<AActor*> UDetectionComponent::SortDetectedList(TArray<AActor*> _detectedList)
{
	const int _size = _detectedList.Num();
	int _smallestRangeIndex = 0;
	TObjectPtr<AActor> _owner = GetOwner();
	const FVector _ownerLoc = _owner->GetActorLocation();
	for (int i = 0; i < _size - 1; i++) {
		_smallestRangeIndex = i;
		for (int j = i + 1; j < _size; j++) {
			const FVector _iLoc = _detectedList[i]->GetActorLocation();
			const FVector _jLoc = _detectedList[j]->GetActorLocation();
			if (FVector::Dist(_iLoc, _ownerLoc) > FVector::Dist(_jLoc, _ownerLoc)) {
				if (FVector::Dist(_detectedList[_smallestRangeIndex]->GetActorLocation(), _ownerLoc) > FVector::Dist(_jLoc, _ownerLoc)) {
					_smallestRangeIndex = j;
				}
			}
		}
		if (i != _smallestRangeIndex) {
			TObjectPtr<AActor> _temp = _detectedList[i];
			_detectedList[i] = _detectedList[_smallestRangeIndex];
			_detectedList[_smallestRangeIndex] = _temp;
		}
	}
	return _detectedList;
}

void UDetectionComponent::SortTick()
{
	allDetected = SortDetectedList(allDetected);
	onFirstTargetFound.Broadcast(allDetected.Num() < 1 ? nullptr : allDetected[0]);
	
}

void UDetectionComponent::Init()
{
	TObjectPtr<AActor> _spawner = UGameplayStatics::GetActorOfClass(this, AProtoSpawner::StaticClass());
	spawnerRef = Cast<AProtoSpawner>(_spawner);
	if (!spawnerRef)return;
	spawnerRef->OnEntityListUpdated().AddDynamic(this, &UDetectionComponent::UpdateDetectedList);
	FTimerHandle _sortingTimer;
	GetWorld()->GetTimerManager().SetTimer(_sortingTimer, this, &UDetectionComponent::SortTick,1,true);

}

void UDetectionComponent::SetDetection(const float& _range)
{
	detectionRange = _range;
}

void UDetectionComponent::UpdateDetectedList(TArray<AActor*> _detectedList)
{
	_detectedList = SortDetectedList(_detectedList);
	allDetected = _detectedList;
}

