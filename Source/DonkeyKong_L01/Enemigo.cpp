// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemigo.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

// Sets default values
AEnemigo::AEnemigo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> EnemigoMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_QuadPyramid.Shape_QuadPyramid'"));
	EnemigoMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrilMesh"));
	RootComponent = EnemigoMesh;
	EnemigoMesh->SetStaticMesh(EnemigoMeshAsset.Object);

	EnemigoMesh->SetSimulatePhysics(true);
	EnemigoMesh->SetMobility(EComponentMobility::Movable);
}

// Called when the game starts or when spawned
void AEnemigo::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemigo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

