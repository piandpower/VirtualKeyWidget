// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "SCheckBox.h"

class VIRTUALKEYWIDGET_API STouchCheckBox : public SCheckBox
{
public:

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;

};