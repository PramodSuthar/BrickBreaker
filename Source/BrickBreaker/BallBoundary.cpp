// Fill out your copyright notice in the Description page of Project Settings.


#include "BallBoundary.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Paddle_Player_Controller.h"

// Sets default values
ABallBoundary::ABallBoundary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Box_Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collsion"));
}

// Called when the game starts or when spawned
void ABallBoundary::BeginPlay()
{
	Super::BeginPlay();

	Box_Collision->OnComponentBeginOverlap.AddDynamic(this, &ABallBoundary::OnOverlapBegin);

	Player_Controller_REF = Cast<APaddle_Player_Controller>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	
}


// Called every frame
void ABallBoundary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABallBoundary::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndexType, bool bFromSweep, 
	const FHitResult& SweepResult)
{
    if(OtherActor->ActorHasTag(("Ball"))) {

		OtherActor->Destroy();
		Player_Controller_REF->SpawnNewBall();
    }
}


