#include <iostream>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TextTestRunner.h>

int main(int argc, char *argv[]) {
	std::cout << "compile con las librerias de CppUnit" << std::endl;

	/* Fragmento de un ejemplo extraido de 
	 * http://lahosken.san-francisco.ca.us/frivolity/prog/cppunit/
	 */

	// Get the top level suite from the registry
	CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();

	// Adds the test to the list of test to run
	CppUnit::TextTestRunner runner;
	runner.addTest( suite );

	return 0;
}
