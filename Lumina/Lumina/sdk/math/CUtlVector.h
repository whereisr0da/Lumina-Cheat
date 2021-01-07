#pragma once

inline int UtlMemory_CalcNewAllocationCount( int nAllocationCount, int nGrowSize, int nNewSize, int nBytesItem )
{
	if ( nGrowSize )
	{
		nAllocationCount = ( ( 1 + ( ( nNewSize - 1 ) / nGrowSize ) ) * nGrowSize );
	}
	else
	{
		if ( !nAllocationCount )
		{
			// Compute an allocation which is at least as big as a cache line...
			nAllocationCount = ( 31 + nBytesItem ) / nBytesItem;
		}

		while ( nAllocationCount < nNewSize )
		{
			nAllocationCount *= 2;
		}
	}

	return nAllocationCount;
}

template <class T, class I = int> class CUtlMemory
{
public:
	inline bool IsIdxValid( I i ) const
	{
		long x = i;
		return ( x >= 0 ) && ( x < m_nAllocationCount );
	}
	T& operator[]( I i );
	const T& operator[]( I i ) const;
	T *Base()
	{
		return m_pMemory;
	}
	inline int NumAllocated() const
	{
		return m_nAllocationCount;
	}
	void Grow( int num )
	{
		Assert( num > 0 );

		auto oldAllocationCount = m_nAllocationCount;
		// Make sure we have at least numallocated + num allocations.
		// Use the grow rules specified for this memory (in m_nGrowSize)
		int nAllocationRequested = m_nAllocationCount + num;

		int nNewAllocationCount = UtlMemory_CalcNewAllocationCount( m_nAllocationCount, m_nGrowSize, nAllocationRequested, sizeof( T ) );

		// if m_nAllocationRequested wraps index type I, recalculate
		if ( ( int )( I )nNewAllocationCount < nAllocationRequested )
		{
			if ( ( int )( I )nNewAllocationCount == 0 && ( int )( I )( nNewAllocationCount - 1 ) >= nAllocationRequested )
			{
				--nNewAllocationCount; // deal w/ the common case of m_nAllocationCount == MAX_USHORT + 1
			}
			else
			{
				if ( ( int )( I )nAllocationRequested != nAllocationRequested )
				{
					// we've been asked to grow memory to a size s.t. the index type can't address the requested amount of memory
					Assert( 0 );
					return;
				}
				while ( ( int )( I )nNewAllocationCount < nAllocationRequested )
				{
					nNewAllocationCount = ( nNewAllocationCount + nAllocationRequested ) / 2;
				}
			}
		}

		m_nAllocationCount = nNewAllocationCount;

		if ( m_pMemory )
		{
			auto ptr = new unsigned char[ m_nAllocationCount * sizeof( T ) ];

			memcpy( ptr, m_pMemory, oldAllocationCount * sizeof( T ) );
			m_pMemory = ( T* )ptr;
		}
		else
		{
			m_pMemory = ( T* )new unsigned char[ m_nAllocationCount * sizeof( T ) ];
		}
	}
protected:
	T * m_pMemory;
	int m_nAllocationCount;
	int m_nGrowSize;
};

template< class T, class I >
inline T& CUtlMemory<T, I>::operator[]( I i )
{
	Assert( IsIdxValid( i ) );
	return m_pMemory[ i ];
}

template< class T, class I >
inline const T& CUtlMemory<T, I>::operator[]( I i ) const
{
	Assert( IsIdxValid( i ) );
	return m_pMemory[ i ];
}

template <class T>
inline void Destruct( T *pMemory )
{
	pMemory->~T();
}

template <class T>
inline T* Construct( T* pMemory )
{
	return ::new( pMemory ) T;
}

template< typename T, size_t SIZE, int nAlignment = 0 >
class CUtlMemoryFixed
{
public:
	// constructor, destructor
	CUtlMemoryFixed( int nGrowSize = 0, int nInitSize = 0 ) { Assert( nInitSize == 0 || nInitSize == SIZE ); }
	CUtlMemoryFixed( T* pMemory, int numElements ) { Assert( 0 ); }

