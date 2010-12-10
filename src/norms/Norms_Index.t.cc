//----------------------------------*-C++-*----------------------------------//
/*!
  \file   Norms_Index.t.cc
  \author Rob Lowrie
  \date   Fri Jan 14 13:00:47 2005
  \brief  Instantiates Norms_Index for some types.
*/
//---------------------------------------------------------------------------//
// $Id$
//---------------------------------------------------------------------------//

#include "Norms_Index.t.hh"
#include "Index_Labeled.hh"
#include "Index_Proc.hh"

using namespace rtt_norms;

template class Norms_Index<size_t>;
template class Norms_Index<Index_Labeled>;
template class Norms_Index<Index_Proc>;

//---------------------------------------------------------------------------//
// end of norms/Norms_Index.t.cc
//---------------------------------------------------------------------------//
