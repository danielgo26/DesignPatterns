
#include <ShlObj_core.h>

#include "BuilderWithLinksFollowing.h"
#include "FileNode.h"
#include "FolderNode.h"

using namespace std;

fs::path BuilderWithLinksFollowing::getTargetPathFromShortcut(const fs::path& pathToShortcut)
{
	std::string name = pathToShortcut.string();
	wstring str = wstring(name.begin(), name.end());
	LPCWSTR lnkFilePath = str.c_str();

	std::string msgIfThrow = "";

	// Initialize COM
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

	if (SUCCEEDED(hr)) {
		// Create an instance of the ShellLink interface
		IShellLink* pShellLink;
		hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&pShellLink);

		if (SUCCEEDED(hr)) {
			// Create a pointer to the IPersistFile interface
			IPersistFile* pPersistFile;
			hr = pShellLink->QueryInterface(IID_IPersistFile, (LPVOID*)&pPersistFile);

			if (SUCCEEDED(hr)) {
				// Load the shortcut file
				hr = pPersistFile->Load(lnkFilePath, STGM_READ);

				if (SUCCEEDED(hr)) {
					// Resolve the shortcut to get the target file path
					WCHAR targetPath[MAX_PATH];
					hr = pShellLink->GetPath(targetPath, MAX_PATH, NULL, SLGP_UNCPRIORITY);

					if (SUCCEEDED(hr))
						return targetPath;
					msgIfThrow = "Failed to get target path from the shortcut.";
				}
				else
					msgIfThrow = "Failed to load the shortcut file.";

				// Release the IPersistFile interface
				pPersistFile->Release();
			}
			else
				msgIfThrow = "Failed to query IPersistFile interface.";

			// Release the IShellLink interface
			pShellLink->Release();
		}
		else
			msgIfThrow = "Failed to create ShellLink instance.";

		// Uninitialize COM
		CoUninitialize();
	}
	else
		msgIfThrow = "Failed to initialize COM.";

	throw std::runtime_error(msgIfThrow);
}

std::unique_ptr<Directory> BuilderWithLinksFollowing::buildRecursively(
	const fs::path& targetDir, const std::string& currPath)
{
	if (!fs::exists(targetDir))
		return std::make_unique<FileNode>(currPath +
			"[error reading directory...not able to continue]", targetDir.string(), 0, false);

	//shortcut
	if (targetDir.extension() == ".lnk")
	{
		fs::path targetPath = getTargetPathFromShortcut(targetDir.string());

		return std::move(buildRecursively(targetPath,
			currPath + targetDir.filename().string() + " -(links to)-> "));
	}
	//symlink
	else if (fs::is_symlink(targetDir.string()))
	{
		fs::path pathToTarget = fs::read_symlink(targetDir.string());

		return std::move(buildRecursively(fs::path(targetDir.parent_path().string() + "\\" + pathToTarget.filename().string()),
			currPath + targetDir.filename().string() + ".symlink" + " -(links to)-> "));
	}
	//"pure" directories(directories that do not link to somewhere)
	else
	{
		//file
		if (fs::is_regular_file(targetDir))
		{
			return std::move(std::make_unique<FileNode>
				(currPath + targetDir.filename().string(), targetDir.string(), fs::file_size(targetDir.string())));
		}
		//folder
		else
		{
			std::string newCurrPath = currPath + targetDir.filename().string();
			//a cycle dependency
			if (this->usedDirectories.count(targetDir.string()) != 0)
				return std::move(std::make_unique<FolderNode>(newCurrPath, targetDir.string(), 0, false));

			//add the directory in set to avoid cycling dependencies
			this->usedDirectories.insert(fs::absolute(targetDir).string());

			//here we set the size of the folder to be initialy zero,
			//so later we will increase it when adding subdirectories

			std::unique_ptr<FolderNode> currFolder =
				std::make_unique<FolderNode>(newCurrPath, targetDir.string(), 0);

			try {
				// Iterate through all entries(files and folders) in the directory
				for (const auto& entry : fs::directory_iterator(targetDir))
				{
					std::unique_ptr<Directory> subDirectory =
						std::move(buildRecursively(entry.path(), newCurrPath + "\\"));

					currFolder->setByteSize(currFolder->getByteSize() + subDirectory->getByteSize());
					currFolder->addSubDirectory(std::move(subDirectory));
				}
			}
			catch (...) {
				currFolder->setByteSize(currFolder->getByteSize());
				currFolder->addSubDirectory(std::make_unique<FileNode>
					(newCurrPath + "\\[error reading directory...not able to continue]", targetDir.string(), 0, false));
			}

			//remove the already traversed directory
			usedDirectories.erase(targetDir.string());

			return std::move(currFolder);
		}
	}
}

void BuilderWithLinksFollowing::build(const std::string& targetDirectoryPath)
{
	this->directoryProduct = std::move(this->buildRecursively(targetDirectoryPath));
}