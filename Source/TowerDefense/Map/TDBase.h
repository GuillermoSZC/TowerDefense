#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TDInterface.h"
#include "AbilitySystemInterface.h"
#include "Delegates/TDDeclareDelegates.h"
#include "TDBase.generated.h"





class UDataTable;
struct FOnAttributeChangeData;
class UTDHealthAttributeSet;
class UTDBaseUpgrade;

UCLASS()
class TOWERDEFENSE_API ATDBase : public AActor, public ITDInterface, public IAbilitySystemInterface
{
    GENERATED_BODY()

public:
    ATDBase(const FObjectInitializer& ObjectInitializer);

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ability System")
        UDataTable* healthDatatable;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ability System")
        TArray<TSubclassOf<class UGameplayAbility>> AbiliyList;


    FOnHealthChangeSignature FOnHealthChangeDelegate;

    static UPROPERTY(EditAnywhere)
        UTDBaseUpgrade* uiUpgradeRef;

    UPROPERTY(EditDefaultsOnly)
        TSubclassOf<UTDBaseUpgrade> uiUpgradeClass;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
        bool isUIActive;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        float distanceToUI;

    UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
        void TDOnClickedBase(AActor* Target, FKey ButtonPressed);


protected:


    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "HUD")
        class UWidgetComponent* widgetComponent;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "HUD")
        class UTDHealthBar* healthBar;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Ability System", meta = (AllowPrivateAccess = "true"))
        UAbilitySystemComponent* AbilitySystem;

#pragma region DELEGATES
    FDelegateHandle BaseHealthChangedDelegateHandle;
#pragma endregion

private:
#pragma region COMPONENTS_TREE
    UPROPERTY(Category = "BaseBuild", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        class UBoxComponent* BoxCollision;

    UPROPERTY(Category = "BaseBuild", VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
        class UStaticMeshComponent* BaseStaticMesh;

    static FName BoxComponentName;

    static FName StaticMeshName;

    UPROPERTY()
        float distSquared;
#pragma endregion

    UPROPERTY(Transient)
        const UTDHealthAttributeSet* BaseAttributes;

public:
    UFUNCTION(BlueprintCallable)
        UAbilitySystemComponent* GetAbilitySystemComponent() const override;

    UFUNCTION()
        int TGGApplyEffect_Implementation();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDHideUI();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
        void TDVisibleUI();


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
        void OnBaseDeath();


private:
    void TDInitialize();

    void TDActivateDelegates();

    void TDHealthChanged(const FOnAttributeChangeData& Data);

    UFUNCTION(BlueprintPure)
        float TDCheckDistanceWithPlayer();

    UFUNCTION(BlueprintPure)
        bool TDCheckPlayerInRange();

    UFUNCTION(BlueprintPure)
        bool TDCanShowUI();

};
