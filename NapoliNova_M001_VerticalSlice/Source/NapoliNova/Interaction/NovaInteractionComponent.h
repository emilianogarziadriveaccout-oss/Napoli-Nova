#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NovaInteractionComponent.generated.h"

UCLASS(ClassGroup=(Nova), meta=(BlueprintSpawnableComponent))
class NAPOLINOVA_API UNovaInteractionComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNovaInteractionComponent();

    UFUNCTION(BlueprintCallable)
    void TryInteract();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float InteractionDistance = 250.0f;
};
