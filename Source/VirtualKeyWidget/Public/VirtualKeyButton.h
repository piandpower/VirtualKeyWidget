// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
class VIRTUALKEYWIDGET_API UVirtualKeyButton : public UButton
{
	GENERATED_UCLASS_BODY()
		
public:

	UFUNCTION(BlueprintCallable, Category = "VirtualKey")
	static EKeyboardIME GetKeyboardIME();

	UPROPERTY(EditAnywhere, Category = "VirtualKey")
	FString InputKey;
	UPROPERTY(EditAnywhere, Category = "VirtualKey")
	FString InputKeyWithShift;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VirtualKey")
	bool bIsShift;

protected:

	UFUNCTION()
	void OnPressedVirtualKey();
	UFUNCTION()
	void OnReleasedVirtualKey();

	TWeakPtr<SWidget> PreviousFocusedWidget;
	
};
