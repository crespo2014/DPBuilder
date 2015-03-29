/*
 * Serializer.cpp
 *  Created on: 10 Mar 2015
 *      Author: lester
 */

#include <new>
#include <ostream>
#include <iostream>

#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

#include "../basicItem.h"


TEST_GROUP(Serialization)
{
	void setup()
	{

	}
	void teardown()
	{

	}
};

TEST(Serialization, fullTest)
{
	basicItem item("root",item_type::object);
}


