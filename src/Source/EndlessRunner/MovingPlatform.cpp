// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creating our Default Components
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));

	SetRootComponent(StaticMeshComp);

	//Using Constructor Helpers to set our Static Mesh Comp with a Sphere Shape.
	static ConstructorHelpers::FObjectFinder<UStaticMesh>CubeMeshAsset(TEXT("/Script/Engine.StaticMesh'/Game/SM_Cube.SM_Cube'"));
	StaticMeshComp->SetStaticMesh(CubeMeshAsset.Object);

	StaticMeshComp->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	StaticMeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);


}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	startpos = GetActorLocation();

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector currentloctation = GetActorLocation();

	SetActorLocation(currentloctation + DeltaTime * speed * direction,true);
}

void AMovingPlatform::updateLifetime()
{
	FVector currentloctation = GetActorLocation();

	float distanceTravveled = currentloctation.IsZero() ? 0 : FVector::Dist(GetActorLocation(), startpos);
	float wayToGo = distance - distanceTravveled;
	float travelTimeOfWayToGo = wayToGo / speed;

	SetLifeSpan(travelTimeOfWayToGo);
}

