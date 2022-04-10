// Fill out your copyright notice in the Description page of Project Settings.

#include "EngineUtils.h"
#include"ShooterAIController.h"
#include "GameFramework/Controller.h"
#include "KillEmll_GameMode.h"

void AKillEmll_GameMode::PawnKilled(APawn* PawnKilled)
{
    Super :: PawnKilled(PawnKilled);

    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
    
    if(PlayerController != nullptr)
    {
        EndGame(false);
    }

    for(AShooterAIController* EnemyController : TActorRange<AShooterAIController>(GetWorld()) )
    {
        if(!EnemyController->IsDead())
        {
            return;//Loop to ensure if any EnemyController is alive or not, if not alive then execute EndGame;
        }
        
    }  
    
    EndGame(true);           
}

void AKillEmll_GameMode::EndGame(bool bIsPlayerWon)
{
    for(AController* Controller :TActorRange<AController>(GetWorld()) )
    {
        bool bIsWinner = (Controller->IsPlayerController() == bIsPlayerWon);
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
    }
}
