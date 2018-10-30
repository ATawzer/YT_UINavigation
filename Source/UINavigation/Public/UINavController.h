// Copyright (C) 2018 Gon�alo Marques - All Rights Reserved

#pragma once

#include "Engine.h"
#include "GameFramework/PlayerController.h"
#include "UINavController.generated.h"

UENUM(BlueprintType)
enum class EInputType : uint8
{
	None UMETA(DisplayName = "None"),
	Keyboard UMETA(DisplayName = "Keyboard"),
	Mouse UMETA(DisplayName = "Mouse"),
	Gamepad UMETA(DisplayName = "Gamepad")
};

UENUM(BlueprintType)
enum class EInputDirection : uint8
{
	None UMETA(DisplayName = "None"),
	Up UMETA(DisplayName = "Up"),
	Down UMETA(DisplayName = "Down"),
	Left UMETA(DisplayName = "Left"),
	Right UMETA(DisplayName = "Right")
};

UENUM(BlueprintType)
enum class ECountdownPhase : uint8
{
	None UMETA(DisplayName = "None"),
	First UMETA(DisplayName = "First"),
	Looping UMETA(DisplayName = "Looping")
};

/**
 * This class contains the logic for input-related actions with UINavWidgets
 */
UCLASS()
class UINAVIGATION_API AUINavController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(BlueprintReadOnly)
		class UUINavWidget* ActiveWidget;

	UPROPERTY(BlueprintReadOnly)
		EInputType CurrentInputType = EInputType::Keyboard;

	TMap<FString, TArray<FKey>> KeyMap = TMap<FString, TArray<FKey>>();

	EInputDirection Direction = EInputDirection::None;

	float PreviousX = -1.f;
	float PreviousY = -1.f;

	/*
	Indicates whether navigation will occur periodically after the player
	holds down a navigation key
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
		bool bChainNavigation = true;

	/*
	The amount of time the player needs to hold a key for the navigation to
	start occuring periodically
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float InputHeldWaitTime = 0.5f;

	/*
	The amount of time that passes before the navigation chains further
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float NavigationChainFrequency = 0.2f;

	ECountdownPhase CountdownPhase = ECountdownPhase::None;

	EInputDirection CallbackDirection;
	float TimerCounter = 0.f;

	/*************************************************************************/

	void TimerCallback();

	/**
	*	Searches all the Input Actions relevant to UINav plugin and saves them in a map
	*/
	void FetchUINavActionKeys();

	/**
	*	Returns the input type of the given key
	*
	*	@param Key The specified key	
	*	@return The input type of the given key
	*/
	EInputType GetKeyInputType(FKey Key);

	/**
	*	Returns the input type of the given action
	*
	*	@return The input type of the given action
	*/
	EInputType GetActionInputType(FString Action);

	/**
	*	Verifies if a new input type is being used
	*
	*	@param Key The specified key
	*	@param PressedKey The pressed key
	*/
	void VerifyInputTypeChangeByKey(FKey Key);

	/**
	*	Verifies if a new input type is being used
	*
	*	@param Action The specified action
	*/
	void VerifyInputTypeChangeByAction(FString Action);

	/**
	*	Notifies to the active UUINavWidget that the input type changed
	*
	*	@param NewInputType The new input type that is being used
	*/
	void NotifyInputTypeChange(EInputType NewInputType);

	/**
	*	Notifies to the active UUINavWidget that the input type changed
	*
	*	@param Action The action's name
	*	@param bPressed Whether the action was pressed or released
	*/
	void ExecuteActionByName(FString Action, bool bPressed);

	/**
	*	Traverses the key map to find the action name associated with the given key
	*
	*	@param PressedKey The pressed key
	*	@param bPressed Whether the action was pressed or released
	*/
	void FindActionByKey(FKey PressedKey, bool bPressed);

	virtual void SetupInputComponent() override;
	virtual void Possess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

public:

	/**
	*	Checks whether a gamepad is connected
	*
	*	@return Whether a gamepad is connected
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UINavigation")
		bool IsGamepadConnected();

	/**
	*	Notifies the controller that a mouse is being used
	*/
	void NotifyMouseInputType();

	/**
	*	Notifies the controller that the given key was just pressed
	*
	*	@param PressedKey The pressed key
	*/
	void NotifyKeyPressed(FKey PressedKey);

	/**
	*	Notifies the controller that the given key was just released
	*
	*	@param ReleasedKey The released key
	*/
	void NotifyKeyReleased(FKey ReleasedKey);

	/**
	*	Indicates whether the pressed key is associated with the return action
	*
	*	@param PressedKey The pressed key
	*/
	bool IsReturnKey(FKey PressedKey);

	/**
	*	Changes the widget this PC will communicate with
	*
	*	@param NewWidget The new active widget
	*/
	UFUNCTION(BlueprintCallable, Category = "UINavigation")
		void SetActiveWidget(class UUINavWidget* NewWidget);

	UFUNCTION(BlueprintNativeEvent, Category = "UINavigation")
		void OnRootWidgetRemoved();
	void OnRootWidgetRemoved_Implementation();

	void SetTimer(EInputDirection TimerDirection);
	void ClearTimer();

	void MenuUp();
	void MenuDown();
	void MenuLeft();
	void MenuRight();
	void MenuSelect();
	void MenuReturn();

	void MenuUpRelease();
	void MenuDownRelease();
	void MenuLeftRelease();

	void MouseInputWorkaround();

	void StartMenuUp();
	void StartMenuDown();
	void StartMenuLeft();
	void StartMenuRight();
	void MenuRightRelease();

	FORCEINLINE EInputType GetCurrentInputType() const { return CurrentInputType; }

	FORCEINLINE UUINavWidget* GetActiveWidget() const { return ActiveWidget; }

	FORCEINLINE TMap<FString, TArray<FKey>> GetKeyMap() const { return KeyMap; }

	
};
