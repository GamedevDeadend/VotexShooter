// Fill out your copyright notice in the Description page of Project Settings.

#include "TimerManager.h"
#include"Kismet/KismetSystemLibrary.h"
#include"Blueprint/UserWidget.h"
#include "ShooterPlayerController.h"



void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    CrossairArrow->RemoveFromViewport();

    if(!bIsWinner)
    {
        UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);

        if(LoseScreen != nullptr)
        {
            LoseScreen->AddToViewport();
            GetWorldTimerManager().SetTimer(Restart, this, &APlayerController :: RestartLevel, RestartDelay);
        }

    }

    else

    {
        UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);

        if(WinScreen != nullptr)
        {
            WinScreen->AddToViewport();
            GetWorldTimerManager().SetTimer(Restart, this, &AShooterPlayerController :: Quit, RestartDelay);
        }

    }
    
    
}

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

    CrossairArrow = CreateWidget(this, Crossair);
    if(CrossairArrow)
    {
        CrossairArrow->AddToViewport();
    }
}

void AShooterPlayerController::Quit()
{
    this->ConsoleCommand("quit");
}

void AShooterPlayerController::LvlRestart()
{
    this->RestartLevel();
}
