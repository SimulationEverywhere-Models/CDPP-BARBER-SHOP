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
/** include files **/
#include "reception.h"      // class Reception
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Reception
* Description: 
********************************************************************/
Reception::Reception( const string &name )
: Atomic( name )
, newcust( addInputPort( "newcust" ) )
, next( addInputPort( "next" ) )
, cust( addOutputPort( "cust" ) )
, preparationTime( 0,0, 0, 0 )
, openingTime( 9,0, 0, 0 )
, closingTime( 16,0, 0, 0 )
, numberofChairs( 7 )
{
   initInt = ( MainSimulator::Instance().getParameter( description(), "numberofChairs" ) ) ;
	if(initInt != "")
		numberofChairs = str2Int(initInt) ;
	string time = ( MainSimulator::Instance().getParameter( description(), "preparationTime" ) ) ;
	if( time != "" )
		preparationTime = time ;
	time = ( MainSimulator::Instance().getParameter( description(), "openingTime" ) ) ;
	if( time != "" )
		openingTime = time ;
	time = ( MainSimulator::Instance().getParameter( description(), "closingTime" ) ) ;
	if( time != "" )
		closingTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Reception::initFunction()
{
   we_are_full = false ;
   cust_is_ready = false ;
	elements.erase( elements.begin(), elements.end() ) ;
	return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Reception::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == newcust ){
      if    (   (msg.time().asMsecs() - Time(openingTime).asMsecs() < 0)
             || (msg.time().asMsecs() - Time(closingTime).asMsecs() > 0)
           ) { 
          cout << lastChange()        << "rcptn  x we are closed - sorry            : " << elements.size() << " : " << elements.front() << "\n" ; 
      } else {  
          if (!(elements.size() < numberofChairs)) {
              cout << lastChange()    << "rcptn  x we are full - sorry              : " << elements.size() << " : " << elements.front() <<  "\n" ;
          }else{
            elements.push_back( abs((int)msg.value()) ) ;
             cout << lastChange()     << "rcptn  x queued a newcust request         : " << elements.size() << " : " << elements.front() << "\n" ;
            if (elements.size() == 1) {
                cout << lastChange()  << "rcptn  x activating first cust is coming  : " << elements.size() << " : " << elements.front() << "\n" ;
               holdIn( active, preparationTime ) ;
            } else {
                cout << lastChange()  << "rcptn  x NEW cust in queue                : " << elements.size() << " : " << elements.front() << "\n" ;
            }
         }
      }
   } 
   if (msg.port() == next) {
            cout << lastChange()      << "rcptn  x activating queued cust is coming : " << elements.size() << " : " << elements.front() << "\n" ;
            holdIn( active, preparationTime ) ;
	}
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Reception::internalFunction( const InternalMessage & )
{
    cout << lastChange()              << "rcptn  i transition                       : " << elements.size() << " : " << elements.front() << "\n" ;
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Reception::outputFunction( const InternalMessage &msg )
{  
   if (elements.size()) {
      cout << lastChange()            << "rcptn  o transition                       : " << elements.size() << " : " << elements.front() << "\n" ;
     sendOutput( msg.time(), cust, elements.front() ) ;
     elements.pop_front();
   } else {
      cout << lastChange()            << "rcptn  o transition no customer to work on: " << elements.size() << " : " << elements.front() << "\n" ;
   }
	return *this ;
}
