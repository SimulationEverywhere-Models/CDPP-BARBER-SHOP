/*******************************************************************
*
*  DESCRIPTION: Atomic Model Checkhair
*
*  AUTHOR: Art Gresham 
*  cloned from q ueue Barylko & Jorge Beyoglonian 
*
*  EMAIL: 
*
*  DATE: 20/10/2003
*
*******************************************************************/
#ifndef __CHECKHAIR_H
#define __CHECKHAIR_H

#include <list>
#include "atomic.h"     // class Atomic

class Checkhair : public Atomic
{
public:
	Checkhair( const string &name = "Checkhair" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
   const Port &cust ;
   const Port &progress ;
   Port &cutcontinue ;
	Port &finished ;
	Time preparationTime;
   int cutcount, cutmax, newcutmax;
	Time timeLeft;

};	// class Checkhair

// ** inline ** // 
inline
string Checkhair::className() const
{
	return "Checkhair" ;
}

#endif   //__CHECKHAIR_H
