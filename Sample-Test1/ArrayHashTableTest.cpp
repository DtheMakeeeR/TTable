#include "pch.h"
#include "../TTable/ArrayHashTable.h"
TEST(ArrayHashTable, CantInsertFull)
{
	ArrayHashTable<int, int> ht1;
	for (int i = 0; i < 10; i++)
	{
		ht1.Insert(i, i);
	}
	EXPECT_ANY_THROW(ht1.Insert(10, 10));
}
TEST(ArrayHashTable, CantInsertExcisting)
{
	ArrayHashTable<int, int> ht1;
	ht1.Insert(10, 100);
	EXPECT_ANY_THROW(ht1.Insert(10, 10));
}
TEST(ArrayHashTable, CantDeleteNoPresent)
{
	ArrayHashTable<int, int> ht1;
	EXPECT_ANY_THROW(ht1.Delete(10));
}
TEST(ArrayHashTable, CorrectInsert)
{
	ArrayHashTable<int, int> ht1;
	int a[5] = { 40, 2, 1, 4, 0 };
	for (size_t i = 0; i < 5; i++)
	{
		ht1.Insert(a[i], a[i]);
	}
	for (int i = 0; i < 5; i++)
	{
		EXPECT_EQ(ht1.Find(a[i]), true);
	}
}
TEST(ArrayHashTable, CorrectDelete)
{
	ArrayHashTable<int, int> ht1;
	int a1[5] = { 44, 5, 1, 4, 0 }; 
	int a2[4] = { 0, 1, 5, 4 };
	for (size_t i = 0; i < 5; i++)
	{
		ht1.Insert(a1[i], a1[i]);
	}
	ht1.Delete(44);
	int i = 0;
	for (ht1.Reset(); !ht1.IsEnd(); ht1.GoNext())
	{
		EXPECT_EQ(ht1.GetCurrVal(), a2[i]);
		i++;
	}
}
TEST(ArrayHashTable, CorrectAssign)
{
	ArrayHashTable<int, int> ht1, ht2;
	for (int i = 0; i < 5; i++)
	{
		ht1.Insert(i, i);
	}
	ht2 = ht1;
	ht2.Delete(4);
	EXPECT_EQ(ht1.Find(4), true);
	EXPECT_EQ(ht2.Find(4), false);
}
TEST(ArrayHashTable, CanFindExistingKey) {
	ArrayHashTable<int, int> ht;
	ht.Insert(123, 456);
	EXPECT_EQ(ht.Find(123), true);
}
TEST(ArrayHashTable, CantFindNoExistingKey) {
	ArrayHashTable<int, int> ht;
	ht.Insert(123, 456);
	EXPECT_EQ(ht.Find(321), false);
}
TEST(ArrayHashTable, CanClearTable) {
	ArrayHashTable<int, int> ht;
	ht.Insert(1, 2);
	ht.Insert(2, 3);
	ht.Clear();
	EXPECT_EQ(ht.GetDataCount(), 0);
	EXPECT_EQ(ht.IsEmpty(), true);
}
TEST(ArrayHashTable, ChainIsUnbreakble)
{
	ArrayHashTable<int, int> ht1(100);
	/*int a1[5] = { 5, 105, 205, 305, 405};
	for (size_t i = 0; i < 5; i++)
	{
		ht1.Insert(a1[i], a1[i]);
	}
	ht1.Delete(205);
	int i = 0;
	EXPECT_TRUE(ht1.Find(5));
	EXPECT_TRUE(ht1.Find(105));
	EXPECT_TRUE(ht1.Find(305));
	EXPECT_TRUE(ht1.Find(405));*/
	ht1.Insert(47);
	ht1.Insert(4700);
	ht1.Insert(47000);
	ht1.Find(4700);
	ht1.Delete(47);
	ht1.Find(4700);
}