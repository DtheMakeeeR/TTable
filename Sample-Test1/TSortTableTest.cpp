#include "pch.h"
#include "../TTable/TSortTable.h"
TEST(TSortTable, CantInsertFull)
{
	TSortTable<int, int> st1;
	for (int i = 0; i < 10; i++)
	{
		st1.Insert(i, i);
	}
	EXPECT_ANY_THROW(st1.Insert(10, 10));
}
TEST(TSortTable, CantInsertExcisting)
{
	TSortTable<int, int> st1;
	st1.Insert(10, 100);
	EXPECT_ANY_THROW(st1.Insert(10, 10));
}
TEST(TSortTable, CantDeleteNoPresent)
{
	TSortTable<int, int> st1;
	EXPECT_ANY_THROW(st1.Delete(10));
}
TEST(TSortTable, CorrectInsert)
{
	TSortTable<int, int> st1;
	int a1[5] = { 40, 2, 1, -1, 0 };
	int a2[5] = { -1, 0, 1, 2, 40 };
	for (size_t i = 0; i < 5; i++)
	{
		st1.Insert(a1[i], a1[i]);
	}
	int i = 0;
	for (st1.Reset(); !st1.IsEnd(); st1.GoNext())
	{
		EXPECT_EQ(st1.GetCurrVal(), a2[i]);
		i++;
	}
}
TEST(TSortTable, CorrectDelete)
{
	TSortTable<int, int> st1;
	int a1[5] = { 40, 2, 1, -1, 0 };
	int a2[4] = { 0, 1, 2, 40 };
	for (size_t i = 0; i < 5; i++)
	{
		st1.Insert(a1[i], a1[i]);
	}
	st1.Delete(-1);
	int i = 0;
	for (st1.Reset(); !st1.IsEnd(); st1.GoNext())
	{
		EXPECT_EQ(st1.GetCurrVal(), a2[i]);
		i++;
	}
}
TEST(TSortTable, CorrectAssign)
{
	TSortTable<int, int> st1, st2;
	for (int i = 0; i < 5; i++)
	{
		st1.Insert(i, i);
	}
	st2 = st1;
	st2.Delete(4);
	EXPECT_EQ(st1.Find(4), true);
	EXPECT_EQ(st2.Find(4), false);
}