/*
 * CDAControler.h
 *
 *  Created on: 5 lip 2014
 *      Author: dev
 */

#ifndef CDACONTROLER_H_
#define CDACONTROLER_H_
#include "CDAMenagerPlugin.h"
#include "CDASetting.h"

class CDAControler {
public:
	static CDAControler& getInstance()
	{
		static CDAControler instance;
		return instance;
	}

	CDAMenagerPlugin menagerPlugin;
protected:
private:
	CDAControler() {

	}
	~CDAControler() {}
	CDAControler(CDAControler const &);
	CDAControler& operator=(CDAControler const&);
};

#endif /* CDACONTROLER_H_ */
