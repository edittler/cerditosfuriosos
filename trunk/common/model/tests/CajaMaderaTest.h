/** 
 * Generated CppUnit test driver template.
 * To build it, add the following line at the end of
 * your existing Makefile:
 *    include model/tests/CajaMaderaTest.mk
 * Build the model/tests/CajaMaderaTest target from the Make Target view
 */

#ifndef TEST_CajaMaderaTest
#define TEST_CajaMaderaTest

#ifdef ECUT_MAIN

#include "cppunit/extensions/HelperMacros.h"

class CajaMaderaTest : public CPPUNIT_NS::TestFixture {
public:
	void setUp();
	void tearDown();
	void testCajaMadera();
	void testDCajaMadera();
	CPPUNIT_TEST_SUITE(CajaMaderaTest);
	CPPUNIT_TEST(testCajaMadera);
	CPPUNIT_TEST(testDCajaMadera);
	CPPUNIT_TEST_SUITE_END();
};

#endif /* ECUT_MAIN */

#endif /*CAJAMADERATEST*/
