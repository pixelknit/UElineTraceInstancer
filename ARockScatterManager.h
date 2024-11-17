// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ARockScatterManager.generated.h"

UCLASS()
class TEMPLETEST01_API ARockScatterManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ARockScatterManager();

protected:
    virtual void OnConstruction(const FTransform& Transform) override;

public:	
    UPROPERTY()
    TArray<AActor*> SpawnedRocks;

    UPROPERTY(EditAnywhere, Category = "Rock Scatter")
    AActor* TargetFlatSurface; 

    UPROPERTY(EditAnywhere, Category = "Rock Scatter")
    float MinScale = 0.8f;

    UPROPERTY(EditAnywhere, Category = "Rock Scatter")
    float MaxScale = 1.2f;

    UPROPERTY(EditAnywhere, Category = "Rock Scatter")
    UStaticMesh* Rock01Mesh;

    UPROPERTY(EditAnywhere, Category = "Rock Scatter")
    UStaticMesh* Rock02Mesh;

    UPROPERTY(EditAnywhere, Category = "Rock Scatter")
    FVector ScatterCenter;

    UPROPERTY(EditAnywhere, Category = "Rock Scatter")
    float ScatterRadius;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rock Scatter")
    UTexture2D* ScatterMask;

    UPROPERTY(EditAnywhere, Category = "Rock Scatter")
    int32 NumRocksToScatter;

    void ScatterRocks();
};
