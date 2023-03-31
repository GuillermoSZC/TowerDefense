// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "DelegateTickTask.h"
#include "WaitAddRemoveTag.generated.h"



// DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTickSignatures, float, DeltaTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitGameplayTagDelegate);




/**
 *
 */
UCLASS()
class TOWERDEFENSE_API UWaitAddRemoveTag : public UAbilityTask
{
    GENERATED_BODY()

public:

    UWaitAddRemoveTag();



public:

protected:


    bool RegisteredCallback;

    bool OnlyTriggerOnce;

    bool hasTag;

    FDelegateHandle DelegateHandle;

    FGameplayTag	mTag;

private:



  



    UPROPERTY(BlueprintAssignable)
        FWaitGameplayTagDelegate	Added;

    UPROPERTY(BlueprintAssignable)
        FWaitGameplayTagDelegate	Removed;

  

public:

    UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
        static UWaitAddRemoveTag* WaitAddRemoveTag(UGameplayAbility* OwningAbility, FGameplayTag _Tag, bool _OnlyTriggerOnce = true);

protected:


    UAbilitySystemComponent* GetTargetASC();

    virtual void OnDestroy(bool AbilityIsEnding) override;

        virtual void Activate() override;

    UFUNCTION()
        virtual void GameplayTagCallback(const FGameplayTag Tag, int32 NewCount);



private:





};
