/*******************************************************************
*
*  DESCRIPTION: Atomic Model Reception
*
*  AUTHOR: Art Gresham 
*  cloned from q ueue Barylko & Jorge Beyoglonian 
*
*  EMAIL: 
*
*  DATE: 20/10/2003
*
*******************************************************************/
#ifndef __RECEPTION_H
#define __RECEPTION_H

#include <list>
#include "atomic.h"     // class Atomic

class Reception : public Atomic
{
public:
	Reception( const string &name = "Reception" );					//Default constructor

	virtual string className() const ;
protected:
	Model &initFunction();
	Model &externalFunction( const ExternalMessage & );
	Model &internalFunction( const InternalMessage & );
	Model &outputFunction( const InternalMessage & );

private:
	const Port &newcust;
	const Port &next;
	Port &cust;
	Time preparationTime;
   Time openingTime ;
   Time closingTime ;
   unsigned int numberofChairs  ;
   string initInt ;
   bool we_are_full ;
   bool cust_is_ready ;
	typedef list<Value> ElementList ;
	ElementList elements ;

	Time timeLeft;

};	// class Reception

// ** inline ** // 
inline
string Reception::className() const
{
	return "Reception" ;
}

#endif   //__RECEPTION_H
