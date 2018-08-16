//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   c4/ofpstream.hh
 * \author Kent G. Budge
 * \brief  Define class ofpstream
 * \note   Copyright (C) 2018 Los Alamos National Security, LLC.
 *         All rights reserved.
 */
//---------------------------------------------------------------------------//

//---------------------------------------------------------------------------//

#ifndef c4_ofpstream_hh
#define c4_ofpstream_hh

#include <fstream>
#include <vector>

#include "c4/config.h"

namespace rtt_c4 {

//===========================================================================//
/*!
 * \class ofpstream
 *
 * Output stream for serializing output from all MPI ranks.
 *
 * This class is an output stream that serialized output from all MPI ranks.
 * Output is inserted to the stream as with any other output stream. When the
 * send() function is invoked, which *must be done synchronously across all
 * processors*, all output inserted to the stream since the last call to send()
 * is printed to the associated file, by MPI rank. In other words, all output
 * inserted to an instance of ofpstream by rank 0 since the last call to send()
 * is printed to the associated file, then all output inserted to the instance
 * of ofpstream by rank 1 is printed to cout, and so on for all processors.
 * There is no requirement that any processor have actually inserted any output
 * to the stream since the last cal to send(), nor does the output from any
 * processor have to resemble that from any other processor in any way (though
 * it very often will.)
 *
 * Because this requires that output be buffered in the stream for each rank
 * between send() calls, memory consumption might become significant if
 * very large blocks of output are generated by MPI ranks between calls to
 * send(). In other words, this stream is most suitable for TL;DR type
 * messages to a file.
 *
 * Memory allocated for buffering is retained between calls unless the
 * shrink_to_fit function is called, which releases all memory not needed
 * for the current buffered output. In typical usage, this means the stream
 * will grow its buffer size silently until it is big enough for the largest
 * blocks of output being generated, then remain there through the rest
 * of the scope containing the stream, unless shrink_to_fit is called.
 *
 * Any output remaining in the buffer when the buffer goes out of scope and is
 * destroyed will be discarded. The alternative, of doing a final send() as
 * part of the destructor, risks propagating an exception out of the
 * destructor, which is bad practice.
 *
 * \example c4/test/tstofpstream.cc
 */
//===========================================================================//

class ofpstream : public std::ostream {
public:
  //! Constructor -- default to standard output mode (ascii)
  DLL_PUBLIC_c4 ofpstream(std::string const &filename,
                          ios_base::openmode const mode = ios_base::out);

  //! Write all buffered output to the file stream, in MPI rank order.
  void send() { sb_.send(); }
  //! Shrink the internal buffer to fit the data currently in buffer.
  void shrink_to_fit() { sb_.shrink_to_fit(); }

private:
  struct mpibuf : public std::streambuf {

    DLL_PUBLIC_c4 void send();
    DLL_PUBLIC_c4 void shrink_to_fit();

    DLL_PUBLIC_c4 virtual int_type overflow(int_type c);

    std::vector<char> buffer_;
    ios_base::openmode mode_;
    std::ofstream out_;
  };

  mpibuf sb_;
};

} // end namespace rtt_c4

#endif // c4_ofpstream_hh

//---------------------------------------------------------------------------//
// end of c4/ofpstream.hh
//---------------------------------------------------------------------------//
