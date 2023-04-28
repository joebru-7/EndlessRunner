// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Components/BoxComponent.h"


#define MY_LOG(format,...) UE_LOG(LogTemp, Warning, TEXT(format), __VA_ARGS__)

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

	if (FVector::Dist(currentloctation, startpos) > distance)
		Destroy();

	SetActorLocation(currentloctation + DeltaTime * speed * direction);


}

