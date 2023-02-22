#include "TDBase.h"
#include "Components/BoxComponent.h"
#include "TDBaseAttributeSet.h"
#include "GameplayEffectTypes.h"
#include "GameLogic/TDGameData.h"
#include "Components/StaticMeshComponent.h"

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

    abilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>("AbilityComponent");
}

// Called when the game starts or when spawned
void ATDBase::BeginPlay()
{
    Super::BeginPlay();

    TDInitialize();
}

// Called every frame
void ATDBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

UAbilitySystemComponent* ATDBase::GetAbilitySystemComponent() const
{
    return abilitySystem;
}

int ATDBase::TGGApplyEffect_Implementation()
{
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("BaseApplyEffect_Implementation"));

    return 0;
}

void ATDBase::TDInitialize()
{

    const UAttributeSet* attributesInit = abilitySystem->InitStats(UTDBaseAttributeSet::StaticClass(), statsDatatable);
    BaseAttributes = Cast<UTDBaseAttributeSet>(attributesInit);

    for (size_t i = 0; i < abiliyList.Num(); ++i)
    {
        FGameplayAbilitySpecHandle specHandle = abilitySystem->GiveAbility(FGameplayAbilitySpec(abiliyList[i].GetDefaultObject(), 1, 0));
    }

    TDActivateDelegates();
}

void ATDBase::TDActivateDelegates()
{
    BaseHealthChangedDelegateHandle = abilitySystem->GetGameplayAttributeValueChangeDelegate(BaseAttributes->GethealthAttribute()).AddUObject(this, &ATDBase::TDHealthChanged);
}

void ATDBase::TDHealthChanged(const FOnAttributeChangeData& Data)
{

}