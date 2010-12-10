//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   c4/C4_MPI.hh
 * \author Thomas M. Evans
 * \date   Thu Mar 21 16:56:16 2002
 * \brief  C4 MPI function declarations.
 * \note   Copyright 2004 The Regents of the University of California.
 */
//---------------------------------------------------------------------------//
// $Id$
//---------------------------------------------------------------------------//

#ifndef c4_C4_MPI_hh
#define c4_C4_MPI_hh

#include "c4/config.h"
#include <algorithm>

#ifdef C4_MPI

#include "C4_Functions.hh"
#include "ds++/Assert.hh"
#include "c4_mpi.h"

namespace rtt_c4
{

//---------------------------------------------------------------------------//
// MPI Communicator
//---------------------------------------------------------------------------//

extern MPI_Comm communicator;
extern bool initialized;

//---------------------------------------------------------------------------//
// Null source/destination rank
//---------------------------------------------------------------------------//

extern const int proc_null;

//---------------------------------------------------------------------------//
// SETUP FUNCTIONS
//---------------------------------------------------------------------------//

template<class Comm>
void inherit(const Comm &comm)
{
    int result = MPI_Comm_dup(comm, &communicator);
    Check (result == MPI_SUCCESS);
}

//---------------------------------------------//
/*!
 * Broadcast the range [first, last) from proc 0 
 * into [result, ...) on all other processors.
 */
template<class ForwardIterator, class OutputIterator>
void broadcast(ForwardIterator first,
	       ForwardIterator last,
	       OutputIterator  result)
{
    typedef typename std::iterator_traits<ForwardIterator>::value_type
	value_type;
    typedef typename std::iterator_traits<ForwardIterator>::difference_type 
	diff_type;

    // Proc 0 does not copy any data into the result iterator.

    diff_type size;
    if( rtt_c4::node() == 0)
    {
	size = std::distance(first, last);
    }
    broadcast(&size, 1, 0);

    value_type *buf = new value_type[size];
    if ( rtt_c4::node() == 0)
    {
	std::copy(first, last, buf);
    }
    broadcast(buf, size, 0);
    
    if ( rtt_c4::node() != 0)
    {
	std::copy(buf, buf+size, result);
    }
    
    delete [] buf;
}

} // end namespace rtt_c4

#endif // C4_MPI

#endif                          // c4_C4_MPI_hh

//---------------------------------------------------------------------------//
//                              end of c4/C4_MPI.hh
//---------------------------------------------------------------------------//
