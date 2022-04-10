// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CanSee.generated.h"

/**
 * 
 */
UCLASS()
class VOTEXSHOOTER_API UBTService_CanSee : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	public:

		UBTService_CanSee();

	protected:

		virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
		
	
};
