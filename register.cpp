/*******************************************************************
*
*  DESCRIPTION: Simulator::registerNewAtomics()
*
*  AUTHOR: Amir Barylko & Jorge Beyoglonian 
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*
*  DATE: 27/6/1998
*
*******************************************************************/

#include "modeladm.h" 
#include "mainsimu.h"
#include "queue.h"      // class Queue
#include "reception.h"  // class Reception
#include "cuthair.h"     // class Review
#include "checkhair.h"     // class Review
#include "generat.h"    // class Generator
#include "cpu.h"        // class CPU
#include "transduc.h"   // class Transducer
#include "trafico.h"    // class Trafico


void MainSimulator::registerNewAtomics()
{
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Reception>() , "Reception" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Cuthair>() , "Cuthair" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Checkhair>() , "Checkhair" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Queue>() , "Queue" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Generator>() , "Generator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<CPU>() , "CPU" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Transducer>() , "Transducer" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Trafico>() , "Trafico" ) ;
}