	// Can we use this index?
	// Use unsigned math to improve performance
	bool IsIdxValid( int i ) const { return ( size_t )i < SIZE; }

	// Specify the invalid ('null') index that we'll only return on failure
	static const int INVALID_INDEX = -1; // For use with COMPILE_TIME_Assert
	static int InvalidIndex() { return INVALID_INDEX; }

	// Gets the base address
	T* Base() { if ( nAlignment == 0 ) return ( T* )( &m_Memory[ 0 ] ); else return ( T* )AlignValue( &m_Memory[ 0 ], nAlignment ); }
	const T* Base() const { if ( nAlignment == 0 ) return ( T* )( &m_Memory[ 0 ] ); else return ( T* )AlignValue( &m_Memory[ 0 ], nAlignment ); }

	// element access
	// Use unsigned math and inlined checks to improve performance.
	T& operator[]( int i ) { Assert( ( size_t )i < SIZE ); return Base()[ i ]; }
	const T& operator[]( int i ) const { Assert( ( size_t )i < SIZE ); return Base()[ i ]; }
	T& Element( int i ) { Assert( ( size_t )i < SIZE ); return Base()[ i ]; }
	const T& Element( int i ) const { Assert( ( size_t )i < SIZE ); return Base()[ i ]; }

	// Attaches the buffer to external memory....
	void SetExternalBuffer( T* pMemory, int numElements ) { Assert( 0 ); }

	// Size
	int NumAllocated() const { return SIZE; }
	int Count() const { return SIZE; }

	// Grows the memory, so that at least allocated + num elements are allocated
	void Grow( int num = 1 ) { Assert( 0 ); }

	// Makes sure we've got at least this much memory
	void EnsureCapacity( int num ) { Assert( num <= SIZE ); }

	// Memory deallocation
	void Purge() {}

	// Purge all but the given number of elements (NOT IMPLEMENTED IN CUtlMemoryFixed)
	void Purge( int numElements ) { Assert( 0 ); }

	// is the memory externally allocated?
	bool IsExternallyAllocated() const { return false; }

	// Set the size by which the memory grows
	void SetGrowSize( int size ) {}

	class Iterator_t
	{
	public:
		Iterator_t( int i ) : index( i ) {}
		int index;
		bool operator==( const Iterator_t it ) const { return index == it.index; }
		bool operator!=( const Iterator_t it ) const { return index != it.index; }
	};
	Iterator_t First() const { return Iterator_t( IsIdxValid( 0 ) ? 0 : InvalidIndex() ); }
	Iterator_t Next( const Iterator_t &it ) const { return Iterator_t( IsIdxValid( it.index + 1 ) ? it.index + 1 : InvalidIndex() ); }
	int GetIndex( const Iterator_t &it ) const { return it.index; }
	bool IsIdxAfter( int i, const Iterator_t &it ) const { return i > it.index; }
	bool IsValidIterator( const Iterator_t &it ) const { return IsIdxValid( it.index ); }
	Iterator_t InvalidIterator() const { return Iterator_t( InvalidIndex() ); }

private:
	char m_Memory[ SIZE * sizeof( T ) + nAlignment ];
};

template< class T, class A = CUtlMemory<T> >
class CUtlVector
{
	typedef A CAllocator;

	typedef T *iterator;
	typedef const T *const_iterator;
public:
	T & operator[]( int i );
	const T& operator[]( int i ) const;

	T& Element( int i )
	{
		return m_Memory[ i ];
	}

	T* Base()
	{
		return m_Memory.Base();
	}

	int Count() const
	{
		return m_Size;
	}

	void RemoveAll()
	{
		for ( int i = m_Size; --i >= 0; )
			Destruct( &Element( i ) );

		m_Size = 0;
	}

	inline bool IsValidIndex( int i ) const
	{
		return ( i >= 0 ) && ( i < m_Size );
	}

	void GrowVector( int num = 1 )
	{
		if ( m_Size + num > m_Memory.NumAllocated() )
		{
			m_Memory.Grow( m_Size + num - m_Memory.NumAllocated() );
		}

		m_Size += num;
	}

