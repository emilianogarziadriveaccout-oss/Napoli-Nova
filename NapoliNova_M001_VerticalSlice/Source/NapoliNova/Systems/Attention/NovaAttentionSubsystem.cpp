#include "NovaAttentionSubsystem.h"

void UNovaAttentionSubsystem::AddAttention(float Amount)
{
    Attention = FMath::Clamp(Attention + Amount, 0.0f, 100.0f);
    OnAttentionChanged.Broadcast(Attention);
}
