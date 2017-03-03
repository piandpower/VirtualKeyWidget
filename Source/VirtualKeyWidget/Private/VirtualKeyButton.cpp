// Fill out your copyright notice in the Description page of Project Settings.

#include "VirtualKeyWidgetPrivatePCH.h"
#include "VirtualKeyButton.h"
#include "SVirtualKeyButton.h"





UVirtualKeyButton::UVirtualKeyButton(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	OnClicked.AddDynamic(this, &UVirtualKeyButton::OnClickedVirtualKey);

	IsFocusable = false;
}

EKeyboardIME UVirtualKeyButton::GetKeyboardIME()
{
	HIMC himc;
	unsigned long dwConversion = 0, dwSentence = 0;
	himc = ImmGetContext((HWND)GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle());
	if (himc)
	{
		ImmSetOpenStatus(himc, true);
		ImmGetConversionStatus(himc, &dwConversion, &dwSentence);
	}
	if (dwConversion & IME_CMODE_HANGUL)
	{
		return EKeyboardIME::Hangul;
	}
	else
	{
		return EKeyboardIME::Alphanumeric;
	}
}

TSharedRef<SWidget> UVirtualKeyButton::RebuildWidget()
{
	MyButton = SNew(SVirtualKeyButton)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleClicked))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandlePressed))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleReleased))
		.OnHovered_UObject(this, &ThisClass::SlateHandleHovered)
		.OnUnhovered_UObject(this, &ThisClass::SlateHandleUnhovered)
		.ButtonStyle(&WidgetStyle)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.IsFocusable(IsFocusable)
		;

	if (GetChildrenCount() > 0)
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
	}

	return MyButton.ToSharedRef();
}

void UVirtualKeyButton::OnClickedVirtualKey()
{
	FString TargetKey;
	if (bIsShift)
	{
		TargetKey = InputKeyWithShift;
	}
	else
	{
		TargetKey = InputKey;
	}
	if (TargetKey.IsEmpty())
	{
		return;
	}
	uint32 PressedKey = FParse::HexNumber(*TargetKey);
	if (PressedKey == 0)
	{
		return;
	}

	if (bIsShift)
	{
		INPUT ShiftInput;
		ShiftInput.type = INPUT_KEYBOARD;
		ShiftInput.ki.wScan = 0;
		ShiftInput.ki.time = 0;
		ShiftInput.ki.dwExtraInfo = 0;
		ShiftInput.ki.dwFlags = 0;
		ShiftInput.ki.wVk = 0x10;
		SendInput(1, &ShiftInput, sizeof(INPUT));
	}

	INPUT KeyInput;
	KeyInput.type = INPUT_KEYBOARD;
	KeyInput.ki.wScan = 0;
	KeyInput.ki.time = 0;
	KeyInput.ki.dwExtraInfo = 0;
	KeyInput.ki.dwFlags = 0;
	KeyInput.ki.wVk = PressedKey;
	SendInput(1, &KeyInput, sizeof(INPUT));

	KeyInput.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &KeyInput, sizeof(INPUT));

	if (bIsShift)
	{
		INPUT ShiftInput;
		ShiftInput.type = INPUT_KEYBOARD;
		ShiftInput.ki.wScan = 0;
		ShiftInput.ki.time = 0;
		ShiftInput.ki.dwExtraInfo = 0;
		ShiftInput.ki.dwFlags = KEYEVENTF_KEYUP;
		ShiftInput.ki.wVk = 0x10;
		SendInput(1, &ShiftInput, sizeof(INPUT));
	}
	/*
	HIMC himc;
	unsigned long dwConversion, dwSentence;
	himc = ImmGetContext((HWND)GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle());
	if (himc)
	{
		ImmSetOpenStatus(himc, true);
		ImmGetConversionStatus(himc, &dwConversion, &dwSentence);

		if (dwConversion & IME_CMODE_HANGUL)
		{
			// 한글 입력기 상태

			// 영어로 변환
			dwConversion = IME_CMODE_ALPHANUMERIC;
		}
		else
		{
			// 영어 입력기 상태

			// 한글로 변환
			dwConversion = IME_CMODE_HANGUL;
		}
		ImmSetConversionStatus(himc, dwConversion, dwSentence);
		ImmReleaseContext((HWND)GEngine->GameViewport->GetWindow()->GetNativeWindow()->GetOSWindowHandle(), himc);
	}
	else
	{
		// 입력 불가 상태
	}
	*/
}