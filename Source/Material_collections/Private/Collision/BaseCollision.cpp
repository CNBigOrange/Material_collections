// Fill out your copyright notice in the Description page of Project Settings.


#include "Collision/BaseCollision.h"

// Sets default values
ABaseCollision::ABaseCollision()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	box = CreateDefaultSubobject<UBoxComponent>(TEXT("BOX"));
	box->InitBoxExtent(FVector(200.0f, 200.0f, 200.0f));

	//box->OnComponentBeginOverlap

}

// Called when the game starts or when spawned
void ABaseCollision::BeginPlay()
{
	Super::BeginPlay();
	
}

bool ABaseCollision::OnComponetOverlap()
{
	if (box)
	{
		UE_LOG(LogTemp,Display, TEXT("BeginOverlap"));
	}
	return false;
}

// Called every frame
void ABaseCollision::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

