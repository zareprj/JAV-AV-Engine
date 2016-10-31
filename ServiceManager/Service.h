
#ifndef _SERVICE_
#define _SERVICE_

class Service
{

public:
	virtual bool Start()=0;
	virtual bool Stop()=0;
	virtual bool Puase()=0;
	virtual bool Continue()=0;
};

#endif