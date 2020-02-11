#include "TimeOperator.h"

SYSTEM_TIME TimeOperator::ToSystemTime( std::string _s )
{
	SYSTEM_TIME st = {};
	//MessageBoxA(0,_s.c_str(),"a",0);
	
	char* buffer = new char[_s.size()+1];
	//fprintf(stderr,"_s1: %s\n", _s.c_str());
	strcpy(buffer, _s.c_str());
	//fprintf(stderr,"_s2: %s\n", _s.c_str());
	
	if(_s != "")
	{
		sscanf(buffer, "%d-%d-%d %d:%d:%d,%d", 
			&st.wYear, &st.wMonth, &st.wDay, &st.wHour, &st.wMinute, &st.wSecond, &st.wMilliseconds);
	}
	//fprintf(stderr,"TIME:%d\t%d\t%d\t%d\t%d\t%d\t%d\n",st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds);
    
	//MessageBoxA(0,_s.c_str(),"b",0);
	//fprintf(stderr,"_s3: %s\n", _s.c_str());
	return st;
}

int TimeOperator::TimeSubtraction(SYSTEM_TIME _a, SYSTEM_TIME _b)
{
	
	SYSTEM_TIME dif_st = {};

	int retSub = 0;
  
   	dif_st.wYear = _b.wYear - _a.wYear;
   	dif_st.wMonth = _b.wMonth - _a.wMonth;
   	dif_st.wDay = _b.wDay - _a.wDay;
   	dif_st.wHour = _b.wHour - _a.wHour;
   	dif_st.wMinute = _b.wMinute - _a.wMinute;
   	dif_st.wSecond = _b.wSecond - _a.wSecond;
   	dif_st.wMilliseconds = _b.wMilliseconds - _a.wMilliseconds;
	fprintf(stderr, "a_y= %d\ta_m= %d\ta_d= %d\ta_h= %d\ta_m= %d\ta_s= %d\ta_mm= %d\n", dif_st.wYear,dif_st.wMonth,dif_st.wDay,dif_st.wHour,dif_st.wMinute,dif_st.wSecond,dif_st.wMilliseconds);
	retSub = (dif_st.wDay * 86400 + dif_st.wHour * 3600 + dif_st.wMinute * 60 + dif_st.wSecond) * 1000 + dif_st.wMilliseconds;
		
	if(retSub < 0)
	{
		//C_DBG_ERR("TIME SUB ERROR!\t");
		//fprintf(stderr, "a_h= %d\ta_m= %d\ta_s= %d\ta_mm= %d\n", _a.wHour,_a.wMinute,_a.wSecond,_a.wMilliseconds);
		//fprintf(stderr, "b_h= %d\tb_m= %d\tb_s= %d\tb_mm= %d\n", _b.wHour,_b.wMinute,_b.wSecond,_b.wMilliseconds);
		//fprintf(stderr, "retSub= %d\n", retSub);
	}
	if(retSub > (60 * 1000))
	{
		fprintf(stderr, "a_h= %d\ta_m= %d\ta_s= %d\ta_mm= %d\n", _a.wHour,_a.wMinute,_a.wSecond,_a.wMilliseconds);
		fprintf(stderr, "b_h= %d\tb_m= %d\tb_s= %d\tb_mm= %d\n", _b.wHour,_b.wMinute,_b.wSecond,_b.wMilliseconds);
		fprintf(stderr, "retSub= %d\n", retSub);
	}
	return retSub;
}
