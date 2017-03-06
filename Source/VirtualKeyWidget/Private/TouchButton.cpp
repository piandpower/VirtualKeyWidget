// Fill out your copyright notice in the Description page of Project Settings.

#include "VirtualKeyWidgetPrivatePCH.h"
#include "TouchButton.h"
#include "STouchButton.h"





UTouchButton::UTouchButton(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	IsFocusable = false;
}

TSharedRef<SWidget> UTouchButton::RebuildWidget()
{
	MyButton = SNew(STouchButton)
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
