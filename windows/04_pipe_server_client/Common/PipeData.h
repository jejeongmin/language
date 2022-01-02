#pragma once

//////////////////////////////////////////////////////////////////////////
// Pipe Data를 지원한다.
//
// - 본 Class Instance를 2개 이상의 Thread에서 공유하지 마시오.
//	 즉, Class Instance를 생성한 곳에서만 Method가 동작한다.
//
// - Parameter Name에 |,=,* 문자가 들어가면 안된다.
//	 물론 해당 문자를 UTF8로 변환했을 때에도 들어가면 안되니, 되도록 알파벳으로 구성하라.
//
// - GetParamPtr로 얻어진 Parameter Data는 반드시 read-only로 사용하라.
//   변경이 필요한 경우, caller에서는 복사본을 만들어 사용하라.
//
//////////////////////////////////////////////////////////////////////////

class CPipeData
{
public:
	CPipeData(void);
	~CPipeData(void);

public:
	//////////////////////////////////////////////////////////////////////////
	// Pipe Data Method
	BOOL SetParam(IN LPCTSTR lpszName, IN const LPBYTE pData, IN size_t dwCbSize);
	BOOL GetParamPtr(IN LPCTSTR lpszName, OPTIONAL OUT LPBYTE* ppData, OPTIONAL OUT size_t* pdwCbSize);
	VOID ClearAllParam(VOID);
	INT  GetCount(VOID);
	BOOL GetName(IN INT nIndex, OUT LPTSTR lpszName, IN size_t dwCchLength);

public:
	//////////////////////////////////////////////////////////////////////////
	// Pipe Stream Method
	BOOL ToByteAlloc(OUT LPBYTE* ppBuf, OUT size_t* pdwCbSize);
	BOOL FromByte(IN LPBYTE pBuf, IN size_t dwCbSize);

	//////////////////////////////////////////////////////////////////////////
	// Pipe Base64 Stream Method
	BOOL ToBase64Alloc(OUT LPBYTE* ppBuf, OUT size_t* pdwCbSize);
	BOOL FromBase64(IN LPBYTE pBuf, IN size_t dwCbSize);

	//////////////////////////////////////////////////////////////////////////
	// Stream Size
	static size_t	GetSizeStream(IN LPBYTE pBuf, IN size_t dwCbLengthBuf);
	static size_t	GetSizeBase64Stream(IN LPBYTE pBuf, IN size_t dwCbLengthBuf);

	//////////////////////////////////////////////////////////////////////////
	// Free
	static VOID FreeAlloc(IN LPBYTE pBuf);

#ifdef _DEBUG
	VOID DUMP(VOID);
#else
	inline VOID DUMP(VOID) { }
#endif

protected:
	//////////////////////////////////////////////////////////////////////////
	// Parameter name valid check
	BOOL CheckName(IN LPCTSTR lpszName);

	//////////////////////////////////////////////////////////////////////////
	// Structure
private:
	typedef struct tagST_PIPEDATA_PARAM
	{
		LPTSTR	lpszParamName;
		size_t	dwCbSize;
		LPBYTE	pData;
	} ST_PIPEDATA_PARAM, *LPST_PIPEDATA_PARAM;

	//////////////////////////////////////////////////////////////////////////
	// Utility
public:
	LPSTR	W_2_A(IN LPCWSTR lpszSource);
	LPWSTR	A_2_W(IN LPCSTR lpszSourceA);
	size_t	GetSizeFieldLength(IN size_t dwCbSize);

private:
	CRITICAL_SECTION	m_cs;
	LPST_PIPEDATA_PARAM	m_pstArrParam;
	INT					m_nCountArrParam;
	INT					m_nAllocArrParam;
	DWORD				m_dwThreadId;

	//////////////////////////////////////////////////////////////////////////
	// Base64 (from ATL(atlenc.h))
	#define PIPEDATA_BASE64_FLAG_NONE	 0
	#define PIPEDATA_BASE64_FLAG_NOPAD	 1
	#define PIPEDATA_BASE64_FLAG_NOCRLF  2
public:
	static int Base64EncodeGetRequiredLength(int nSrcLen, DWORD dwFlags);
	static int Base64DecodeGetRequiredLength(int nSrcLen);
	static BOOL Base64Encode(_In_count_(nSrcLen) const BYTE *pbSrcData, _In_ int nSrcLen, _Out_z_cap_post_count_(*pnDestLen, *pnDestLen) LPSTR szDest, _Inout_ int *pnDestLen, _In_ DWORD dwFlags);
	static BOOL Base64Decode(LPCSTR szSrc, int nSrcLen, BYTE *pbDest, int *pnDestLen);
protected:
	static int DecodeBase64Char(unsigned int ch);
};
