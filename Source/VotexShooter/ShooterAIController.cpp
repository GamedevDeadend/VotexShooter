// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include"GalaxyShooter.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
    Super ::BeginPlay();

    if( AIBehavior != nullptr)
    {
        RunBehaviorTree( AIBehavior);

        APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);


        GetBlackboardComponent()->SetValueAsVector(TEXT("Start Coordinates"), GetPawn()->GetActorLocation());

    }
}

void AShooterAIController :: Tick(float DeltaTime)
{
    Super :: Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
    AGalaxyShooter* ControlledPawn = Cast<AGalaxyShooter>(GetPawn());

    if(ControlledPawn != nullptr)
    {
        return ControlledPawn->IsDead();
    } 
    
    else
    {
        return true;
    }
}
