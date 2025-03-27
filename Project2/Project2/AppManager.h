#pragma once

/// <summary>
/// Main user interface related functionalities
/// Delegating the demanded task to a lower level functions responsible for its management 
/// </summary>

class AppManager
{
public:
	AppManager() = delete;

	static void createLabel();
	static void createTextTransformation();
	static void decorateLabel();
	static void listAllLabels();
	static void listAllTextTransformations();
	static void deleteLabel();
	static void deleteTransformation();
	static void removeDecorator();
	static void getContent();
};