/*
 * IPluhin.h
 *
 *  Created on: 2 lip 2014
 *      Author: dev
 */

#ifndef IPLUHIN_H_
#define IPLUHIN_H_
#include <string>

using std::string;

class IPlugin
{
public:
	virtual void getName(std::string & name) = 0;
	virtual void moduleMain() = 0;
	virtual ~IPlugin() {}
protected:
private:
};



#endif /* IPLUHIN_H_ */
