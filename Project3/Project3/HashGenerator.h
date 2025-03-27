#pragma once
#include "GeneratorBase.h"
#include "ChecksumCalculator.h"
#include "Observable.h"
#include "Observer.h"

class HashGenerator : public GeneratorBase, public Observable, public Observer
{
private:
	std::unique_ptr<ChecksumCalculator> hashCalculator;
public:
	HashGenerator(std::unique_ptr<FileNodeOperator> fileOperator,
		std::unique_ptr<ChecksumCalculator> hashCalculator, std::ostream* os = &std::cout);
	void visitFile(FileNode* file) override;
	void visitFolder(FolderNode* folder) override;

	//because it is also and a observer, too
	void update(const Context& context) override;
	void addObserver(const std::shared_ptr<Observer>& observer) override;
	void changeHashingAlgorithm(std::unique_ptr<HashAlgorithmBase> algorithm);
};
