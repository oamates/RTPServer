//
// SmartPtr -- very basic smart pointer template
//
// Provides thread-safe auto-delete for shared pointers, using
// reference counting.
//
// (c) 2003-4 Geraint Davies. Freely Redistributable.


// Destructors
//
// You can use smart_ptr/smart_array with types that are not fully defined,
// just as you can with pointers:
//      class CPointedTo;   // defined elsewhere
//      smart_ptr<CPointedTo> ptr;
//
// However the type (CPointedTo) must be fully defined when the
// destructor for the smart_ptr (ptr) is required.
// If the smart_ptr is a member of a class CYourClass, and your class has no
// explicit destructor, then the full type definition of CPointedTo is
// required at your class definition (for the default destructor). You can
// get round this by declaring an empty destructor and defining it 
// in the cpp module (where CPointedTo is fully defined).


#ifndef __SMARTPTR_H_
#define __SMARTPTR_H_

// thread-safe shared count
// -- stored separately -- the smart_ptr has a pointer
// to one of these and to the object.
class SharedPtrCount
{
public:
    SharedPtrCount()
    : m_cRef(1)
    {
    }
    void Increment()
    {
        InterlockedIncrement(&m_cRef);
    }
    bool Decrement()
    {
        return (InterlockedDecrement(&m_cRef) == 0);
    }
private:
    SharedPtrCount(const SharedPtrCount& r);
    SharedPtrCount operator=(const SharedPtrCount& r);

    long m_cRef;
};

// smart pointer. Lifetime management via reference count.
// Reference count is stored separately and each smart pointer
// has a pointer to the reference count and to the object.
// Thread safe (using InterlockedIncrement)
// 
// This version for single objects. For objects allocated with new[],
// see smart_array
template<class T>
class SmartPtr
{
public:
    ~SmartPtr()
    {
        Release();
    }

    // initialisation
    SmartPtr()
    : m_pObject(NULL),
      m_pCount(NULL)
    {
    }

    SmartPtr(T* pObj)
    {
        m_pObject = pObj;
        AssignNew();
    }

    SmartPtr(const SmartPtr<T>& ptr)
    {
        m_pObject = ptr.m_pObject;
        m_pCount = ptr.m_pCount;
		if (m_pCount != NULL)
		{
			m_pCount->Increment();
		}
    }

    SmartPtr& operator=(const SmartPtr<T>& r)
    {
        Release();
        m_pObject = r.m_pObject;
        m_pCount = r.m_pCount;
        if (m_pCount != NULL)
        {
            m_pCount->Increment();
        }
        return *this;
    }
    SmartPtr& operator=(T* p)
    {
        Release();
        m_pObject = p;
        AssignNew();
        return *this;
    }
    SmartPtr& operator=(int null)
    {
        if (null != 0)
        {
            throw E_INVALIDARG;
        }
        Release();
        m_pObject = 0;
        m_pCount = NULL;
        return *this;
    }

    // access 

    T* operator->() const
    {
        return m_pObject;
    }
    T& operator*() const
    {
        return *m_pObject;
    }
    operator T*() const
    {
        return m_pObject;
    }

    // comparison
    bool operator!() const
    {
        return (m_pObject == 0);
    }
    bool operator==(int null) const
    {
        if (null != 0) {
            throw E_INVALIDARG;
        } else {
            return (m_pObject == NULL) ? true : false;
        }
    }


private:
    void AssignNew()
    {
        m_pCount = new SharedPtrCount();
    }
    void Release()
    {
        if (m_pCount)
        {
            if (m_pCount->Decrement())
            {
                delete m_pCount;
                delete m_pObject;
            }
        }
        m_pObject = NULL;
        m_pCount = NULL;
    }

private:
    T* m_pObject;
    SharedPtrCount* m_pCount;
};

// smart pointer to array (allocated with new[])
// 
// lightweight, not bounds-checked, not auto-sizing.
template<class T>
class SmartArray
{
public:
    ~SmartArray()
    {
        Release();
    }

    // initialisation
    SmartArray()
    : m_pObject(NULL),
      m_pCount(NULL)
    {
    }

    SmartArray(T* pObj)
    {
        m_pObject = pObj;
        AssignNew();
    }

    SmartArray(const SmartArray<T>& ptr)
    {
        m_pObject = ptr.m_pObject;
        m_pCount = ptr.m_pCount;
		if (m_pCount != NULL)
		{
			m_pCount->Increment();
		}
    }

    SmartArray& operator=(const SmartArray<T>& r)
    {
        Release();
        m_pObject = r.m_pObject;
        m_pCount = r.m_pCount;
		if (m_pCount != NULL)
		{
			m_pCount->Increment();
		}
        return *this;
    }
    SmartArray& operator=(T* p)
    {
        Release();
        m_pObject = p;
        AssignNew();
        return *this;
    }
    SmartArray& operator=(int null)
    {
        if (null != 0)
        {
            throw E_INVALIDARG;
        }
        Release();
        m_pObject = 0;
        m_pCount = NULL;
        return *this;
    }

    // access 
    operator T*() const
    {
        return m_pObject;
    }

    // comparison
    bool operator!() const
    {
        return (m_pObject == 0);
    }
    bool operator==(int null) const
    {
        if (null != 0) {
            throw E_INVALIDARG;
        } else {
            return (m_pObject == NULL) ? true : false;
        }
    }


private:
    void AssignNew()
    {
        m_pCount = new SharedPtrCount();
    }
    void Release()
    {
        if (m_pCount)
        {
            if (m_pCount->Decrement())
            {
                delete m_pCount;
                delete[] m_pObject;
            }
        }
        m_pObject = NULL;
        m_pCount = NULL;
    }
private:
    T* m_pObject;
    SharedPtrCount* m_pCount;
};



#endif // __SMARTPTR_H_

