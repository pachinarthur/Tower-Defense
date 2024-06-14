// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTPS.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AttackComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APlayerTPS::APlayerTPS()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletor");
	springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	movement = CreateDefaultSubobject<UFloatingPawnMovement>("Movement");
	attack = CreateDefaultSubobject<UAttackComponent>("Attack");
	mesh->SetupAttachment(RootComponent);
	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
	AddOwnedComponent(movement);
}

// Called when the game starts or when spawned
void APlayerTPS::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Init();

}

void APlayerTPS::Init()
{
	ULocalPlayer* _localPlayer = GetWorld()->GetFirstPlayerController()->GetLocalPlayer();	// ULocalPlayer* _localPlayer =  Permet de stocker la variable
	if (!_localPlayer)return;
	UEnhancedInputLocalPlayerSubsystem* _subsystem = _localPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if (!_subsystem)return;
	_subsystem->AddMappingContext(mappingContext, 0);
	bUseControllerRotationYaw = true;
	movement->MaxSpeed = moveSpeed;
}

void APlayerTPS::Move(const FInputActionValue& _value)
{
	const FVector2D _movementValue = _value.Get<FVector2D>();

	AddMovementInput(GetActorForwardVector(), _movementValue.Y);
	AddMovementInput(GetActorRightVector(), _movementValue.X);
	forwardAnim = _movementValue.Y;
	rightAnim = _movementValue.X;
}

void APlayerTPS::RotateCamera(const FInputActionValue& _value)
{
	const float _rotValue = _value.Get<float>();
	AddControllerYawInput(_rotValue * rotationSpeed * GetWorld()->DeltaTimeSeconds);
}

void APlayerTPS::Sprint()
{
	isSprinting = !isSprinting;	//un toogle, dès qu'on appuie, ça fait l'inverse
	isCrounching = false;

	UpdateSpeed(isSprinting ? sprintSpeed : moveSpeed);
}

void APlayerTPS::Crounch(const FInputActionValue& _value)
{
	isCrounching = _value.Get<bool>();	//là faut laisser appuyer. input renvoi un bool de base. 
	isSprinting = false;

	//3eme façon de faire (une terciaire mais avec fonction dédiée)
	UpdateSpeed(isCrounching ? crounchSpeed : moveSpeed);
}

void APlayerTPS::UpdateSpeed(const float& _value)
{
	if (!movement)return;			//pas nécessaire
	movement->MaxSpeed = _value;
}
void APlayerTPS::Shoot()
{
	if (currentMunition <= 0)return;
	currentMunition = currentMunition - 1 ;
	UE_LOG(LogTemp, Warning, TEXT("PEEW PEEW"));
	attack->Fire();
}
void APlayerTPS::Reload()
{
	currentMunition = 0;
	currentMunition = MaxMunition;
}
// Called to bind functionality to input
void APlayerTPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* _inputCompo = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!_inputCompo)
	{
		UE_LOG(LogTemp, Error, TEXT("Cast Input Component Failed !"));
		return;
	}
	_inputCompo->BindAction(inputMovement, ETriggerEvent::Triggered, this, &APlayerTPS::Move);
	_inputCompo->BindAction(inputMovement, ETriggerEvent::Completed, this, &APlayerTPS::Move);
	_inputCompo->BindAction(inputCamera, ETriggerEvent::Triggered, this, &APlayerTPS::RotateCamera);

	_inputCompo->BindAction(inputSprint, ETriggerEvent::Started, this, &APlayerTPS::Sprint);
	_inputCompo->BindAction(inputSprint, ETriggerEvent::Completed, this, &APlayerTPS::Sprint);

	_inputCompo->BindAction(inputCrounch, ETriggerEvent::Triggered, this, &APlayerTPS::Crounch);
	_inputCompo->BindAction(inputCrounch, ETriggerEvent::Completed, this, &APlayerTPS::Crounch);

	_inputCompo->BindAction(inputShoot, ETriggerEvent::Triggered, this, &APlayerTPS::Shoot);
	_inputCompo->BindAction(inputShoot, ETriggerEvent::Completed, this, &APlayerTPS::Shoot);

	_inputCompo->BindAction(inputReload, ETriggerEvent::Triggered, this, &APlayerTPS::Reload);
	_inputCompo->BindAction(inputReload, ETriggerEvent::Completed, this, &APlayerTPS::Reload);
}

