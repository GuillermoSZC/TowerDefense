#include "TDBase.h"
#include "Components/BoxComponent.h"
#include "GameplayEffectTypes.h"
#include "GameLogic/TDGameData.h"
#include "Components/StaticMeshComponent.h"
#include "AttributesSets/TDHealthAttributeSet.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "UI/Utilities/TDHealthBar.h"
#include "GameLogic/TDRoundManager.h"
#include "Interfaces/TDInterface.h"
#include "AttributesSets/TDLevelAttributeSet.h"
#include "GameLogic/ElementsEnum.h"
#include "GameLogic/TDCostManager.h"
#include "Character/TDPlayerCharacter.h"
#include "Components/TDWidgetShopComponent.h"
//#include "Character/TDPlayerCharacter.h"
//#include "Character/TDPlayerController.h"

FName ATDBase::BoxComponentName(TEXT("BoxComponentName"));
FName ATDBase::StaticMeshName(TEXT("BaseMesh"));

ATDBase::ATDBase(const FObjectInitializer& ObjectInitializer)
{
    PrimaryActorTick.bCanEverTick = true;

    BoxCollision = CreateDefaultSubobject<UBoxComponent>(ATDBase::BoxComponentName);
    BoxCollision->SetBoxExtent(FVector(32.f, 32.f, 32.f));

    RootComponent = BoxCollision;

    BaseStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(ATDBase::StaticMeshName);
    BaseStaticMesh->AttachToComponent(BoxCollision, FAttachmentTransformRules::KeepRelativeTransform);

    AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilityComponent");

    widgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
    widgetComponent->SetupAttachment(RootComponent);


    widgetShopRef = CreateDefaultSubobject<UTDWidgetShopComponent>("TDWidgetShop");
    AddOwnedComponent(widgetShopRef);



}



void ATDBase::TDTriggerOpenUI()
{
    OnClicked.Broadcast(this, FKey());
}

void ATDBase::TDCalculateElementChangeCost_Implementation(FBuyCost& _cost, ELootItems _item) 
{
    EElements spawnedElement = ITDInterface::Execute_TDGetElementComponent(UTDGameData::TDGetPlayerRef())->TDGetSpawnedElement();
    EElements elementToBuy = EElements::None;
    _cost.GemItem = _item;

    switch (_item)
    {
    case ELootItems::Fire:
    {
        elementToBuy = EElements::Fire;
    }
    break;

    case ELootItems::Ice:
    {
        elementToBuy = EElements::Freeze;

    }
    break;

    case ELootItems::Plasma:
    {
        elementToBuy = EElements::Plasma;

    }
    break;

    default:
    {
    }
    break;
    }


    UTDGameData::TDGetCostManager()->TDCalculateElementChange(_cost, elementToBuy, spawnedElement); 
}

void ATDBase::TDCalcultateCostWithLoot_Implementation(FBuyCost& _cost, ELootItems _item)
{
    int level = 0;
    UAbilitySystemComponent* abilitySystem = UTDGameData::TDGetPlayerRef()->abilitySystem;
    bool found = false;

    switch (_item)
    {
    case ELootItems::BootsBP:
    {
        level = abilitySystem->GetGameplayAttributeValue(UTDLevelAttributeSet::GetBootsLevelAttribute(), found);
        ensure(found);
    }
    break;

    case ELootItems::ArmorBP:
    {
        level = abilitySystem->GetGameplayAttributeValue(UTDLevelAttributeSet::GetArmorLevelAttribute(), found);
        ensure(found);
    }
    break;

    case ELootItems::SwordBP:
    {
        level = abilitySystem->GetGameplayAttributeValue(UTDLevelAttributeSet::GetDamageLevelAttribute(), found);
        ensure(found);
    }
    break;

    default:
    {

    }
    break;
    }

    ensure(found);

    _cost.BPItem = _item;
    UTDGameData::TDGetCostManager()->TDCalculateUpgradeCost(_cost, level);

}

