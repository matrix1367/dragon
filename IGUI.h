/*
 * IGUI.h
 *
 *  Created on: 13 lip 2014
 *      Author: dev
 */

#ifndef IGUI_H_
#define IGUI_H_


class IGUI
{
public:
	virtual ~IGUI(){}
	virtual int WindowMain(int argc, char **argv) = 0;
protected:
private:
	//IGUI();

};


#endif /* IGUI_H_ */
