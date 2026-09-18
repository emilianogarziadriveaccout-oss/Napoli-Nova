#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NovaMissionTrigger.generated.h"

class UBoxComponent;

UCLASS()
class NAPOLINOVA_API ANovaMissionTrigger : public AActor
{
    GENERATED_BODY()

public:
    ANovaMissionTrigger();

protected:
    virtual void BeginPlay() override;

    UFUNCTION()
    void OnOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

public:
    UPROPERTY(VisibleAnywhere)
    TObjectPtr<UBoxComponent> Box;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName MissionID = TEXT("M001");
};
