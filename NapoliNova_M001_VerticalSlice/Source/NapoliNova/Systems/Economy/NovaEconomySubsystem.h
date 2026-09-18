#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NovaEconomySubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNovaMoneyChanged, int32, NewMoney);

UCLASS()
class NAPOLINOVA_API UNovaEconomySubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnNovaMoneyChanged OnMoneyChanged;

    UFUNCTION(BlueprintCallable)
    void AddMoney(int32 Amount);

    UFUNCTION(BlueprintPure)
    int32 GetMoney() const { return Money; }

private:
    UPROPERTY()
    int32 Money = 500;
};
