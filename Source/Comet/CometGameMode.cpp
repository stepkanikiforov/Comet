// Fill out your copyright notice in the Description page of Project Settings.


#include "CometGameMode.h"

ACometGameMode::ACometGameMode()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	ConstructorHelpers::FClassFinder<UUserWidget>MainMenuBPClass(TEXT("/Game/Blueprints/Menu/WBP_MainMenu"));
	if (!ensure(MainMenuBPClass.Class != nullptr)) return;
	MainMenuClass = MainMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget>GameMenuBPClass(TEXT("/Game/Blueprints/Menu/WBP_GameMenu"));
	if (!ensure(GameMenuBPClass.Class != nullptr)) return;
	GameMenuClass = GameMenuBPClass.Class;

	//ConstructorHelpers::FClassFinder<UUserWidget>PauseMenuBPClass(TEXT("/Game/Blueprints/Menu/WBP_PauseMenu"));
	//if (!ensure(PauseMenuBPClass.Class != nullptr)) return;
	//PauseMenuClass = PauseMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget>LoseMenuBPClass(TEXT("/Game/Blueprints/Menu/WBP_LoseMenu"));
	if (!ensure(LoseMenuBPClass.Class != nullptr)) return;
	LoseMenuClass = LoseMenuBPClass.Class;

	ConstructorHelpers::FClassFinder<UUserWidget>ShopMenuBPClass(TEXT("/Game/Blueprints/Menu/WBP_ShopMenu"));
	if (!ensure(ShopMenuBPClass.Class != nullptr)) return;
	ShopMenuClass = ShopMenuBPClass.Class;

	static ConstructorHelpers::FObjectFinder<USoundCue> GameMusicCueObject(TEXT("/Game/Music/GameMusic"));
	GameMusicCue = GameMusicCueObject.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> MenuMusicCueObject(TEXT("/Game/Music/MenuMusic"));
	MenuMusicCue = MenuMusicCueObject.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> ButtonSoundCueObject(TEXT("/Game/Music/ButtonSound"));
	ButtonSoundCue = ButtonSoundCueObject.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> CrystalSoundCueObject(TEXT("/Game/Music/CrystalSound"));
	CrystalSoundCue = CrystalSoundCueObject.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> SatelliteSoundCueObject(TEXT("/Game/Music/SatelliteSound"));
	SatelliteSoundCue = SatelliteSoundCueObject.Object;

	static ConstructorHelpers::FObjectFinder<USoundCue> AsteroidSoundCueObject(TEXT("/Game/Music/AsteroidSound"));
	AsteroidSoundCue = AsteroidSoundCueObject.Object;

	MusicComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("MusicComponent"));
	MusicComponent->bAutoActivate = false;

	ButtonSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ButtonSoundComponent"));
	ButtonSoundComponent->bAutoActivate = false;

	SoundCrystal = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundCrystal"));
	SoundCrystal->bAutoActivate = false;

	SoundSatellite = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundSatellite"));
	SoundSatellite->bAutoActivate = false;

	SoundAsteroid = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundAsteroid"));
	SoundAsteroid->bAutoActivate = false;

}

void ACometGameMode::BeginPlay()
{
	Super::BeginPlay();

	GameInstance = Cast<UCometGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	Trigger = GameInstance->TriggerVolume;

	LoadSaveGame();
	if (LoadScore == nullptr)
	{
		FirstSave = Cast<USaveCometGame>(UGameplayStatics::CreateSaveGameObject(USaveCometGame::StaticClass()));
		UGameplayStatics::SaveGameToSlot(FirstSave, FirstSave->SaveSlotName, FirstSave->UserIndex);
	}

	FString NameLevel = GetWorld()->GetName();
	if (NameLevel == MenuLevel)
	{
		MusicComponent->SetSound(MenuMusicCue);
		PlayMusic();
		SetMainMenu();
		GameInstance->PawnVisibility = false;
	}

	if (NameLevel == GameLevel)
	{
		MusicComponent->SetSound(GameMusicCue);
		PlayMusic();
		SetGameMenu();
		GameInstance->PawnVisibility = true;
	}
	PlayerController = GetWorld()->GetFirstPlayerController();

	ButtonSoundComponent->SetSound(ButtonSoundCue);
	SoundCrystal->SetSound(CrystalSoundCue);
	SoundSatellite->SetSound(SatelliteSoundCue);
	SoundAsteroid->SetSound(AsteroidSoundCue);

	ChoosenSaveSkin = GameInstance->SkinColor;
;}

void ACometGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bProgress|| bProgressSatellite || bProgressCrystal)
	{
		Persent -= DeltaTime;
		GameMenu->PandoraProgress->SetPercent(Persent / 5.0f);
		
	}
}

void ACometGameMode::LoadSaveGame()
{
	LoadScore = Cast<USaveCometGame>(UGameplayStatics::CreateSaveGameObject(USaveCometGame::StaticClass()));
	LoadScore = Cast<USaveCometGame>(UGameplayStatics::LoadGameFromSlot(LoadScore->SaveSlotName, LoadScore->UserIndex));
	if (!(LoadScore == nullptr))
	{
		RecordScore = LoadScore->ScoreText;
		Crystal = LoadScore->CrystalText;
		GameInstance->SkinColor = LoadScore->ChoosenSkin;
		PinkSkinGame = LoadScore->PinkSkin;
		YellowSkinGame = LoadScore->YellowSkin;
		PinkShopGame = LoadScore->PinkShop;
		YellowShopGame = LoadScore->YellowShop;
	}
}

void ACometGameMode::SaveGame()
{
	LoadScore = Cast<USaveCometGame>(UGameplayStatics::CreateSaveGameObject(USaveCometGame::StaticClass()));
	LoadScore->ScoreText = RecordScore;
	LoadScore->CrystalText = Crystal;
	LoadScore->ChoosenSkin = GameInstance->SkinColor;
	LoadScore->PinkSkin = PinkSkinGame;
	LoadScore->YellowSkin = YellowSkinGame;
	LoadScore->PinkShop = PinkShopGame;
	LoadScore->YellowShop = YellowShopGame;
	UGameplayStatics::SaveGameToSlot(LoadScore, LoadScore->SaveSlotName, LoadScore->UserIndex);
}

void ACometGameMode::SetMainMenu()
{

	if (!ensure(MainMenuClass != nullptr)) return;

	PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	MainMenu = CreateWidget<UMainMenu>(PlayerController, MainMenuClass);
	MainMenu->SetMenuInterface(this);
	MainMenu->RecordScore->SetText(FText::FromString(FString::FromInt(RecordScore)));
	MainMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));
	MainMenu->AddToViewport();

	FInputModeGameAndUI InputModeData;
	PlayerController->SetInputMode(InputModeData);

}

void ACometGameMode::SetShopMenu()
{

	if (!ensure(ShopMenuClass != nullptr)) return;

	PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	ShopMenu = CreateWidget<UPayMenu>(PlayerController, ShopMenuClass);
	ShopMenu->SetMenuInterface(this);
	ShopMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));
	ShopMenu->SetVisibilityCheck(ChoosenSaveSkin);
	
	if (PinkSkinGame)
	{
		ShopMenu->PinkColorButton->SetVisibility(ESlateVisibility::Visible);
		ShopMenu->BuyPinkButton->SetVisibility(ESlateVisibility::Hidden);
	}

	if (YellowSkinGame)
	{
		ShopMenu->YellowColorButton->SetVisibility(ESlateVisibility::Visible);
		ShopMenu->BuyYellowButton->SetVisibility(ESlateVisibility::Hidden);
	}

	ShopMenu->AddToViewport();

	FInputModeUIOnly InputModeData; 
	PlayerController->SetInputMode(InputModeData);
}

void ACometGameMode::SetGameMenu()
{

	if (!ensure(GameMenuClass != nullptr)) return;

	PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	GameMenu = CreateWidget<UGameMenu>(PlayerController, GameMenuClass);
	GameMenu->SetMenuInterface(this);
	GameMenu->AddToViewport();
	GameMenu->Score->SetText(FText::FromString(FString::FromInt(Score)));
	GameMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));

	FInputModeGameAndUI InputModeData; //Структура позволяющая настроить режим ввода
	PlayerController->SetInputMode(InputModeData);

}

//void ACometGameMode::SetPauseMenu()
//{
//	if (!ensure(PauseMenuClass != nullptr)) return;
//
//	UGameplayStatics::SetGamePaused(GetWorld(), true);
//
//	PlayerController = GetWorld()->GetFirstPlayerController();
//	if (!ensure(PlayerController != nullptr)) return;
//
//	PauseMenu = CreateWidget<UPauseMenu>(PlayerController, PauseMenuClass);
//	PauseMenu->SetMenuInterface(this);
//	PauseMenu->AddToViewport();
//
//	FInputModeUIOnly InputModeData; //Структура позволяющая настроить режим ввода
//	PlayerController->SetInputMode(InputModeData);
//}

