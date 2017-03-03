// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "VirtualKeyWidgetPrivatePCH.h"
#include "SVirtualKeyButton.h"



FReply SVirtualKeyButton::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	FReply Reply = FReply::Handled();
	if (MouseEvent.IsTouchEvent())
	{	// button event called twice in windows touch screen.
		Reply = SButton::OnMouseButtonDown(MyGeometry, MouseEvent);
	}

	if (Reply.IsEventHandled())
	{
		TSharedPtr<SWidget> FocusedWidget = FSlateApplicationBase::Get().GetKeyboardFocusedWidget();
		if (FocusedWidget.IsValid())
		{
			Reply = Reply.SetUserFocus(FocusedWidget.ToSharedRef());
		}
	}

	return Reply;
}
