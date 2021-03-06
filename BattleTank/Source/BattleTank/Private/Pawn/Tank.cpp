// Copyright TempleGames GmbH

#include "BattleTank.h"
#include "AIController/TankAIController.h"
#include "PlayerController/TankPlayerController.h"
#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth -= DamageToApply;

	if (CurrentHealth <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("ATank::TakeDamage -- Destroy!"));
		OnDeath.Broadcast();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("ATank::TakeDamage: DamageToApply::%i || CurrentHealth::%i"), DamageToApply, CurrentHealth);
	}

	return CurrentHealth;
}

float ATank::GetHealthPercent() const
{
	return static_cast<float>(CurrentHealth) / static_cast<float>(StartingHealth);
}

void ATank::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if (NewController)
	{
		auto AIController = Cast<ATankAIController>(NewController);
		auto PlayerController = Cast<ATankPlayerController>(NewController);

		if (AIController)
		{
			StartingHealth = AIStartingHealth;
		}
		else if (PlayerController)
		{
			StartingHealth = PlayerStartingHealth;
		}
		CurrentHealth = StartingHealth;
	}
}

