/*L
*  Copyright Northwestern University
*  Copyright Stanford University (ATB 1.0 and ATS 1.0)
*
*  Distributed under the OSI-approved BSD 3-Clause License.
*  See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
*/

#include "dcmtk/config/osconfig.h"
#include "dcmtk/ofstd/ofstd.h"
#include "dcmtk/ofstd/oftypes.h"

#define OFTEST_OFSTD_ONLY
#include "dcmtk/ofstd/oftest.h"

#define INCLUDE_CMATH
#include "dcmtk/ofstd/ofstdinc.h"


struct ValuePair
{
  const char *s;
  double d;
  OFBool r;
};

const ValuePair vp[] =
{
  // normal conversions
  {"0", 0.0, OFTrue},
  {"1", 1.0, OFTrue},
  {"     1", 1.0, OFTrue},
  {"\t\t1", 1.0, OFTrue},
  {"\n\n1", 1.0, OFTrue},
  {" \t\n1", 1.0, OFTrue},
  {"2.5", 2.5, OFTrue},
  {"  +2.5", 2.5, OFTrue},
  {"  -2.5", -2.5, OFTrue},
  {"20", 20.0, OFTrue},
  {"1E3", 1000.0, OFTrue},
  {"1.e3", 1000.0, OFTrue},
  {"1.0E+003", 1000.0, OFTrue},
  {"10000.0E-001", 1000.0, OFTrue},
  {"1.23456E-0", 1.23456, OFTrue},
  {"9.87654321e-10", 9.87654321e-10, OFTrue},

  // big number
  {"1.797693134862315E+308", 1.797693134862315e+308, OFTrue},

  // since our precision is limited, everything else smaller then this may be converted to zero.
  {"2.2250738585072014E-292", 2.2250738585072014E-292, OFTrue},
  {"3.402823466E+38F", 3.402823466E+38F, OFTrue},
  {"1.175494351E-38F", 1.175494351E-38F, OFTrue},

  // overflow is reported as infinity
  {"1.7976931348623157E+1000", HUGE_VAL, OFTrue},

  // underflow is reported as zero
  {"2.2250738585072014E-1000", 0.0, OFTrue},

  // conversions that should fail
  // {"NaN", 0.0, OFFalse}, // this test will fail if DISABLE_OFSTD_ATOF is defined
  {"BIGNUM", 0.0, OFFalse},
  {"_1.0", 0.0, OFFalse},
  {"", 0.0, OFFalse}
};

OFTEST(ofstd_atof)
{
  unsigned long numVp = sizeof(vp)/sizeof(ValuePair);
  double d1, d2, delta;
  OFBool r = OFFalse;

  for (unsigned long i=0; i<numVp; i++)
  {
    d1 = vp[i].d;
    d2 = OFStandard::atof(vp[i].s, &r);
    if (r && vp[i].r)
    {
      if (d1 != d2)
      {
        delta = fabs(d1-d2);
        // fail if precision is less then 9 decimal digits
        if (delta * 1.0E9 > fabs(d1))
        {
          OFCHECK_FAIL("test #" << i << " failed: conversion error, atof=" << d2 << ", ref="
               << d1 << ", delta=" << delta);
        }
      }
    }
    else
    {
      if (r != vp[i].r)
      {
        if (r)
          OFCHECK_FAIL("test #" << i << " failed: conversion did not flag error as expected, atof=" << d2);
        else
          OFCHECK_FAIL("test #" << i << " failed: conversion did not succeed as expected");
      }
    }
  }
}
