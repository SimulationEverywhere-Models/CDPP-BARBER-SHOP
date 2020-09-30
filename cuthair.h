/*******************************************************************
*
*  DESCRIPTION: Atomic Model Cuthair
*
*  AUTHOR: Art Gresham 
*  cloned from q ueue Barylko & Jorge Beyoglonian 
*
*  EMAIL: 
*
*  DATE: 20/10/2003
*
*******************************************************************/
#ifndef __CUTHAIR_H
#define __CUTHAIR_H

#include <list>
#include "atomic.h"     // class Atomic

class Cuthair : public Atomic
{
public:
	Cuthair( const string &name = "Cuthair" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
   const Port &cutcontinue ;
   Port &progress ;
	Time preparationTime;
	Time timeLeft;

};	// class Cuthair

// ** inline ** // 
inline
string Cuthair::className() const
{
	return "Cuthair" ;
}

#endif   //__CUTHAIR_H
