#pragma once
#include <gtest/gtest.h>

#include "ChecksumCalculatorTests.h"
#include "BuilderWithoutLinksFollowingTests.h"
#include "BuilderWithLinksFollowingTests.h"
#include "HashFileOperatorTests.h"
#include "ReportFileOperatorTests.h"
#include "ObservableTests.h"
#include "ProgressReporterTests.h"

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}