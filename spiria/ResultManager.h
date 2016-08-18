#pragma once

#include <string>
#include <vector>

using namespace std;

class Result;

class ResultManager
{
public:
    enum Verbosity
    {
        verbosity_max,
        verbosity_normal,
        verbosity_min
    };
    
    enum StopCondition
    {
        stop_onTarget,
        stop_atEnd
    };
    
    ResultManager (int target, Verbosity verbosity, StopCondition stopCondition);
    
    void          SetResult         (int result, string opString);
    bool          WasTargetFound    () {return m_bestDiff == 0;} ;
    int           GetNewUid         () ;
    StopCondition GetStopCondition  () {return m_stopCondition;} ;
    int           GetSolutionCount  () {return m_solutionCount;} ;
    int           GetOperationCount () {return m_operationCount;} ;
    string        GetClosestResult  (int & result) ;
    void          PrintNodeCreated  (int uid, Result *previousNode, int cumulated, string operation, int operand, vector<int> nextValues) ;
    void          PrintNodeDropped  (int uid) ;
    void          PrintNodeDeleted  (int uid) ;
    
private:
    int           m_uid ;
    Verbosity     m_verbosity ;
    StopCondition m_stopCondition ;
    int           m_target ;
    int           m_bestDiff ;
    int           m_bestResult ;
    string        m_opString ;
    int           m_solutionCount ;
    int           m_operationCount ;
} ;
