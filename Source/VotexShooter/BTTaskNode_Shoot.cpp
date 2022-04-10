// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTaskNode_Shoot.h"
#include "AIController.h"
#include "GalaxyShooter.h"


VOTEXSHOOTER_API UBTTaskNode_Shoot::UBTTaskNode_Shoot()
{
    NodeName = TEXT("Shoot");
}



EBTNodeResult::Type UBTTaskNode_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

   if(OwnerComp.GetAIOwner() == nullptr)
   {
       return EBTNodeResult::Failed;
   }

   AGalaxyShooter* Character = Cast<AGalaxyShooter>(OwnerComp.GetAIOwner()->GetPawn());

   if(Character == nullptr)
   {
       return EBTNodeResult::Failed;
   }

   Character->Fire();
     
    return EBTNodeResult::Succeeded;
}
