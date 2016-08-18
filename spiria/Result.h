#pragma once

#include <vector>
#include "ResultManager.h"

using namespace std;

class Result
{
public:

    enum OpIs
    {
        opIsInit,
        opIsPlus,
        opIsMinus,
        opIsTimes,
        opIsDivide
    };
    
    Result (OpIs operation, vector<int> values, int cumulated, 
            Result *previous, ResultManager *resultManager = NULL);
    ~Result();
    
    bool           GoDeeper         () ;
    string         GetOpString      () {return m_opString;} ;
    int            GetUid           () {return m_uid;     } ;
    ResultManager* GetResultManager () {return m_manager; } ;
    
private:
    Result        *m_previous;
    ResultManager *m_manager;
    
    ResultManager::Verbosity     m_verbosity;
    ResultManager::StopCondition m_stopCondition;
    int                          m_uid;
    
    vector<int>   m_available;
    int           m_cumulated;
    int           m_operand;
    
    OpIs          m_operation;
    string        m_opString ;
    
    Result       *m_plus;
    Result       *m_minus;
    Result       *m_times;
    Result       *m_divide;
} ; 
