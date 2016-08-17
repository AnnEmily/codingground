#pragma once

#include <string>

using namespace std;

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
    
    void          SetResult        (int target, int result, string opString);
    bool          WasTargetFound   () ;
    int           GetNewUid        () ;
    Verbosity     GetVerbosity     () {return m_verbosity;} ;
    StopCondition GetStopCondition () {return m_stopCondition;} ;
    string        GetClosestResult (int & result) ;
    
private:
    int           m_uid ;
    Verbosity     m_verbosity ;
    StopCondition m_stopCondition;
    int           m_target;
    int           m_bestDiff;
    int           m_bestResult;
    string        m_opString;
} ;
