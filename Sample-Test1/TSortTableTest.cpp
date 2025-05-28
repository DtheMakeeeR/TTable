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
TEST(TSortTable, CanFindExistingKey)
{
	TSortTable<int, int> st1;
	st1.Insert(5, 50);
	EXPECT_EQ(st1.Find(5), true);
}
TEST(TSortTable, CantFindNoExistingKey)
{
	TSortTable<int, int> st1;
	st1.Insert(5, 50);
	EXPECT_EQ(st1.Find(6), false);
}
TEST(TSortTable, CanIterate)
{
	TSortTable<int, int> st1;
	int a[5] = { 40, 2, 1, -1, 0 };
	int a1[5] = { -1, 0, 1, 2, 40 };
	for (size_t i = 0; i < 5; i++)
	{
		st1.Insert(a[i], a[i]);
	}
	int i = 0;
	for (st1.Reset(); !st1.IsEnd(); st1.GoNext())
	{
		EXPECT_EQ(st1.GetCurrVal(), a1[i]);
		i++;
	}
}
TEST(TSortTable, CanClearTable)
{
	TSortTable<int, int> st1;
	for (int i = 0; i < 5; i++)
		st1.Insert(i, i);
	st1.Clear();
	EXPECT_EQ(st1.GetDataCount(), 0);
	EXPECT_EQ(st1.IsEmpty(), true);
}
TEST(TSortTable, SortsTable)
{
	int a[5] = { 40, 2, 1, -1, 0 };
	int a1[5] = { -1, 0, 1, 2, 40 };
	TScanTable<int, int> table1;
	for (size_t i = 0; i < 5; i++)
	{
		table1.Insert(a[i], a[i]);
	}
	TSortTable<int, int> table2(table1, SortType::QuickSort), table3(table1, SortType::MergeSort), table4(table1, SortType::SelectSort);
	table2.Reset();
	table3.Reset();
	table4.Reset();
	for (size_t i = 0; i < 5; i++)
	{
		EXPECT_EQ(table2.GetCurrVal(), a1[i]);
		table2.GoNext();
		EXPECT_EQ(table3.GetCurrVal(), a1[i]);
		table3.GoNext();
		EXPECT_EQ(table4.GetCurrVal(), a1[i]);
		table4.GoNext();
	}
}