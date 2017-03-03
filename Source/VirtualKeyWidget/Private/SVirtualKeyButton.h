// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SButton.h"

class VIRTUALKEYWIDGET_API SVirtualKeyButton : public SButton
{
public:

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

};