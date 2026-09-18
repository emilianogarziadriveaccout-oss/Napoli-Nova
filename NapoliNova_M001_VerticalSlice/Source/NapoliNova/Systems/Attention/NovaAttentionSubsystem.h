#pragma once
#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NovaAttentionSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNovaAttentionChanged, float, NewAttention);

UCLASS()
class NAPOLINOVA_API UNovaAttentionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnNovaAttentionChanged OnAttentionChanged;

    UFUNCTION(BlueprintCallable)
    void AddAttention(float Amount);

    UFUNCTION(BlueprintPure)
    float GetAttention() const { return Attention; }

private:
    UPROPERTY()
    float Attention = 0.0f;
};
