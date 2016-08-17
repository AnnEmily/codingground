
#include "ResultManager.h"

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

void ResultManager::SetResult (int target, int result, string opString)
{
    if (target != m_target)
    {
        // Ignore this call. Target is not the same as the one declared on construction
        return;
    }
    
    int currentDiff = abs (result-target);
    
    if (currentDiff < m_bestDiff)
    {
        m_bestResult = result ;
        m_bestDiff   = currentDiff;
        m_opString   = opString;
    }
} ;

bool ResultManager::WasTargetFound ()
{
    return m_bestDiff == 0;
};

string ResultManager::GetClosestResult (int & result)
{
    result = m_bestResult ;
    return m_opString ;
}