#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "NovaInteractable.generated.h"

UINTERFACE(BlueprintType)
class NAPOLINOVA_API UNovaInteractable : public UInterface
{
    GENERATED_BODY()
};

class NAPOLINOVA_API INovaInteractable
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Nova|Interaction")
    void Interact(AActor* Interactor);
};
