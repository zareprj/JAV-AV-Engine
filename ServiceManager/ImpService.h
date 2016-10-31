#include "Service.h"
#include <windows.h>
class ImpService: public Service
{
public:
	bool Start();
	bool Stop();
protected:
private:
};