// Fill out your copyright notice in the Description page of Project Settings.


#include "ObstaclesActor.h"

// Sets default values
AObstaclesActor::AObstaclesActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

}

// Called when the game starts or when spawned
void AObstaclesActor::BeginPlay()
{
	Super::BeginPlay();
	
	Body = this->FindComponentByClass<UStaticMeshComponent>();

	NameBody = Body->GetName();

	SphereCollision = this->FindComponentByClass<USphereComponent>();
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AObstaclesActor::BeginOverlap);



	RandX = FMath::RandRange(-1, 1);
	RandY = FMath::RandRange(-1, 1);
	RandZ = FMath::RandRange(-1, 1);

	GameMode = Cast<ACometGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	SetLifeSpan(5);
}

// Called every frame
void AObstaclesActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Direction = this->GetActorForwardVector(); // Получание направления передвижения
	FVector NewLocation = GetActorLocation() + (Direction * GameMode->GetRunSpeedObstacles() * DeltaTime); // Указание новой координаты для передвижения
	SetActorLocation(NewLocation); // Применение новой координаты для передвижения

	if (NameBody == "Asteroid")
	{
		Body->AddLocalRotation(FRotator(RandX, RandY, RandZ));// Рандомное вращение
	}

	if (NameBody == "Satellite")
	{
		Body->AddLocalRotation(FRotator(RandX, RandY, RandZ));// Рандомное вращение
	}

	if (NameBody == "Crystal")
	{
		Body->AddLocalRotation(FRotator(RandX, RandY, RandZ));
	}

	if (NameBody == "Effect")
	{
		Body->AddLocalRotation(FRotator(0, 1, 0));
	}

	
}

void AObstaclesActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (NameBody == "Asteroid")
	{
		FVector Location = this->GetActorLocation();
		GetWorld()->SpawnActor<ADestroyObstaclesActor>(DestroyActor, Location, FRotator(0, 0, 0));

		GameMode->EndGame();
	}

	if (NameBody == "Satellite")
	{
		FVector Location = this->GetActorLocation();
		GetWorld()->SpawnActor<ADestroyObstaclesActor>(DestroyActor, Location, FRotator(0, 0, 0));
		GameMode->SetDeltaScore(1);
	}

	if (NameBody == "Crystal")
	{
		GameMode->SetDeltaCrystal(1);
	}

	if (NameBody == "Effect")
	{
		FVector Location = this->GetActorLocation();
		GetWorld()->SpawnActor<ADestroyObstaclesActor>(DestroyActor, Location, FRotator(0, 0, 0));

		GameMode->RandPandorasEffect();
	}
	

	Destroy();
}





