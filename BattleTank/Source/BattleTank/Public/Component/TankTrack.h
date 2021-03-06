// Copyright TempleGames GmbH

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force and to apply forces to the tank.
 */
UCLASS( ClassGroup=(custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	// Sets a Throttle between -1 and +1
	UFUNCTION(BlueprintCallable, Category = "Input")
		void SetThrottle(float Throttle);

	void DriveTrack();


	// Max force per track, in Newtons (Force (Newtons) = Mass (Kg) x Acceleration (m/s^2)
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
		// (40000 x 2.7) (calculated using WolframAlpha: https://goo.gl/pSZfkf) -> used 10m/s^2 instead
		// However since the tank is massive and the friction is high we use a different value
		float TrackMaxDrivingForce = 30000000;

private:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	float CurrentThrottle = 0;
};
