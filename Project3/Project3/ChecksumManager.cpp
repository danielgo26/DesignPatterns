#include "ChecksumManager.h"
#include <stdio.h>
#include <conio.h>

void ChecksumManager::printMainMenu() const
{
	cout << "-------Menu-------" << endl;
	cout << "1. Settings" << endl;
	cout << "2. Generate report" << endl;
	cout << "3. Generate checksums" << endl;
	cout << "4. Exit" << endl;

	cout << "Enter index of operation: ";
}

void ChecksumManager::printSettingsMenu() const
{
	cout << "----------Settings----------" << endl;
	cout << "1. Change target directory" << endl;
	cout << "2. Change checksums output file" << endl;
	cout << "3. Change type of scanning" << endl;
	cout << "4. Change hashing algorithm" << endl;
	cout << "5. Back" << endl;

	cout << "Enter index of operation: ";
}

void ChecksumManager::printChangeTypeOfScanningMenu() const
{
	string type = (this->shouldFollowLinks ? "[follow]" : "[not follow]");
	cout << "--Change type of scanning(currentType: " << type << " )--" << endl;
	cout << "1. Follow links" << endl;
	cout << "2. Do NOT follow links" << endl;

	cout << "Enter index of operation: ";
}

void ChecksumManager::printChangeTypeOfHashingMenu() const
{
	string type = (this->hashingAlgorithm == HashingAlgorithms::MD5 ? "MD5" :
		this->hashingAlgorithm == HashingAlgorithms::SHA256 ? "SHA-256" : "[undefined]");
	cout << "--Change type of hashing(currrent: " << type << " )--" << endl;
	cout << "1. MD5" << endl;
	cout << "2. SHA-256" << endl;

	cout << "Enter index of operation: ";
}

int ChecksumManager::isValidIntegerIndex(string index, int from, int to) const
{
	try
	{
		int number = std::stoi(index);
		if (number >= from && number <= to)
			return number;

		std::cout << "Index should be between " << from << " and " << to << "!" << std::endl;
		return -1;
	}
	catch (const std::invalid_argument& e) {
		std::cout << "Invalid input index!" << std::endl;
	}
	catch (const std::out_of_range& e) {
		std::cout << "Invalid input index!" << e.what() << std::endl;
	}
	return -1;
}

void ChecksumManager::executeSettingsMenuOperation()
{
	while (true)
	{
		printSettingsMenu();
		std::string input;
		int indexOperation = -1;
		cin >> input;

		system("cls");
		indexOperation = isValidIntegerIndex(input, 1, 5);
		if (indexOperation == -1)
		{
			continue;
		}
		if (indexOperation == (int)SettingsMenuOperations::changeDirectory)
		{
			cout << "Current directory path: " << this->targetDirectory << endl;
			cout << "Enter new target directory path: ";
			string newTarget;
			cin.ignore();
			getline(cin, newTarget);
			this->targetDirectory = newTarget;
			system("cls");
			cout << "Target directory path changed successfully!" << endl;
			this->isReportGeneratorInitialized = false;
			this->isHashGeneratorInitialized = false;
			this->alreadyBuild = false;
		}
		else if (indexOperation == (int)SettingsMenuOperations::changeOutputFile)
		{
			cout << "Current output file path: " << this->outputFilePath << endl;
			cout << "Enter new output file path: ";
			string newFilePath;
			cin.ignore();
			getline(cin, newFilePath);
			this->outputFilePath = newFilePath;
			system("cls");
			cout << "Output file path changed successfully!" << endl;
		}
		else if (indexOperation == (int)SettingsMenuOperations::changeTypeOfScanning)
		{
			while (true)
			{
				printChangeTypeOfScanningMenu();
				std::string input;
				int indexOperation = -1;
				cin >> input;

				system("cls");
				indexOperation = isValidIntegerIndex(input, 1, 2);
				if (indexOperation == -1)
				{
					continue;
				}

				if (indexOperation == (int)TypeOfScanning::followLinks)
				{
					if (this->shouldFollowLinks != true)
					{
						this->isReportGeneratorInitialized = false;
						this->isHashGeneratorInitialized = false;
						this->alreadyBuild = false;
					}
					this->shouldFollowLinks = true;
				}
				else if (indexOperation == (int)TypeOfScanning::doNotFollowLinks)
				{
					if (this->shouldFollowLinks != false)
					{
						this->isReportGeneratorInitialized = false;
						this->isHashGeneratorInitialized = false;
						this->alreadyBuild = false;
					}
					this->shouldFollowLinks = false;
				}
				system("cls");
				cout << "Type of scanning changed successfully!" << endl;
				break;
			}
		}
		else if (indexOperation == (int)SettingsMenuOperations::changeHashingAlgorithm)
		{
			while (true)
			{
				printChangeTypeOfHashingMenu();
				std::string input;
				int indexOperation = -1;
				cin >> input;

				system("cls");
				indexOperation = isValidIntegerIndex(input, 1, 2);
				if (indexOperation == -1)
				{
					continue;
				}

				if (indexOperation == (int)HashingAlgorithms::MD5) {
					this->hashingAlgorithm = HashingAlgorithms::MD5;
					if (this->isHashGeneratorInitialized)
						this->hashGenerator->changeHashingAlgorithm(std::make_unique<MD5>());
				}
				else if (indexOperation == (int)HashingAlgorithms::SHA256) {
					this->hashingAlgorithm = HashingAlgorithms::SHA256;
					if (this->isHashGeneratorInitialized)
						this->hashGenerator->changeHashingAlgorithm(std::make_unique<SHA256>());
				}

				system("cls");
				cout << "Type of hashing changed successfully!" << endl;
				break;
			}
		}
		else if (indexOperation == (int)SettingsMenuOperations::back)
			return;
	}
}

