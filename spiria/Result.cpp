
#include "Result.h"
#include <iostream>

using namespace std;

Result::Result (OpIs operation, vector<int> values, int cumulated, 
                Result *previous, ResultManager *resultManager)
    :
        m_previous  (previous),
        m_manager   (resultManager),
        m_plus      (NULL),
        m_minus     (NULL),
        m_times     (NULL),
        m_divide    (NULL),
        m_operation (operation),
        m_available (values),
        m_cumulated (cumulated),
        m_verbosity (ResultManager::verbosity_none)
{
    // Safety
        
    if (m_available.empty())
    {
        return ;
    }
    
    if (m_manager == NULL)
    {
        if (m_previous == NULL)
        {
            cout << "Nothing will be printed at all !" << endl ;
            return ;
        }
        else
        {
            m_manager = m_previous->GetResultManager () ;
        }
    }
    
    // Initialize
        
    m_uid           = m_manager->GetNewUid();
    m_verbosity     = m_manager->GetVerbosity();
    m_stopCondition = m_manager->GetStopCondition();
        
    m_operand = m_available.back();
    m_available.pop_back();
        
    if (m_previous != NULL)
    {
        m_opString = "(" + m_previous->GetOpString();
    }
        
    std:string strOp;
        
    switch (m_operation)
    {
        case opIsPlus:   strOp = "+" ;
                         break ;
        case opIsMinus:  strOp = "-" ;
                         break ;
        case opIsTimes:  strOp = "*" ;
                         break ;
        case opIsDivide: strOp = "/" ;
                         break ;
        default:         strOp = "init";
                         break;
    }

    if (m_verbosity == ResultManager::verbosity_all)
    {
        cout << "Creating node " << m_uid ;
        
        if (m_previous)
            cout << " from node " << m_previous->GetUid() << " :" ;
        else
            cout << " from NULL   :" ;
        
        cout << "  cumulated = " << m_cumulated
             << ", op "          << strOp
             << ", operand = "   << m_operand ;
             
        if (!m_available.empty())
        {
            cout << ", next = " ;
        
            for (std::vector<int>::const_iterator i = m_available.begin(); i != m_available.end(); ++i)
                cout << *i << ' ' ;
        }
            
        cout << endl;
    }
        
    // Compute result
        
    if (m_operation != opIsInit)
    {
        switch (m_operation)
        {
            case opIsPlus:   m_cumulated = m_cumulated + m_operand ;
                             break ;
                         
            case opIsMinus:  m_cumulated = m_cumulated - m_operand ;
                             break ;
                         
            case opIsTimes:  m_cumulated = m_cumulated * m_operand ;
                             break ;
            
            case opIsDivide: if (m_operand != 0)
                             {
                                int quotient = m_cumulated / m_operand ;
                                
                                if (m_operand*quotient == m_cumulated)
                                {
                                    m_cumulated = quotient ;
                                    break ;
                                }
                             }

                             // Division is not allowed (result not integer or divide by zero)
                             m_manager->PrintBranchDropped (m_uid) ;
                             return;
        }

        m_opString += strOp;
        m_opString += std::to_string(m_operand);
        m_opString += ")";
    }
    else
    {
        m_opString  = std::to_string(m_operand);
        m_cumulated = m_operand;
    }
        
    if (m_available.empty())
    {
        // Report final result to manager
        m_manager->SetResult (m_cumulated, m_opString);
        return;
    }
    
    // Go deeper if needed
    
    if (GoDeeper())
        m_plus   = new Result (opIsPlus,   m_available, m_cumulated, this);
        
    if (GoDeeper())
        m_minus  = new Result (opIsMinus,  m_available, m_cumulated, this);
        
    if (GoDeeper())
        m_times  = new Result (opIsTimes,  m_available, m_cumulated, this);
        
    if (GoDeeper())
        m_divide = new Result (opIsDivide, m_available, m_cumulated, this);
};
    
Result::~Result()
{
    if (m_plus)
        delete m_plus;
            
    if (m_minus)
        delete m_minus;
        
    if (m_times)
        delete m_times;
        
    if (m_divide)
        delete m_divide;

    if (m_manager)
        m_manager->PrintNodeDeleted (m_uid) ;
};

bool Result::GoDeeper ()
{ 
    return ! (m_stopCondition == ResultManager::stop_onTarget && m_manager->WasTargetFound () );
};
 
