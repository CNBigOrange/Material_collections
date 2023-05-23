// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SmoothLineWidget.generated.h"

/**
 * 
 */
UCLASS()
class MATERIAL_COLLECTIONS_API USmoothLineWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
		void SetValues(TArray<float> InValues);
	
protected:

	virtual int32 NativePaint(const FPaintArgs& Args,
		const FGeometry& AllottedGeometry,
		const FSlateRect& MyCullingRect,
		FSlateWindowElementList& OutDrawElements,
		int32 LayerId, const FWidgetStyle& InWidgetStyle,
		bool bParentEnabled) const override;

private:
	UPROPERTY()
		TArray<FVector2D> MultiplyPoints;

	void DrawSmoothedLine(
		FSlateWindowElementList& OutDrawElement,
		int32 InLayerID,
		const FGeometry& InAllottedGeometry,
		TArray<FVector2D> InPoints,
		float InThickness,
		FColor InColor
	)const;
};
