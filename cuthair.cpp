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
/** include files **/
#include "cuthair.h"      // class Cuthair
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Cuthair
* Description: 
********************************************************************/
Cuthair::Cuthair( const string &name )
: Atomic( name )
, cutcontinue( addInputPort( "cutcontinue" ) )
, progress( addOutputPort( "progress" ) )
, preparationTime( 0, 0, 10, 0 )
{
   string time( MainSimulator::Instance().getParameter( description(), "preparationTime" ) ) ;

   if( time != "" )
		preparationTime = time ;
}

/*******************************************************************
* Function Name: initFunction
* Description: Resetea la lista
* Precondition: El tiempo del proximo evento interno es Infinito
********************************************************************/
Model &Cuthair::initFunction()
{
   passivate();
   return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Cuthair::externalFunction( const ExternalMessage &msg )
{
   if(state() == active){
      cout << lastChange()                          << "cuthr x i'm already cutting - can't do     : " << msg.value() << "\n"  ; 
   } else {
         holdIn(active, preparationTime ); 
         cout << lastChange()                       << "cuthr x ok i'm cutting now                 : " << msg.value() << "\n"  ; 
   }
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Cuthair::internalFunction( const InternalMessage & )
{

   //cout << "passivate"  ;
   cout << lastChange()                              << "cuthr i internal transition               : \n"  ; 
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Cuthair::outputFunction( const InternalMessage &msg )
{
      //cout << "output finished" << cutcount ;
   cout << lastChange()                              << "cuthr o output reporting progress         : \n"  ; 
   sendOutput( msg.time(), progress, 1 ) ;
	return *this ;
}
