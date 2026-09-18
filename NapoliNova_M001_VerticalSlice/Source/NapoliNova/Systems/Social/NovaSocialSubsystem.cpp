#include "NovaSocialSubsystem.h"

void UNovaSocialSubsystem::PublishVideo(float VideoQuality)
{
    const float Quality = FMath::Clamp(VideoQuality, 0.0f, 100.0f);
    const float Viral = Quality * 12.0f;
    const int32 NewFollowers = FMath::RoundToInt(Quality * 18.0f);

    ViralPoints += Viral;
    Followers += NewFollowers;

    if (Quality >= 70.0f)
        Reputation += 1;

    OnVideoPublished.Broadcast(Viral, NewFollowers, Quality);
}

void UNovaSocialSubsystem::AddFollowers(int32 Amount)
{
    Followers = FMath::Max(0, Followers + Amount);
}

void UNovaSocialSubsystem::AddReputation(int32 Amount)
{
    Reputation = FMath::Max(0, Reputation + Amount);
}
