
// GlimReport92728974.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

#include <functional>

// CGlimReport92728974App:
// See GlimReport92728974.cpp for the implementation of this class
//

class CGlimReport92728974App : public CWinApp
{
public:
	CGlimReport92728974App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGlimReport92728974App theApp;


class KAtEnd
{
public:
	std::function<void()> _lambda;

	template<typename Func>
	KAtEnd(Func lb)	{
		_lambda = lb;// new std::function<void()>(lambda);
	}
	~KAtEnd()	{
		if(_lambda)
			_lambda();
	}
};
