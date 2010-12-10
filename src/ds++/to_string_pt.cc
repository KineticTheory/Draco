//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   ds++/to_string_pt.hh
 * \author Kent Budge
 * \brief  Instantiate class to_string
 * \note   Copyright (C) 2007 Los Alamos National Security, LLC
 */
//---------------------------------------------------------------------------//
// $Id$
//---------------------------------------------------------------------------//

#include "to_string.hh"

namespace rtt_dsxx
{

template
string to_string(int num, unsigned precision );

template
string to_string(unsigned num, unsigned precision );

template
string to_string(double num, unsigned precision );

} // end namespace rtt_dsxx

//---------------------------------------------------------------------------//
//              end of ds++/to_string_pt.hh
//---------------------------------------------------------------------------//
