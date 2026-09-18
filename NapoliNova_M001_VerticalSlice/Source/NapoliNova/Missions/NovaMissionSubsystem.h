#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "NovaMissionSubsystem.generated.h"

UENUM(BlueprintType)
enum class ENovaMissionObjective : uint8
{
    None,
    ReachParking,
    FindTarget,
    RecordTarget,
    PublishVideo,
    Completed
};

USTRUCT(BlueprintType)
struct FNovaMission
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FName MissionID = NAME_None;

    UPROPERTY(BlueprintReadWrite)
    FText Title;

    UPROPERTY(BlueprintReadWrite)
    FText Description;

    UPROPERTY(BlueprintReadWrite)
    ENovaMissionObjective Objective = ENovaMissionObjective::None;

    UPROPERTY(BlueprintReadWrite)
    bool bActive = false;

    UPROPERTY(BlueprintReadWrite)
    bool bCompleted = false;

    UPROPERTY(BlueprintReadWrite)
    float RecordingDuration = 0.0f;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNovaMissionUpdated, FNovaMission, Mission);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNovaMissionCompleted, FName, MissionID);

UCLASS()
class NAPOLINOVA_API UNovaMissionSubsystem : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnNovaMissionUpdated OnMissionUpdated;

    UPROPERTY(BlueprintAssignable)
    FOnNovaMissionCompleted OnMissionCompleted;

    UFUNCTION(BlueprintCallable)
    bool StartMission(FName MissionID);

    UFUNCTION(BlueprintCallable)
    void CompleteObjective();

    UFUNCTION(BlueprintCallable)
    bool AdvanceObjective(ENovaMissionObjective ExpectedObjective);

    UFUNCTION(BlueprintCallable)
    void SetRecordingDuration(float Duration);

    UFUNCTION(BlueprintCallable)
    bool ValidateRecording();

    UFUNCTION(BlueprintCallable)
    void CompleteMission();

    UFUNCTION(BlueprintPure)
    bool IsMissionActive() const;

    UFUNCTION(BlueprintPure)
    FNovaMission GetCurrentMission() const;

private:
    FNovaMission ActiveMission;

    void BroadcastMission();
};
