#include <algorithm>
#include <iostream>
#include <vector>

#include "ResultManager.h"
#include "Result.h"

using namespace std;

int main()
{
    //-------- Change as needed for testing -------
    
    int target = 10 ;
    int values[] = {7,3,5,4};

    ResultManager::StopCondition stopCondition = ResultManager::stop_atEnd ;
//  ResultManager::StopCondition stopCondition = ResultManager::stop_onTarget ;

    ResultManager::Verbosity verbosity = ResultManager::verbosity_min ;
//  ResultManager::Verbosity verbosity = ResultManager::verbosity_normal ;
//  ResultManager::Verbosity verbosity = ResultManager::verbosity_max ;
    
    
    //-------------- Don't edit below -------------
    
    // Print source and target values
    
    cout << endl << "Target = " << target << endl;
    cout << "Values = " ;
    
    vector<int> source (values, values + sizeof(values) / sizeof(int) );
    std::sort (source.begin(), source.end()) ;
    
    for (vector<int>::const_iterator i = source.begin(); i != source.end(); ++i)
            cout << *i << ' ' ;
            
    cout << endl << endl ;
        
    // Try all permutations of the source vector
    
    ResultManager resultManager (target, verbosity, stopCondition) ;
    
    do
    {
        Result result (Result::opIsInit, source, 0, NULL, &resultManager);
        
        if (stopCondition == ResultManager::stop_onTarget && 
            resultManager.WasTargetFound ()                 )
            break ;
    } 
    while ( std::next_permutation (source.begin(), source.end()) );
    
    // Print a summary of operations and eventual solutions found
   
    cout << endl << resultManager.GetOperationCount() << " operations tested." << endl ;
    
    if (!resultManager.WasTargetFound())
    {
        int    bestResult;
        string opString = resultManager.GetClosestResult (bestResult);
        
        cout << "Target not found. Closest result was : " ;
        cout << opString << " = " << bestResult ;
    }
    else
    {
        cout << resultManager.GetSolutionCount() << " solutions found." ;
    }
        
    cout << endl << endl ;
    
    return 0;
}
