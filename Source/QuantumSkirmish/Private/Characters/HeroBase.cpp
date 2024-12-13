// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/HeroBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


DEFINE_LOG_CATEGORY(LogHeroBase);

AHeroBase::AHeroBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 0.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->CameraLagSpeed = 15.f;
	SpringArm->bUsePawnControlRotation = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>("FirstPerson Camera");
	FirstPersonCamera->SetupAttachment(SpringArm);
	FirstPersonCamera->bUsePawnControlRotation = false;

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh 1P");
	Mesh1P->SetupAttachment(FirstPersonCamera);
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetOwnerNoSee(false);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->PrimaryComponentTick.TickGroup = TG_PrePhysics;

	GetMesh()->SetOnlyOwnerSee(false);
	GetMesh()->SetOwnerNoSee(true);
	GetMesh()->bReceivesDecals = false;
}

void AHeroBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHeroBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHeroBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
