// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletor");
	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");

	mesh->SetupAttachment(RootComponent);
	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
	AddOwnedComponent(movement);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	Init();
	GetAllActor();
}

void AMyPawn::Init()
{
	ULocalPlayer* _localPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();	// ULocalPlayer* _localPlayer =  Permet de stocker la variable
	if (!_localPlayer)return;
	UEnhancedInputLocalPlayerSubsystem* _subsystem = _localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_subsystem)return;
	_subsystem->AddMappingContext(mappingContext, 0);

	bUseControllerRotationYaw = true;
	movement->MaxSpeed = moveSpeed;
}

void AMyPawn::Move(const FInputActionValue& _value)
{
	const FVector2D _movementValue = _value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), _movementValue.Y);
	AddMovementInput(GetActorRightVector(), _movementValue.X);
	forwardAnim = _movementValue.Y;
	rightAnim = _movementValue.X;
}

void AMyPawn::RotateCamera(const FInputActionValue& _value)
{
	const float _rotValue = _value.Get<float>();
	AddControllerYawInput(_rotValue * rotationSpeed * GetWorld()->DeltaTimeSeconds);
}

void AMyPawn::Sprint()
{
	isSprinting = !isSprinting;	//un toogle, dès qu'on appuie, ça fait l'inverse
	isCrounching = false;

	UpdateSpeed(isSprinting ? sprintSpeed : moveSpeed);
}

void AMyPawn::Crounch(const FInputActionValue& _value)
{
	isCrounching = _value.Get<bool>();	//là faut laisser appuyer. input renvoi un bool de base. 
	isSprinting = false;

	//3eme façon de faire (une terciaire mais avec fonction dédiée)
	UpdateSpeed(isCrounching ? crounchSpeed : moveSpeed);
}

void AMyPawn::UpdateSpeed(const float& _value)
{
	if (!movement)return;			//pas nécessaire
	movement->MaxSpeed = _value;
}

void AMyPawn::GetAllActor()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ClassToFind, FoundActors);

}

void AMyPawn::IfCheckpointPassed()
{
	for (AActor* _currentActor : FoundActors) {
		float _distance = FVector::Dist(this->GetActorLocation(), _currentActor->GetActorLocation());
		if (_distance < minDistance) {
			CheckPointArrived.Add(_currentActor);
			FoundActors.RemoveSingle(_currentActor);
			NearDist = FLT_MAX;
		}
	}
}

void AMyPawn::MoveToCheckpoint(const TObjectPtr<AActor> _checkpoint)
{
	FVector _direction = (_checkpoint->GetActorLocation(), -GetActorLocation()).GetSafeNormal();
	UE_LOG(LogTemp, Warning, TEXT("Curent: %s"), *(_direction.ToString()));
	AddMovementInput(LocationCheck, 1.0f);
}

TObjectPtr<AActor> AMyPawn::GetNearestActor(const TArray<AActor*>& _foundActors)
{
	for(AActor* _currentActor : _foundActors){
		float _distance = FVector::Dist(this->GetActorLocation(), _currentActor->GetActorLocation());
		//GEngine->AddOnScreenDebugMessage(-1,15.)
		if (_distance < NearDist) {
			NearestActor = _currentActor;
			NearDist = _distance;
		}
		LocationCheck = _currentActor->GetActorLocation();
	}
	return NearestActor;
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*GetNearestActor(FoundActors);
	MoveToCheckpoint(NearestActor);
	IfCheckpointPassed();*/
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* _inputCompo = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!_inputCompo)
	{
		UE_LOG(LogTemp, Error, TEXT("Cast Input Component Failed !"));
		return;
	}
	_inputCompo->BindAction(inputMovement, ETriggerEvent::Triggered, this, &AMyPawn::Move);
	_inputCompo->BindAction(inputMovement, ETriggerEvent::Completed, this, &AMyPawn::Move);
	_inputCompo->BindAction(inputCamera, ETriggerEvent::Triggered, this, &AMyPawn::RotateCamera);

	//_inputCompo->BindAction(inputSprint, ETriggerEvent::Triggered, this, &AExoPawn::Sprint);
	_inputCompo->BindAction(inputSprint, ETriggerEvent::Started, this, &AMyPawn::Sprint);

	_inputCompo->BindAction(inputCrounch, ETriggerEvent::Triggered, this, &AMyPawn::Crounch);
	_inputCompo->BindAction(inputCrounch, ETriggerEvent::Completed, this, &AMyPawn::Crounch);

}

