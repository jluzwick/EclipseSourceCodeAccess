/*
 * EclipseSourceCodeAccessor.cpp
 *
 *  Created on: Jun 29, 2015
 *      Author: jluzwick
 */

#include "EclipseSourceCodeAccessor.h"

#include "EclipseSourceCodeAccessPrivatePCH.h"
#include "EclipseSourceCodeAccessor.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"

FEclipseSourceCodeAccessor::FEclipseSourceCodeAccessor() { }
FEclipseSourceCodeAccessor::~FEclipseSourceCodeAccessor() { }

#define LOCTEXT_NAMESPACE "EclipseSourceCodeAccessor"

bool FEclipseSourceCodeAccessor::CanAccessSourceCode() const {
	return FPaths::FileExists(TEXT("/usr/bin/clang++"));
}

FName FEclipseSourceCodeAccessor::GetFName() const {
	return FName("EclipseSourceCodeAccessor");
}

FText FEclipseSourceCodeAccessor::GetNameText() const {
	return LOCTEXT("EclipseDisplayName", "Eclipse");
}

FText FEclipseSourceCodeAccessor::GetDescriptionText() const {
	return LOCTEXT("EclipseDisplayDesc", "Open source code files with Eclipse");
}

bool FEclipseSourceCodeAccessor::OpenSolution() {
	//  TODO
	FString FullPath;
	FString SolutionFilenameWithoutExtension = TEXT("UE4");
	FString CodeSolutionFile = SolutionFilenameWithoutExtension + TEXT(".pro");

	if (FDesktopPlatformModule::Get()->GetSolutionPath(FullPath)) {
		if (FPaths::FileExists(FullPath)) {
			FString Editor = FString(TEXT("/usr/bin/qtcreator"));
			FString Args = FString(TEXT("-client "));

			// Add this to handle spaces in path names.
			const FString NewFullPath = FString::Printf(TEXT("\"%s\""),
					*FullPath);

			Args.Append(NewFullPath);
			if (FLinuxPlatformProcess::CreateProc(*Editor, *Args, true, true,
					false, nullptr, 0, nullptr, nullptr).IsValid()) {
				return true;
			}
		}
	}
	return false;
}

bool FEclipseSourceCodeAccessor::OpenFileAtLine(const FString& FullPath,
		int32 LineNumber, int32 ColumnNumber) {

	// TODO: Need to test if eclipse is installed in the default location.
	FString Editor = FString(TEXT("/usr/bin/eclipse"));
	FString Args = FString(TEXT("-launcher.openFile "));

	// TODO: Unfortunately Eclipse does not allow one to launch to a file AND a source line
	// See bug: https://bugs.eclipse.org/bugs/show_bug.cgi?id=305336
	// Add this to handle spaces in path names.
	const FString NewFullPath = FString::Printf(TEXT("\"%s\""), *FullPath);

	Args.Append(NewFullPath); // .Append(TEXT(":")).Append(FString::FromInt(LineNumber));
	if (FLinuxPlatformProcess::CreateProc(*Editor, *Args, true, true, false,
			nullptr, 0, nullptr, nullptr).IsValid()) {
		return true;
	}

	return false;
}

bool FEclipseSourceCodeAccessor::OpenSourceFiles(
		const TArray<FString>& AbsoluteSourcePaths) {
	for (const FString& SourcePath : AbsoluteSourcePaths) {
		FString Editor = FString(TEXT("/usr/bin/qtcreator"));
		FString Args = FString(TEXT("-client "));

		// Add this to handle spaces in path names.
		const FString NewSourcePath = FString::Printf(TEXT("\"%s\""),
				*SourcePath);

		Args.Append(NewSourcePath);
		if (!(FLinuxPlatformProcess::CreateProc(*Editor, *Args, true, true,
				false, nullptr, 0, nullptr, nullptr).IsValid())) {
			return false;
		}
	}

	return true;
}

bool FEclipseSourceCodeAccessor::AddSourceFiles(
		const TArray<FString>& AbsoluteSourcePaths,
		const TArray<FString>& AvailableModules) {
	return false;
}

bool FEclipseSourceCodeAccessor::SaveAllOpenDocuments() const {
	return false;
}

void FEclipseSourceCodeAccessor::Tick(const float DeltaTime) {

}

#undef LOCTEXT_NAMESPACE
