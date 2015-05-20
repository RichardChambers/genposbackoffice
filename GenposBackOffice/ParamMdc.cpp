#include "StdAfx.h"
#include "ParamMdc.h"

CParamMdc::CParamMdc(void)
{
}

CParamMdc::~CParamMdc(void)
{
}

short CParamMdc::PullParam (void)
{
	USHORT  usReadOffset = 0;
	USHORT  usActualRead = 0;

	m_sLastError = ::CliParaAllRead (CLASS_PARAMDC, (UCHAR *)abMDCData, sizeof( abMDCData ), usReadOffset, &usActualRead);
	m_bDataRead = 1;
	return m_sLastError;
}

short CParamMdc::PushParam (void)
{
	USHORT  usReadOffset = 0;
	USHORT  usActualRead = 0;

	m_sLastError = ::CliParaAllWrite (CLASS_PARAMDC, (UCHAR *)abMDCData, sizeof( abMDCData ), usReadOffset, &usActualRead);
	return m_sLastError;
}

unsigned short CParamMdc::GetMdcValue (unsigned short usAddress, MdcBit usBit)
{
	unsigned short  usBuffAddr = ((usAddress - 1) / 2);
	unsigned short  usMask = 0xff;
	unsigned short  usNibbleByte = 0;
	switch (usBit) {
		case CParamMdc::MdcBitD:
			usMask = 0x01;
			break;
		case CParamMdc::MdcBitC:
			usMask = 0x02;
			break;
		case CParamMdc::MdcBitB:
			usMask = 0x04;
			break;
		case CParamMdc::MdcBitA:
			usMask = 0x08;
			break;
		case CParamMdc::MdcNibbleUpper:
			usMask = 0xf0;
			usNibbleByte = 1;
			break;
		case CParamMdc::MdcNibbleLower:
			usMask = 0x0f;
			usNibbleByte = 1;
			break;
		case CParamMdc::MdcByte:
			usMask = 0xff;
			usNibbleByte = 1;
			break;
	}
	unsigned short usMdcValue = abMDCData[usBuffAddr];
	if ((usAddress & 0x01) == 0 && !usNibbleByte) {
		// The even numbered MDCs are stored in the upper nibble so lets shift bits
		// if we are getting a particular bit.  If byte then leave alone.
		usMdcValue >>= 4;
	}

	usMdcValue &= usMask;

	return usMdcValue;
}
