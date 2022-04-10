// Fill out your copyright notice in the Description page of Project Settings.

#include "GalaxyShooter.h"
#include "PrimitiveSceneProxy.h"
#include "Components/CapsuleComponent.h"
#include "VotexShooterGameModeBase.h"
#include"ShooterPlayerController.h"
#include "GunBase.h"

// Sets default values
AGalaxyShooter::AGalaxyShooter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGalaxyShooter::BeginPlay()
{

	Super::BeginPlay();

	OurController = Cast<AShooterPlayerController>(this->GetController());
	OurPlayer = Cast<AActor>(this);
	Health = MaxHealth;
	Gun = GetWorld()->SpawnActor<AGunBase>(GunClass);
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}


// Called every frame
void AGalaxyShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AGalaxyShooter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Forward"), this, &AGalaxyShooter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Move Right"), this, &AGalaxyShooter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Look Up"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("Look Right"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter ::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AGalaxyShooter::Fire);
	PlayerInputComponent->BindAction(TEXT("Quit"), EInputEvent::IE_Pressed, this, &AGalaxyShooter::Exit);
	PlayerInputComponent->BindAction(TEXT("Restart"), EInputEvent::IE_Pressed, this, &AGalaxyShooter::ResetLvl);
}

float AGalaxyShooter::TakeDamage(float DamageAmount, FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	DamageToApply = FMath::Min(Health, DamageToApply);
	Health -= DamageToApply;


	if (IsDead())
	{
		AVotexShooterGameModeBase *GameMode = GetWorld()->GetAuthGameMode<AVotexShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}

		if(OurPlayer-> GetName() != TEXT("BP_PlayerShooter_C_0") )
		{
			DetachFromControllerPendingDestroy();
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			return 0.0f;
		}

		else
		{
			GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			return 0.0f;
		}

	}

	return 0.0f;
}

float AGalaxyShooter::GetPlayerHealth() const
{
	return Health/MaxHealth;
}

bool AGalaxyShooter::IsDead() const
{
	return Health <= 0;
}

void AGalaxyShooter::MoveForward(float axis)
{
	AddMovementInput(GetActorForwardVector() * axis);
}

void AGalaxyShooter::MoveRight(float axis)
{
	AddMovementInput(GetActorRightVector() * axis);
}

void AGalaxyShooter::Exit()
{
	if(OurController != nullptr)
	OurController->Quit();
}

void AGalaxyShooter::ResetLvl()
{
	if(OurController != nullptr)
	OurController->LvlRestart();
}

void AGalaxyShooter::Fire()
{
	Gun->PullTheTrigger();
}
