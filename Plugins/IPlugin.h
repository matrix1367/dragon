/*
 * IPluhin.h
 *
 *  Created on: 2 lip 2014
 *      Author: dev
 */

#ifndef IPLUHIN_H_
#define IPLUHIN_H_
#include <string>
#include <stdio.h>
using std::string;

class IPlugin
{
public:
	virtual void getName(std::string & name) = 0;
	virtual void moduleMain(int argc, char **argv) = 0;
	virtual ~IPlugin() {printf("[CDAMenagerPlugin::%s] : (%d)" , __FUNCTION__ , __LINE__);}
protected:
private:
};



#endif /* IPLUHIN_H_ */
