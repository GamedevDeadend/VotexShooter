// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "VotexShooterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class VOTEXSHOOTER_API AVotexShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	public:

		virtual void PawnKilled(APawn* PawnKilled);
	
};
