#include <cppunit/extensions/HelperMacros.h>

class test_chessboard : public CPPUNIT_NS::TestCase {

    private:
	CPPUNIT_TEST_SUITE(test_chessboard);
	CPPUNIT_TEST(test_case_1);
	CPPUNIT_TEST(test_case_2);
	CPPUNIT_TEST(test_case_3);
	CPPUNIT_TEST(test_case_4);
	CPPUNIT_TEST(test_case_5);
	CPPUNIT_TEST(test_case_6);
	CPPUNIT_TEST(test_case_7);
	CPPUNIT_TEST(test_case_8);
	CPPUNIT_TEST(test_case_9);
	CPPUNIT_TEST(test_case_10);
	CPPUNIT_TEST(test_case_11);
	CPPUNIT_TEST(test_case_12);
	CPPUNIT_TEST(test_case_13);
	CPPUNIT_TEST_SUITE_END();

    public:
	void setUp() override { }
	void tearDown() override { }

    protected:
	void test_case_1();
	void test_case_2();
	void test_case_3();
	void test_case_4();
	void test_case_5();
	void test_case_6();
	void test_case_7();
	void test_case_8();
	void test_case_9();
	void test_case_10();
	void test_case_11();
	void test_case_12();
	void test_case_13();
};

CPPUNIT_TEST_SUITE_REGISTRATION(test_chessboard);
