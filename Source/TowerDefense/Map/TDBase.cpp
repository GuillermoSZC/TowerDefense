#include "TDBase.h"
#include "Components/BoxComponent.h"

#include "GameplayEffectTypes.h"
#include "GameLogic/TDGameData.h"
#include "Components/StaticMeshComponent.h"
#include "AttributesSets/TDHealthAttributeSet.h"

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