// Copyright (c) 2022 Nicolas Castelli. Licensed under the MIT License.

#pragma once

#include "CoreMinimal.h"

class FFlatNodesModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	void ApplyEditorStyle();
};
