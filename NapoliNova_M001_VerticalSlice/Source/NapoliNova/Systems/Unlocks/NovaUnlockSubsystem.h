#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NovaUnlockSubsystem.generated.h"

UCLASS()
class NAPOLINOVA_API UNovaUnlockSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void UnlockMission(FName MissionID);

    UFUNCTION(BlueprintCallable)
    void UnlockArea(FName AreaID);

    UFUNCTION(BlueprintPure)
    bool IsMissionUnlocked(FName MissionID) const;

    UFUNCTION(BlueprintPure)
    bool IsAreaUnlocked(FName AreaID) const;

private:
    UPROPERTY()
    TSet<FName> UnlockedMissions;

    UPROPERTY()
    TSet<FName> UnlockedAreas;
};
