// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "EndlessRunner/EndlessRunnerCharacter.h"
#include "Engine/DamageEvents.h"
#include "Components/PrimitiveComponent.h"
#include "../PlatformSpawner.h"



AObstacle::AObstacle()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating our Default Components
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	SetRootComponent(StaticMeshComp);

	////Using Constructor Helpers to set our Static Mesh Comp with a.
	//static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/SM_Cube.SM_Cube'"));
	//StaticMeshComp->SetStaticMesh(CubeMeshAsset.Object);

	//StaticMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	//StaticMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);

	//Using Constructor Helpers to set our Static Mesh Comp with a  .
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/obstacle_model'"));
	StaticMeshComp->SetStaticMesh(CubeMeshAsset.Object);


	StaticMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	StaticMeshComp->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	startpos = GetActorLocation();
	StaticMeshComp->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnCollision);

}

// Called every frame
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentloctation = GetActorLocation();

	SetActorLocation(currentloctation + DeltaTime * speed * direction, true);
}

void AObstacle::updateLifetime()
{
	FVector currentloctation = GetActorLocation();

	float distanceTravveled = currentloctation.IsZero() ? 0 : FVector::Dist(GetActorLocation(), startpos);
	float wayToGo = distance - distanceTravveled;
	float travelTimeOfWayToGo = wayToGo / speed;

	SetLifeSpan(travelTimeOfWayToGo);
}




void AObstacle::OnCollision(UPrimitiveComponent* OtherComponent, AActor* OtherActor, UPrimitiveComponent* x, int32 y, bool z, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("collide"));
	OtherActor->TakeDamage(1, {}, nullptr, this);
	this->Destroy();
	
}

void AObstacle::LifeSpanExpired()
{
	//succsessfully dodged

	if(FMath::FRandRange(0,10)<=2)
		parent->ExplodeRandomObstacle();
	Destroy();
}

void AObstacle::Destroyed()
{
	parent->PlatformExpiered(this);
}
