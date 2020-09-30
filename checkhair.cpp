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
/** include files **/
#include "checkhair.h"      // class Checkhair
#include "message.h"    // class ExternalMessage, InternalMessage
#include "mainsimu.h"   // MainSimulator::Instance().getParameter( ... )

/** public functions **/

/*******************************************************************
* Function Name: Checkhair
* Description: 
********************************************************************/
Checkhair::Checkhair( const string &name )
: Atomic( name )
, cust( addInputPort( "cust" ) )
, progress( addInputPort( "progress" ) )
, cutcontinue( addOutputPort( "cutcontinue" ) )
, finished( addOutputPort( "finished" ) )
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
Model &Checkhair::initFunction()
{
   cutcount = 0 ;
   cutmax = 0 ;
   passivate();
   return *this ;
}

/*******************************************************************
* Function Name: externalFunction
* Description: 
********************************************************************/
Model &Checkhair::externalFunction( const ExternalMessage &msg )
{
	if( msg.port() == progress ){
     if(!cutmax){
        cout << lastChange()                         << "chkhr x no cust here for haircut         : " << cutcount << ":" <<  cutmax << "\n"  ; 
     }
	  else { 
       if (!cutcount) {
            cout << lastChange()                     << "chkhr x no hair to cut                   : " << cutcount << ":" <<  cutmax << "\n"  ; 
       } else {
          ++cutcount ;
          holdIn(active, preparationTime ); 
          cout << lastChange()                       << "chkhr x inc count and issue cutcontinue  : " << cutcount << ":" <<  cutmax << "\n"  ; 
       }
     } 
   } else{
       if(state() == active){
          cout << lastChange()                       << "chkhr x busy and interrupted no new cust : " << cutcount << ":" <<  cutmax << "\n"  ; 
       }else{
	      if( msg.port() == cust ){
           if(!cutcount) {
              cout << lastChange()                   << "chkhr x normal receive new customer      : " << cutcount << ":" <<  cutmax << "\n"  ; 
             cutcount++ ;
             newcutmax = abs((int)msg.value())    ;
             holdIn(active, preparationTime ) ; 
           } else {
                cout << lastChange()                 << "chkhr x cust rejected - busy with cust   : " << cutcount << ":" <<  cutmax << "\n"  ; 
           }
         }
      }
   }
	return *this;
}

/*******************************************************************
* Function Name: internalFunction
* Description: 
********************************************************************/
Model &Checkhair::internalFunction( const InternalMessage & )
{

   cout << lastChange()                              << "chkhr i transition :                     : " << cutcount << ":" <<  cutmax << "\n"  ; 
	passivate();
	return *this ;
}

/*******************************************************************
* Function Name: outputFunction
* Description: 
********************************************************************/
Model &Checkhair::outputFunction( const InternalMessage &msg )
{
  if(cutcount == 1) {
      cutmax = newcutmax ;
        cout << lastChange()                         << "chkhr o  first cutcontinue ->cuthair     : " << cutcount << ":" <<  cutmax << "\n"  ; 
      sendOutput( msg.time(), cutcontinue, cutcount ) ;
   } else { 
      if(cutcount > cutmax){
            cout << lastChange()                     << "chkhr o output finished - haircut done   : " << cutcount << ":" <<  cutmax << "\n"  ; 
          cutcount=0;
          sendOutput( msg.time(), finished, cutmax  ) ;
          cutmax=newcutmax ;
      } else {
           cout << lastChange()                      << "chkhr o output ongoing cutcontinue       : " << cutcount << ":" <<  cutmax << "\n"  ; 
         sendOutput( msg.time(), cutcontinue, cutcount ) ;
      }
   }
	return *this ;
}
