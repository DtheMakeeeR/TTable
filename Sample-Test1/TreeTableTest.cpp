#include "pch.h"
#include "../TTable/TreeTable.h"
TEST(TreeTable, CantInsertExcisting)
{
    TreeTable<int, int> t;
    t.Insert(10, 100);
    EXPECT_ANY_THROW(t.Insert(10, 10));
}

TEST(TreeTable, CorrectInsert)
{
    TreeTable<int, int> t;
    int a[5] = { 40, 2, 1, -1, 0 };
    for (int i = 0; i < 5; ++i)
        t.Insert(a[i], a[i]);

    int insertedCount = 0;
    for (t.Reset(); !t.IsEnd(); t.GoNext())
    {
        EXPECT_EQ(t.GetCurrKey(), t.GetCurrVal());
        ++insertedCount;
    }
    EXPECT_EQ(insertedCount, 5);
}
TEST(TreeTable, CorrectDelete)
{
    TreeTable<int, int> t;
    int a1[5] = { 40, 2, 1, -1, 0 };
    int a2[4] = { 0, 1, 2, 40 };
    for (size_t i = 0; i < 5; i++)
    {
        t.Insert(a1[i], a1[i]);
    }
    t.Delete(-1);
    int i = 0;
    for (t.Reset(); !t.IsEnd(); t.GoNext())
    {
        EXPECT_EQ(t.GetCurrVal(), a2[i]);
        i++;
    }
}
TEST(TreeTable, CantDeleteNoPresent)
{
    TreeTable<int, int> t;
    EXPECT_ANY_THROW(t.Delete(10));
}

TEST(TreeTable, CorrectAssign)
{
    TreeTable<int, int> t1, t2;
    for (int i = 0; i < 5; ++i)
        t1.Insert(i, i);

    t2 = t1;
    t2.Delete(4);

    EXPECT_EQ(t1.Find(4), true);
    EXPECT_EQ(t2.Find(4), false);
}

TEST(TreeTable, CanFindExistingKey)
{
    TreeTable<int, int> t;
    t.Insert(5, 50);
    EXPECT_EQ(t.Find(5), true);
}

TEST(TreeTable, CantFindNoExistingKey)
{
    TreeTable<int, int> t;
    t.Insert(5, 50);
    EXPECT_EQ(t.Find(6), false);
}

TEST(TreeTable, CanIterate)
{
    TreeTable<int, int> t;
    int a[5] = { 40, 2, 1, -1, 0 };
    for (int i = 0; i < 5; ++i)
        t.Insert(a[i], a[i]);

    int count = 0;
    for (t.Reset(); !t.IsEnd(); t.GoNext())
    {
        ++count;
    }
    EXPECT_EQ(count, 5);
}

TEST(TreeTable, CanClearTable)
{
    TreeTable<int, int> t;
    for (int i = 0; i < 5; ++i)
        t.Insert(i, i);

    t.Clear();
    EXPECT_EQ(t.GetDataCount(), 0);
    EXPECT_EQ(t.IsEmpty(), true);
}
TEST(TreeTable, EfficiencyTest)
{
    TreeTable<int, int> tree;

    for (int i = 0; i < 1000; ++i) {
        tree.Insert(i, i);
    }

    int lastEff = tree.GetEff();

    EXPECT_GE(lastEff, 1000); 
}