	iterator begin() { return Base(); }
	const_iterator begin() const { return Base(); }
	iterator end() { return Base() + Count(); }
	const_iterator end() const { return Base() + Count(); }

protected:
	CAllocator m_Memory;
	int m_Size;
	T *m_pElements;
};

template< typename T, class A >
inline T& CUtlVector<T, A>::operator[]( int i )
{
	Assert( i < m_Size );
	return m_Memory[ i ];
}

template< typename T, class A >
inline const T& CUtlVector<T, A>::operator[]( int i ) const
{
	Assert( i < m_Size );
	return m_Memory[ i ];
}

template< class T, size_t MAX_SIZE >
class CUtlVectorFixed : public CUtlVector< T, CUtlMemoryFixed<T, MAX_SIZE > >
{
	typedef CUtlVector< T, CUtlMemoryFixed<T, MAX_SIZE > > BaseClass;
public:

	// constructor, destructor
	explicit CUtlVectorFixed( int growSize = 0, int initSize = 0 ) : BaseClass( growSize, initSize ) {}
	explicit CUtlVectorFixed( T* pMemory, int numElements ) : BaseClass( pMemory, numElements ) {}
};

template< class T, class M = CUtlMemory< T > > 
class CUtlStack
{
public:
	// constructor, destructor
	CUtlStack( int growSize = 0, int initSize = 0 );
	~CUtlStack();

	void CopyFrom( const CUtlStack<T, M> &from );

	// element access
	T& operator[]( int i );
	T const& operator[]( int i ) const;
	T& Element( int i );
	T const& Element( int i ) const;

	// Gets the base address (can change when adding elements!)
	T* Base();
	T const* Base() const;

	// Looks at the stack top
	T& Top();
	T const& Top() const;

	// Size
	int Count() const;

	// Is element index valid?
	bool IsIdxValid( int i ) const;

	// Adds an element, uses default constructor
	int Push();

	// Adds an element, uses copy constructor
	int Push( T const& src );

	// Pops the stack
	void Pop();
	void Pop( T& oldTop );
	void PopMultiple( int num );

	// Makes sure we have enough memory allocated to store a requested # of elements
	void EnsureCapacity( int num );

	// Clears the stack, no deallocation
	void Clear();

	// Memory deallocation
	void Purge();

private:
	// Grows the stack allocation
	void GrowStack();

	// For easier access to the elements through the debugger
	void ResetDbgInfo();

	M m_Memory;
	int m_Size;

	// For easier access to the elements through the debugger
	T* m_pElements;
};


//-----------------------------------------------------------------------------
// For easier access to the elements through the debugger
//-----------------------------------------------------------------------------

template< class T, class M >
inline void CUtlStack<T,M>::ResetDbgInfo()
{
	m_pElements = m_Memory.Base();
}

//-----------------------------------------------------------------------------
// constructor, destructor
//-----------------------------------------------------------------------------

template< class T, class M >
CUtlStack<T,M>::CUtlStack( int growSize, int initSize )	: 
	m_Memory(growSize, initSize), m_Size(0)
{
	ResetDbgInfo();
}

template< class T, class M >
CUtlStack<T,M>::~CUtlStack()
{
	Purge();
}


//-----------------------------------------------------------------------------
// copy into
//-----------------------------------------------------------------------------

template< class T, class M >
void CUtlStack<T,M>::CopyFrom( const CUtlStack<T, M> &from )
{
	Purge();
	EnsureCapacity( from.Count() );
	for ( int i = 0; i < from.Count(); i++ )
	{
		Push( from[i] );
	}
}

//-----------------------------------------------------------------------------
// element access
//-----------------------------------------------------------------------------

template< class T, class M >
inline T& CUtlStack<T,M>::operator[]( int i )
{
	Assert( IsIdxValid(i) );
	return m_Memory[i];
}

template< class T, class M >
inline T const& CUtlStack<T,M>::operator[]( int i ) const
{
	Assert( IsIdxValid(i) );
	return m_Memory[i];
}

