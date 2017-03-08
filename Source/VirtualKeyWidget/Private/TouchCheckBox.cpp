// Fill out your copyright notice in the Description page of Project Settings.

#include "VirtualKeyWidgetPrivatePCH.h"
#include "TouchCheckBox.h"
#include "STouchCheckBox.h"





UTouchCheckBox::UTouchCheckBox(const FObjectInitializer& InObjectInitializer)
	: Super(InObjectInitializer)
{
	IsFocusable = false;
}

TSharedRef<SWidget> UTouchCheckBox::RebuildWidget()
{
	MyCheckbox = SNew(STouchCheckBox)
		.OnCheckStateChanged(BIND_UOBJECT_DELEGATE(FOnCheckStateChanged, SlateOnCheckStateChangedCallback))
		.Style(&WidgetStyle)
		.HAlign(HorizontalAlignment)
		.IsFocusable(IsFocusable)
		;

	if (GetChildrenCount() > 0)
	{
		MyCheckbox->SetContent(GetContentSlot()->Content ? GetContentSlot()->Content->TakeWidget() : SNullWidget::NullWidget);
	}

	return MyCheckbox.ToSharedRef();
}
