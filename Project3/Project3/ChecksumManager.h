#pragma once
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>

#include "FileNode.h"
#include "FolderNode.h"
#include "BuilderWithLinksFollowing.h"
#include "BuilderWithoutLinksFollowing.h"
#include "ReportGenerator.h"
#include "HashGenerator.h"
#include "ChecksumCalculator.h"
#include "HashAlgorithmBase.h"
#include "ProgressReporter.h"
#include "ReportFileOperator.h"
#include "HashFileOperator.h"]
#include "MD5.h"
#include "SHA256.h"

using namespace std;

/// <summary>
/// A class that will manage the user's request and take the corresponding actions
/// By default it will follows links when building the composite hierarchy and use MD5 as hashing algorithm
/// </summary>
class ChecksumManager//to be observer for the memento, so will have update
{
private:
	enum class MainMenuOperations
	{
		openSettings = 1,
		generateReport = 2,
		generateChecksums = 3,
		exit = 4
	};
	enum class SettingsMenuOperations
	{
		changeDirectory = 1,
		changeOutputFile = 2,
		changeTypeOfScanning = 3,
		changeHashingAlgorithm = 4,
		back = 5
	};
	enum class HashingAlgorithms
	{
		MD5 = 1,
		SHA256 = 2
	};
	enum class TypeOfScanning
	{
		followLinks = 1,
		doNotFollowLinks = 2
	};

	string targetDirectory = "";
	bool alreadyBuild = false;
	string outputFilePath = "";
	bool shouldFollowLinks = false;
	HashingAlgorithms hashingAlgorithm;
	bool isReportGeneratorInitialized = false;
	bool isHashGeneratorInitialized = false;

	unique_ptr<BuilderBase> hierarchyBuilder = nullptr;
	unique_ptr<Directory> rootOfHierarchy = nullptr;
	std::unique_ptr<ReportGenerator> reportGenerator = nullptr;
	std::unique_ptr<HashGenerator> hashGenerator = nullptr;
	std::shared_ptr<Observer> checksumGeneratingProgressReported = nullptr;

	bool initializeReportGenerator();
	bool initializeHashGenerator();
	bool build(bool addReporter);
	void printMainMenu() const;
	void printSettingsMenu() const;
	void printChangeTypeOfScanningMenu() const;
	void printChangeTypeOfHashingMenu() const;
	int isValidIntegerIndex(string index, int from, int to) const;
	void executeSettingsMenuOperation();
	void executeMainMenuOperation();
public:
	ChecksumManager(std::string targetDirectory = "", string outputFilePath = "",
		bool shouldFollowLinks = false, HashingAlgorithms hashingAlgorithm = HashingAlgorithms::MD5);
	void start();
};
