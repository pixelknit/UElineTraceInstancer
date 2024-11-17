// Fill out your copyright notice in the Description page of Project Settings.


#include "ARockScatterManager.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/KismetSystemLibrary.h"


ARockScatterManager::ARockScatterManager()
{
    PrimaryActorTick.bCanEverTick = false;

}

void ARockScatterManager::OnConstruction(const FTransform& Transform)
{
    // Clear previously spawned rocks
    for (AActor* RockActor : SpawnedRocks)
    {
        if (RockActor)
        {
            RockActor->Destroy();
        }
    }
    SpawnedRocks.Empty();

    ScatterRocks();
}


void ARockScatterManager::ScatterRocks()
{
    if (!TargetFlatSurface)
    {
        UE_LOG(LogTemp, Warning, TEXT("No target flat surface specified for rock scattering."));
        return;
    }

    for (int i = 0; i < NumRocksToScatter; ++i)
    {
        FVector RandomOffset = FMath::VRand() * FMath::FRandRange(0.0f, ScatterRadius);
        FVector SpawnLocation = TargetFlatSurface->GetActorLocation() + RandomOffset;

        FHitResult HitResult;
        FVector Start = SpawnLocation + FVector(0, 0, 100); 
        FVector End = SpawnLocation - FVector(0, 0, 100);  
        FCollisionQueryParams CollisionParams;

        // Perform line trace
        if (GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, CollisionParams))
        {
            SpawnLocation.Z = HitResult.ImpactPoint.Z;

            float RandomScale = FMath::FRandRange(MinScale, MaxScale);

            FRotator RandomRotation = FRotator(0.0f, FMath::FRandRange(0.0f, 360.0f), 0.0f);
            // For now this is hard coded for my 2 specific rocks to instance: Rock01Mesh and Rock02Mesh
            UStaticMesh* SelectedMesh = FMath::RandBool() ? Rock01Mesh : Rock02Mesh;
            if (SelectedMesh)
            {
                AStaticMeshActor* RockActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass(), SpawnLocation, RandomRotation);
                if (RockActor && RockActor->GetStaticMeshComponent())
                {
                    RockActor->GetStaticMeshComponent()->SetStaticMesh(SelectedMesh);
                    RockActor->GetStaticMeshComponent()->SetWorldScale3D(FVector(RandomScale));
                    SpawnedRocks.Add(RockActor); 
                }
            }
        }
    }

}
