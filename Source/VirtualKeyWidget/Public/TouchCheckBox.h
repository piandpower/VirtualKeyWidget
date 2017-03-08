// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ContentWidget.h"
#include "Components/CheckBox.h"
#include "TouchCheckBox.generated.h"

/**
 * 
 */
UCLASS()
class VIRTUALKEYWIDGET_API UTouchCheckBox : public UCheckBox
{
	GENERATED_UCLASS_BODY()
		
protected:

	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;
	//~ End UWidget Interface
};
