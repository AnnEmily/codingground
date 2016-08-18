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
        verbosity_all,
        verbosity_operation,
        verbosity_none
    };
    
    enum StopCondition
    {
        stop_onTarget,
        stop_atEnd
    };
    
    ResultManager (int target, Verbosity verbosity, StopCondition stopCondition);
    
    void          SetResult          (int result, string opString);
    bool          WasTargetFound     () {return m_bestDiff == 0;} ;
    int           GetNewUid          () ;
    Verbosity     GetVerbosity       () {return m_verbosity;} ;
    StopCondition GetStopCondition   () {return m_stopCondition;} ;
    string        GetClosestResult   (int & result) ;
    void          PrintNodeCreated   (int uid, Result *previousNode, int cumulated, string operation, int operand, vector<int> nextValues) ;
    void          PrintBranchDropped (int uid) ;
    void          PrintNodeDeleted   (int uid) ;
    
private:
    int           m_uid ;
    Verbosity     m_verbosity ;
    StopCondition m_stopCondition;
    int           m_target;
    int           m_bestDiff;
    int           m_bestResult;
    string        m_opString;
} ;
