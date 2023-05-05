// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"
#include "Engine/DamageEvents.h"
#include "Components/PrimitiveComponent.h"


void AObstacle::OnCollision(UPrimitiveComponent* OtherComponent, AActor* OtherActor, UPrimitiveComponent* x, int32 y, bool z, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("collide"));
	OtherActor->TakeDamage(1, {}, nullptr, this);
	
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComp->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnCollision);
}

AObstacle::AObstacle() : Super()
{
	//Using Constructor Helpers to set our Static Mesh Comp with a Sphere Shape.
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/obstacle_model'"));
	StaticMeshComp->SetStaticMesh(CubeMeshAsset.Object);


	StaticMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	StaticMeshComp->SetGenerateOverlapEvents(true);

}
