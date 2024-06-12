// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTriggerBox.h"
#include "Engine/Engine.h"

AMyTriggerBox::AMyTriggerBox()
{
	
}

void AMyTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	OnActorEndOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapEnd);
	OnActorBeginOverlap.AddDynamic(this, &AMyTriggerBox::OnOverlapBegin);
	DrawDebugBox(GetWorld(), GetActorLocation(), GetComponentsBoundingBox().GetExtent(), FColor::Purple, true, -1, 0, 5);
}

void AMyTriggerBox::OnOverlapBegin(AActor* OverlappedActor, AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Some debug message!"));
}

void AMyTriggerBox::OnOverlapEnd(AActor* OverlappedActor, AActor* OtherActor)
{

}

