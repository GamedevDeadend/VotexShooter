// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GalaxyShooter.generated.h"

class AGunBase;
class AShooterPlayerController;

UCLASS()
class VOTEXSHOOTER_API AGalaxyShooter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AGalaxyShooter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintPure)
	float GetPlayerHealth() const;
	
	UFUNCTION(BlueprintPure)
	bool IsDead() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	void Fire();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage
	(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser
	)override;

private:


UPROPERTY(EditAnywhere, BlueprintInternalUseOnly, Category = "Health")
	float MaxHealth = 100;
	float Health;

	void MoveForward(float axis);
	void MoveRight(float axis);

	void Exit();
	void ResetLvl();

	void LookUp(float axis);
	void LookRight(float axis);

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGunBase> GunClass;

	UPROPERTY()
	AGunBase* Gun;

	AShooterPlayerController* OurController;
	AActor* OurPlayer;

};
