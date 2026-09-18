#include "NovaMissionTrigger.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Pawn.h"
#include "Engine/GameInstance.h"
#include "NovaMissionSubsystem.h"

ANovaMissionTrigger::ANovaMissionTrigger()
{
    PrimaryActorTick.bCanEverTick = false;

    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    RootComponent = Box;

    Box->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    Box->SetCollisionResponseToAllChannels(ECR_Overlap);
    Box->SetGenerateOverlapEvents(true);
}

void ANovaMissionTrigger::BeginPlay()
{
    Super::BeginPlay();
    Box->OnComponentBeginOverlap.AddDynamic(this, &ANovaMissionTrigger::OnOverlap);
}

void ANovaMissionTrigger::OnOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!Cast<APawn>(OtherActor))
        return;

    if (UGameInstance* GI = GetGameInstance())
    {
        if (UNovaMissionSubsystem* Missions =
            GI->GetSubsystem<UNovaMissionSubsystem>())
        {
            Missions->StartMission(MissionID);
        }
    }
}
