#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NovaProgressionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnNovaProgressionChanged, int32, Level, int32, XP);

UCLASS()
class NAPOLINOVA_API UNovaProgressionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnNovaProgressionChanged OnProgressionChanged;

    UFUNCTION(BlueprintCallable)
    void AddXP(int32 Amount);

    UFUNCTION(BlueprintPure)
    int32 GetLevel() const { return Level; }

    UFUNCTION(BlueprintPure)
    int32 GetXP() const { return XP; }

private:
    UPROPERTY()
    int32 Level = 1;

    UPROPERTY()
    int32 XP = 0;
};
