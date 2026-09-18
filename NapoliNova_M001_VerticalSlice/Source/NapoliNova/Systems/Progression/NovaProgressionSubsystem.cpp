#include "NovaProgressionSubsystem.h"

void UNovaProgressionSubsystem::AddXP(int32 Amount)
{
    XP += FMath::Max(0, Amount);

    while (XP >= Level * 1000)
    {
        XP -= Level * 1000;
        ++Level;
    }

    OnProgressionChanged.Broadcast(Level, XP);
}
