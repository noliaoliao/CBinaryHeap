#pragma once
//#include "stdafx.h"

#define SWAP(a, b) \
    a^=b; b^=a; a^=b;

//#define __DEBUG__  
#ifdef __DEBUG__  
#define DEBUG(format,...) printf(""format"",##__VA_ARGS__)  
#else  
#define DEBUG(format,...)  
#endif

class CBinaryHeap
{
    public:
        CBinaryHeap(int nMaxSize = 128)
        {
            m_pHeapArray = new int[nMaxSize];
            m_nHeapSize = nMaxSize;
            m_nDataCount = 0;
        }
        ~CBinaryHeap()
        {
            delete m_pHeapArray;
            m_pHeapArray = NULL;
            DEBUG("call ~~~~");
        }
        bool pushHeap(int nVal);
        int  popHeap();
        bool isEmpty();
        int  getLength();
        void printHeap();
    private:
        int *m_pHeapArray;
        int m_nHeapSize;
        int m_nDataCount;
};


bool CBinaryHeap::pushHeap(int nVal)
{
    //bool bRet = false;
    if(m_nHeapSize == m_nDataCount) return false;   //堆满

    m_pHeapArray[m_nDataCount] = nVal;              //新入堆的元素总是在数组最后
    m_nDataCount++;

    //调整堆的顺序
    //如果子节点比父节点小，则交换两者的值
    //依次往上和父节点比较，上升操作
    int nIndex = m_nDataCount - 1;
    while(m_pHeapArray[nIndex] < m_pHeapArray[(nIndex-1)/2])
    {
        SWAP(m_pHeapArray[nIndex],m_pHeapArray[(nIndex-1)/2]);
        nIndex = (nIndex - 1) / 2;
    }

    return true;
}


int CBinaryHeap::popHeap()
{
    if(m_nDataCount == 0) return 0;     //堆为空
    int nRet = m_pHeapArray[0];         //出堆的总是第一个元素
    int nIndex = 0;
    m_nDataCount--;

    //将最后一个元素放到最前，执行下降操作
    SWAP(m_pHeapArray[0],m_pHeapArray[m_nDataCount]);
    while(nIndex < m_nDataCount)
    {
        int nlChild = nIndex * 2 + 1;
        int nrChild = nIndex * 2 + 2;

        //左右孩子节点同时存在
        if(nlChild < m_nDataCount && nrChild < m_nDataCount)
        {
            //最后一个元素必定比左右孩子中的较小的那个大
            //和较小的交换
            if(m_pHeapArray[nlChild] < m_pHeapArray[nrChild])
            {
                SWAP(m_pHeapArray[nIndex],m_pHeapArray[nlChild]);
                nIndex = nlChild;
            }
            else
            {
                SWAP(m_pHeapArray[nIndex],m_pHeapArray[nrChild]);
                nIndex = nrChild;
            }
        }
        //只有左孩子,且比左孩子大
        else if(nlChild < m_nDataCount && m_pHeapArray[nIndex] > m_pHeapArray[nlChild])
        {
            SWAP(m_pHeapArray[nIndex],m_pHeapArray[nlChild]);
            nIndex = nlChild;
        }
        else
        {
            break;
        }
    }
    
    return nRet;
}


bool CBinaryHeap::isEmpty()
{
    return 0 == m_nDataCount;
}


int CBinaryHeap::getLength()
{
    return m_nDataCount;
}


void CBinaryHeap::printHeap()
{
    for(int i = 0; i < m_nDataCount; i++)
    {
        DEBUG("%d",m_pHeapArray[i]);
    }
}