/*
 * EclipseSourceCodeAccessModule.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: jluzwick
 */

#include "EclipseSourceCodeAccessModule.h"

#include "EclipseSourceCodeAccessPrivatePCH.h"
#include "Runtime/Core/Public/Features/IModularFeatures.h"

IMPLEMENT_MODULE( FEclipseSourceCodeAccessModule, EclipseSourceCodeAccess );

void FEclipseSourceCodeAccessModule::StartupModule()
{
	// Bind our source control provider to the editor
	IModularFeatures::Get().RegisterModularFeature(TEXT("SourceCodeAccessor"), &FEclipseSourceCodeAccessor );
}

void FEclipseSourceCodeAccessModule::ShutdownModule()
{
	// unbind provider from editor
	IModularFeatures::Get().UnregisterModularFeature(TEXT("SourceCodeAccessor"), &FEclipseSourceCodeAccessor);
}

FEclipseSourceCodeAccessor& FEclipseSourceCodeAccessModule::GetAccessor()
{
	return EclipseSourceCodeAccessor;
}