void ACometGameMode::SetLoseMenu()
{
	//UGameplayStatics::SetGamePaused(GetWorld(), true);

	if (!ensure(GameMenu != nullptr)) return;
	GameMenu->RemoveFromViewport();

	if (!ensure(LoseMenuClass != nullptr)) return;

	PlayerController = GetWorld()->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;



	LoseMenu = CreateWidget<ULoseMenu>(PlayerController, LoseMenuClass);
	LoseMenu->AddToViewport();
	
	LoseMenu->Score->SetText(FText::FromString(FString::FromInt(Score)));
	LoseMenu->RecordScore->SetText(FText::FromString(FString::FromInt(RecordScore)));
	LoseMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));

	FInputModeUIOnly InputModeData;
	PlayerController->SetInputMode(InputModeData);

	GetWorld()->GetTimerManager().SetTimer(VisibleDeltraRecordTimer, this, &ACometGameMode::VisibleAddCrystalEndGame, DeltaRecordTime, false);
	GetWorld()->GetTimerManager().SetTimer(PauseGameTimer, this, &ACometGameMode::PauseGame, PauseGameTime, false);
}

void ACometGameMode::SetDeltaScore(int32 Delta)
{
	PlaySound(SoundSatellite);
	Score += Delta;
	if (!ensure(GameMenu != nullptr)) return;
	GameMenu->Score->SetText(FText::FromString(FString::FromInt(Score)));

	ACometPawn* Comet = Cast<ACometPawn>(PlayerController->GetPawn());
	Comet->SetTextScoreToGameUI("+1");
	Comet->SetPunchParticles();
}

void ACometGameMode::SetDeltaCrystal(int32 Delta)
{
	PlaySound(SoundCrystal);
	Crystal += Delta;
	if (!ensure(GameMenu != nullptr)) return;
	GameMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));

	ACometPawn* Comet = Cast<ACometPawn>(PlayerController->GetPawn());
	Comet->SetTextCrystalToGameUI("+1");
	Comet->SetPunchParticles();
}

float ACometGameMode::GetRunSpeedObstacles()
{
	return RunSpeedObstacles;
}

void ACometGameMode::SetRunSpeedObstacles(float SpeedToSet)
{
	RunSpeedObstacles = SpeedToSet;
}

float ACometGameMode::GetObstaclesSpawnTime()
{
	return ObstaclesSpawnTime;
}

void ACometGameMode::SetObstaclesSpawnTime(float TimeToSet)
{
	ObstaclesSpawnTime = TimeToSet;
}

int32 ACometGameMode::GetPawnDirectionInput()
{
	return PawnDirectionInput;
}

void ACometGameMode::SetPawnDirectionInput(int32 DirectiontToSet)
{
	ACometPawn* Comet = Cast<ACometPawn>(PlayerController->GetPawn());
	Comet->SetDirectionInput(DirectiontToSet);
}

// Продолжительность эффектов ящика Пандоры

void ACometGameMode::RandPandorasEffect()
{
	PlaySound(SoundSatellite);

	ACometPawn* Comet = Cast<ACometPawn>(PlayerController->GetPawn());
	Comet->SetPunchParticles();

	GameMenu->PandoraProgress->SetPercent(Persent / 5.0f);
	GameMenu->PandoraProgress->SetVisibility(ESlateVisibility::Visible);
	GameMenu->AnimationEffectImage->SetVisibility(ESlateVisibility::Visible);

	int32 RandEffect = FMath::RandRange(1, 5);
	switch (RandEffect)
	{
	case 1:
		GetWorld()->GetTimerManager().SetTimer(AnimationTimer, this, &ACometGameMode::SpeedObstaclesProgressEffect, AnimationTime, false);
		break;
	case 2:
		GetWorld()->GetTimerManager().SetTimer(AnimationTimer, this, &ACometGameMode::TimeSpawnObstaclesProgressEffect, AnimationTime, false);
		break;
	case 3:
		GetWorld()->GetTimerManager().SetTimer(AnimationTimer, this, &ACometGameMode::PawnDirectionInputProgressEffect, AnimationTime, false);
		break;
	case 4:
		GetWorld()->GetTimerManager().SetTimer(AnimationTimer, this, &ACometGameMode::SatelliteProgressEffect, AnimationTime, false);
		break;
	case 5:
		GetWorld()->GetTimerManager().SetTimer(AnimationTimer, this, &ACometGameMode::CrystalProgressEffect, AnimationTime, false);
		break;
	default:
		break;
	}

}

