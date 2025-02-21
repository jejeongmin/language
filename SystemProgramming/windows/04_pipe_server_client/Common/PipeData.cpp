#include "pch.h"
#include "PipeData.h"
#include <assert.h>
#include <strsafe.h>

// PIPETRACELOG�� stdafx.h�� ������ ������ Log�� �� �� ����.
#ifndef PIPETRACELOG
#define PIPETRACELOG(...) ((void)(0))
#endif

// ������� stdafx.h��,
/*
#ifndef PIPETRACELOG
#define PIPETRACELOG(...) _tprintf(__VA_ARGS__);_tprintf(TEXT("\r\n"));
#endif
*/
// �� ���� ������ ������, ���� �α׸� �ܼ� stdout�� Ȯ���� �����ϴ�.

CPipeData::CPipeData(void)
{
	::InitializeCriticalSection(&m_cs);
	m_pstArrParam		= NULL;
	m_nCountArrParam	= 0;
	m_nAllocArrParam	= 0;
	m_dwThreadId		= ::GetCurrentThreadId();
}

CPipeData::~CPipeData(void)
{
	ClearAllParam();

	::DeleteCriticalSection(&m_cs);
}

// parameter�� �����Ѵ�.
// �̹� �ִ� Paramter �̸��� ��� �����ϸ�, FALSE ���ϵȴ�.
BOOL CPipeData::SetParam(IN LPCTSTR lpszName, IN const LPBYTE pData, IN size_t dwCbSize)
{
	BOOL				bRtnValue	= FALSE;
	INT					i			= 0;
	INT					nAlloc		= 0;
	size_t				dwCchLength	= 0;
	LPST_PIPEDATA_PARAM	pstParam	= NULL;

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);

	if (m_dwThreadId != ::GetCurrentThreadId())
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if ((NULL == lpszName) || (NULL == pData) || (0 == dwCbSize))
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if (FALSE == CheckName(lpszName))
	{
		bRtnValue = FALSE;
		PIPETRACELOG(TEXT("[P][ERROR] Fail to verify name, %s"), lpszName);
		assert(FALSE);
		goto FINAL;
	}

	if (TRUE == GetParamPtr(lpszName, NULL, NULL))
	{
		// ���� �ִٸ�,...
		bRtnValue = FALSE;
		PIPETRACELOG(TEXT("[P][ERROR] Fail to already exists, %s"), lpszName);
		assert(FALSE);
		goto FINAL;
	}

	// realloc �ʿ�?
	if (m_nCountArrParam + 1 >= m_nAllocArrParam)
	{
		// 2�辿 Ŀ��������.
		nAlloc = m_nAllocArrParam * 2;
		if (0 == nAlloc)
		{
			nAlloc = 1;
		}

		pstParam = new ST_PIPEDATA_PARAM[nAlloc];
		if (NULL == pstParam)
		{
			bRtnValue = FALSE;
			PIPETRACELOG(TEXT("[P][ERROR] Fail to new"));
			assert(FALSE);
			goto FINAL;
		}
		ZeroMemory(pstParam, sizeof(ST_PIPEDATA_PARAM)*nAlloc);

		if (NULL != m_pstArrParam)
		{
			CopyMemory(pstParam, m_pstArrParam, sizeof(ST_PIPEDATA_PARAM)*m_nAllocArrParam);
			delete [] m_pstArrParam;
		}

		m_pstArrParam    = pstParam;
		m_nAllocArrParam = nAlloc;
	}

	if ((m_nCountArrParam < 0) || (m_nCountArrParam > m_nAllocArrParam))
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	pstParam = &m_pstArrParam[m_nCountArrParam];
	if ((NULL == pstParam) ||
		(NULL != pstParam->lpszParamName))
	{
		// �ٸ����� ���� �� ����
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	// ���� �Ҵ�~!!!
	dwCchLength = _tcslen(lpszName);
	pstParam->lpszParamName = new TCHAR[dwCchLength+1];
	if (NULL == pstParam->lpszParamName)
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}
	ZeroMemory(pstParam->lpszParamName, sizeof(TCHAR)*(dwCchLength+1));
	StringCchCopy(pstParam->lpszParamName, dwCchLength+1, lpszName);

	pstParam->pData = new BYTE[dwCbSize];
	if (NULL == pstParam->pData)
	{
		delete [] pstParam->lpszParamName;
		pstParam->lpszParamName = NULL;

		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}
	::CopyMemory(pstParam->pData, pData, dwCbSize);

	pstParam->dwCbSize = dwCbSize;

	m_nCountArrParam++;

	// ������� �Դٸ� ����
	bRtnValue = TRUE;

FINAL:

	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////
	return bRtnValue;
}

