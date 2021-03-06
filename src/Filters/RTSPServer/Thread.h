#pragma once


class Thread
{
public:
    Thread() :
        m_hThread(NULL),
        m_idThread(0),
        m_evExit(true)    // manual reset
    {}

    void StartThread()
    {
        if (m_hThread == NULL)
        {
            m_evExit.Reset();
            m_hThread = CreateThread(NULL, 0, DispatchThread, this, 0, &m_idThread);
        }
    }

    void StopThread()
    {
        m_evExit.Set();
        if (m_hThread != NULL)
        {
            if (GetCurrentThreadId() != m_idThread)
            {
                WaitForSingleObject(m_hThread, INFINITE);
            }
            CloseHandle(m_hThread);
            m_hThread = NULL;
        }
    }

    bool ShouldExit()
    {
        return m_evExit.Check() ? true : false;
    }
    HANDLE ExitEvent()
    {
        return m_evExit;
    }


private:
    static DWORD WINAPI DispatchThread(void *pContext)
    {
        Thread *pThis = (Thread *) pContext;
        return pThis->ThreadProc();
    }

    virtual DWORD ThreadProc()
    {
        return 0;
    }

private:
    HANDLE m_hThread;
    DWORD m_idThread;
    CAMEvent m_evExit;
};
