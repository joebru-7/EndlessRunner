// Fill out your copyright notice in the Description page of Project Settings.


#include "AI.h"
#include "../EndlessRunnerGameMode.h"

// Sets default values
AAI::AAI()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	static float countdown = 1;
	countdown -= DeltaTime;

	if (countdown < 0)
	{
		countdown = 1;
		AddActorLocalOffset(FVector{ (double)(FMath::RandBool() ? 1:-1) * 100,0,0 });
	}
}

// Called to bind functionality to input
void AAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAI::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	//TODO make better
	Cast<AEndlessRunnerGameMode>(GetWorld()->GetAuthGameMode())->updateHealth(-(int)DamageAmount);

	return DamageAmount;
}
