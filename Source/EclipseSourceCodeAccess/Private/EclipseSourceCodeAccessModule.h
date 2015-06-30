/*
 * EclipseSourceCodeAccessModule.h
 *
 *  Created on: Jun 29, 2015
 *      Author: jluzwick
 */

#pragma once

#include "EclipseSourceCodeAccessor.h"

class FEclipseSourceCodeAccessModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	FEclipseSourceCodeAccessor& GetAccessor();

private:
	FEclipseSourceCodeAccessor EclipseSourceCodeAccessor;
};