void ACometGameMode::SpeedObstaclesProgressEffect()
{
	SetRunSpeedObstacles(10000);
	SetObstaclesSpawnTime(0.1f);
	bProgress = true;
	GameMenu->AnimationEffectImage->SetVisibility(ESlateVisibility::Hidden);
	GameMenu->SpeedEffect->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(ProgressTimer, this, &ACometGameMode::SpeedObstaclesEffect, ProgressTime, false);
}

void ACometGameMode::TimeSpawnObstaclesProgressEffect()
{
	SetObstaclesSpawnTime(0.1f);
	bProgress = true;
	GameMenu->AnimationEffectImage->SetVisibility(ESlateVisibility::Hidden);
	GameMenu->AsteroidEffect->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(ProgressTimer, this, &ACometGameMode::TimeSpawnObstaclesEffect, ProgressTime, false);
}

void ACometGameMode::PawnDirectionInputProgressEffect()
{
	SetPawnDirectionInput(-1);
	bProgress = true;
	GameMenu->AnimationEffectImage->SetVisibility(ESlateVisibility::Hidden);
	GameMenu->ReversEffect->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(ProgressTimer, this, &ACometGameMode::PawnDirectionInputEffect, ProgressTime, false);
}

void ACometGameMode::SatelliteProgressEffect()
{
	bProgressSatellite = true;
	GameMenu->AnimationEffectImage->SetVisibility(ESlateVisibility::Hidden);
	GameMenu->SatelliteEffect->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(ProgressTimer, this, &ACometGameMode::SatelliteEffect, ProgressTime, false);
}

void ACometGameMode::CrystalProgressEffect()
{
	bProgressCrystal = true;
	GameMenu->AnimationEffectImage->SetVisibility(ESlateVisibility::Hidden);
	GameMenu->CrystalEffect->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(ProgressTimer, this, &ACometGameMode::CrystalEffect, ProgressTime, false);
}

void ACometGameMode::SpeedObstaclesEffect()
{
	SetObstaclesSpawnTime(0.5f);
	SetRunSpeedObstacles(3000);
	if (Persent < 0.1f)
	{
		CrystalOfBuff();
	}
	
	GameMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));
	GameMenu->PandoraProgress->SetVisibility(ESlateVisibility::Hidden);
	GameMenu->SpeedEffect->SetVisibility(ESlateVisibility::Hidden);
	bProgress = false;
	Persent = 5;
}

void ACometGameMode::TimeSpawnObstaclesEffect()
{
	SetObstaclesSpawnTime(0.5f);
	if (Persent < 0.1f)
	{
		CrystalOfBuff();
	}
	GameMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));
	GameMenu->PandoraProgress->SetVisibility(ESlateVisibility::Hidden);
	GameMenu->AsteroidEffect->SetVisibility(ESlateVisibility::Hidden);
	bProgress = false;
	Persent = 5;
}

void ACometGameMode::PawnDirectionInputEffect()
{
	SetPawnDirectionInput(1);
	if (Persent < 0.1f)
	{
		CrystalOfBuff();
	}
	GameMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));
	GameMenu->PandoraProgress->SetVisibility(ESlateVisibility::Hidden);
	GameMenu->ReversEffect->SetVisibility(ESlateVisibility::Hidden);
	bProgress = false;
	Persent = 5;
}

void ACometGameMode::SatelliteEffect()
{
	GameMenu->PandoraProgress->SetVisibility(ESlateVisibility::Hidden);
	GameMenu->SatelliteEffect->SetVisibility(ESlateVisibility::Hidden);
	bProgressSatellite = false;
	Persent = 5;
}

void ACometGameMode::CrystalEffect()
{
	GameMenu->PandoraProgress->SetVisibility(ESlateVisibility::Hidden);
	GameMenu->CrystalEffect->SetVisibility(ESlateVisibility::Hidden);
	bProgressCrystal = false;
	Persent = 5;
}

void ACometGameMode::CrystalOfRecord()
{
	int32 DeltaPlus;
	if (RecordScore < 50)
	{
		DeltaPlus = 10;
		Crystal += DeltaPlus;
	}
	else if (RecordScore > 100)
	{
		DeltaPlus = 100;
		Crystal += DeltaPlus;
	}
	else
	{
		DeltaPlus = 50;
		Crystal += DeltaPlus;
	}
	LoseMenu->RecordCalculate->SetText(FText::FromString(FString::FromInt(DeltaPlus)));
	LoseMenu->RecordScore->SetText(FText::FromString(FString::FromInt(RecordScore)));
	LoseMenu->RecordCalculate->SetVisibility(ESlateVisibility::Visible);
	LoseMenu->PlusRecord->SetVisibility(ESlateVisibility::Visible);
	GetWorld()->GetTimerManager().SetTimer(VisibleRecordTimer, this, &ACometGameMode::HiddenRecord, RecordTime, false);
}

