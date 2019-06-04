// Train1.h: interface for the CTrain class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAIN1_H__056C46E4_DDD0_465C_B4F9_DB72B02DCAC7__INCLUDED_)
#define AFX_TRAIN1_H__056C46E4_DDD0_465C_B4F9_DB72B02DCAC7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTrain  
{
public:
	CTrain();
	virtual ~CTrain();
public:
	char id[10];
	char begin[10];
	char end[10];
	char date[20];
	int number;
	int buy;

};

#endif // !defined(AFX_TRAIN1_H__056C46E4_DDD0_465C_B4F9_DB72B02DCAC7__INCLUDED_)
