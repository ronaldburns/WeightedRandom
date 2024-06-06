// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeightedRandomBlueprintLibrary.h"

struct FIndexWeightedSampler : public FWeightedRandomSampler
{
public:
	FIndexWeightedSampler() = default;

	FIndexWeightedSampler(const int32 IndexRange, const TConstArrayView<float> IndexWeights)
	{
		TotalWeight = 0.0f;
		PerIndexWeight.Reserve(IndexRange);
		for (int32 i = 0; i < IndexRange; ++i)
		{
			if (IndexWeights.Num() > 0)
			{
				PerIndexWeight.Add(IndexWeights.IsValidIndex(i) ? FMath::Max(IndexWeights[i], 0.0f) : 0.0f);
			}
			else
			{
				PerIndexWeight.Add(1.0f);
			}
			TotalWeight += PerIndexWeight.Last();
		}
	}

	virtual float GetWeights(TArray<float>& OutWeights) override
	{
		OutWeights = PerIndexWeight;
		return TotalWeight;
	}

	TArray<float> PerIndexWeight;
	float TotalWeight = 0.0f;
};

void UWeightedRandomBlueprintFunctionLibrary::GenerateWeightedRandomIndex(const TArray<float>& Weights, int32& RandomIndex)
{
	if (Weights.IsEmpty()) return;

	auto Sampler = FIndexWeightedSampler(Weights.Num(), Weights);
	Sampler.Initialize();

	RandomIndex = Sampler.GetEntryIndex(FMath::FRand(), FMath::FRand());
}

void UWeightedRandomBlueprintFunctionLibrary::GenerateWeightedRandomIndexFromStream(const TArray<float>& Weights, const FRandomStream& RandomStream, int32& RandomIndex)
{
	if (Weights.IsEmpty()) return;

	auto Sampler = FIndexWeightedSampler(Weights.Num(), Weights);
	Sampler.Initialize();

	RandomIndex = Sampler.GetEntryIndex(RandomStream.FRand(), RandomStream.FRand());
}

void UWeightedRandomBlueprintFunctionLibrary::GenerateWeightedRandomIndices(const TArray<float>& Weights, const int32 NumIndicesToGenerate, TArray<int32>& RandomIndices)
{
	if (Weights.IsEmpty()) return;

	auto Sampler = FIndexWeightedSampler(Weights.Num(), Weights);
	Sampler.Initialize();

	RandomIndices.SetNumUninitialized(NumIndicesToGenerate);
	for (int32 i = 0; i < NumIndicesToGenerate; i++)
	{
		const auto RandomIndex = Sampler.GetEntryIndex(FMath::FRand(), FMath::FRand());
		RandomIndices[i] = RandomIndex;
	}
}

void UWeightedRandomBlueprintFunctionLibrary::GenerateWeightedRandomIndicesFromStream(const TArray<float>& Weights, const int32 NumIndicesToGenerate, const FRandomStream& RandomStream, TArray<int32>& RandomIndices)
{
	if (Weights.IsEmpty()) return;

	auto Sampler = FIndexWeightedSampler(Weights.Num(), Weights);
	Sampler.Initialize();

	RandomIndices.SetNumUninitialized(NumIndicesToGenerate);
	for (int32 i = 0; i < NumIndicesToGenerate; i++)
	{
		const auto RandomIndex = Sampler.GetEntryIndex(RandomStream.FRand(), RandomStream.FRand());
		RandomIndices[i] = RandomIndex;
	}
}
