// Fill out your copyright notice in the Description page of Project Settings.


#include "CometPawn.h"

// Sets default values
ACometPawn::ACometPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0; // Автоматическое подключение пешки к контроллеру игрока

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	ConstructorHelpers::FClassFinder<UUserWidget>GameUIBPClass(TEXT("/Game/Blueprints/Menu/WBP_GameUI"));
	if (!ensure(GameUIBPClass.Class != nullptr)) return;
	GameUIClass = GameUIBPClass.Class;

}

// Called when the game starts or when spawned
void ACometPawn::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	Body = this->FindComponentByClass<USkeletalMeshComponent>();
	Scene = Cast<USceneComponent>(this->GetDefaultSubobjectByName(TEXT("Scene")));
	PunchParticles = FindComponentByClass<UParticleSystemComponent>();

	Widget = FindComponentByClass<UWidgetComponent>();
	Widget->SetWidgetClass(GameUIClass);
	GameUI = Cast<UGameUI>(Widget->GetUserWidgetObject());

	FString NameLevel = GetWorld()->GetName();
	if (NameLevel == "MenuLevel")
	{
		SetVisibilityBody(false);
	}
	else
	{
		SetVisibilityBody(true);
	}
	

	//GameMode = Cast<ACometGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

// Called every frame
void ACometPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bMove)
	{
		Touch();
		FVector Location = Scene->GetRelativeLocation(); // Текущее положение модели
		Location += Speed * DeltaTime * FVector(0, Direction.X, -Direction.Y) * DirectionInput; // Указание новой координаты для перемещения

	
		SideRotate();
		Body->AddLocalRotation(FRotator(0, 0, SideRotation * Speed / 200));
	


		// Квадратные границы перемещения
		if (Location.Y >= Side)
		{
			Location.Y = Side;
		}
		if (Location.Y <= -Side)
		{
			Location.Y = -Side;
		}

		if (Location.Z >= Side)
		{
			Location.Z = Side;
		}

		if (Location.Z <= -Side)
		{
			Location.Z = -Side;
		}

		LocationToSet = Location;

		Scene->SetRelativeLocation(LocationToSet); //  Применение новой координаты для перемещения
	}

}

// Called to bind functionality to input
void ACometPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("Input", IE_Pressed, this, &ACometPawn::TouchPreesed);
	PlayerInputComponent->BindAction("Input", IE_Released, this, &ACometPawn::TouchReleased);
}

void ACometPawn::TouchPreesed()
{
	bool bIsCurrentlyPressed;
	PlayerController->GetInputTouchState(ETouchIndex::Touch1, FinishtLocation.X, FinishtLocation.Y, bIsCurrentlyPressed);

	StartLocation.X = FinishtLocation.X;
	StartLocation.Y = FinishtLocation.Y;

	bMove = true;

}

void ACometPawn::TouchReleased()
{
	bMove = false;
}

void ACometPawn::Touch()
{
	StartLocation.X = FinishtLocation.X;
	StartLocation.Y = FinishtLocation.Y;

	bool bIsCurrentlyPressed;
	PlayerController->GetInputTouchState(ETouchIndex::Touch1, FinishtLocation.X, FinishtLocation.Y, bIsCurrentlyPressed);

	Direction = FinishtLocation - StartLocation;

	if (UKismetMathLibrary::Abs(Direction.X) > UKismetMathLibrary::Abs(Direction.Y))
	{
		Speed = UKismetMathLibrary::Abs(Direction.X) * 100;
	}
	else
	{
		Speed = UKismetMathLibrary::Abs(Direction.Y) * 100;	
	}

	Direction = Direction.GetSafeNormal();
}

void ACometPawn::SideRotate()
{
	bool bIsCurrentlyPressed;
	PlayerController->GetInputTouchState(ETouchIndex::Touch1, SideRotateLocation.X, SideRotateLocation.Y, bIsCurrentlyPressed);

	FVector2D Difference = SideRotateLocation - StartLocation;

	
		if (Difference.X > 0 || Difference.Y > 0)
		{
			SideRotation = 1;
		}
		else
		{
			SideRotation = -1;
		}
	
}

void ACometPawn::SetDirectionInput(int32 DirectionToSet)
{
	DirectionInput = DirectionToSet;
}


void ACometPawn::SetPunchParticles()
{
	PunchParticles->Activate();
}

void ACometPawn::SetTextScoreToGameUI(FString TextToSet)
{
	GameUI->DeltaCrystal->SetVisibility(ESlateVisibility::Hidden);
	GameUI->DeltaScore->SetText(FText::FromString(TextToSet));
	GameUI->DeltaScore->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(VisibleTimer, this, &ACometPawn::EndVisibleScore, VisibleTime, false);
}

void ACometPawn::SetTextCrystalToGameUI(FString TextToSet)
{
	GameUI->DeltaScore->SetVisibility(ESlateVisibility::Hidden);
	GameUI->DeltaCrystal->SetText(FText::FromString(TextToSet));
	GameUI->DeltaCrystal->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(VisibleTimer, this, &ACometPawn::EndVisibleCrystal, VisibleTime, false);
}

void ACometPawn::EndVisibleScore()
{
	GameUI->DeltaScore->SetVisibility(ESlateVisibility::Hidden);
}

void ACometPawn::EndVisibleCrystal()
{
	GameUI->DeltaCrystal->SetVisibility(ESlateVisibility::Hidden);
}

void ACometPawn::SetVisibilityBody(bool bVisibility)
{
	Body->SetVisibility(bVisibility);
}