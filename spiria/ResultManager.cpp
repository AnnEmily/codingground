
#include "ResultManager.h"

#include <iostream>
#include <limits>

ResultManager::ResultManager (int target, Verbosity verbosity, StopCondition stopCondition)
    :
        m_uid           (0),
        m_verbosity     (verbosity),
        m_stopCondition (stopCondition),
        m_target        (target),
        m_bestDiff      (numeric_limits<int>::max()),
        m_bestResult    (0)
{} ;

int ResultManager::GetNewUid ()
{
    m_uid++;
    return m_uid;
} ;

void ResultManager::SetResult (int result, string opString)
{
    int currentDiff = abs (result-m_target);
    
    if (currentDiff < m_bestDiff)
    {
        m_bestResult = result ;
        m_bestDiff   = currentDiff;
        m_opString   = opString;
    }
    
    // Verbose as required
        
    if (m_verbosity == verbosity_none)
    {
        if (currentDiff == 0)
        {
            cout << opString << "=" << result << " .............. target found" << endl;
        }
    }
    else
    {
        cout << opString << "=" << result ;
        
        if (currentDiff == 0)
        {
            cout << " .............. target found" << endl;
        }
        else
        {
            cout << endl;
        }
    }
} ;

string ResultManager::GetClosestResult (int & result)
{
    result = m_bestResult ;
    return m_opString ;
}

void ResultManager::PrintBranchDropped (int uid)
{
    if (m_verbosity == verbosity_all)
    {
        cout << "  branch from node " << uid <<" dropped" << endl;
    }
}

void ResultManager::PrintNodeDeleted (int uid)
{
    if (m_verbosity == verbosity_all)
    {
        cout << "Deleting node " << m_uid << endl;
    }
}