template< class T, class M >
inline T& CUtlStack<T,M>::Element( int i )
{
	//Assert( IsIdxValid(i) );
	return m_Memory[i];
}

template< class T, class M >
inline T const& CUtlStack<T,M>::Element( int i ) const
{
	Assert( IsIdxValid(i) );
	return m_Memory[i];
}


//-----------------------------------------------------------------------------
// Gets the base address (can change when adding elements!)
//-----------------------------------------------------------------------------

template< class T, class M >
inline T* CUtlStack<T,M>::Base()
{
	return m_Memory.Base();
}

template< class T, class M >
inline T const* CUtlStack<T,M>::Base() const
{
	return m_Memory.Base();
}

//-----------------------------------------------------------------------------
// Returns the top of the stack
//-----------------------------------------------------------------------------

template< class T, class M >
inline T& CUtlStack<T,M>::Top()
{
	Assert( m_Size > 0 );
	return Element(m_Size-1);
}

template< class T, class M >
inline T const& CUtlStack<T,M>::Top() const
{
	Assert( m_Size > 0 );
	return Element(m_Size-1);
}

//-----------------------------------------------------------------------------
// Size
//-----------------------------------------------------------------------------

template< class T, class M >
inline int CUtlStack<T,M>::Count() const
{
	return m_Size;
}


//-----------------------------------------------------------------------------
// Is element index valid?
//-----------------------------------------------------------------------------

template< class T, class M >
inline bool CUtlStack<T,M>::IsIdxValid( int i ) const
{
	return (i >= 0) && (i < m_Size);
}
 
//-----------------------------------------------------------------------------
// Grows the stack
//-----------------------------------------------------------------------------

template< class T, class M >
void CUtlStack<T,M>::GrowStack()
{
	if (m_Size >= m_Memory.NumAllocated())
		m_Memory.Grow();

	++m_Size;

	ResetDbgInfo();
}

//-----------------------------------------------------------------------------
// Makes sure we have enough memory allocated to store a requested # of elements
//-----------------------------------------------------------------------------

template< class T, class M >
void CUtlStack<T,M>::EnsureCapacity( int num )
{
	m_Memory.EnsureCapacity(num);
	ResetDbgInfo();
}


//-----------------------------------------------------------------------------
// Adds an element, uses default constructor
//-----------------------------------------------------------------------------

template< class T, class M >
int CUtlStack<T,M>::Push()
{
	GrowStack();
	Construct( &Element(m_Size-1) );
	return m_Size - 1;
}

//-----------------------------------------------------------------------------
// Adds an element, uses copy constructor
//-----------------------------------------------------------------------------

template< class T, class M >
int CUtlStack<T,M>::Push( T const& src )
{
	GrowStack();
	CopyConstruct( &Element(m_Size-1), src );
	return m_Size - 1;
}


//-----------------------------------------------------------------------------
// Pops the stack
//-----------------------------------------------------------------------------

template< class T, class M >
void CUtlStack<T,M>::Pop()
{
	Assert( m_Size > 0 );
	Destruct( &Element(m_Size-1) );
	--m_Size;
}

template< class T, class M >
void CUtlStack<T,M>::Pop( T& oldTop )
{
	Assert( m_Size > 0 );
	oldTop = Top();
	Pop();
}

template< class T, class M >
void CUtlStack<T,M>::PopMultiple( int num )
{
	Assert( m_Size >= num );
	for ( int i = 0; i < num; ++i )
		Destruct( &Element( m_Size - i - 1 ) );
	m_Size -= num;
}


//-----------------------------------------------------------------------------
// Element removal
//-----------------------------------------------------------------------------

template< class T, class M >
void CUtlStack<T,M>::Clear()
{
	for (int i = m_Size; --i >= 0; )
		Destruct(&Element(i));

	m_Size = 0;
}


//-----------------------------------------------------------------------------
// Memory deallocation
//-----------------------------------------------------------------------------

template< class T, class M >
void CUtlStack<T,M>::Purge()
{
	Clear();
	m_Memory.Purge( );
	ResetDbgInfo();
}