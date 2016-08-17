
#include "Result.h"
#include <iostream>

using namespace std;

Result::Result (OpIs operation, vector<int> values, int target, int cumulated, 
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
        m_target    (target),
        m_cumulated (cumulated),
        m_verbosity (ResultManager::verbosity_none)
{
    // Safety
        
    if (m_available.empty() ||
        m_manager == NULL      )
    {
        return ;
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
        cout << "Created node " << m_uid ;
        
        if (m_previous)
            cout << " from node " << m_previous->GetUid() << " :" << endl ;
        else
            cout << " from NULL   :" << endl ;
        
        cout << "  cumulated = " << m_cumulated
             << ", operation "  << strOp
             << ", operand = "  << m_operand 
             << ", next operands = " ;
        
        for (std::vector<int>::const_iterator i = m_available.begin(); i != m_available.end(); ++i)
            cout << *i << ' ' ;
            
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
                                }
                                else
                                {
                                    // Division is not allowed
                                    if (m_verbosity == ResultManager::verbosity_all)
                                    {
                                        cout << "  branch from node " << m_uid <<" dropped" << endl;
                                    }
                                        
                                    return;
                                }
                             }
                             else
                             {
                                // Division is not allowed
                                if (m_verbosity == ResultManager::verbosity_all)
                                {
                                    cout << "  branch from node " << m_uid <<" dropped" << endl;
                                }  
                             }
                             break ;
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
    
        m_manager->SetResult (m_target, m_cumulated, m_opString);
        
        // Verbose as required
        
        if (m_verbosity == ResultManager::verbosity_none)
        {
            if (m_cumulated == m_target)
            {
                cout << m_opString << "=" << m_cumulated << " .............. target found" << endl;
            }
        }
        else
        {
            cout << m_opString << "=" << m_cumulated ;
        
            if (m_cumulated == m_target)
            {
                cout << " .............. target found" << endl;
                return;
            }
            else
            {
                cout << endl;
            }
        }
    }
    
    // Go deeper if needed
    
    if (GoDeeper())
        m_plus   = new Result (opIsPlus,   m_available, m_target, m_cumulated, this, m_manager);
        
    if (GoDeeper())
        m_minus  = new Result (opIsMinus,  m_available, m_target, m_cumulated, this, m_manager);
        
    if (GoDeeper())
        m_times  = new Result (opIsTimes,  m_available, m_target, m_cumulated, this, m_manager);
        
    if (GoDeeper())
        m_divide = new Result (opIsDivide, m_available, m_target, m_cumulated, this, m_manager);
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
        
    if (m_verbosity == ResultManager::verbosity_all)
    {
        cout << "Deleting node " << m_uid << endl;
    }
};

bool Result::GoDeeper ()
{ 
    return ! (m_stopCondition == ResultManager::stop_onTarget && m_manager->WasTargetFound () );
};
