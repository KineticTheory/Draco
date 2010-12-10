//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   norms/Index_Labeled.cc
 * \author Rob Lowrie
 * \date   Fri Jan 14 13:57:58 2005
 * \brief  Implementation of Index_Labeled.
 * \note   Copyright 2004 The Regents of the University of California.
 */
//---------------------------------------------------------------------------//
// $Id$
//---------------------------------------------------------------------------//

#include "Index_Labeled.hh"
#include <c4/global.hh>

namespace rtt_norms
{

//---------------------------------------------------------------------------//
/*!
  \brief Constructor.
*/
//---------------------------------------------------------------------------//
Index_Labeled::Index_Labeled(const size_t       index_,
			     const std::string &label_)
    : index(index_)
    , processor(rtt_c4::node())
    , label(label_)
{
}

//---------------------------------------------------------------------------//
/*!
  \brief Equality operator.
*/
//---------------------------------------------------------------------------//
bool Index_Labeled::operator==(const Index_Labeled &rhs) const
{
    return (index == rhs.index) && (processor == rhs.processor) &&
	(label == rhs.label);
}

} // end namespace rtt_norms

//---------------------------------------------------------------------------//
//                 end of Index_Labeled.cc
//---------------------------------------------------------------------------//
