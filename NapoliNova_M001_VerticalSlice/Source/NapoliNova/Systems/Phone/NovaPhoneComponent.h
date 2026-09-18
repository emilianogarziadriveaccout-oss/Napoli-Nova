#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NovaPhoneComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNovaPlayerRecording, AActor*, RecordingTarget);

UCLASS(ClassGroup=(Nova), meta=(BlueprintSpawnableComponent))
class NAPOLINOVA_API UNovaPhoneComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UNovaPhoneComponent();

    virtual void TickComponent(
        float DeltaTime,
        ELevelTick TickType,
        FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable)
    void TogglePhone();

    UFUNCTION(BlueprintCallable)
    void StartRecording();

    UFUNCTION(BlueprintCallable)
    void StopRecording();

    UFUNCTION(BlueprintCallable)
    void PublishCurrentVideo();

    UFUNCTION(BlueprintPure)
    bool IsPhoneOpen() const { return bPhoneOpen; }

    UFUNCTION(BlueprintPure)
    bool IsRecording() const { return bRecording; }

    UFUNCTION(BlueprintPure)
    bool IsTargetAcquired() const { return bTargetAcquired; }

    UFUNCTION(BlueprintPure)
    bool IsValidMissionRecording() const { return bValidMissionRecording; }

    UFUNCTION(BlueprintPure)
    float GetRecordingDuration() const { return RecordingDuration; }

    UPROPERTY(BlueprintAssignable)
    FOnNovaPlayerRecording OnPlayerRecording;

protected:
    virtual void BeginPlay() override;

private:
    bool FindMissionTarget(AActor*& OutTarget) const;
    void UpdateRecording(float DeltaTime);
    void TryAdvanceToRecordObjective(AActor* Target);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Phone", meta=(AllowPrivateAccess="true"))
    float TargetDistance = 800.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Phone", meta=(AllowPrivateAccess="true"))
    float RequiredRecordingDuration = 3.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Phone", meta=(AllowPrivateAccess="true"))
    bool bPhoneOpen = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Phone", meta=(AllowPrivateAccess="true"))
    bool bRecording = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Phone", meta=(AllowPrivateAccess="true"))
    bool bTargetAcquired = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Phone", meta=(AllowPrivateAccess="true"))
    bool bValidMissionRecording = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Phone", meta=(AllowPrivateAccess="true"))
    float RecordingDuration = 0.0f;

    UPROPERTY()
    TObjectPtr<AActor> CurrentRecordingTarget;
};