void ChecksumManager::executeMainMenuOperation()
{
	while (true)
	{
		printMainMenu();
		std::string input;
		int indexOperation = -1;
		cin >> input;

		system("cls");
		indexOperation = isValidIntegerIndex(input, 1, 4);
		if (indexOperation == -1)
			continue;

		if (indexOperation == (int)MainMenuOperations::openSettings)
		{
			executeSettingsMenuOperation();
		}
		else if (indexOperation == (int)MainMenuOperations::generateReport)
		{
			if (!this->build(false))
				continue;

			if (!isReportGeneratorInitialized)
				this->initializeReportGenerator();

			try
			{
				this->rootOfHierarchy->accept(this->reportGenerator.get());
			}
			catch (const std::exception& e)
			{
				system("cls");
				std::cout << e.what() << endl;
			}
		}
		else if (indexOperation == (int)MainMenuOperations::generateChecksums)
		{
			if (!this->build(true))
				continue;

			if (!isHashGeneratorInitialized)
				this->initializeHashGenerator();

			if (this->outputFilePath == "")
			{
				system("cls");
				std::cout << "First set the output file!" << endl;
				continue;
			}

			if (!std::filesystem::exists(this->outputFilePath))
			{
				system("cls");
				std::cout << "The file does not exist!" << endl;
				continue;
			}
			std::ofstream ofs(this->outputFilePath);
			this->hashGenerator->resetOutputStream(&ofs);
			try
			{
				/*char key = '\0';
				if (_kbhit()) {
					key = _getch();
				}*/

				this->rootOfHierarchy->accept(this->hashGenerator.get());

				/*if (_kbhit())
				{
					key = _getch();
					cout << key << " pressed" << endl;
				}*/
			}
			catch (const std::exception& e)
			{
				system("cls");
				std::cout << e.what() << endl;
				continue;
			}

			this->hashGenerator->notify({ "", 0, type::resetInitialState });
		}
		else if (indexOperation == (int)MainMenuOperations::exit)
			return;
	}
}

void ChecksumManager::start()
{
	this->executeMainMenuOperation();
}

bool ChecksumManager::initializeReportGenerator()
{
	std::unique_ptr<FileNodeOperator> fileReportOperator = std::make_unique<ReportFileOperator>();
	this->reportGenerator = make_unique<ReportGenerator>(std::move(fileReportOperator));

	return this->isReportGeneratorInitialized = true;
}

bool ChecksumManager::initializeHashGenerator()
{
	std::unique_ptr<FileNodeOperator> fileHashOperator = std::make_unique<HashFileOperator>();
	std::unique_ptr<HashAlgorithmBase> algorithm;
	switch (this->hashingAlgorithm)
	{
	case HashingAlgorithms::MD5:
		algorithm = std::make_unique<MD5>();
		break;
	case HashingAlgorithms::SHA256:
		algorithm = std::make_unique<SHA256>();
		break;
	default:
		algorithm = std::make_unique<MD5>();
		break;
	}
	std::unique_ptr<ChecksumCalculator> calc = std::make_unique<ChecksumCalculator>(std::move(algorithm));
	this->hashGenerator = make_unique<HashGenerator>(std::move(fileHashOperator), std::move(calc));

	this->checksumGeneratingProgressReported =
		std::make_shared<ProgressReporter>(this->rootOfHierarchy->getByteSize());

	if (this->checksumGeneratingProgressReported)
		this->hashGenerator->addObserver(this->checksumGeneratingProgressReported);

	return this->isHashGeneratorInitialized = true;
}

bool ChecksumManager::build(bool addReporter)
{
	if (alreadyBuild)
		return true;

	try
	{
		if (!fs::exists(this->targetDirectory)) {
			cout << "That directory does not exist!" << endl;
			return false;
		}

		if (this->shouldFollowLinks)
		{
			BuilderWithLinksFollowing b;
			b.build(this->targetDirectory);
			this->rootOfHierarchy = std::move(b.getResult());
		}
		else
		{
			BuilderWithoutLinksFollowing b;
			b.build(this->targetDirectory);
			this->rootOfHierarchy = std::move(b.getResult());
		}
	}
	catch (const std::invalid_argument& e)
	{
		if (this->targetDirectory == "")
			cout << "First specify a target directory!" << endl;
		else
			cout << "Error while scanning! " << e.what() << endl;
		return false;
	}

	return this->alreadyBuild = true;
}

ChecksumManager::ChecksumManager(std::string targetDirectory, string outputFilePath,
	bool shouldFollowLinks, HashingAlgorithms hashingAlgorithm)
	:targetDirectory(std::move(targetDirectory)), outputFilePath(std::move(outputFilePath)),
	shouldFollowLinks(shouldFollowLinks), hashingAlgorithm(hashingAlgorithm) {}