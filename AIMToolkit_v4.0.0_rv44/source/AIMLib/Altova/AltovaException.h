/*
Copyright (c) 2008-2013, Northwestern University
All rights reserved.
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 
  Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
 
  Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.
 
  Neither the name of the Northwestern University nor the names of its contributors
  may be used to endorse or promote products derived from this software
  without specific prior written permission.
 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

////////////////////////////////////////////////////////////////////////
//
// AltovaException.h
//
// This file was generated by XMLSpy 2012r2sp1 Enterprise Edition.
//
// YOU SHOULD NOT MODIFY THIS FILE, BECAUSE IT WILL BE
// OVERWRITTEN WHEN YOU RE-RUN CODE GENERATION.
//
// Refer to the XMLSpy Documentation for further details.
// http://www.altova.com/xmlspy
//
////////////////////////////////////////////////////////////////////////

#pragma once
#ifndef ALTOVA_ALTOVAEXCEPTION_H_INCLUDED
#define ALTOVA_ALTOVAEXCEPTION_H_INCLUDED

namespace altova {


class ALTOVA_DECLSPECIFIER CAltovaException
{
public:
	typedef enum
	{
		eError1,
		eError2,
		eDatabaseError,
	} ECode;

	CAltovaException(int nCode, const tstring& sMessage, bool bUserExc = false);
	int GetCode();
	const tstring& GetInfo() const;
	bool IsUserException() const;

protected:
	int		m_nCode;
	tstring	m_sMessage;
	bool m_bUserExc;
};

////////////////////////////////////////////////////////////////////////
//
//  Utility functions and templates
//
////////////////////////////////////////////////////////////////////////

template<typename TValue>
TValue InRangeInt(TValue nValue, ALTOVA_INT64 nMin, ALTOVA_INT64 nMax)
{
	if( nValue < nMin || nValue > nMax )
		throw CAltovaException(CAltovaException::eError1, _T("Out of range!"));
	return nValue;
}


template<typename TValue>
TValue InRangeDbl(TValue nValue, const double nPosMin, const double nPosMax)
{
	TValue nTmpValue = nValue;
	if( nTmpValue == 0 )
		return nValue;
	if( nTmpValue < 0 )
		nTmpValue = -nTmpValue;
	if( nTmpValue >= nPosMin  &&  nTmpValue <= nPosMax )
		return nValue;
	throw CAltovaException(CAltovaException::eError1, _T("Out of range!"));
}

} // namespace altova

#endif // ALTOVA_ALTOVAEXCEPTION_H_INCLUDED