void ACometGameMode::CrystalOfScore()
{
	int32 ScoreCrystal = Score / 10;
	if (ScoreCrystal > 0)
	{
		Crystal += ScoreCrystal;
		LoseMenu->ScoreCalculate->SetText(FText::FromString(FString::FromInt(ScoreCrystal)));
		LoseMenu->ScoreCalculate->SetVisibility(ESlateVisibility::Visible);
		LoseMenu->PlusScore->SetVisibility(ESlateVisibility::Visible);
		GetWorld()->GetTimerManager().SetTimer(VisibleScoreTimer, this, &ACometGameMode::HiddenScore, ScoreTime, false);
	}
}

void ACometGameMode::HiddenScore()
{
	LoseMenu->ScoreCalculate->SetVisibility(ESlateVisibility::Hidden);
	LoseMenu->PlusScore->SetVisibility(ESlateVisibility::Hidden);
	LoseMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));
	SaveGame();
}

void ACometGameMode::HiddenRecord()
{
	LoseMenu->RecordCalculate->SetVisibility(ESlateVisibility::Hidden);
	LoseMenu->PlusRecord->SetVisibility(ESlateVisibility::Hidden);
	LoseMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));
	SaveGame();
}

void ACometGameMode::VisibleAddCrystalEndGame()
{
	if (Score > RecordScore)
	{
		RecordScore = Score;
		CrystalOfRecord();
	}

	CrystalOfScore();
	
}

void ACometGameMode::CrystalOfBuff()
{
	Crystal += 10;
	ACometPawn* Comet = Cast<ACometPawn>(PlayerController->GetPawn());
	Comet->SetTextCrystalToGameUI("+10");
}

void ACometGameMode::VolumeTrigger()
{
	if (Trigger)
	{
		Trigger = false;
		GameInstance->TriggerVolume = false;

		
	}
	else
	{
		Trigger = true;
		GameInstance->TriggerVolume = true;
	}
	PlayMusic();
}

void ACometGameMode::PlayMusic()
{
	if (Trigger)
	{
		MusicComponent->Play();
	}
	else
	{
		MusicComponent->Stop();
	}
}

void ACometGameMode::PlaySound(UAudioComponent* Sound)
{
	if (Trigger && (Sound != nullptr))
	{
		Sound->Play();
	}
}

void ACometGameMode::BuyingPinkSkin()
{
	if (Crystal >= 1000)
	{
		Crystal = Crystal - 1000;
		ShopMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));
		ShopMenu->BuyPinkButton->SetVisibility(ESlateVisibility::Hidden);
		ShopMenu->PinkColorButton->SetVisibility(ESlateVisibility::Visible);
		PinkSkinGame = true;
		PinkShopGame = false;
	}
}

void ACometGameMode::BuyingYellowSkin()
{
	if (Crystal >= 1000)
	{
		Crystal = Crystal - 1000;
		ShopMenu->Crystal->SetText(FText::FromString(FString::FromInt(Crystal)));
		ShopMenu->BuyYellowButton->SetVisibility(ESlateVisibility::Hidden);
		ShopMenu->YellowColorButton->SetVisibility(ESlateVisibility::Visible);
		YellowSkinGame = true;
		YellowShopGame = false;
	}
}

void ACometGameMode::EndGame()
{
	PlaySound(SoundAsteroid);
	SetRunSpeedObstacles(0);
	SetObstaclesSpawnTime(5);
	bMoveSky = false;
	bActivateParticles = false;
	ACometPawn* Comet = Cast<ACometPawn>(PlayerController->GetPawn());
	Comet->SetPunchParticles();
	Comet->SetVisibilityBody(false);

	GetWorld()->GetTimerManager().SetTimer(LoseMenuTimer, this, &ACometGameMode::SetLoseMenu, LoseMenuTime, false);
}

void ACometGameMode::PauseGame()
{
	SaveGame();
	LoseMenu->RepeatButton->SetVisibility(ESlateVisibility::Visible);
	LoseMenu->MainMenuButton->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}