// parameter�� ���Ѵ�.
// pointer�� �����ϴµ�, Copy�� ������ �ƴϴ�.
// �׷��Ƿ�, caller������ �ش� pointer�� �����ؼ��� �ȵȴ�. read-only�� ����϶�.
// ������ �ʿ��ϴٸ�, caller���� �޸𸮸� �����Ͽ� ����϶�.
// ���� �ش� name�� �ִ� ���, TRUE�� �����Ѵ�.
// ppData�� NULL�� �����ϸ�, ���ϰ� üũ �뵵(�ֳ�? ����?)�� Ȱ��ȴ�.
BOOL CPipeData::GetParamPtr(IN LPCTSTR lpszName, OPTIONAL OUT LPBYTE* ppData, OPTIONAL OUT size_t* pdwCbSize)
{
	INT  i		   = 0;
	BOOL bRtnValue = FALSE;

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);

	if (m_dwThreadId != ::GetCurrentThreadId())
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if (NULL == m_pstArrParam)
	{
		bRtnValue = FALSE;
		goto FINAL;
	}

	if (FALSE == CheckName(lpszName))
	{
		bRtnValue = FALSE;
		goto FINAL;
	}

	for (i=0; i<m_nCountArrParam; i++)
	{
		if (0 == _tcscmp(lpszName, m_pstArrParam[i].lpszParamName))
		{
			// ã�Ҵ�~!!!
			bRtnValue = TRUE;

			if (NULL != ppData)
			{
				*ppData	= m_pstArrParam[i].pData;
			}

			if (NULL != pdwCbSize)
			{
				*pdwCbSize = m_pstArrParam[i].dwCbSize;
			}

			break;
		}
	}

FINAL:
	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////
	return bRtnValue;
}

VOID CPipeData::ClearAllParam(VOID)
{
	INT					i		 = 0;
	LPST_PIPEDATA_PARAM pstParam = NULL;

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);

	if (m_dwThreadId != ::GetCurrentThreadId())
	{
		assert(FALSE);
		goto FINAL;
	}

	if (NULL != m_pstArrParam)
	{
		for (i=0; i<m_nAllocArrParam; i++)
		{
			if (NULL != m_pstArrParam[i].lpszParamName)
			{
				delete [] m_pstArrParam[i].lpszParamName;
				m_pstArrParam[i].lpszParamName = NULL;
			}

			if (NULL != m_pstArrParam[i].pData)
			{
				delete [] m_pstArrParam[i].pData;
				m_pstArrParam[i].pData = NULL;
			}
		}

		delete [] m_pstArrParam;
		m_pstArrParam = NULL;
	}

	m_nAllocArrParam = 0;
	m_nCountArrParam = 0;

FINAL:
	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////
}

INT CPipeData::GetCount(VOID)
{
	INT nRtnValue = 0;

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);
	nRtnValue = m_nCountArrParam;
	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////

	return nRtnValue;
}

// Parameter �̸��� ������ �� �ֵ��� �̸��� �����Ѵ�.
BOOL CPipeData::GetName(IN INT nIndex, OUT LPTSTR lpszName, IN size_t dwCchLength)
{
	BOOL bRtnValue = FALSE;

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);

	if (m_dwThreadId != ::GetCurrentThreadId())
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if ((NULL == lpszName) ||
		(nIndex >= m_nCountArrParam))
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if (FAILED(StringCchCopy(lpszName, dwCchLength, m_pstArrParam[nIndex].lpszParamName)))
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	// ������� �Դٸ� ����
	bRtnValue = TRUE;

FINAL:

	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////
	return bRtnValue;
}

