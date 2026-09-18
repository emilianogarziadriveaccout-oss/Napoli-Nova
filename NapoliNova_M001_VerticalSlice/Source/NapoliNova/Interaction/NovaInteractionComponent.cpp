#include "NovaInteractionComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Interfaces/NovaInteractable.h"

UNovaInteractionComponent::UNovaInteractionComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UNovaInteractionComponent::TryInteract()
{
    APawn* Pawn = Cast<APawn>(GetOwner());
    if (!Pawn)
        return;

    APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
    if (!PC)
        return;

    FVector Start;
    FRotator Rot;
    PC->GetPlayerViewPoint(Start, Rot);

    FVector End = Start + Rot.Vector() * InteractionDistance;

    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(NovaInteraction), true);
    Params.AddIgnoredActor(GetOwner());

    if (!GetWorld()->LineTraceSingleByChannel(
        Hit, Start, End, ECC_Visibility, Params))
        return;

    AActor* Target = Hit.GetActor();

    if (Target && Target->GetClass()->ImplementsInterface(UNovaInteractable::StaticClass()))
    {
        INovaInteractable::Execute_Interact(Target, GetOwner());
    }
}
