// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ComponentePlataforma.generated.h"

class UStaticMeshComponent;

UCLASS()
class DONKEYKONG_L01_API AComponentePlataforma : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AComponentePlataforma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//PROPERTY(EditAnywhere, Category = "Mesh")
	UStaticMeshComponent* meshPlataforma;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	//SE DECLARA LAS SIGUIENTES VARIABLES DE TIPO FVECTOR
	FVector posicionInicial;
	FVector posicionActual;
	FVector posicionFinal;
	FVector incremento;
	//Y OTRA DE TIPO FROTATOR
	FRotator incrementoRotacion;

	//SE DECLARAN LAS SIGUIENTES VARIABLES DE TIPO BOOLEANO PARA EL MOVIMIENTO DE LAS PLATAFORMAS
	bool moverArribaAbajo;
	bool moverIzquierdaDerecha;
	bool moverAdelanteAtras;
	bool rotarZ;
	bool detener;
public:
	//SE DECLARAN LOS SIGUIENTES METODOS
	void setIncremento(FVector nuevoIncremento);
	void setIncrementoRotacion(FRotator nuevoIncrementoRotacion);
	void setDetener(bool _detener);
	void GenerarMovimientoAleatorio();
};
