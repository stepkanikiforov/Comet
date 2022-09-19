// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"

#include "MenuWidget.h"
#include "MainMenu.h"
#include "GameMenu.h"
//#include "PauseMenu.h"
#include "LoseMenu.h"
#include "PayMenu.h"
#include "MenuInterface.h"


#include "SaveCometGame.h"

#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

#include "CometPawn.h"
#include "CometGameInstance.h"

#include "CometGameMode.generated.h"

/**
 * 
 */
UCLASS()
class COMET_API ACometGameMode : public AGameModeBase, public IMenuInterface
{
	GENERATED_BODY()
	
public:
	ACometGameMode();

	virtual void Tick(float DeltaTime) override;

	void SetMainMenu();
	void SetGameMenu();
	//void SetPauseMenu();
	void SetLoseMenu();
	void SetShopMenu();

	void SetDeltaScore(int32 Delta);
	void SetDeltaCrystal(int32 Delta);

	float GetRunSpeedObstacles();
	void SetRunSpeedObstacles(float SpeedToSet);

	float GetObstaclesSpawnTime();
	void SetObstaclesSpawnTime(float TimeToSet);

	int32 GetPawnDirectionInput();
	void SetPawnDirectionInput(int32 DirectiontToSet);

	void RandPandorasEffect();

	void SpeedObstaclesProgressEffect();
	void TimeSpawnObstaclesProgressEffect();
	void PawnDirectionInputProgressEffect();
	void SatelliteProgressEffect();
	void CrystalProgressEffect();

	void SpeedObstaclesEffect();
	void TimeSpawnObstaclesEffect();
	void PawnDirectionInputEffect();
	void SatelliteEffect();
	void CrystalEffect();

	float Persent = 5;

	bool bProgress = false;
	bool bProgressSatellite = false;
	bool bProgressCrystal = false;

	void LoadSaveGame();
	void SaveGame();

	void CrystalOfRecord();
	void CrystalOfScore();
	void CrystalOfBuff();

	void PlayMusic();
	void PlaySound(UAudioComponent* Sound);
	void VolumeTrigger();
	bool Trigger;

	

	void EndGame();
	bool bMoveSky = true;
	bool bActivateParticles = true;

	void BuyingPinkSkin();
	void BuyingYellowSkin();

	bool PinkSkinGame;
	bool YellowSkinGame;
	bool PinkShopGame;
	bool YellowShopGame;

	void VisibleAddCrystalEndGame();
	void HiddenScore();
	void HiddenRecord();

	void PauseGame();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	class UMainMenu* MainMenu = nullptr;
	class UGameMenu* GameMenu = nullptr;
	//class UPauseMenu* PauseMenu = nullptr;
	class ULoseMenu* LoseMenu = nullptr;
	class UPayMenu* ShopMenu = nullptr;
	

	USaveCometGame* FirstSave = nullptr;
	USaveCometGame* LoadScore = nullptr;

	APlayerController* PlayerController = nullptr;


private:

	UCometGameInstance* GameInstance;

	TSubclassOf<UUserWidget> MainMenuClass;
	TSubclassOf<UUserWidget> GameMenuClass;
	//TSubclassOf<UUserWidget> PauseMenuClass;
	TSubclassOf<UUserWidget> LoseMenuClass;
	TSubclassOf<UUserWidget> ShopMenuClass;
	

	FString MenuLevel = FString("MenuLevel");
	FString GameLevel = FString("GameLevel");

	int32 Score = 0; // Очки во время игры
	int32 RecordScore = 0; // Рекорд по очкам за все игры
	int32 Crystal = 0; // Всё колличество кристалов 
	float RunSpeedObstacles = 3000;
	float ObstaclesSpawnTime = 0.5f;

	int32 PawnDirectionInput = 1;

	FTimerHandle AnimationTimer;
	float AnimationTime = 1.0f;

	FTimerHandle ProgressTimer;
	float ProgressTime = 5.0f;

	FTimerHandle LoseMenuTimer;
	float LoseMenuTime = 0.3f;

	FTimerHandle VisibleScoreTimer;
	float ScoreTime = 0.5f;

	FTimerHandle VisibleRecordTimer;
	float RecordTime = 0.5f;

	FTimerHandle VisibleDeltraRecordTimer;
	float DeltaRecordTime = 1.0f;

	FTimerHandle PauseGameTimer;
	float PauseGameTime = 2.0f;
	
	USoundCue* GameMusicCue;
	USoundCue* MenuMusicCue;
	USoundCue* ButtonSoundCue;
	USoundCue* CrystalSoundCue;
	USoundCue* SatelliteSoundCue;
	USoundCue* AsteroidSoundCue;

	UAudioComponent* MusicComponent;
	UAudioComponent* ButtonSoundComponent;
	UAudioComponent* SoundCrystal;
	UAudioComponent* SoundSatellite;
	UAudioComponent* SoundAsteroid;

	int32 ChoosenSaveSkin = 1;
};
