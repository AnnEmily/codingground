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

//  ResultManager::Verbosity verbosity = ResultManager::verbosity_min ;
    ResultManager::Verbosity verbosity = ResultManager::verbosity_normal ;
//  ResultManager::Verbosity verbosity = ResultManager::verbosity_max ;
    
    //-------------- Don't edit below -------------
    
    cout << endl << "Target = " << target << endl;
    cout << "Values = " ;
    
    vector<int> source (values, values + sizeof(values) / sizeof(int) );
    
    for (vector<int>::const_iterator i = source.begin(); i != source.end(); ++i)
            cout << *i << ' ' ;
            
    cout << endl << endl ;
        
    ResultManager resultManager (target, verbosity, stopCondition) ;
    Result        result (Result::opIsInit, source, 0, NULL, &resultManager);
   
    if (!resultManager.WasTargetFound())
    {
        int    bestResult;
        string opString = resultManager.GetClosestResult (bestResult);
        
        cout << "Target not found. Closest result was : " ;
        cout << opString << " = " << bestResult ;
    }
        
    cout << endl ;
    
    return 0;
}
