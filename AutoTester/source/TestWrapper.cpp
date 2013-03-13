#include <list>
#include <string>
#include "TestWrapper.h"

using std::list;
using std::string;

// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
  if (wrapper == 0) wrapper = new TestWrapper;
  return wrapper;
}
// Do not modify the following line
volatile bool TestWrapper::GlobalStop = false;

// a default constructor
TestWrapper::TestWrapper(): evaluator()
{
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
}

// method for parsing the SIMPLE source
void TestWrapper::parse(string filename)
{
	// call your parser to do the parsing
    // ...rest of your code...
    this->evaluator.parseSimple_from_file(filename);
}

// method to evaluating a query
void TestWrapper::evaluate(string query, list<string>& results)
{
    // call your evaluator to evaluate the query here
    // ...code to evaluate query...

    // store the answers to the query in the results list (it is initially empty)
    // each result must be a string.
    this->evaluator.evaluate(query, results);
}
