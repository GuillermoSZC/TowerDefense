#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDWidgetShopComponent.generated.h"

class UTDCostWidget;
class UPrimitiveComponent;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOpenUISignature, UTDCostWidget*, _widget);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseUISignature);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDWidgetShopComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTDWidgetShopComponent();

public:


    UPROPERTY(EditAnywhere, Category = "User Interface")
        TSubclassOf<UTDCostWidget> widgetClass;



    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "User Interface")
        float distanceToUI;



    UPROPERTY(VisibleAnywhere, Category = "User Interface")
        UTDCostWidget* widgetRef;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "User Interface")
        bool isUIActive;

protected:


private:
    UPROPERTY()
        float distSquared;

    UPROPERTY()
        FOnOpenUISignature  FOnOpenUIDelegate;
    UPROPERTY()
        FOnCloseUISignature  FOnCloseUIDelegate;

public:
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDHideUI();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDVisibleUI();

    UFUNCTION(BlueprintCallable)
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
        void TDOnCombatPhaseStart(int32 _value);

    UFUNCTION()
        void TDSetPlayerHUDVisibility(ESlateVisibility _visibility);

    UFUNCTION()
        void TDOnHoveredActor(AActor* _actor);

    UFUNCTION()
        void TDOnUnhoveredActor(AActor* _actor);

    UFUNCTION()
        void TDChangeCursor(EMouseCursor::Type _cursor);
};
