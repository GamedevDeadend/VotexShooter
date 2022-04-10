// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "AIController.h"
#include "BTService_CanSee.h"

UBTService_CanSee::UBTService_CanSee()
{
    NodeName = TEXT("Can See?");
}

void UBTService_CanSee::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *PlayerPawn = UGameplayStatics ::GetPlayerPawn(GetWorld(), 0);

    AAIController *PlayerControll = OwnerComp.GetAIOwner();

    if (PlayerControll != nullptr && PlayerPawn != nullptr)
    {
        if (PlayerControll->LineOfSightTo(PlayerPawn))
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerPawn);
        }

        else
        {
            OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        }
    }
}
