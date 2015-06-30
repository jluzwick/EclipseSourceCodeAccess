/*
 * EclipseSourceCodeAccessor.h
 *
 *  Created on: Jun 29, 2015
 *      Author: jluzwick
 */

#include "ISourceCodeAccessor.h"

#pragma once

class FEclipseSourceCodeAccessor : public ISourceCodeAccessor
{
public:

	FEclipseSourceCodeAccessor();
	virtual ~FEclipseSourceCodeAccessor();

	/** ISourceCodeAccessor implementation */
	virtual bool CanAccessSourceCode() const override;
	virtual FName GetFName() const override;
	virtual FText GetNameText() const override;
	virtual FText GetDescriptionText() const override;
	virtual bool OpenSolution() override;
	virtual bool OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber = 0) override;
	virtual bool OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) override;
	virtual bool AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules) override;
	virtual bool SaveAllOpenDocuments() const override;
	virtual void Tick(const float DeltaTime) override;
};
