// Fill out your copyright notice in the Description page of Project Settings.


#include "ComponentePlataforma.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/UnrealMathUtility.h" //SE INCLUYE LA LIBRERIA MATH PARA GENERAR NUMEROS ALEATORIOS Y NUMEROS ALEATORIOS DENTRO DE UN DETERMINADO RANGO


// Sets default values
AComponentePlataforma::AComponentePlataforma()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Geometry/Meshes/1M_Cube.1M_Cube'"));

	meshPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	meshPlataforma->SetStaticMesh(MeshAsset.Object);
	RootComponent = meshPlataforma;
	
	FVector NewScale(2.0f, 6.0f, 0.5f); // Cambia estos valores según tus necesidades
	SetActorScale3D(NewScale);

	//EN EL CONSTRUCTOR SE INICIALIZAN LAS VARIABLES BOOLEANASPARA CONTROLAR EL COMPORTAMIENTO DEL ACTOR
	PrimaryActorTick.bCanEverTick = true;
	moverArribaAbajo = false;
	moverIzquierdaDerecha = false;
	moverAdelanteAtras = false;
	rotarZ = false;
	detener = false;

}

// Called when the game starts or when spawned
void AComponentePlataforma::BeginPlay()
{
	Super::BeginPlay();
	
	posicionInicial = GetActorLocation();
	posicionActual = posicionInicial;

	GenerarMovimientoAleatorio(); //FUNCION PARA ASIGNAR A LAS PLATAFORMAS UN MOVIMIENTO ALEATORIO
}

// Called every frame
void AComponentePlataforma::Tick(float DeltaTime)
{
	//ACA ESTA LA LOGICA DE MOVIMIENTO QUE TENDRAN LAS PLATAFORMAS TANTO EN EJE X,Y,Z Y ROTACION SOBRE SU PROPIO EJE
	Super::Tick(DeltaTime);
	if (!detener) {
		// Movimiento en el eje Z (arriba/abajo)
		if (moverArribaAbajo)
		{
			posicionActual.Z += incremento.Z;

			if (posicionActual.Z >= posicionFinal.Z || posicionActual.Z <= posicionInicial.Z)
			{
				incremento.Z *= -1;  // Cambiar dirección cuando alcanza los límites
			}

			SetActorLocation(posicionActual);
		}


		// Movimiento en el eje Y (izquierda/derecha)
		if (moverIzquierdaDerecha)
		{
			posicionActual.Y += incremento.Y;

			if (posicionActual.Y >= posicionFinal.Y || posicionActual.Y <= posicionInicial.Y)
			{
				incremento.Y *= -1;  // Cambiar dirección cuando alcanza los límites
			}

			SetActorLocation(posicionActual);
		}
		
		// Movimiento en el eje X (adelante/atrás)
		if (moverAdelanteAtras)
		{
			posicionActual.X += incremento.X;

			if (posicionActual.X >= posicionFinal.X || posicionActual.X <= posicionInicial.X)
			{
				incremento.X *= -1;  // Cambiar dirección cuando alcanza los límites
			}

			SetActorLocation(posicionActual);
		}

		// Rotación
		if (rotarZ)
		{
			FRotator nuevaRotacion = GetActorRotation();
			nuevaRotacion.Yaw += incrementoRotacion.Yaw;  // Solo rotación en el eje Z (Yaw)
			SetActorRotation(nuevaRotacion);
		}
	

		// Actualizar la posición
		SetActorLocation(posicionActual);
	}
}

void AComponentePlataforma::GenerarMovimientoAleatorio() //EN ESTE METODO SE ASIGNA A CADA UNA DE LAS PLATAFORMAS 4 POSIBLES ESTADOS DE MOVIMIENTO, CON RESPECTO A EJE Z, Y,X y SIN MOVIMIENTO
{
	
	int tipoMovimiento = FMath::RandRange(0, 3);

	switch (tipoMovimiento)
	{
	case 0:  // Movimiento en eje Z (arriba/abajo)
	{
		float rangoMovimientoZ = FMath::RandRange(200.0f, 1000.0f);  // Rango aleatorio de 400 a 800 unidades en Z
		float velocidadMovimientoZ = FMath::RandRange(1.0f, 2.0f);  // Velocidad aleatoria en Z
		posicionFinal = posicionInicial + FVector(0.0f, 0.0f, rangoMovimientoZ);
		incremento = FVector(0.0f, 0.0f, velocidadMovimientoZ);
		moverArribaAbajo = true;  // Habilitar movimiento en Z
		break;
	}
	case 1:  // Movimiento en eje Y (izquierda/derecha)
	{
		float rangoMovimientoY = FMath::RandRange(-400.0f, 400.0f); // Rango aleatorio de -400 a 400 unidades en Y
		float velocidadMovimientoY = FMath::RandRange(1.0f, 2.0f);  // Velocidad aleatoria en Y
		posicionFinal = posicionInicial + FVector(0.0f, rangoMovimientoY, 0.0f);
		incremento = FVector(0.0f, velocidadMovimientoY, 0.0f);
		moverIzquierdaDerecha = true;  // Habilitar movimiento en Y
		break;
	}
	case 2: // Movimiento en eje X (adelante/atrás)
	{
		float rangoMovimientoX = FMath::RandRange(-300.0f, 600.0f); // Rango aleatorio de -400 a 400 unidades en X
		float velocidadMovimientoX = FMath::RandRange(1.0f, 2.0f);  // Velocidad aleatoria en X
		posicionFinal = posicionInicial + FVector(0.0f,rangoMovimientoX, 0.0f);
		incremento = FVector(0.0f, velocidadMovimientoX, 0.0f);
		moverAdelanteAtras = true;  // Habilitar movimiento en X
		break;
	}
	case 3:  // Rotación
	{
		float velocidadRotacionYaw = FMath::RandRange(0.1f, 2.0f);   // Velocidad de rotación alrededor del eje Z (Yaw)
		incrementoRotacion = FRotator(0.0f, velocidadRotacionYaw, 0.0f);
		rotarZ = true;  // Habilitar rotación en Z
		break;
	}
	default:
		break;
	}
}
//ESTE METODO AJUSTA LA VELOCIDAD Y DIRECCION DEL MOVIMIENTO DE LAS PLATAFORMAS EN X,Y,Z
void AComponentePlataforma::setIncremento(FVector nuevoIncremento)
{
	incremento = nuevoIncremento;
}
//AJUSTA LA VELOCIDAD DE ROTACION DE LA PLATAFORMA
void AComponentePlataforma::setIncrementoRotacion(FRotator nuevoIncrementoRotacion)
{
	incrementoRotacion = nuevoIncrementoRotacion;
}

//ESTE METODO ACTIVA O DESACTIVA EL MOVIMIENTO DE LAS PLATAFORMAS
void AComponentePlataforma::setDetener(bool _detener)
{
	detener = _detener;
}
