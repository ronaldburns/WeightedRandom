// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "WeightedRandomBlueprintLibrary.generated.h"

/**
 * A library of functions for generating weighted random indices.
 */
UCLASS()
class UWeightedRandomBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/**
	 * Generate a weighted random index based on the provided weights.
	 * @param Weights				An array of weights for each index. The weights do not need to sum to 1.0, they will be normalized.
	 * @param RandomIndex			The output random index.
	 * @return A weighted random index.
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Random")
	static void GenerateWeightedRandomIndex(const TArray<float>& Weights, int32& RandomIndex);
	
	/**
	 * Generate a weighted random index based on the provided weights.
	 * @param Weights				An array of weights for each index. The weights do not need to sum to 1.0, they will be normalized.
	 * @param RandomStream			The random stream to use for generating the random number.
	 * @param RandomIndex			The output random index.
	 * @return A weighted random index.
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Random")
	static void GenerateWeightedRandomIndexFromStream(const TArray<float>& Weights, const FRandomStream& RandomStream, int32& RandomIndex);
	
	/**
	 * Generate an array of random indices based on the provided weights.
	 * @param Weights				An array of weights for each index. The weights do not need to sum to 1.0, they will be normalized.
	 * @param NumIndicesToGenerate	The number of indices to generate.
	 * @param RandomIndices			The output array of random indices.
	 * @return An array of random indices.
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Random")
	static void GenerateWeightedRandomIndices(const TArray<float>& Weights, int32 NumIndicesToGenerate, TArray<int32>& RandomIndices);
	
	/**
	 * Generate an array of random indices based on the provided weights.
	 * @param Weights				An array of weights for each index. The weights do not need to sum to 1.0, they will be normalized.
	 * @param NumIndicesToGenerate	The number of indices to generate.
	 * @param RandomStream			The random stream to use for generating the random numbers.
	 * @param RandomIndices			The output array of random indices.
	 * @return An array of random indices.
	 */
	UFUNCTION(BlueprintCallable, Category = "Math|Random")
	static void GenerateWeightedRandomIndicesFromStream(const TArray<float>& Weights, int32 NumIndicesToGenerate, const FRandomStream& RandomStream, TArray<int32>& RandomIndices);
};
