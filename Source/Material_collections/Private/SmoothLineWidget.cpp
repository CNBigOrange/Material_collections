// Fill out your copyright notice in the Description page of Project Settings.


#include "SmoothLineWidget.h"
#include "Components/CanvasPanelSlot.h"

void USmoothLineWidget::SetValues(TArray<float> InValues)
{
	if (InValues.Num() < 2)
		return;

	MultiplyPoints.Empty();
	/*���ռ�Slotת��Ϊ����Slot*/
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(this->Slot);
	if (!CanvasPanelSlot)
		return;

	/*��ȡ�ؼ���۵Ŀ�Ⱥ͸߶�*/
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
	/*������*/
	FRichCurve* RichCurve = new FRichCurve();
	//TSharedPtr<FRichCurve> RichCurve;
	
	for (FVector2D InPoint : InPoints)
	{
		/*AddKey����һ��FKeyHandle������ָ����ֵ��ʽ*/
		/*�ؼ��㱻�Ž��˸���������*/
		FKeyHandle KeyHandle = RichCurve->AddKey(InPoint.X, InPoint.Y);
		RichCurve->SetKeyInterpMode(KeyHandle, ERichCurveInterpMode::RCIM_Cubic);
	}

	/*���ռ�Slotת��Ϊ����Slot*/
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(this->Slot);
	if (!CanvasPanelSlot)
		return;

	TArray<FVector2D> ResultPoints;

	/*��ȡ�ؼ���۵Ŀ�Ⱥ͸߶�*/
	float WidgetWidth = CanvasPanelSlot->GetSize().X;

	int32 Begin = 0;
	int32 End = WidgetWidth;
	for (int32 X = Begin; X < End; X++)
	{
		/*����ÿһ��Yֵ*/
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
