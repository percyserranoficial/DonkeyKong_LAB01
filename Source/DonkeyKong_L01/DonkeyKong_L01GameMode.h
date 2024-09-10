// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DonkeyKong_L01GameMode.generated.h"

class AObstaculo;
class AComponentePlataforma;
class ADonkeyKong_L01Character;
class ABarril;
class AEnemigo;
class ABomba;

UCLASS(minimalapi)
class ADonkeyKong_L01GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADonkeyKong_L01GameMode();
protected:
	virtual void BeginPlay() override;

	//void CrearPlataformaDinamica();
public:
	AObstaculo* obstaculo01;
	ADonkeyKong_L01Character* player01;
	/*AComponentePlataforma* cp01;
	AComponentePlataforma* cp02;
	AComponentePlataforma* cp03;
	AComponentePlataforma* cp04;
	AComponentePlataforma* cp05;*/
	//ABarril* barril01;

	TMap<int32, AComponentePlataforma*> componentesPlataformaMap; //TMAP QUE CONTIENE A LOS COMPONENTES DE PLATAFORMA
	TArray<ABarril*> barriles;
	TArray<AEnemigo*> enemigos;

public:
	void SpawnBarril();
	void SpawnEnemigo();
private:
	FTimerHandle SpawnBarrilTimerHandle;
	int numeroBarriles;

	FTimerHandle SpawnEnemigoTimerHandle;
	int numeroEnemigos;
};



