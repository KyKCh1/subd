#include "pch.h"
#include "../List/List.h"
#include <string>

using namespace std;

class ListPushTest : public testing::Test {
protected:
	List<int> l1;
	List<string> l2;
};

TEST_F(ListPushTest, PushBackStringWorks) {
	l2.pushBack("rty");
	l2.pushBack("qwe");
	EXPECT_EQ(l2.getSize(), 2);
	EXPECT_EQ(l2.getBack(), "qwe");

}

TEST_F(ListPushTest, PushFrontStringWorks) {
	l2.pushFront("rty");
	l2.pushFront("qwe");
	EXPECT_EQ(l2.getSize(), 2);
	EXPECT_EQ(l2.getFront(), "qwe");
}

TEST_F(ListPushTest, PushBackIntWorks) {
	l1.pushBack(5);
	l1.pushBack(1);
	EXPECT_EQ(l1.getSize(), 2);
	EXPECT_EQ(l1.getBack(), 1);
}

TEST_F(ListPushTest, PushFrontIntWorks) {
	l1.pushFront(3);
	l1.pushFront(10);
	EXPECT_EQ(l1.getSize(), 2);
	EXPECT_EQ(l1.getFront(), 10);
}


/*
* @brief Класс ListTest. Используется для дальнейшего тестирования класса List.
*/
class ListTest : public testing::Test {
protected:
	List<int> l1;
	List<string> l2;
	void SetUp() override {
		l1.pushBack(1);
		l1.pushBack(5);
		l2.pushFront("qwe");
	}
};

TEST_F(ListTest, GetElementIntWorks) {
	l1.pushBack(10);
	l1.pushBack(15);
	EXPECT_EQ(l1.getElement(2), 10);
	EXPECT_EQ(l1.getElement(3), 15);
	EXPECT_EQ(l1.getElement(0), 1);
}

TEST_F(ListTest, GetElementStringWorks) {
	l2.pushBack("---");
	l2.pushBack("rty");
	EXPECT_EQ(l2.getElement(1), "---");
}

TEST_F(ListTest, CopyConstructorIntWorks) {
	List<int> l3 = List<int>(l1);
	for (size_t i = 0; i < l1.getSize(); i++)
	{
		EXPECT_EQ(l3.getElement(i), l1.getElement(i));
	}
}

TEST_F(ListTest, CopyConstructorStringWorks) {
	List <string> l3 = List<string>(l2);
	for (size_t i = 0; i < l2.getSize(); i++)
	{
		EXPECT_TRUE(l2.getElement(i).compare(l3.getElement(i)) == 0);
	}
}

TEST_F(ListTest, PopFrontThrowsLogicError) {
	List <int> l3;
	EXPECT_THROW(l3.popFront(), logic_error);
}

TEST_F(ListTest, PopFrontWorks ) {
	l1.popFront();
	EXPECT_EQ(l1.getSize(), 1);

	l2.popFront();
	EXPECT_EQ(l2.getSize(), 0);
}

TEST_F(ListTest, PopBackThrowsLogicError) {
	List <int> l3;
	EXPECT_THROW(l3.popBack(), logic_error);
}

TEST_F(ListTest, PopBackWorks) {
	l1.popBack();
	EXPECT_EQ(l1.getSize(), 1);

	l2.popBack();
	EXPECT_EQ(l2.getSize(), 0);
}

TEST_F(ListTest, DeleteElementThrowsOutOfRange) {
	EXPECT_THROW(l1.deleteELement(4), out_of_range);
}

TEST_F(ListTest, DeleteElementWorks) {
	l1.pushFront(10);
	l1.deleteELement(1);
	std::vector<int> v3 = { 10, 5 };
	for (size_t i = 0; i < v3.size(); i++)
	{
		EXPECT_EQ(l1.getElement(i), v3[i]);
	}
}

TEST_F(ListTest, InsertElementThrowsOutOfRange) {
	EXPECT_THROW(l1.insertElement(14, 4), out_of_range);
}

TEST_F(ListTest, InserElementIntWorks) {
	l1.insertElement(3, 1);
	std::vector<int> v3 = { 1, 3, 5 };
	for (size_t i = 0; i < v3.size(); i++)
	{
		EXPECT_EQ(l1.getElement(i), v3[i]);
	}
}

TEST_F(ListTest, InsertElementStringWorks) {
	l2.pushBack("rty");
	l2.insertElement("---", 1);
	std::vector<string> v3 = { "qwe", "---", "rty" };
	for (size_t i = 0; i < v3.size(); i++)
	{
		EXPECT_TRUE(l2.getElement(i).compare(v3[i]) == 0);
	}
}

TEST_F(ListTest, GetElementThrowsOutOfRange) {
	EXPECT_THROW(l1.deleteELement(4), out_of_range);
}

TEST_F(ListTest, DeleteAllWorks) {
	EXPECT_NO_FATAL_FAILURE(l1.deleteAll());
	EXPECT_EQ(l1.getSize(), 0);
}

