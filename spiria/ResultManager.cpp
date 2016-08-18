
#include "ResultManager.h"
#include "Result.h"

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

void ResultManager::PrintNodeCreated (int uid, Result *previousNode, int cumulated, string operation, int operand, vector<int> nextValues)
{
    if (m_verbosity == verbosity_all)
    {
        cout << "Creating node " << uid ;
        
        if (previousNode)
            cout << " from node " << previousNode->GetUid() << " :" ;
        else
            cout << " from NULL   :" ;
        
        cout << "  cumulated = " << cumulated
             << ", op "          << operation
             << ", operand = "   << operand ;
             
        if (!nextValues.empty())
        {
            cout << ", next = " ;
        
            for (std::vector<int>::const_iterator i = nextValues.begin(); i != nextValues.end(); ++i)
                cout << *i << ' ' ;
        }
            
        cout << endl;
    } 
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
        cout << "Deleting node " << uid << endl;
    }
}
 
