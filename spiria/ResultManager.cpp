#include "ResultManager.h"
#include "Result.h"
 
#include <iomanip>
#include <iostream>
#include <limits>
 
ResultManager::ResultManager (int target, Verbosity verbosity, StopCondition stopCondition)
    :
     m_uid            (0),
     m_verbosity      (verbosity),
     m_stopCondition  (stopCondition),
     m_target         (target),
     m_bestDiff       (numeric_limits<int>::max()),
     m_bestResult     (0),
     m_solutionCount  (0),
     m_operationCount (0)
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
    
    if (currentDiff == 0)
        m_solutionCount++;
        
    m_operationCount++ ;
    
    // Verbose as required
         
    if (m_verbosity == verbosity_min)
    {
        if (currentDiff == 0)
        {
            cout << std::setw(3) << m_solutionCount << " : " << opString << "=" << result << " .............. target found" << endl;
        }
    }
    else
    {
        cout << std::setw(5) << m_operationCount << " : "<<  opString << "=" << result ;
         
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
    if (m_verbosity == verbosity_max)
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
 
void ResultManager::PrintNodeDropped (int uid)
{
    if (m_verbosity == verbosity_max)
    {
        cout << "  branch from node " << uid <<" dropped" << endl;
    }
}
 
void ResultManager::PrintNodeDeleted (int uid)
{
    if (m_verbosity == verbosity_max)
    {
        cout << "Deleting node " << uid << endl;
    }
}
