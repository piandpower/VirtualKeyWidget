// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "VirtualKeyWidgetPrivatePCH.h"
#include "STouchButton.h"



FReply STouchButton::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsTouchEvent())
	{	// button event called twice in windows touch screen.
		return SButton::OnMouseButtonDown(MyGeometry, MouseEvent);
	}

	return FReply::Unhandled();
}
