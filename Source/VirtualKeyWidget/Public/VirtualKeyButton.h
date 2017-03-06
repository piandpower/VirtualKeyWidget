// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tickable.h"
#include "Components/ContentWidget.h"
#include "Components/Button.h"
#include "VirtualKeyButton.generated.h"

UENUM(BlueprintType)
enum class EKeyboardIME
{
	Alphanumeric,
	Hangul,
};
/**
 * 
 */
UCLASS()
class VIRTUALKEYWIDGET_API UVirtualKeyButton : public UButton, public FTickableGameObject
{
	GENERATED_UCLASS_BODY()
		
public:

	virtual ~UVirtualKeyButton();

	UFUNCTION(BlueprintCallable, Category = "VirtualKey")
	static EKeyboardIME GetKeyboardIME();

	//~ Begin FTickableGameObject Interfaces
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	//~ End FTickableGameObject Interfaces

	UPROPERTY(EditAnywhere, Category = "VirtualKey")
	FString InputKey;
	UPROPERTY(EditAnywhere, Category = "VirtualKey")
	FString InputKeyWithShift;
	
	UPROPERTY(EditAnywhere, Category = "VirtualKey")
	float KeepInputDelay;
	UPROPERTY(EditAnywhere, Category = "VirtualKey")
	float KeepInputTerm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VirtualKey")
	bool bIsShift;

protected:

	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface
	
	UFUNCTION()
	void OnClickedVirtualKey();
	UFUNCTION()
	void OnPressedVirtualKey();
	UFUNCTION()
	void OnReleasedVirtualKey();
	
	float PressTime;
};
