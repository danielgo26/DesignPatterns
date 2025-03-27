#include <fstream>
#include <filesystem>
#include <sstream>

#include "HashGenerator.h"
#include "FolderNode.h"
#include "FileNode.h"

HashGenerator::HashGenerator(std::unique_ptr<FileNodeOperator> fileOperator,
	std::unique_ptr<ChecksumCalculator> hashCalculator, std::ostream* os)
	:GeneratorBase(std::move(fileOperator), os),
	hashCalculator(std::move(hashCalculator)) {}

void HashGenerator::visitFile(FileNode* file)
{
	//starting to process a new file
	if (file)
	{

		//check is a key pressed
		std::string nameOfFile = std::filesystem::path(file->getFullPath()).filename().string();
		this->notify({ nameOfFile, 0, type::getFileInfo });//that will notify and the class 
		//that is responsible for user input
		//so - the checksum generator
		try
		{
			if (!this->fileOperator->operateWithFileNode(file, *this->os, this->hashCalculator, this->aligningSpaces))
				throw std::invalid_argument("Invalid arguments!");
		}
		catch (const std::exception& e)
		{
			std::string msg = "Could not operate with file " +
				std::filesystem::path(file->getFullPath()).filename().string() + "! " +
				std::string(e.what());
			for (size_t i = 0; i < this->aligningSpaces; i++)
			{
				*this->os << " ";
			}
			*this->os << msg << std::endl;
		}
	}
	else
		throw std::runtime_error("Invalid file node!");
}

void HashGenerator::visitFolder(FolderNode* folder)
{
	if (folder)
	{
		for (size_t i = 0; i < this->aligningSpaces; i++)
		{
			*this->os << " ";
		}

		this->aligningSpaces += 2;
		*this->os << "Folder: " << folder->getRelativePath() << std::endl;
		try
		{
			for (size_t i = 0; i < folder->countSubDirectories(); i++)
			{
				folder->getSubDirectoryAt(i)->accept(this);
			}
		}
		catch (const std::exception& e)
		{
			*this->os << e.what() << std::endl;
		}
		this->aligningSpaces -= 2;
	}
	else
		throw std::invalid_argument("Invalid folder node!");
}

void HashGenerator::update(const Context& context)
{
	notify(context);
}

void HashGenerator::addObserver(const std::shared_ptr<Observer>& observer) {
	if (observer)
	{
		Observable::addObserver(observer);
		this->hashCalculator->addObserver(observer);
	}
}

void HashGenerator::changeHashingAlgorithm(std::unique_ptr<HashAlgorithmBase> algorithm)
{
	this->hashCalculator->changeHashAlgorithm(std::move(algorithm));
}