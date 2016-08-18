
#include "Result.h"
#include <iostream>

using namespace std;

Result::Result (OpIs operation, vector<int> values, int cumulated, 
                Result *previousNode, ResultManager *resultManager)
    :
        m_previousNode (previousNode),
        m_manager      (resultManager),
        m_operation    (operation),
        m_nextValues   (values),
        m_cumulated    (cumulated),
        m_plus         (NULL),
        m_minus        (NULL),
        m_times        (NULL),
        m_divide       (NULL)
{
    // Safety
        
    if (m_nextValues.empty())
    {
        return ;
    }
    
    if (m_manager == NULL)
    {
        if (m_previousNode == NULL)
        {
            cout << "Nothing will be printed at all !" << endl ;
            return ;
        }
        else
        {
            m_manager = m_previousNode->GetResultManager () ;
        }
    }
    
    // Initialize
        
    m_uid           = m_manager->GetNewUid();
    m_stopCondition = m_manager->GetStopCondition();
        
    m_operand = m_nextValues.back();
    m_nextValues.pop_back();
        
    if (m_previousNode != NULL)
    {
        m_opString = "(" + m_previousNode->GetOpString();
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
        
    m_manager->PrintNodeCreated (m_uid, m_previousNode, m_cumulated, strOp, m_operand, m_nextValues) ;
    
    // Compute result so far
        
    if (m_operation == opIsInit)
    {
        // This is the root node : initialize only
        
        m_opString  = std::to_string(m_operand);
        m_cumulated = m_operand;
    }
    else
    {
        // This is a branch or leaf node : compute from previous result
        
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
                             m_manager->PrintNodeDropped (m_uid) ;
                             return;
        }

        m_opString += strOp;
        m_opString += std::to_string(m_operand);
        m_opString += ")";
    }
        
    // Recurse or return
    
    if (m_nextValues.empty())
    {
        // Report final result to manager
        m_manager->SetResult (m_cumulated, m_opString);
    }
    else
    {
        // Go deeper as long as needed
        m_plus = new Result (opIsPlus, m_nextValues, m_cumulated, this);
        
        if (GoDeeper())
            m_minus  = new Result (opIsMinus,  m_nextValues, m_cumulated, this);
        
        if (GoDeeper())
            m_times  = new Result (opIsTimes,  m_nextValues, m_cumulated, this);
        
        if (GoDeeper())
            m_divide = new Result (opIsDivide, m_nextValues, m_cumulated, this);
    }
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
 