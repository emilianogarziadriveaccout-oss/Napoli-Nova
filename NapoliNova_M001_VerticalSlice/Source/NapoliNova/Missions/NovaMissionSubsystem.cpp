#include "NovaMissionSubsystem.h"
#include "Systems/Social/NovaSocialSubsystem.h"
#include "Systems/Economy/NovaEconomySubsystem.h"
#include "Systems/Progression/NovaProgressionSubsystem.h"
#include "Systems/Attention/NovaAttentionSubsystem.h"
#include "Systems/Unlocks/NovaUnlockSubsystem.h"

bool UNovaMissionSubsystem::StartMission(FName MissionID)
{
    if (ActiveMission.bActive)
        return false;

    if (MissionID == TEXT("M001"))
    {
        ActiveMission = FNovaMission();
        ActiveMission.MissionID = MissionID;
        ActiveMission.Title = FText::FromString(TEXT("IL PARCHEGGIO IMPOSSIBILE"));
        ActiveMission.Description = FText::FromString(TEXT("Raggiungi il parcheggio."));
        ActiveMission.Objective = ENovaMissionObjective::ReachParking;
        ActiveMission.bActive = true;
        ActiveMission.bCompleted = false;
        BroadcastMission();
        return true;
    }

    return false;
}

void UNovaMissionSubsystem::CompleteObjective()
{
    if (!ActiveMission.bActive || ActiveMission.bCompleted)
        return;

    switch (ActiveMission.Objective)
    {
        case ENovaMissionObjective::ReachParking:
            ActiveMission.Objective = ENovaMissionObjective::FindTarget;
            break;

        case ENovaMissionObjective::FindTarget:
            ActiveMission.Objective = ENovaMissionObjective::RecordTarget;
            break;

        case ENovaMissionObjective::RecordTarget:
            ActiveMission.Objective = ENovaMissionObjective::PublishVideo;
            break;

        case ENovaMissionObjective::PublishVideo:
            CompleteMission();
            return;

        default:
            return;
    }

    BroadcastMission();
}

bool UNovaMissionSubsystem::AdvanceObjective(ENovaMissionObjective ExpectedObjective)
{
    if (!ActiveMission.bActive || ActiveMission.bCompleted)
        return false;

    if (ActiveMission.Objective != ExpectedObjective)
        return false;

    CompleteObjective();
    return true;
}

void UNovaMissionSubsystem::SetRecordingDuration(float Duration)
{
    ActiveMission.RecordingDuration = Duration;
}

bool UNovaMissionSubsystem::ValidateRecording()
{
    if (!ActiveMission.bActive ||
        ActiveMission.Objective != ENovaMissionObjective::RecordTarget ||
        ActiveMission.RecordingDuration < 3.0f)
        return false;

    ActiveMission.Objective = ENovaMissionObjective::PublishVideo;
    BroadcastMission();
    return true;
}

void UNovaMissionSubsystem::CompleteMission()
{
    if (!ActiveMission.bActive || ActiveMission.bCompleted)
        return;

    const FName CompletedID = ActiveMission.MissionID;

    ActiveMission.bCompleted = true;
    ActiveMission.bActive = false;
    ActiveMission.Objective = ENovaMissionObjective::Completed;

    if (UGameInstance* GI = GetGameInstance())
    {
        if (UNovaEconomySubsystem* Economy = GI->GetSubsystem<UNovaEconomySubsystem>())
            Economy->AddMoney(100);

        if (UNovaProgressionSubsystem* Progression = GI->GetSubsystem<UNovaProgressionSubsystem>())
            Progression->AddXP(250);

        if (UNovaSocialSubsystem* Social = GI->GetSubsystem<UNovaSocialSubsystem>())
            Social->AddReputation(1);

        if (UNovaAttentionSubsystem* Attention = GI->GetSubsystem<UNovaAttentionSubsystem>())
            Attention->AddAttention(10);

        if (UNovaUnlockSubsystem* Unlocks = GI->GetSubsystem<UNovaUnlockSubsystem>())
        {
            Unlocks->UnlockMission(TEXT("M002"));
            Unlocks->UnlockArea(TEXT("VIA_MARINA"));
        }
    }

    BroadcastMission();
    OnMissionCompleted.Broadcast(CompletedID);
}

bool UNovaMissionSubsystem::IsMissionActive() const
{
    return ActiveMission.bActive && !ActiveMission.bCompleted;
}

FNovaMission UNovaMissionSubsystem::GetCurrentMission() const
{
    return ActiveMission;
}

void UNovaMissionSubsystem::BroadcastMission()
{
    OnMissionUpdated.Broadcast(ActiveMission);
}
