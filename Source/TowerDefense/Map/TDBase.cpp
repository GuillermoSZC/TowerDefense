#include "TDBase.h"
#include "Components/BoxComponent.h"
#include "GameplayEffectTypes.h"
#include "GameLogic/TDGameData.h"
#include "Components/StaticMeshComponent.h"
#include "AttributesSets/TDHealthAttributeSet.h"
#include <UMG/Public/Components/WidgetComponent.h>
#include "UI/Utilities/TDHealthBar.h"
#include "UI/TDBaseUpgrade.h"
#include "GameLogic/TDRoundManager.h"
#include "Character/TDPlayerCharacter.h"
#include <UMG/Public/Blueprint/WidgetBlueprintLibrary.h>
#include "Character/TDPlayerController.h"

FName ATDBase::BoxComponentName(TEXT("BoxComponentName"));
FName ATDBase::StaticMeshName(TEXT("BaseMesh"));
UTDBaseUpgrade* ATDBase::uiUpgradeRef = nullptr;

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

}

// Called when the game starts or when spawned
void ATDBase::BeginPlay()
{
    Super::BeginPlay();

    UTDGameData::TDSetBaseActor(this);

    OnClicked.AddDynamic(this, &ATDBase::TDOnClickedBase);

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

    distSquared = distanceToUI * distanceToUI;

    if (uiUpgradeClass && !uiUpgradeRef)
    {
        uiUpgradeRef = CreateWidget<UTDBaseUpgrade>(GetWorld(), uiUpgradeClass);
        uiUpgradeRef->AddToViewport();
        uiUpgradeRef->SetVisibility(ESlateVisibility::Collapsed);
    }

    TDInitialize();
}

// Called every frame
void ATDBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (isUIActive && !TDCheckPlayerInRange())
    {
        TDHideUI();
    }
}

UAbilitySystemComponent* ATDBase::GetAbilitySystemComponent() const
{
    return AbilitySystem;
}

void ATDBase::TDHideUI_Implementation()
{
    isUIActive = false;

    if (uiUpgradeRef)
    {
        uiUpgradeRef->SetVisibility(ESlateVisibility::Collapsed);
        UWidgetBlueprintLibrary::SetInputMode_GameOnly(Cast<ATDPlayerController>(UTDGameData::playerRef->GetController()));
    }
}

void ATDBase::TDVisibleUI_Implementation()
{
    isUIActive = true;

    if (uiUpgradeRef)
    {
        uiUpgradeRef->TDSetOwner(this);
        uiUpgradeRef->SetVisibility(ESlateVisibility::Visible);
        UWidgetBlueprintLibrary::SetInputMode_GameAndUIEx(Cast<ATDPlayerController>(UTDGameData::playerRef->GetController()), uiUpgradeRef);
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

    TDActivateDelegates();
}

void ATDBase::TDActivateDelegates()
{
    BaseHealthChangedDelegateHandle = AbilitySystem->GetGameplayAttributeValueChangeDelegate(BaseAttributes->GethealthAttribute()).AddUObject(this, &ATDBase::TDHealthChanged);
}

void ATDBase::TDHealthChanged(const FOnAttributeChangeData& Data)
{


    float MaxHealth = BaseAttributes->GetmaxHealth();
    float healthPercent = Data.NewValue / MaxHealth;
    FOnHealthChangeDelegate.Broadcast(healthPercent);

    if (Data.NewValue <= 0.f)
    {
        UTDGameData::TDDisableAllEnemies();
        OnBaseDeath();
    }

}

float ATDBase::TDCheckDistanceWithPlayer()
{
    float distanceSquared;

    FVector ownerLocation = GetActorLocation();
    FVector playerLocation = UTDGameData::TDGetPlayerRef()->GetActorLocation();
    distanceSquared = FVector::DistSquared2D(ownerLocation, playerLocation);
    
    return distanceSquared;
}

bool ATDBase::TDCheckPlayerInRange()
{
    if (TDCheckDistanceWithPlayer() > distSquared)
    {
        return false;
    }

    return true;
}

bool ATDBase::TDCanShowUI()
{
    if (!TDCheckPlayerInRange())
    {
        return false;
    }

    if (UTDGameData::TDGetRoundManager()->TDGetActualPhase() != GamePhase::BuyPhase)
    {
        return false;
    }

    return true;
}
