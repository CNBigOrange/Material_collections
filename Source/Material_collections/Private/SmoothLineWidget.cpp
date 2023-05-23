// Fill out your copyright notice in the Description page of Project Settings.


#include "SmoothLineWidget.h"
#include "Components/CanvasPanelSlot.h"

void USmoothLineWidget::SetValues(TArray<float> InValues)
{
	if (InValues.Num() < 2)
		return;

	MultiplyPoints.Empty();
	/*将空间Slot转换为画布Slot*/
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(this->Slot);
	if (!CanvasPanelSlot)
		return;

	/*获取控件插槽的宽度和高度*/
	float WidgetWidth = CanvasPanelSlot->GetSize().X;
	float WidgetHeight = CanvasPanelSlot->GetSize().Y;

	float Space = WidgetWidth / (InValues.Num() - 1);

	for (int32 Index = 0; Index < InValues.Num(); Index++)
	{
		FVector2D KeyPosition(Space * Index, WidgetHeight - InValues[Index]);
		MultiplyPoints.Add(KeyPosition);
	}
}

int32 USmoothLineWidget::NativePaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled) const
{
	DrawSmoothedLine(
		OutDrawElements,
		LayerId,
		AllottedGeometry,
		MultiplyPoints,
		1.0f,
		FColor::Red);

	return LayerId;
}

void USmoothLineWidget::DrawSmoothedLine(FSlateWindowElementList& OutDrawElement,
	int32 InLayerID, const FGeometry& InAllottedGeometry, TArray<FVector2D> InPoints,
	float InThickness, FColor InColor) const
{
	if (InPoints.Num() < 2)
		return;
	/*富曲线*/
	FRichCurve* RichCurve = new FRichCurve();
	//TSharedPtr<FRichCurve> RichCurve;
	
	for (FVector2D InPoint : InPoints)
	{
		/*AddKey返回一个FKeyHandle，可以指定插值方式*/
		/*关键点被放进了富曲线里面*/
		FKeyHandle KeyHandle = RichCurve->AddKey(InPoint.X, InPoint.Y);
		RichCurve->SetKeyInterpMode(KeyHandle, ERichCurveInterpMode::RCIM_Cubic);
	}

	/*将空间Slot转换为画布Slot*/
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(this->Slot);
	if (!CanvasPanelSlot)
		return;

	TArray<FVector2D> ResultPoints;

	/*获取控件插槽的宽度和高度*/
	float WidgetWidth = CanvasPanelSlot->GetSize().X;

	int32 Begin = 0;
	int32 End = WidgetWidth;
	for (int32 X = Begin; X < End; X++)
	{
		/*计算每一个Y值*/
		int32 Y = RichCurve->Eval(X);

		FVector2D ResultPoint(X, Y);
		ResultPoints.Add(ResultPoint);
	}
	
	delete RichCurve;

	FSlateDrawElement::MakeLines(
		OutDrawElement,
		InLayerID,
		InAllottedGeometry.ToPaintGeometry(),
		ResultPoints,
		ESlateDrawEffect::None,
		InColor,
		true,
		InThickness
	);
}
