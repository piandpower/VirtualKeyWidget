// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "VirtualKeyWidgetPrivatePCH.h"
#include "STouchCheckBox.h"



FReply STouchCheckBox::OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	if (MouseEvent.IsTouchEvent())
	{	// button event called twice in windows touch screen.
		return SCheckBox::OnMouseButtonDown(MyGeometry, MouseEvent);
	}

	return FReply::Unhandled();
}
