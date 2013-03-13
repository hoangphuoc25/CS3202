#ifndef T4_TESTWRAPPER_H
#define T4_TESTWRAPPER_H

#include <string>
#include <iostream>
#include <list>

#include "AbstractWrapper.h"
#include "../../SPA/QueryEvaluator.h"

class TestWrapper: public AbstractWrapper {
public:
    /// Default constructor
    TestWrapper();

    /// Destructor
    ~TestWrapper();

    /// Method for parsing the SIMPLE source
    /// @filename name of the source file
    virtual void parse(std::string filename);
  
    /// method for evaluating a query
    /// @param query the PQL query string
    /// @param results a reference to a list of strings for storing
    ///                the evaluation results
    virtual void evaluate(std::string query,
            std::list<std::string>& results);

private:
    QueryEvaluator evaluator;
};

#endif
