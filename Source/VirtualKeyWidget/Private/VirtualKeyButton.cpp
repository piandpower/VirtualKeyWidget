// Fill out your copyright notice in the Description page of Project Settings.

#include "VirtualKeyWidgetPrivatePCH.h"
#include "VirtualKeyButton.h"





UVirtualKeyButton::UVirtualKeyButton(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
	, PreviousFocusedWidget(nullptr)
{
	OnPressed.AddDynamic(this, &UVirtualKeyButton::OnPressedVirtualKey);
	OnReleased.AddDynamic(this, &UVirtualKeyButton::OnReleasedVirtualKey);
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

void UVirtualKeyButton::OnPressedVirtualKey()
{
	PreviousFocusedWidget = FSlateApplicationBase::Get().GetKeyboardFocusedWidget();
}

void UVirtualKeyButton::OnReleasedVirtualKey()
{
	auto d = FSlateApplicationBase::Get().GetKeyboardFocusedWidget();
	if (PreviousFocusedWidget.IsValid())
	{
		FSlateApplication::Get().ClearKeyboardFocus(EFocusCause::SetDirectly);
		FSlateApplication::Get().SetKeyboardFocus(PreviousFocusedWidget.Pin());
	}

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

	INPUT ip;
	ip.type = INPUT_KEYBOARD;
	ip.ki.wScan = 0;
	ip.ki.time = 0;
	ip.ki.dwExtraInfo = 0;
	ip.ki.dwFlags = 0;
	ip.ki.wVk = PressedKey;
	SendInput(1, &ip, sizeof(INPUT));

	ip.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &ip, sizeof(INPUT));

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