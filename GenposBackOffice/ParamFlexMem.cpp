#include "StdAfx.h"
#include "ParamFlexMem.h"

CParamFlexMem::CParamFlexMem(void)
{
}

CParamFlexMem::~CParamFlexMem(void)
{
}

short CParamFlexMem::PullParam (void)
{
	USHORT  usReadOffset = 0;
	USHORT  usActualRead = 0;

	m_sLastError = ::CliParaAllRead (CLASS_PARAFLEXMEM, (UCHAR *)m_paraFlexMem, sizeof( m_paraFlexMem ), usReadOffset, &usActualRead);
	return m_sLastError;
}

short CParamFlexMem::PushParam (void)
{
	USHORT  usReadOffset = 0;
	USHORT  usActualRead = 0;

	m_sLastError = ::CliParaAllWrite (CLASS_PARAFLEXMEM, (UCHAR *)m_paraFlexMem, sizeof( m_paraFlexMem ), usReadOffset, &usActualRead);
	return m_sLastError;
}