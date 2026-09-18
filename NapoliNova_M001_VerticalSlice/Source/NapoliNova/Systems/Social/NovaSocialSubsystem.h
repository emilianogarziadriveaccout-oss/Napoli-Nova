#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NovaSocialSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnNovaVideoPublished, float, ViralPoints, int32, NewFollowers, float, VideoQuality);

UCLASS()
class NAPOLINOVA_API UNovaSocialSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnNovaVideoPublished OnVideoPublished;

    UFUNCTION(BlueprintCallable)
    void PublishVideo(float VideoQuality);

    UFUNCTION(BlueprintCallable)
    void AddFollowers(int32 Amount);

    UFUNCTION(BlueprintCallable)
    void AddReputation(int32 Amount);

    UFUNCTION(BlueprintPure)
    int32 GetFollowers() const { return Followers; }

    UFUNCTION(BlueprintPure)
    float GetViralPoints() const { return ViralPoints; }

    UFUNCTION(BlueprintPure)
    int32 GetReputation() const { return Reputation; }

private:
    UPROPERTY()
    int32 Followers = 100;

    UPROPERTY()
    float ViralPoints = 0.0f;

    UPROPERTY()
    int32 Reputation = 0;
};
