#include "NovaPhoneComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Engine/World.h"
#include "Engine/GameInstance.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "Missions/NovaMissionSubsystem.h"
#include "Systems/Social/NovaSocialSubsystem.h"

UNovaPhoneComponent::UNovaPhoneComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UNovaPhoneComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UNovaPhoneComponent::TogglePhone()
{
    bPhoneOpen = !bPhoneOpen;

    if (!bPhoneOpen && bRecording)
        StopRecording();
}

bool UNovaPhoneComponent::FindMissionTarget(AActor*& OutTarget) const
{
    OutTarget = nullptr;

    const APawn* Pawn = Cast<APawn>(GetOwner());
    if (!Pawn)
        return false;

    const APlayerController* PC = Cast<APlayerController>(Pawn->GetController());
    if (!PC)
        return false;

    FVector CameraLocation;
    FRotator CameraRotation;
    PC->GetPlayerViewPoint(CameraLocation, CameraRotation);

    const FVector End =
        CameraLocation + CameraRotation.Vector() * TargetDistance;

    FHitResult Hit;
    FCollisionQueryParams Params(SCENE_QUERY_STAT(NovaPhoneTrace), true);
    Params.AddIgnoredActor(GetOwner());

    if (!GetWorld()->LineTraceSingleByChannel(
        Hit, CameraLocation, End, ECC_Visibility, Params))
    {
        return false;
    }

    AActor* HitActor = Hit.GetActor();

    if (!HitActor || !HitActor->ActorHasTag(TEXT("M001_Target")))
        return false;

    OutTarget = HitActor;
    return true;
}

void UNovaPhoneComponent::TryAdvanceToRecordObjective(AActor* Target)
{
    if (!Target)
        return;

    UGameInstance* GI = GetWorld()->GetGameInstance();
    if (!GI)
        return;

    UNovaMissionSubsystem* Missions =
        GI->GetSubsystem<UNovaMissionSubsystem>();

    if (!Missions)
        return;

    const FNovaMission Mission = Missions->GetCurrentMission();

    if (Mission.MissionID != TEXT("M001") ||
        Mission.Objective != ENovaMissionObjective::FindTarget)
        return;

    Missions->AdvanceObjective(ENovaMissionObjective::FindTarget);
}

void UNovaPhoneComponent::TickComponent(
    float DeltaTime,
    ELevelTick TickType,
    FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!bPhoneOpen)
        return;

    AActor* Target = nullptr;
    bTargetAcquired = FindMissionTarget(Target);

    if (bTargetAcquired)
    {
        CurrentRecordingTarget = Target;
        TryAdvanceToRecordObjective(Target);
    }

    if (bRecording)
        UpdateRecording(DeltaTime);
}

void UNovaPhoneComponent::StartRecording()
{
    if (!bPhoneOpen || bRecording)
        return;

    AActor* Target = nullptr;

    if (!FindMissionTarget(Target))
        return;

    bRecording = true;
    bValidMissionRecording = false;
    RecordingDuration = 0.0f;
    CurrentRecordingTarget = Target;

    OnPlayerRecording.Broadcast(Target);
}

void UNovaPhoneComponent::UpdateRecording(float DeltaTime)
{
    if (!bRecording)
        return;

    AActor* Target = nullptr;

    if (!FindMissionTarget(Target) ||
        Target != CurrentRecordingTarget)
    {
        bTargetAcquired = false;
        return;
    }

    bTargetAcquired = true;
    RecordingDuration += DeltaTime;

    if (RecordingDuration >= RequiredRecordingDuration)
        bValidMissionRecording = true;
}

void UNovaPhoneComponent::StopRecording()
{
    if (!bRecording)
        return;

    bRecording = false;

    if (UGameInstance* GI = GetWorld()->GetGameInstance())
    {
        if (UNovaMissionSubsystem* Missions =
            GI->GetSubsystem<UNovaMissionSubsystem>())
        {
            Missions->SetRecordingDuration(RecordingDuration);

            if (bValidMissionRecording)
                Missions->ValidateRecording();
        }
    }
}

void UNovaPhoneComponent::PublishCurrentVideo()
{
    if (!bValidMissionRecording)
        return;

    UGameInstance* GI = GetWorld()->GetGameInstance();
    if (!GI)
        return;

    UNovaMissionSubsystem* Missions =
        GI->GetSubsystem<UNovaMissionSubsystem>();

    UNovaSocialSubsystem* Social =
        GI->GetSubsystem<UNovaSocialSubsystem>();

    if (!Missions || !Social)
        return;

    const FNovaMission Mission = Missions->GetCurrentMission();

    if (Mission.MissionID != TEXT("M001") ||
        Mission.Objective != ENovaMissionObjective::PublishVideo)
        return;

    const float VideoQuality =
        FMath::Clamp(55.0f + RecordingDuration * 10.0f, 55.0f, 95.0f);

    Social->PublishVideo(VideoQuality);
    Missions->CompleteObjective();

    bValidMissionRecording = false;
    bRecording = false;
    bTargetAcquired = false;
    RecordingDuration = 0.0f;
    CurrentRecordingTarget = nullptr;
}