bool ATDBase::TDCanAffordCostWithLoot_Implementation(FBuyCost& _cost)
{
    return UTDGameData::TDGetCostManager()->TDCanAffordBuy(_cost);
}

bool ATDBase::TDCommitBuyUpgrade_Implementation(ELootItems _item /*= ELootItems::None*/)
{
    FBuyCost cost = FBuyCost();

    if (_item == ELootItems::Fire || _item == ELootItems::Ice || _item == ELootItems::Plasma)
    {

        ITDCostInterface::Execute_TDCalculateElementChangeCost(this, cost, _item);
        if (!ITDCostInterface::Execute_TDCanAffordCostWithLoot(this, cost))
        {
            return false;
        }

        UTDGameData::TDGetCostManager()->TDCommitResources(cost);
        return true;

    }

    if (_item == ELootItems::ArmorBP || _item == ELootItems::BootsBP || _item == ELootItems::SwordBP)
    {
        cost.BPItem = _item;
        ITDCostInterface::Execute_TDCalcultateCostWithLoot(this, cost, cost.BPItem);

        if (!ITDCostInterface::Execute_TDCanAffordCostWithLoot(this, cost))
        {
            return false;
        }

        UTDGameData::TDGetCostManager()->TDCommitResources(cost);
        return true;
    }

    return false;
}

// Called when the game starts or when spawned
void ATDBase::BeginPlay()
{
    Super::BeginPlay();

 

    UTDGameData::TDSetBaseActor(this);


    if (widgetComponent)
    {
        healthBar = Cast<UTDHealthBar>(widgetComponent->GetUserWidgetObject());

        if (healthBar)
        {
            FOnHealthChangeDelegate.AddDynamic(healthBar, &UTDHealthBar::TDSetBarPercentage);
            FVector2D sizeTemp = FVector2D(1.2f, 0.4f);
            healthBar->TDSetHealthBarSize(sizeTemp);
        }
    }


    TDInitialize();
}

// Called every frame
void ATDBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

UAbilitySystemComponent* ATDBase::GetAbilitySystemComponent() const
{
    return AbilitySystem;
}





void ATDBase::TDUpdateRoundValues(int32 _Rounds)
{
    if (effectRef)
    {
        FGameplayEffectContextHandle context;
        AbilitySystem->ApplyGameplayEffectToSelf(effectRef, 1, context);
    }
}

int ATDBase::TGGApplyEffect_Implementation()
{
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BaseApplyEffect_Implementation"));

    return 0;
}

void ATDBase::TDInitialize()
{

    const UAttributeSet* attributesInit = AbilitySystem->InitStats(UTDHealthAttributeSet::StaticClass(), healthDatatable);
    BaseAttributes = Cast<UTDHealthAttributeSet>(attributesInit);

    for (size_t i = 0; i < AbiliyList.Num(); ++i)
    {
        FGameplayAbilitySpecHandle specHandle = AbilitySystem->GiveAbility(FGameplayAbilitySpec(AbiliyList[i].GetDefaultObject(), 1, 0));
    }

    if (EffectClass)
    {
        effectRef = Cast<UGameplayEffect>(EffectClass->GetDefaultObject());
    }


    TDActivateDelegates();
}

void ATDBase::TDActivateDelegates()
{
    BaseHealthChangedDelegateHandle = AbilitySystem->GetGameplayAttributeValueChangeDelegate(BaseAttributes->GethealthAttribute()).AddUObject(this, &ATDBase::TDHealthChanged);
    UTDGameData::TDGetRoundManager()->FOnBuyPhaseStartDelegate.AddDynamic(this, &ATDBase::TDUpdateRoundValues);
}

void ATDBase::TDHealthChanged(const FOnAttributeChangeData& Data)
{


    float MaxHealth = BaseAttributes->GetmaxHealth();
    float healthPercent = Data.NewValue / MaxHealth;
    FOnHealthChangeDelegate.Broadcast(healthPercent,0.f);

    if (Data.NewValue <= 0.f)
    {
        UTDGameData::TDDisableAllEnemies();
        OnBaseDeath();
    }

}
