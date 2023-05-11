#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDWidgetShopComponent.generated.h"

class UUserWidget;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDWidgetShopComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTDWidgetShopComponent();

public:
    static UPROPERTY(EditAnywhere, Category = "User Interface")
        UUserWidget* widgetRef;

    UPROPERTY(EditDefaultsOnly, Category = "User Interface")
        TSubclassOf<UUserWidget> widgetClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "User Interface")
        bool isUIActive;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "User Interface")
        float distanceToUI;

protected:


private:
    UPROPERTY()
        float distSquared;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDHideUI();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDVisibleUI();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDOnClickedActor(AActor* Target, FKey ButtonPressed);

protected:
    virtual void BeginPlay() override;


private:
    UFUNCTION(BlueprintPure)
        float TDCheckDistanceWithPlayer();

    UFUNCTION(BlueprintPure)
        bool TDCheckPlayerInRange();

    UFUNCTION(BlueprintPure)
        bool TDCanShowUI();

    UFUNCTION()
        void TDOnBuyPhaseStart(int32 _value);
};
