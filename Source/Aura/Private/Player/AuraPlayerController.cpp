// Copyright Blusque Mei


#include "Player/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	// Add the mapping context to the local player's input subsystem
	// Do if statement instead of check() in this case, because only the server and the local client will possess a local player
	// if on the other client, the game will crash
	if (auto InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		InputSubsystem->AddMappingContext(AuraContext, 0);
	}
	// check(InputSubsystem);  // Don't do this in a multiplayer game, players on other client will not possess a local player

	// Set whether to show mouse cursor
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Set input mode in both game and UI
	FInputModeGameAndUI InputModeData;  // FInputModeGameAndUI is a struct that contains data for input mode and cursor behavior
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);  // Do not lock mouse cursor
	InputModeData.SetHideCursorDuringCapture(false);  // Do not hide cursor
	SetInputMode(InputModeData);  // Set input mode with SetInputMode function
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Get the enhanced input component
	auto EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	// Bind the Move action
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	// Get the movement vector
	const FVector2D InputAxisVector = Value.Get<FVector2D>();

	// Get local coordinate
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// Get player pawn
	if (auto ControlledPawn = GetPawn<APawn>())
	{
		// Move the player pawn
		ControlledPawn->AddMovementInput(Forward, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(Right, InputAxisVector.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	// Get cursor hit result
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Pawn, false, CursorHit);
	
	LastHoverActor = CurrentHoverActor;
	/**
	 * If cursor hit something
	 *   - If the hit actor implements the IEnemyInterface, set the hit actor as the current hover actor
	 *   - If not, set the current hover actor to nullptr
	 * If cursor does not hit anything, set the current hover actor to nullptr
	 */
	if (CursorHit.bBlockingHit)
	{
		CurrentHoverActor = CursorHit.GetActor()->Implements<UEnemyInterface>() ? CursorHit.GetActor() : nullptr;
	}
	else
	{
		CurrentHoverActor = nullptr;
	}

	/**
	 *
	 * There are four cases to consider:
	 * Case A: LastHoverActor is nullptr and CurrentHoverActor is nullptr
	 *	- Do nothing
	 * Case B: LastHoverActor is nullptr and CurrentHoverActor is not nullptr
	 *  - Call HighLightActor on CurrentHoverActor
	 * Case C: LastHoverActor is not nullptr and CurrentHoverActor is nullptr
	 *  - Call UnHighLightActor on LastHoverActor
	 * Case D: LastHoverActor is not nullptr and CurrentHoverActor is not nullptr
	 *  - If LastHoverActor is not equal to CurrentHoverActor
	 *	 -- Call UnHighLightActor on LastHoverActor
	 *	 -- Call HighLightActor on CurrentHoverActor
	 *	- If LastHoverActor is equal to CurrentHoverActor
	 *	 -- Do nothing
	 */
	if (LastHoverActor)
	{
		if (CurrentHoverActor)
		{
			if (LastHoverActor != CurrentHoverActor)
			{
				IEnemyInterface::Execute_UnHighLightActor(LastHoverActor);
				IEnemyInterface::Execute_HighLightActor(CurrentHoverActor);
			}
			else
			{
				// Do nothing
			}
		}
		else
		{
			IEnemyInterface::Execute_UnHighLightActor(LastHoverActor);
		}
	}
	else
	{
		if (CurrentHoverActor)
		{
			IEnemyInterface::Execute_HighLightActor(CurrentHoverActor);
		}
		else
		{
			// Do nothing
		}
	}
}
