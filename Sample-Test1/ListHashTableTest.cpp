#include "pch.h"
#include "../TTable/ListHashTable.h"
TEST(ListHashTable, CantInsertExcisting) {
    ListHashTable<int, int> ht;
    ht.Insert(10, 100);
    EXPECT_ANY_THROW(ht.Insert(10, 200));
}
TEST(ListHashTable, CantDeleteNoPresent) {
    ListHashTable<int, int> ht;
    EXPECT_ANY_THROW(ht.Delete(42));
}
TEST(ListHashTable, CorrectInsert) {
    ListHashTable<int, int> ht;
    int a[3] = { 5, 10, 15 };
    for (int i = 0; i < 3; i++)
        ht.Insert(a[i], a[i]);
    for (int i = 0; i < 3; i++)
        EXPECT_EQ(ht.Find(a[i]), true);
}
TEST(ListHashTable, CorrectDelete) {
    ListHashTable<int, int> ht;
    ht.Insert(1, 1);
    ht.Insert(2, 2);
    ht.Delete(1);
    EXPECT_EQ(ht.Find(1), false);
    EXPECT_EQ(ht.Find(2), true);
}
TEST(ListHashTable, CorrectAssign) {
    ListHashTable<int, int> ht1, ht2;
    ht1.Insert(0, 10);
    ht2 = ht1;
    ht2.Delete(0);
    EXPECT_EQ(ht1.Find(0), true);
    EXPECT_EQ(ht2.Find(0), false);
}
TEST(ListHashTable, CanFindExistingKey) {
    ListHashTable<int, int> ht;
    ht.Insert(123, 456);
    EXPECT_EQ(ht.Find(123), true);
}
TEST(ListHashTable, CantFindNoExistingKey) {
    ListHashTable<int, int> ht;
    ht.Insert(123, 456);
    EXPECT_EQ(ht.Find(321), false);
}
TEST(ListHashTable, CanClearTable) {
    ListHashTable<int, int> ht;
    ht.Insert(1, 2);
    ht.Insert(2, 3);
    ht.Clear();
    EXPECT_EQ(ht.GetDataCount(), 0);
    EXPECT_EQ(ht.IsEmpty(), true);
}