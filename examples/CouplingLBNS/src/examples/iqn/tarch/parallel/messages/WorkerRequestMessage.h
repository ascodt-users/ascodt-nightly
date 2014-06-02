#ifndef _TARCH_PARALLEL_MESSAGES_WORKERREQUESTMESSAGE_H
#define _TARCH_PARALLEL_MESSAGES_WORKERREQUESTMESSAGE_H

#include "tarch/compiler/CompilerSpecificSettings.h"
//#include "peano/utils/PeanoOptimisations.h"
#ifdef Parallel
	#include "tarch/parallel/Node.h"
#endif
#ifdef Parallel
	#include <mpi.h>
#endif
#include "tarch/logging/Log.h"
#include "tarch/la/Vector.h"
#include <bitset>
#include <complex>
#include <string>
#include <iostream>

namespace tarch {
   namespace parallel {
      namespace messages {
         class WorkerRequestMessage;
         class WorkerRequestMessagePacked;
      }
   }
}

/**
 * @author This class is generated by DaStGen
 * 		   DataStructureGenerator (DaStGen)
 * 		   2007-2009 Wolfgang Eckhardt
 * 		   2012      Tobias Weinzierl
 *
 * 		   build date: 17-10-2012 11:04
 *
 * @date   17/10/2012 11:05
 */
class tarch::parallel::messages::WorkerRequestMessage { 
   
   public:
      
      typedef tarch::parallel::messages::WorkerRequestMessagePacked Packed;
      
      struct PersistentRecords {
         int _tmp;
         /**
          * Generated
          */
         PersistentRecords();
         
         /**
          * Generated
          */
         PersistentRecords(const int& tmp);
         
         /**
          * Generated
          */
          int getTmp() const ;
         
         /**
          * Generated
          */
          void setTmp(const int& tmp) ;
         
         
      };
      
   private: 
      PersistentRecords _persistentRecords;
      
   public:
      /**
       * Generated
       */
      WorkerRequestMessage();
      
      /**
       * Generated
       */
      WorkerRequestMessage(const PersistentRecords& persistentRecords);
      
      /**
       * Generated
       */
      WorkerRequestMessage(const int& tmp);
      
      /**
       * Generated
       */
      virtual ~WorkerRequestMessage();
      
      /**
       * Generated
       */
       int getTmp() const ;
      
      /**
       * Generated
       */
       void setTmp(const int& tmp) ;
      
      /**
       * Generated
       */
      std::string toString() const;
      
      /**
       * Generated
       */
      void toString(std::ostream& out) const;
      
      
      PersistentRecords getPersistentRecords() const;
      /**
       * Generated
       */
      WorkerRequestMessagePacked convert() const;
      
      
   #ifdef Parallel
      protected:
         static tarch::logging::Log _log;
         
         int _senderRank;
         
      public:
         
         /**
          * Global that represents the mpi datatype.
          * There are two variants: Datatype identifies only those attributes marked with
          * parallelise. FullDatatype instead identifies the whole record with all fields.
          */
         static MPI_Datatype Datatype;
         static MPI_Datatype FullDatatype;
         
         /**
          * Initializes the data type for the mpi operations. Has to be called
          * before the very first send or receive operation is called.
          */
         static void initDatatype();
         
         static void shutdownDatatype();
         
         void send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
         
         void receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
         
         static bool isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
         
         int getSenderRank() const;
         
   #endif
      
   };
   
   /**
    * @author This class is generated by DaStGen
    * 		   DataStructureGenerator (DaStGen)
    * 		   2007-2009 Wolfgang Eckhardt
    * 		   2012      Tobias Weinzierl
    *
    * 		   build date: 17-10-2012 11:04
    *
    * @date   17/10/2012 11:05
    */
   class tarch::parallel::messages::WorkerRequestMessagePacked { 
      
      public:
         
         struct PersistentRecords {
            int _tmp;
            /**
             * Generated
             */
            PersistentRecords();
            
            /**
             * Generated
             */
            PersistentRecords(const int& tmp);
            
            /**
             * Generated
             */
             int getTmp() const ;
            
            /**
             * Generated
             */
             void setTmp(const int& tmp) ;
            
            
         };
         
      private: 
         PersistentRecords _persistentRecords;
         
      public:
         /**
          * Generated
          */
         WorkerRequestMessagePacked();
         
         /**
          * Generated
          */
         WorkerRequestMessagePacked(const PersistentRecords& persistentRecords);
         
         /**
          * Generated
          */
         WorkerRequestMessagePacked(const int& tmp);
         
         /**
          * Generated
          */
         virtual ~WorkerRequestMessagePacked();
         
         /**
          * Generated
          */
          int getTmp() const ;
         
         /**
          * Generated
          */
          void setTmp(const int& tmp) ;
         
         /**
          * Generated
          */
         std::string toString() const;
         
         /**
          * Generated
          */
         void toString(std::ostream& out) const;
         
         
         PersistentRecords getPersistentRecords() const;
         /**
          * Generated
          */
         WorkerRequestMessage convert() const;
         
         
      #ifdef Parallel
         protected:
            static tarch::logging::Log _log;
            
            int _senderRank;
            
         public:
            
            /**
             * Global that represents the mpi datatype.
             * There are two variants: Datatype identifies only those attributes marked with
             * parallelise. FullDatatype instead identifies the whole record with all fields.
             */
            static MPI_Datatype Datatype;
            static MPI_Datatype FullDatatype;
            
            /**
             * Initializes the data type for the mpi operations. Has to be called
             * before the very first send or receive operation is called.
             */
            static void initDatatype();
            
            static void shutdownDatatype();
            
            void send(int destination, int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
            
            void receive(int source, int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
            
            static bool isMessageInQueue(int tag, bool exchangeOnlyAttributesMarkedWithParallelise);
            
            int getSenderRank() const;
            
      #endif
         
      };
      
      #endif
      
