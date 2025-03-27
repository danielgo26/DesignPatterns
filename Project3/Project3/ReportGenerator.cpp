#include "ReportGenerator.h"
#include "FolderNode.h"
#include "FileNode.h"
#include <fstream>
#include <filesystem>

ReportGenerator::ReportGenerator(std::unique_ptr<FileNodeOperator> fileOperator, std::ostream* os)
	:GeneratorBase(std::move(fileOperator), os) {}

void ReportGenerator::visitFile(FileNode* file)
{
	if (file) {

		try
		{
			if (!this->fileOperator->operateWithFileNode(file, *this->os, nullptr, this->aligningSpaces))
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
		throw std::invalid_argument("Invalid file node!");
}

void ReportGenerator::visitFolder(FolderNode* folder)
{
	if (folder)
	{
		for (size_t i = 0; i < this->aligningSpaces; i++)
		{
			*this->os << " ";
		}

		this->aligningSpaces += 2;

		*this->os << "Folder: " << folder->getRelativePath() << "(" << folder->getByteSize() << " bytes)" << std::endl;
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