BOOL CPipeData::CheckName(IN LPCTSTR lpszName)
{
	BOOL	bRtnValue	= FALSE;
	LPSTR	lpszNameA	= NULL;

	if (NULL == lpszName)
	{
		bRtnValue = FALSE;
		goto FINAL;
	}

	if (TEXT('\0') == lpszName[0])
	{
		bRtnValue = FALSE;
		goto FINAL;
	}

	if ((NULL != _tcschr(lpszName, TEXT('|'))) ||
		(NULL != _tcschr(lpszName, TEXT('='))) ||
		(NULL != _tcschr(lpszName, TEXT('*'))) ||
		(NULL != _tcschr(lpszName, TEXT(' '))) ||
		(TEXT('\0') == lpszName[0]))
	{
		// ��Ģ���� üũ
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if (_tcsnlen(lpszName, 32) > 32)
	{
		// ���ڼ� ����
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	// ANSI�� ������ ��쿡�� üũ�Ѵ�.
	lpszNameA = W_2_A(lpszName);
	if ((NULL != strchr(lpszNameA, '|')) ||
		(NULL != strchr(lpszNameA, '=')) ||
		(NULL != strchr(lpszNameA, '*')) ||
		(NULL != strchr(lpszNameA, ' ')) ||
		('\0' == lpszNameA[0]))
	{
		// ��Ģ���� üũ
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	// �׿ܿ� ���
	bRtnValue = TRUE;

FINAL:
	if (NULL != lpszNameA)
	{
		delete [] lpszNameA;
		lpszNameA = NULL;
	}
	return bRtnValue;
}

// Parameter�� byte stream���� ��ȯ�Ѵ�.
//
// ������,
// 32|param1=5|param5=4*helloworld
// �� ����.
// ��, �� buffer ���̰� �켱 ����.
// | ������ Parameter �̸��� ����.
// = ������ Parameter data�� ũ�Ⱑ ����.
// * �������� data�� ����.
BOOL CPipeData::ToByteAlloc(OUT LPBYTE* ppBuf, OUT size_t* pdwCbSize)
{
	INT		i			= 0;
	BOOL	bRtnValue	= FALSE;
	size_t	dwCbNeed	= 0;
	INT		nCbPosA		= 0;
	LPSTR	lpszNameA	= NULL;
	CHAR	szDigitA[12]= {0,};	// 4294967295�� ������ �� �ִ� �����̴�.

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);

	if (m_dwThreadId != ::GetCurrentThreadId())
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if ((NULL == ppBuf) || (NULL == pdwCbSize))
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if (0 == GetCount())
	{
		// ���� �ƹ��͵� ���� ���̶��,...
		*ppBuf = new BYTE[4];
		if (NULL == *ppBuf)
		{
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}

		// 4byte�� �Ѵ�. ( 3|=* )
		(*ppBuf)[0] = '4';
		(*ppBuf)[1] = '|';
		(*ppBuf)[2] = '=';
		(*ppBuf)[3] = '*';
		(*pdwCbSize) = 4;

		// ����
		bRtnValue = TRUE;
		goto FINAL;
	}

	if (NULL == m_pstArrParam)
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	// �켱 ���̺��� �������.
	for (i=0; i<m_nCountArrParam; i++)
	{
		if (NULL != lpszNameA)
		{
			delete [] lpszNameA;
			lpszNameA = NULL;
		}

		dwCbNeed += sizeof(CHAR);	// | ����
		lpszNameA = W_2_A(m_pstArrParam[i].lpszParamName);
		dwCbNeed += strlen(lpszNameA) * sizeof(CHAR);	// parameter �̸�
		dwCbNeed += sizeof(CHAR);	// = ����
		StringCchPrintfA(szDigitA, 12, "%d", m_pstArrParam[i].dwCbSize);
		dwCbNeed += strlen(szDigitA) * sizeof(CHAR);	// size ���� ����
		dwCbNeed += m_pstArrParam[i].dwCbSize;	// data ����
	}

	dwCbNeed += sizeof(CHAR); // * ����

	// �׸��� ���ο� ���� ���̵�~!!
	dwCbNeed += GetSizeFieldLength(dwCbNeed);

	*ppBuf = new BYTE[dwCbNeed+1];
	if (NULL == *ppBuf)
	{
		bRtnValue = FALSE;
		goto FINAL;
	}
	ZeroMemory(*ppBuf, sizeof(BYTE)*(dwCbNeed+1));
	StringCchPrintfA((LPSTR)*ppBuf, dwCbNeed, "%d", dwCbNeed);

	for (i=0; i<m_nCountArrParam; i++)
	{
		if (FAILED(StringCchCatA((LPSTR)*ppBuf, dwCbNeed, "|")))
		{
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}

		if (NULL != lpszNameA)
		{
			delete [] lpszNameA;
			lpszNameA = NULL;
		}

		lpszNameA = W_2_A(m_pstArrParam[i].lpszParamName);
		if (FAILED(StringCchCatA((LPSTR)*ppBuf, dwCbNeed, lpszNameA)))
		{
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}

		if (FAILED(StringCchCatA((LPSTR)*ppBuf, dwCbNeed, "=")))
		{
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}

		StringCchPrintfA(szDigitA, 12, "%d", m_pstArrParam[i].dwCbSize);
		if (FAILED(StringCchCatA((LPSTR)*ppBuf, dwCbNeed, szDigitA)))
		{
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}
	}

	if (FAILED(StringCchCatA((LPSTR)*ppBuf, dwCbNeed, "*")))
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	// �������������.
	nCbPosA = static_cast<int>(strlen((LPSTR)*ppBuf));
	for (i=0; i<m_nCountArrParam; i++)
	{
		if (dwCbNeed - nCbPosA < m_pstArrParam[i].dwCbSize)
		{
			// ���ڸ���.
			PIPETRACELOG(TEXT("[P][ERROR] Fail to mismatch size, %d, %d"), static_cast<int>(dwCbNeed - nCbPosA), static_cast<int>(m_pstArrParam[i].dwCbSize));
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}
		::CopyMemory(&(*ppBuf)[nCbPosA], m_pstArrParam[i].pData, m_pstArrParam[i].dwCbSize);
		nCbPosA += static_cast<int>(m_pstArrParam[i].dwCbSize);
	}

	// ������� �Դٸ� ����
	*pdwCbSize = dwCbNeed;
	bRtnValue  = TRUE;

FINAL:
	if (NULL != lpszNameA)
	{
		delete [] lpszNameA;
		lpszNameA = NULL;
	}
	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////
	return bRtnValue;
}

VOID CPipeData::FreeAlloc(IN LPBYTE pBuf)
{
	if (NULL != pBuf)
	{
		delete [] pBuf;
		pBuf = NULL;
	}
}

// byte stream�� parameter�� SetParam�Ѵ�.
//
// ������,
// 32|param1=5|param5=4*helloworld
// �� ���� ȣ���Ѵ�.
// ��, �� buffer ���̰� �켱 ����.
// | ������ Parameter �̸��� ����.
// = ������ Parameter data�� ũ�Ⱑ ����.
// * �������� data�� ����.
BOOL CPipeData::FromByte(IN LPBYTE pBuf, IN size_t dwCbSize)
{
	BOOL	bRtnValue			= FALSE;
	BOOL	bFound				= FALSE;
	INT		i					= 0;
	LPSTR	lpszFind			= NULL;
	LPSTR	lpszFind2			= NULL;
	LPSTR	lpszDataFieldBegin	= NULL;
	LPSTR	lpszTmp				= NULL;
	LPTSTR	lpszNameW			= NULL;
	CHAR	szNameA[MAX_PATH]	= {0,};
	DWORD	dwCbDataSize		= 0;
	INT		nNamePos			= 0;
	INT		nDataFieldPos		= 0;
	INT		nDataFieldBeginPos	= 0;

	if (NULL == pBuf)
	{
		bRtnValue = FALSE;
		goto FINAL;
	}

	// ���� ������ �켱 ��� ������.
	ClearAllParam();

	if (_atoi64((LPSTR)pBuf) != dwCbSize)
	{
		// �ٸ���?
		PIPETRACELOG(TEXT("[P][ERROR] Fail to mismatch size 2nd, %I64d, %d"), _atoi64((LPSTR)pBuf), static_cast<int>(dwCbSize));
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if (0 == dwCbSize)
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if ((NULL == strchr((LPSTR)pBuf, '|')) ||
		(NULL == strchr((LPSTR)pBuf, '=')))
	{
		// �ּ� �ʿ��� ���� ����.
		PIPETRACELOG(TEXT("[P][ERROR] Fail to suffix"));
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	// *�� ã�´�.
	lpszDataFieldBegin = strchr((LPSTR)pBuf, '*');
	if (NULL == lpszDataFieldBegin)
	{
		PIPETRACELOG(TEXT("[P][ERROR] Fail to suffix 2nd"));
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if (dwCbSize - 1 == (LPBYTE)lpszDataFieldBegin - pBuf)
	{
		// ����ִ� param
		PIPETRACELOG(TEXT("[P][INFO] Empty"));
		bRtnValue = TRUE;
		goto FINAL;
	}

	if ('\0' == lpszDataFieldBegin[1])
	{
		PIPETRACELOG(TEXT("[P][ERROR] Empty"));
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	// DataField�� ���۵Ǵ� ��ġ
	nDataFieldPos		= static_cast<int>(lpszDataFieldBegin - (LPSTR)pBuf + 1);
	nDataFieldBeginPos	= nDataFieldPos;

	lpszFind = strchr(&((LPSTR)pBuf)[0], '|');
	if (NULL == lpszFind)
	{
		// namefield�� ����?
		PIPETRACELOG(TEXT("[P][ERROR] Fail to suffix 3rd"));
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}
	if ((LPVOID)lpszFind <= (LPVOID)pBuf)
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	// NameField�� ���۵Ǵ� ��ġ
	nNamePos = static_cast<int>((LPSTR)lpszFind - (LPSTR)pBuf);

	for (;;)
	{
		lpszFind = strchr(&((LPSTR)pBuf)[nNamePos], '|');
		if (NULL == lpszFind)
		{
			break;
		}

		if (lpszFind >= lpszDataFieldBegin)
		{
			break;
		}

		if ('\0' == lpszFind[1])
		{
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}

		lpszFind2 = strchr(&lpszFind[1], '=');
		if (NULL == lpszFind2)
		{
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}

		if ('\0' == lpszFind2[1])
		{
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}

		dwCbDataSize = (DWORD)_atoi64(&lpszFind2[1]);
		if (0 == dwCbDataSize)
		{
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}

		StringCchCopyNA(szNameA, MAX_PATH, &lpszFind[1], lpszFind2-lpszFind-1);

		if (nDataFieldPos + dwCbDataSize > dwCbSize)
		{
			PIPETRACELOG(TEXT("[P][ERROR] Fail to mismatch size 3rd, %d, %d"), static_cast<int>(nDataFieldPos + dwCbDataSize), static_cast<int>(dwCbSize));
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}

		if (NULL != lpszNameW)
		{
			delete [] lpszNameW;
			lpszNameW = NULL;
		}

		lpszNameW = A_2_W(szNameA);
		bRtnValue = SetParam(lpszNameW, &pBuf[nDataFieldPos], dwCbDataSize);
		if (FALSE == bRtnValue)
		{
			PIPETRACELOG(TEXT("[P][ERROR] Fail to set, %s, %d"), lpszNameW, dwCbDataSize);
			bRtnValue = FALSE;
			assert(FALSE);
			goto FINAL;
		}

		nDataFieldPos += dwCbDataSize;

		// ���� '|' �� ã�´�.
		bFound = FALSE;
		for (i=nNamePos+1; i<nDataFieldBeginPos; i++)
		{
			if ('\0' == (CHAR)pBuf[i])
			{
				break;
			}

			if ('|' == (CHAR)pBuf[i])
			{
				bFound = TRUE;
				nNamePos = i;
				break;
			}
		}

		if (FALSE == bFound)
		{
			break;
		}
	}

FINAL:
	if (NULL != lpszNameW)
	{
		delete [] lpszNameW;
		lpszNameW = NULL;
	}
	return bRtnValue;
}

// Wide�� Ansi�� �����Ѵ�.
// NULL ������ ���� ����.
// ���ϰ��� delete [] �ؾ� �Ѵ�.
LPSTR CPipeData::W_2_A(IN LPCWSTR lpszSourceW)
{
	INT		nCchNeed		= 0;
	LPSTR	lpszRtnValueA	= NULL;

	if (NULL == lpszSourceW)
	{
		lpszSourceW = L"";
	}

	nCchNeed = ::WideCharToMultiByte(CP_UTF8, 0, lpszSourceW, -1, NULL, 0, NULL, NULL);
	nCchNeed++;

	lpszRtnValueA = new CHAR[nCchNeed];
	if (NULL == lpszRtnValueA)
	{
		nCchNeed = 1;
		lpszRtnValueA = new CHAR[nCchNeed];
		lpszRtnValueA[0] = '\0';
		goto FINAL;
	}

	ZeroMemory(lpszRtnValueA, nCchNeed);
	::WideCharToMultiByte(CP_UTF8, 0, lpszSourceW, -1, lpszRtnValueA, nCchNeed, NULL, NULL);
FINAL:
	return lpszRtnValueA;
}

// Ansi�� Wide�� �����Ѵ�.
// NULL ������ ���� ����.
// ���ϰ��� delete [] �ؾ� �Ѵ�.
LPWSTR CPipeData::A_2_W(IN LPCSTR lpszSourceA)
{
	INT		nCchNeed		= 0;
	LPWSTR	lpszRtnValueW	= NULL;

	if (NULL == lpszSourceA)
	{
		lpszSourceA = "";
	}

	nCchNeed = ::MultiByteToWideChar(CP_UTF8, 0, lpszSourceA, -1, NULL, 0);
	nCchNeed++;

	lpszRtnValueW = new WCHAR[nCchNeed];
	if (NULL == lpszRtnValueW)
	{
		nCchNeed = 1;
		lpszRtnValueW = new WCHAR[nCchNeed];
		lpszRtnValueW[0] = TEXT('\0');
		goto FINAL;
	}

	ZeroMemory(lpszRtnValueW, nCchNeed*(sizeof(WCHAR)));
	::MultiByteToWideChar(CP_UTF8, 0, lpszSourceA, -1, lpszRtnValueW, nCchNeed);
FINAL:
	return lpszRtnValueW;
}

// \251[int64size]base64data
// ���·� �����.
// 251�� magic field�̸�,
// int64 ũ���� ��ü ����(magic byte field ����)�� int64������ ����.
// �� �������� ���� base64 data�� ����.
// �̴�, �պκ� �Ϻθ� �о�,
// ��ü Size�� ���� �˱� ���ؼ� �̴�.
BOOL CPipeData::ToBase64Alloc(OUT LPBYTE* ppBuf, OUT size_t* pdwCbSize)
{
	BOOL	bRtnValue	= FALSE;
	LPBYTE	pBufByte	= NULL;
	LPBYTE	pBufAlloc	= NULL;
	INT64	dwCbTotal	= 0;
	size_t	dwCbSize	= 0;
	size_t	dwCbEncode	= 0;

	if (NULL != pdwCbSize)
	{
		*pdwCbSize = 0;
	}

	if ((NULL == ppBuf) || (NULL == pdwCbSize))
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	bRtnValue = ToByteAlloc(&pBufByte, &dwCbSize);
	if ((FALSE == bRtnValue) || (0 == dwCbSize))
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	dwCbEncode = CPipeData::Base64EncodeGetRequiredLength(dwCbSize, PIPEDATA_BASE64_FLAG_NOPAD);
	if (0 == dwCbEncode)
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}
	
	pBufAlloc = new BYTE[dwCbEncode + 1 + sizeof(dwCbTotal)];
	if (NULL == pBufAlloc)
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}
	#ifdef _DEBUG
		ZeroMemory(pBufAlloc, dwCbEncode + 1 + sizeof(dwCbTotal));
	#endif

	if (FALSE == CPipeData::Base64Encode(pBufByte, 
										 dwCbSize, 
										 (LPSTR)&pBufAlloc[1 + sizeof(dwCbTotal)], 
										 (PINT)&dwCbEncode,
										 PIPEDATA_BASE64_FLAG_NOPAD))
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	dwCbTotal = dwCbEncode + 1 + sizeof(dwCbTotal);

	// magic field�� byte���̸� ���δ�.
	pBufAlloc[sizeof(dwCbTotal)] = 241;	// magic field
	CopyMemory(pBufAlloc, &dwCbTotal, sizeof(dwCbTotal));

	// ������� �Դٸ� ����
	*ppBuf		= pBufAlloc;
	*pdwCbSize	= (size_t)(dwCbEncode + 1 + sizeof(dwCbTotal));

FINAL:
	if (NULL != pBufByte)
	{
		FreeAlloc(pBufByte);
		pBufByte = NULL;
	}
	return bRtnValue;
}

BOOL CPipeData::FromBase64(IN LPBYTE pBuf, IN size_t dwCbSize)
{
	BOOL	bRtnValue	= FALSE;
	INT		nCbNeed		= 0;
	INT		nCbDecode	= 0;
	LPBYTE	pBufDecode	= NULL;
	INT64	dwCbTotal	= 0;

	// ���� ������ ��� ������.
	ClearAllParam();

	if ((NULL == pBuf) || (0 == dwCbSize))
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	if (241 != pBuf[sizeof(INT64)])
	{
		bRtnValue = FALSE;
		PIPETRACELOG(TEXT("[P][ERROR] Fail to parity, %d"), pBuf[0]);
		assert(FALSE);
		goto FINAL;
	}

	CopyMemory(&dwCbTotal, pBuf, sizeof(dwCbTotal));
	
	if ((DWORD)dwCbTotal != dwCbSize)
	{
		// ũ�Ⱑ �ٸ�!
		bRtnValue = FALSE;
		PIPETRACELOG(TEXT("[P][ERROR] Fail to parity 2nd, %d, %d"), (DWORD)dwCbTotal, dwCbSize);
		assert(FALSE);
		goto FINAL;
	}

	nCbNeed = CPipeData::Base64DecodeGetRequiredLength(dwCbSize - (1 + sizeof(dwCbTotal)));
	if (0 == nCbNeed)
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	pBufDecode = new BYTE[nCbNeed];
	if (NULL == pBufDecode)
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	#ifdef _DEBUG
		ZeroMemory(pBufDecode, nCbNeed);
	#endif

	nCbDecode = nCbNeed;
	if (FALSE == CPipeData::Base64Decode((LPSTR)&pBuf[1 + sizeof(dwCbTotal)], dwCbSize - (1 + sizeof(dwCbTotal)), pBufDecode, &nCbDecode))
	{
		PIPETRACELOG(TEXT("[P][ERROR] Fail to dec, %d, %d"), dwCbSize, nCbDecode);
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	bRtnValue = FromByte(pBufDecode, nCbDecode);
	if (FALSE == bRtnValue)
	{
		bRtnValue = FALSE;
		assert(FALSE);
		goto FINAL;
	}

	// ������� �Դٸ� ����
	bRtnValue = TRUE;

FINAL:
	if (NULL != pBufDecode)
	{
		delete [] pBufDecode;
		pBufDecode = NULL;
	}
	return bRtnValue;
}

size_t CPipeData::GetSizeFieldLength(IN size_t dwCbSize)
{
	size_t dwRtnValue	= 0;
	size_t dwCchLength	= 0;
	TCHAR  szDigit[12]	= {0,};	// 4294967295�� ������ �� �ִ� �����̴�.

	StringCchPrintf(szDigit, 12, TEXT("%d"), dwCbSize);
	dwCchLength = _tcslen(szDigit);

	StringCchPrintf(szDigit, 12, TEXT("%d"), dwCchLength + dwCbSize);
	dwRtnValue = _tcslen(szDigit);

	return dwRtnValue;
}

// �Ϻ��� ���� Byte Stream�� ������, ��ü ���̸� ���Ѵ�.
// 0�̸� ���� ��Ȳ
size_t CPipeData::GetSizeStream(IN LPBYTE pBuf, IN size_t dwCbLengthBuf)
{
	INT		i			= 0;
	BOOL	bFound		= FALSE;
	size_t	dwRtnValue	= 0;

	if (NULL == pBuf)
	{
		dwRtnValue = 0;
		goto FINAL;
	}

	// valid üũ
	// |�� ���ö����� 0~9�� �;� �Ѵ�.
	for (i=0; i<(INT)dwCbLengthBuf; i++)
	{
		if ('|' == pBuf[i])
		{
			bFound = TRUE;
			break;
		}

		if (('0' <= pBuf[i]) && (pBuf[i] <= '9'))
		{
			// good
		}
		else
		{
			dwRtnValue = 0;
			assert(FALSE);
			goto FINAL;
		}

		if (i > 12)
		{
			dwRtnValue = 0;
			assert(FALSE);
			goto FINAL;
		}
	}

	if (FALSE == bFound)
	{
		dwRtnValue = 0;
		assert(FALSE);
		goto FINAL;
	}

	dwRtnValue = (size_t)_atoi64((LPSTR)pBuf);

FINAL:
	return dwRtnValue;
}

// �Ϻ��� ���� Byte Stream�� ������, ��ü ���̸� ���Ѵ�.
// 0�̸� ���� ��Ȳ
size_t CPipeData::GetSizeBase64Stream(IN LPBYTE pBuf, IN size_t dwCbLengthBuf)
{
	size_t	dwRtnValue	= 0;
	INT64	dwCbTotal	= 0;

	if (NULL == pBuf)
	{
		dwRtnValue = 0;
		goto FINAL;
	}

	if (dwCbLengthBuf < 1 + sizeof(dwCbTotal))
	{
		dwRtnValue = 0;
		assert(FALSE);
		goto FINAL;
	}

	// magic field üũ
	if (241 != pBuf[sizeof(dwCbTotal)])
	{
		dwRtnValue = 0;
		assert(FALSE);
		goto FINAL;
	}

	CopyMemory(&dwCbTotal, &pBuf[0], sizeof(dwCbTotal));

	dwRtnValue = (size_t)dwCbTotal;

FINAL:
	return dwRtnValue;
}

#ifdef _DEBUG
VOID CPipeData::DUMP(VOID)
{
	INT		i					= 0;
	LPBYTE	pData				= 0;
	size_t	dwCbData			= 0;
	TCHAR	szName[MAX_PATH]	= {0,};
	TCHAR	szText[10]			= {0,};

	//////////////////////////////////////////////////////////////////////////
	//
	::EnterCriticalSection(&m_cs);

	PIPETRACELOG(TEXT("[INFO] ****************"));
	PIPETRACELOG(TEXT("[INFO] Start DUMP Param"));
	PIPETRACELOG(TEXT("[INFO] ****************"));

	for (i=0; i<m_nCountArrParam; i++)
	{
		if (FALSE == GetName(i, szName, MAX_PATH))
		{
			PIPETRACELOG(TEXT("[ERROR] Fail to GetName index : %d"), i);
			assert(FALSE);
			goto FINAL;
		}

		if (FALSE == GetParamPtr(szName, &pData, &dwCbData))
		{
			PIPETRACELOG(TEXT("[ERROR] Fail to GetParamPtr index : %d"), i);
			assert(FALSE);
			goto FINAL;
		}

		if (dwCbData < 256)
		{
			LPBYTE  pTemp     = NULL;
			LPCWSTR lpszTemp  = NULL;
			DWORD	dwCbAlloc = 0;

			if (dwCbData > 30)
			{
				dwCbAlloc = 30;
			}
			else
			{
				dwCbAlloc = dwCbData;
			}

			pTemp = new BYTE[dwCbAlloc+1];
			ZeroMemory(pTemp, dwCbAlloc+1);
			CopyMemory(pTemp, pData, dwCbAlloc);

			// pData�� \0�� �ȳ��� �� �����Ƿ�, ���纻�� ���
			lpszTemp = CPipeData::A_2_W((LPCSTR)pTemp);
			delete [] pTemp;
			pTemp = NULL;
			PIPETRACELOG(TEXT("[INFO][%d] Name=%s, Size=%d, Data(UTF8)=%s"), i, szName, dwCbData, lpszTemp);
			delete [] lpszTemp;
			lpszTemp = NULL;
		}
		else
		{
			PIPETRACELOG(TEXT("[INFO][%d] Name=%s, Data=[TOO LARGE]"), i, szName);
		}
	}

FINAL:
	PIPETRACELOG(TEXT("[INFO] *****************"));
	PIPETRACELOG(TEXT("[INFO] Finish DUMP Param"));
	PIPETRACELOG(TEXT("[INFO] *****************"));
	::LeaveCriticalSection(&m_cs);
	//
	//////////////////////////////////////////////////////////////////////////
}
#endif

// Copy from <atlenc.h>

// http://msdn.microsoft.com/ko-kr/library/fs9dykya(v=VS.80).aspx
int CPipeData::Base64EncodeGetRequiredLength(int nSrcLen, DWORD dwFlags/*=PIPEDATA_BASE64_FLAG_NONE*/)
{
	__int64 nSrcLen4=static_cast<__int64>(nSrcLen)*4;
	if (nSrcLen4 <= INT_MAX)
	{
	}
	else
	{
		assert(FALSE);
		return 0;
	}

	int nRet = static_cast<int>(nSrcLen4/3);

	if ((dwFlags & PIPEDATA_BASE64_FLAG_NOPAD) == 0)
		nRet += nSrcLen % 3;

	int nCRLFs = nRet / 76 + 1;
	int nOnLastLine = nRet % 76;

	if (nOnLastLine)
	{
		if (nOnLastLine % 4)
			nRet += 4-(nOnLastLine % 4);
	}

	nCRLFs *= 2;

	if ((dwFlags & PIPEDATA_BASE64_FLAG_NOCRLF) == 0)
		nRet += nCRLFs;

	return nRet;
}

// http://msdn.microsoft.com/ko-kr/library/bxbcyhkh(v=VS.80).aspx
int CPipeData::Base64DecodeGetRequiredLength(int nSrcLen)
{
	return nSrcLen;
}

// http://msdn.microsoft.com/ko-kr/library/ezec6x4e(v=VS.80).aspx
BOOL CPipeData::Base64Encode(
							 _In_count_(nSrcLen) const BYTE *pbSrcData,
							 _In_ int nSrcLen,
							 _Out_z_cap_post_count_(*pnDestLen, *pnDestLen) LPSTR szDest,
							 _Inout_ int *pnDestLen,
							 _In_ DWORD dwFlags/* = PIPEDATA_BASE64_FLAG_NONE*/)
{
	static const char s_chBase64EncodingTable[64] = {
		'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q',
		'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g',	'h',
		'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y',
		'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/' };

		if (!pbSrcData || !szDest || !pnDestLen)
		{
			return FALSE;
		}

		if(*pnDestLen < Base64EncodeGetRequiredLength(nSrcLen, dwFlags))
		{
			assert(FALSE);
			return FALSE;
		}

		int nWritten( 0 );
		int nLen1( (nSrcLen/3)*4 );
		int nLen2( nLen1/76 );
		int nLen3( 19 );

		for (int i=0; i<=nLen2; i++)
		{
			if (i==nLen2)
				nLen3 = (nLen1%76)/4;

			for (int j=0; j<nLen3; j++)
			{
				DWORD dwCurr(0);
				for (int n=0; n<3; n++)
				{
					dwCurr |= *pbSrcData++;
					dwCurr <<= 8;
				}
				for (int k=0; k<4; k++)
				{
					BYTE b = (BYTE)(dwCurr>>26);
					*szDest++ = s_chBase64EncodingTable[b];
					dwCurr <<= 6;
				}
			}
			nWritten+= nLen3*4;

			if ((dwFlags & PIPEDATA_BASE64_FLAG_NOCRLF)==0)
			{
				*szDest++ = '\r';
				*szDest++ = '\n';
				nWritten+= 2;
			}
		}

		if (nWritten && (dwFlags & PIPEDATA_BASE64_FLAG_NOCRLF)==0)
		{
			szDest-= 2;
			nWritten -= 2;
		}

		nLen2 = (nSrcLen%3) ? (nSrcLen%3 + 1) : 0;
		if (nLen2)
		{
			DWORD dwCurr(0);
			for (int n=0; n<3; n++)
			{
				if (n<(nSrcLen%3))
					dwCurr |= *pbSrcData++;
				dwCurr <<= 8;
			}
			for (int k=0; k<nLen2; k++)
			{
				BYTE b = (BYTE)(dwCurr>>26);
				*szDest++ = s_chBase64EncodingTable[b];
				dwCurr <<= 6;
			}
			nWritten+= nLen2;
			if ((dwFlags & PIPEDATA_BASE64_FLAG_NOPAD)==0)
			{
				nLen3 = nLen2 ? 4-nLen2 : 0;
				for (int j=0; j<nLen3; j++)
				{
					*szDest++ = '.';
				}
				nWritten+= nLen3;
			}
		}

		*pnDestLen = nWritten;
		return TRUE;
}

int CPipeData::DecodeBase64Char(unsigned int ch)
{
	// returns -1 if the character is invalid
	// or should be skipped
	// otherwise, returns the 6-bit code for the character
	// from the encoding table
	if (ch >= 'A' && ch <= 'Z')
		return ch - 'A' + 0;	// 0 range starts at 'A'
	if (ch >= 'a' && ch <= 'z')
		return ch - 'a' + 26;	// 26 range starts at 'a'
	if (ch >= '0' && ch <= '9')
		return ch - '0' + 52;	// 52 range starts at '0'
	if (ch == '+')
		return 62;
	if (ch == '/')
		return 63;
	return -1;
}

// http://msdn.microsoft.com/ko-kr/library/2fzdww6e(v=VS.80).aspx
BOOL CPipeData::Base64Decode(LPCSTR szSrc, int nSrcLen, BYTE *pbDest, int *pnDestLen)
{
	// walk the source buffer
	// each four character sequence is converted to 3 bytes
	// CRLFs and =, and any characters not in the encoding table
	// are skiped

	if (szSrc == NULL || pnDestLen == NULL)
	{
		assert(FALSE);
		return FALSE;
	}

	LPCSTR szSrcEnd = szSrc + nSrcLen;
	int nWritten = 0;

	BOOL bOverflow = (pbDest == NULL) ? TRUE : FALSE;

	while (szSrc < szSrcEnd &&(*szSrc) != 0)
	{
		DWORD dwCurr = 0;
		int i;
		int nBits = 0;
		for (i=0; i<4; i++)
		{
			if (szSrc >= szSrcEnd)
				break;
			int nCh = DecodeBase64Char(*szSrc);
			szSrc++;
			if (nCh == -1)
			{
				// skip this char
				i--;
				continue;
			}
			dwCurr <<= 6;
			dwCurr |= nCh;
			nBits += 6;
		}

		if(!bOverflow && nWritten + (nBits/8) > (*pnDestLen))
			bOverflow = TRUE;

		// dwCurr has the 3 bytes to write to the output buffer
		// left to right
		dwCurr <<= 24-nBits;
		for (i=0; i<nBits/8; i++)
		{
			if(!bOverflow)
			{
				*pbDest = (BYTE) ((dwCurr & 0x00ff0000) >> 16);
				pbDest++;
			}
			dwCurr <<= 8;
			nWritten++;
		}

	}

	*pnDestLen = nWritten;

	if(bOverflow)
	{
		if(pbDest != NULL)
		{
			assert(FALSE);
		}

		return FALSE;
	}

	return TRUE;
}

// Copy from <atlenc.h>
//////////////////////////////////////////////////////////////////////////