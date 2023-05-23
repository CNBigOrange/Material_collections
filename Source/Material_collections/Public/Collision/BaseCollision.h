// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BaseCollision.generated.h"

UCLASS()
class MATERIAL_COLLECTIONS_API ABaseCollision : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseCollision();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
		bool OnComponetOverlap();

	//FComponentBeginOverlapSignature OnComponentBeginOverlap;

	UPROPERTY(BlueprintReadWrite,EditAnyWhere)
		class UBoxComponent* box;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
