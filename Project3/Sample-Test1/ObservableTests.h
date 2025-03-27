#pragma once
#include <gtest/gtest.h>
#include "..\Project3\Observable.h"
#include "..\Project3\Observer.h"

class MockObserverWithType : public Observer
{
public:
	type t = type::startReadingNewByteGroup;
	void update(const Context& context)
	{
		t = context.operationType;
	}

	bool operator==(const MockObserverWithType& other)const
	{
		return this->t == other.t;
	}
};

TEST(ObservableTests, indexOutOfRangeScenario)
{
	Observable obs;
	size_t initialSize = obs.size();

	EXPECT_EQ(initialSize, 0);

	obs.removeObserverAt(1);
	EXPECT_EQ(initialSize, 0);

	obs.removeObserverAt(0);
	EXPECT_EQ(initialSize, 0);

	obs.removeObserverAt(-1);
	EXPECT_EQ(initialSize, 0);

	EXPECT_TRUE(obs.isExpired(0));
	EXPECT_TRUE(obs.isExpired(-1));
	EXPECT_TRUE(obs.isExpired(1));


	try {
		obs.getObserverAt(0);
		FAIL() << "Expected exception not thrown.";
	}
	catch (const std::invalid_argument& e) {
		EXPECT_EQ(strcmp("Index out of range!", e.what()), 0);
	}
	catch (...) {
		FAIL() << "Unexpected exception type thrown.";
	}
}

TEST(ObservableTests, changeObserversCount)
{
	Observable obs;
	size_t totalSize = obs.size();
	std::shared_ptr<MockObserverWithType> observerTypeOne = std::make_shared<MockObserverWithType>();
	observerTypeOne->t = type::getFileInfo;
	std::shared_ptr<MockObserverWithType> observerTypeTwo = std::make_shared<MockObserverWithType>();
	observerTypeTwo->t = type::resetInitialState;

	obs.addObserver(observerTypeOne);
	totalSize++;

	EXPECT_EQ(totalSize, obs.size());

	obs.addObserver(observerTypeTwo);
	totalSize++;
	EXPECT_EQ(totalSize, obs.size());
	

	obs.addObserver(nullptr);
	EXPECT_EQ(totalSize, obs.size());

	obs.removeObserverAt(0);
	totalSize--;

	EXPECT_EQ(totalSize, obs.size());

	auto sh = obs.getObserverAt(0).lock();
	EXPECT_TRUE(sh);

	MockObserverWithType* curr = dynamic_cast<MockObserverWithType*>(sh.get());
	EXPECT_TRUE(curr);

	EXPECT_TRUE(curr->t == type::resetInitialState);
}

TEST(ObservableTests, notify)
{
	Observable obs;
	std::shared_ptr<MockObserverWithType> observerTypeOne = std::make_shared<MockObserverWithType>();
	observerTypeOne->t = type::getFileInfo;
	std::shared_ptr<MockObserverWithType> observerTypeTwo = std::make_shared<MockObserverWithType>();
	observerTypeTwo->t = type::resetInitialState;

	obs.addObserver(observerTypeOne);

	obs.addObserver(observerTypeTwo);

	obs.notify({"", 0, type::endReadingNewByteGroup});

	for (size_t i = 0; i < obs.size(); i++)
	{
		auto sh = obs.getObserverAt(i).lock();
		EXPECT_TRUE(sh);

		MockObserverWithType* curr = dynamic_cast<MockObserverWithType*>(sh.get());
		EXPECT_TRUE(curr);

		EXPECT_EQ(curr->t, type::endReadingNewByteGroup);
	}
}

