// Fill out your copyright notice in the Description page of Project Settings.

#include "AIController.h"
#include "EnemyAnimInstance.h"
#include "EnemyCharacter.h"

#include "BTTask_Attack.h"

UBTTask_Attack::UBTTask_Attack()
{
    NodeName = TEXT("Attack");
    bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);
    if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;
    if (OwnerComp.GetAIOwner()->GetPawn() == nullptr) return EBTNodeResult::Failed;

    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    UEnemyAnimInstance* Anim = Cast<UEnemyAnimInstance>(Enemy->GetMesh()->GetAnimInstance());
    Anim->PlayAttackAnim(); //공격몽타주 실행

    return EBTNodeResult::InProgress; //진행중 반환
}

void UBTTask_Attack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
    if (OwnerComp.GetAIOwner() == nullptr) return;
    if (OwnerComp.GetAIOwner()->GetPawn() == nullptr) return;

    AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
    UEnemyAnimInstance* Anim = Cast<UEnemyAnimInstance>(Enemy->GetMesh()->GetAnimInstance());
    if (Anim == nullptr) return;
    if (Anim->Montage_GetIsStopped(Enemy->GetCurrentMontage()))
    {
        //Montage_GetIsStopped : 몽타주가 끝났는지 여부 반환
        //GetCurrentMontage : 현재 재생중인 몽타주
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
    }

}
