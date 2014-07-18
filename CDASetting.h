/*
 * CDASetting.h
 *
 *  Created on: 5 lip 2014
 *      Author: dev
 */

#ifndef CDASETTING_H_
#define CDASETTING_H_

#include <string>

class CDASetting {
public:
	static CDASetting& getInstance()
	{
		static CDASetting instance;
		return instance;
	}

	void load();
	void save();

	std::string pathPlugins;
	bool autoRun;
protected:
private:
	CDASetting()
	{
		pathPlugins = "./Plugins/";
		autoRun = true;
	}
	~CDASetting() {}
	CDASetting(CDASetting const &);
	void operator=(CDASetting const&);
};

#endif /* CDASETTING_H_ */
