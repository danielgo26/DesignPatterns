#pragma once
#include <iostream>
#include <string>
#include "ClassConstInvariants.h"

using namespace std;

namespace {
	bool isIntegerFromRange(std::string string, int& saveInto, int from = 0, int to = -1)
	{
		int number;
		try
		{
			number = stoi(string);
		}
		catch (const std::invalid_argument&)
		{
			return false;
		}
		saveInto = number;

		//if we ommit the 3rd and 4rd argumen or give invalid ones, we do not compare with them 
		if (from <= to)
		{
			return number >= from && number <= to;
		}
		return true;
	}
	bool isDoubleFromRange(std::string string, double& saveInto, double from = 0, double to = -1)
	{
		double number;
		try
		{
			number = stod(string);
		}
		catch (const std::invalid_argument&)
		{
			return false;
		}
		saveInto = number;

		//if we ommit the 3rd and 4rd argumen or give invalid ones, we do not compare with them 
		if (from <= to)
		{
			return number >= from && number <= to;
		}
		return true;
	}

	bool setStringByDefaultIfEmpty(std::string& string)
	{
		if (string == "")
		{
			cout << "Empty string is not a valid one! Set to " << notEmptyReplacement << " by default!" << endl;
			string = notEmptyReplacement;
			return false;
		}
		return true;
	}
}