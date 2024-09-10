// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomba.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
ABomba::ABomba()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshBomba = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMeshComponent"));//(4)

	// Set the mesh for the component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));//(4)
	if (MeshAsset.Succeeded())//(4)
	{
		MeshBomba->SetStaticMesh(MeshAsset.Object);
	}

	MeshBomba->SetSimulatePhysics(true);
}

// Called when the game starts or when spawned
void ABomba::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABomba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

