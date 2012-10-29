#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

/*
 * Main usado en el makefile para correr las pruebas unitarias.
 */
int main_tests(int argc, char **argv) {
	std::cout << "compile con las librerias de CppUnit" << std::endl;

	/* Fragmento de un ejemplo extraido de
	 * http://lahosken.san-francisco.ca.us/frivolity/prog/cppunit/
	 */

	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	// CppUnit::TextUi::TestRunner runner;
	CppUnit::TextTestRunner runner;
	runner.addTest( suite );

	// Run the tests.
	bool wasSucessful = runner.run();

	// Return error code 1 if the one of test failed.
	return wasSucessful ? 0 : 1;
}
