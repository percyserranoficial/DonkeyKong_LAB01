// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_L01GameMode.h"
#include "DonkeyKong_L01Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Obstaculo.h"
#include "DonkeyKong_L01Character.h"
#include "ComponentePlataforma.h"
#include "Barril.h"
#include "Enemigo.h"
#include "Bomba.h"//(2)

ADonkeyKong_L01GameMode::ADonkeyKong_L01GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
	obstaculo01 = nullptr;
	player01 = nullptr;
	numeroBarriles = 0;
	numeroEnemigos=0;

	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
		player01 = Cast<ADonkeyKong_L01Character>(PlayerPawnBPClass.Class);
	}
	//NumeroDePisos = 5;  // Al menos 5 pisos
	//ComponentesPorPiso = 3;  // Al menos 3 componentes por piso
}

void ADonkeyKong_L01GameMode::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Yellow, TEXT("Actor Spawning"));
	// Spawn an instance of the AMyFirstActor class at the
	//default location.
	FTransform SpawnLocation;
	SpawnLocation.SetLocation(FVector(1160.0f, -210.0f, 140.0f));
	SpawnLocation.SetRotation(FQuat(FRotator(0.0f, 0.0f, 0.0f)));
	obstaculo01 = GetWorld()->SpawnActor<AObstaculo>(AObstaculo::StaticClass(), SpawnLocation);
	if (player01 != nullptr)
	{
		player01->SetObstaculo(obstaculo01);
	}

	FVector posicionInicial = FVector(1160.0f, -1100.0f, 400.f);
	FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
	FTransform SpawnLocationCP;
	float anchoComponentePlataforma = 600.0f;
	float incrementoAltoComponentePlataforma = -105.0f;
	float incrementoAltoEntrePisos = 800.0f;
	float incrementoInicioPiso = 100.0f;

	int32 plataformaIndex = 0;


	for (int npp = 0; npp < 5; npp++) {
		rotacionInicial.Roll = rotacionInicial.Roll * -1;
		incrementoInicioPiso = incrementoInicioPiso * -1;
		incrementoAltoComponentePlataforma = incrementoAltoComponentePlataforma * -1;
		SpawnLocationCP.SetRotation(FQuat(rotacionInicial));

		for (int ncp = 0; ncp < 5; ncp++) {
			SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoComponentePlataforma * ncp, posicionInicial.Z));

			AComponentePlataforma* nuevaPlataforma = GetWorld()->SpawnActor<AComponentePlataforma>(AComponentePlataforma::StaticClass(), SpawnLocationCP);

			componentesPlataformaMap.Add(plataformaIndex, nuevaPlataforma);
			plataformaIndex++;

			if (ncp < 4) {
				posicionInicial.Z = posicionInicial.Z + incrementoAltoComponentePlataforma;
			}
		}

		posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
		posicionInicial.Y = posicionInicial.Y + incrementoInicioPiso;
	}

	//SpawnBarril();
	GetWorldTimerManager().SetTimer(SpawnBarrilTimerHandle, this, &ADonkeyKong_L01GameMode::SpawnBarril, 5.0f, true);
	//SpawnLocation.SetLocation(FVector(1160.0f, 550.0f, 800.0f));
	//SpawnLocation.SetRotation(FQuat(FRotator(90.0f, 0.0f, 0.0f)));
	//barril01 = GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), SpawnLocation);
	GetWorldTimerManager().SetTimer(SpawnEnemigoTimerHandle, this, &ADonkeyKong_L01GameMode::SpawnEnemigo, 4.0f, true);

	FVector BombaSpawnLocation = FVector(1207, -516, 4500);  // Definir manualmente la ubicación
	FRotator BombaSpawnRotation = FRotator(0, 0, 0);        // Rotación inicial de la bomba
	GetWorld()->SpawnActor<ABomba>(ABomba::StaticClass(), BombaSpawnLocation, BombaSpawnRotation);

}



void ADonkeyKong_L01GameMode::SpawnBarril()
{
	if (numeroBarriles < 5) {

		// Definir la ubicación y rotación para el nuevo barril
		FVector SpawnLocation = FVector(1160.0f, 550.0f, 800.0f); // Ajusta según sea necesario
		FRotator SpawnRotation = FRotator(90.0f, 0.0f, 0.0f);

		// Crear el actor barril
		barriles.Add(GetWorld()->SpawnActor<ABarril>(ABarril::StaticClass(), SpawnLocation, SpawnRotation));
		numeroBarriles++;
	}
}

void ADonkeyKong_L01GameMode::SpawnEnemigo()
{
	if (numeroEnemigos < 10) {

		// Definir la ubicación y rotación para el nuevo barril
		FVector SpawnLocation = FVector(1200.0f, -550.0f, 2000.0f); // Ajusta según sea necesario
		FRotator SpawnRotation = FRotator(180.0f, 0.0f, 0.0f);

		// Crear el actor barril
		enemigos.Add(GetWorld()->SpawnActor<AEnemigo>(AEnemigo::StaticClass(), SpawnLocation, SpawnRotation));
		numeroEnemigos++;
	}
}

/*void ADonkeyKong_L01GameMode::CrearPlataformaDinamica()
{
	FVector posicionInicial = FVector(1000.0f, 500.0f, 200.0f);  // Posición base de la plataforma
	FRotator rotacionInicial = FRotator(0.0f, 0.0f, 0.0f);
	float SeparacionHorizontal = 500.0f;  // Separación entre componentes en el mismo piso
	float SeparacionVertical = 400.0f;    // Separación entre pisos

	for (int32 Piso = 0; Piso < NumeroDePisos; ++Piso)
	{
		TArray<AComponentePlataforma*> ComponentesDelPiso;

		for (int32 Componente = 0; Componente < ComponentesPorPiso; ++Componente)
		{
			FVector Location = posicionInicial + FVector(0.0f, Componente * SeparacionHorizontal, Piso * SeparacionVertical);

			// Usamos el constructor correcto de FTransform: primero rotación (convertida a FQuat) y luego ubicación
			FTransform Transform(FQuat(rotacionInicial), Location);

			AComponentePlataforma* NuevoComponente = GetWorld()->SpawnActor<AComponentePlataforma>(AComponentePlataforma::StaticClass(), Transform);

			if (NuevoComponente)
			{
				// Configurar movimiento
				NuevoComponente->Movimiento = FVector(50.0f, 200.0f, 100.0f);  // Movimiento hacia arriba y abajo
				NuevoComponente->RangoMovimiento = 100.0f;  // Rango de movimiento

				ComponentesDelPiso.Add(NuevoComponente);  // Agregar a la lista de componentes del piso
			}
		}

		PlataformasPorPiso.Add(Piso, ComponentesDelPiso);
	}
}*/