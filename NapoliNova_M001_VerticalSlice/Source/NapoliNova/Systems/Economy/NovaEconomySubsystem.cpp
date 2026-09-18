#include "NovaEconomySubsystem.h"

void UNovaEconomySubsystem::AddMoney(int32 Amount)
{
    Money += Amount;
    OnMoneyChanged.Broadcast(Money);
}
