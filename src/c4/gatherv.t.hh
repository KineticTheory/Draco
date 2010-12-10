//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   c4/gatherv.t.hh
 * \author Thomas M. Evans, Kent Budge
 * \date   Thu Mar 21 16:56:17 2002
 * \brief  C4 MPI template implementation.
 * \note   Copyright (C) 2002-2010 Los Alamos National Security, LLC.  All
 *         rights reserved.
 */
//---------------------------------------------------------------------------//
// $Id$
//---------------------------------------------------------------------------//

#ifndef c4_gatherv_t_hh
#define c4_gatherv_t_hh

#include "c4/config.h"
#include "gatherv.hh"
#include "C4_Functions.hh"
#include "ds++/Assert.hh"
#include <algorithm>

namespace rtt_c4
{
using std::vector;
using std::copy;

//---------------------------------------------------------------------------//
// GATHER
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//
template<class T>
void indeterminate_gatherv( vector<T>          & outgoing_data,
                            vector<vector<T> > & incoming_data )
{
#ifdef C4_MPI
    { // This block is a no-op for with-c4=scalar 

        unsigned const N( rtt_c4::nodes() );
        incoming_data.resize(N);

        int count( outgoing_data.size() );
        if (rtt_c4::node()==0)
        {
            vector<int> counts(N, -1);
            vector<int> displs(N, -1);
            
            // for valid comm world, this should always be true.
            Check( counts.size() > 0 ); 
            gather( &count,
                    &counts[0],
                    1 );
            unsigned total_count( 0 );
            for( unsigned p=0; p<N; ++p )
            {
                displs[p] = total_count;
                total_count += counts[p];
            }

            // We can only use the &vec[0] notation if the vector is non-zero
            // in length.  An shorthand-if is used to pass 'NULL' to mpi if
            // there is no data to gather.
            vector<T> recbuf(total_count, 42);
            rtt_c4::gatherv(
                (count>0?&outgoing_data[0]:NULL),
                outgoing_data.size(),
                (total_count>0?&recbuf[0]:NULL),
                &counts[0],
                &displs[0]
                );
            
            for( unsigned p=0; p<N; ++p )
            {
                incoming_data[p].resize( counts[p] );
                copy( recbuf.begin()+displs[p],
                      recbuf.begin()+displs[p]+counts[p],
                      incoming_data[p].begin());
            }

        }
        else
        {
            gather( &count, static_cast<int*>(NULL), 1 );
            gatherv(
                (count>0?&outgoing_data[0]:NULL),
                count,
                static_cast<T*>(NULL),
                0,
                static_cast<int*>(NULL)
                );
        }
    }
#else
    {
        // Only need to copy outgoing to incoming
        incoming_data.resize(0);
        incoming_data.resize(1, outgoing_data);
    }
#endif // C4_MPI

    return;
}

//---------------------------------------------------------------------------//
template<class T>
void determinate_gatherv(vector<T>           &outgoing_data,
                         vector<vector<T> >  &incoming_data)
{
    Require(static_cast<int>(incoming_data.size())==rtt_c4::nodes());
    
#ifdef C4_MPI
    { // This block is a no-op for with-c4=scalar 
        unsigned const N( rtt_c4::nodes() );

        int count( outgoing_data.size() );
        if (rtt_c4::node()==0)
        {
            vector<int> counts(N,-1);
            vector<int> displs(N,-1);
            unsigned total_count(0);
            for( unsigned p=0; p<N; ++p )
            {
                counts[p] = incoming_data[p].size();
                displs[p] = total_count;
                total_count += counts[p];
            }
            
            vector<T> recbuf(total_count,42);
            // &vec[0] is only valid if vector has non-zero length
            rtt_c4::gatherv(
                (count>0?&outgoing_data[0]:NULL),
                count,
                (total_count>0?&recbuf[0]:NULL),
                &counts[0],
                &displs[0]
                );
            
            for( unsigned p=0; p<N; ++p )
            {
                incoming_data[p].resize( counts[p] );
                copy( recbuf.begin()+displs[p],
                      recbuf.begin()+displs[p]+counts[p],
                      incoming_data[p].begin() );
            }

        }
        else
        {
            gatherv(
                (count>0?&outgoing_data[0]:NULL),
                count,
                static_cast<T*>(NULL),
                0,
                static_cast<int*>(NULL)
                );
        }
    }
#else
    {
        // Only need to copy outgoing to incoming
        incoming_data.resize(0);
        incoming_data.resize(1, outgoing_data);
    }
#endif // C4_MPI

    return;
}

} // end namespace rtt_c4

#endif // c4_gatherv_t_hh

//---------------------------------------------------------------------------//
//                              end of c4/gatherv.t.hh
//---------------------------------------------------------------------------//
