// Fill out your copyright notice in the Description page of Project Settings.

#include "S05_TestingGrounds.h"
#include "ChooseNextWayPoint.h"
#include "AIController.h"
#include "PatrollingGuard.h"
#include "BehaviorTree/BlackboardComponent.h"







EBTNodeResult::Type UChooseNextWayPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{


	

	//Get the PatrolPoints
	auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrollingGuard = Cast<APatrollingGuard>(ControlledPawn);
	auto PatrolPoints = PatrollingGuard->PatrolPointsCpp;

	// Set next Waypoint
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);
	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);
	

	
	//CycleWaypointIndex
	int32 NewIndex = (Index + 1) % PatrolPoints.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);
	//TODO Protect against empty patrol route 

	//auto name = AIController->GetPawn()->GetName();
	//UE_LOG(LogTemp, Warning, TEXT("WaypointIndex = %s"), *name);
	

	return EBTNodeResult::Succeeded;

}