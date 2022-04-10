// Fill out your copyright notice in the Description page of Project Settings.

#include"GalaxyShooter.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshcomponent.h"
#include "GunBase.h"

// Sets default values
AGunBase ::AGunBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh component"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGunBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGunBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGunBase::PullTheTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound,Mesh, TEXT("MuzzleFlashSocket"));


	FHitResult Hit;
	FVector ShotDirection;
	bool bsuccess = bGunTrace(Hit, ShotDirection);

	if (bsuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		
		AActor *HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(GunDamage, Hit, ShotDirection, nullptr);
			AController* OwnerController = ReturnController();
			HitActor->TakeDamage(GunDamage, DamageEvent, OwnerController, this);
		}
	}
}

AController* AGunBase::ReturnController() const
{
	APawn *OwnerPlayer = Cast<APawn>(GetOwner());
	if (OwnerPlayer == nullptr)
		return nullptr;

	return OwnerPlayer->GetController();
}

bool AGunBase::bGunTrace (OUT FHitResult &Hit, OUT FVector &ShotDirection)
{
	AController* OwnerController = ReturnController();
	if(!OwnerController)
		{return false;}

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(OUT Location, OUT Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;
	ShotDirection = Rotation.Vector();

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
}
