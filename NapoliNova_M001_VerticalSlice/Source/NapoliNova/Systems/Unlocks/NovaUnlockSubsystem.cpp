#include "NovaUnlockSubsystem.h"

void UNovaUnlockSubsystem::UnlockMission(FName MissionID)
{
    if (!MissionID.IsNone())
        UnlockedMissions.Add(MissionID);
}

void UNovaUnlockSubsystem::UnlockArea(FName AreaID)
{
    if (!AreaID.IsNone())
        UnlockedAreas.Add(AreaID);
}

bool UNovaUnlockSubsystem::IsMissionUnlocked(FName MissionID) const
{
    return UnlockedMissions.Contains(MissionID);
}

bool UNovaUnlockSubsystem::IsAreaUnlocked(FName AreaID) const
{
    return UnlockedAreas.Contains(AreaID);
}
