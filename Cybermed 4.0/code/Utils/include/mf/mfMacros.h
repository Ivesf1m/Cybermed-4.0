#ifndef MFMACROS_H
#define MFMACROS_H

// Macros ----------------------------------------------------------------------
#ifdef MF_THREADS
	#define MF_LOCK(m) if(mutex) pthread_mutex_lock(&this->m)
	#define MF_UNLOCK(m) if(mutex) pthread_mutex_unlock(&this->m)
	#define MF_DMUTEXV , bool mutex
	#define MF_DMUTEXVD , bool mutex = true
	#define MF_DMUTEX bool mutex
	#define MF_DMUTEXD bool mutex = true
	#define MF_MUTEX mutex
	#define MF_MUTEXV , mutex
	#define MF_MUTEXT this->mutex
	#define MF_MUTEXVT , this->mutex
	#define MF_MUTEXFALSE false
	#define MF_MUTEXFALSEV , false
	#define MF_MUTEXDO(m) m

	#define MF_TREADER_QTDSQL 1000 //select dividido por blocos
	
#else
	#define MF_LOCK(m)
	#define MF_UNLOCK(m)
	#define MF_DMUTEXV
	#define MF_DMUTEXVD
	#define MF_DMUTEX
	#define MF_DMUTEXD
	#define MF_MUTEX
	#define MF_MUTEXV
	#define MF_MUTEXT
	#define MF_MUTEXVT
	#define MF_MUTEXFALSE
	#define MF_MUTEXFALSEV
	#define MF_MUTEXDO
	
#endif

#ifdef MF_DEBUG
	#define MF_ASSERT(c) assert(c)
	#ifdef MF_THREADS
		#define MF_ASSERTLOCK(c,m) pthread_mutex_lock(&this->m);MF_ASSERT(c);pthread_mutex_unlock(&this->m)
	#else
		#define MF_ASSERTLOCK(c,m) MF_ASSERT(c)
	#endif
#else
	#define MF_ASSERT(c)
	#define MF_ASSERTLOCK(c,m)
#endif

// Definicoes ------------------------------------------------------------------
#define MF_FLAGS_TYPE ids
#define MF_FLAGS_INMESH (sizeof(MF_FLAGS_TYPE)*8-1)

#define MF_ERRO 1.0e-15
#define MF_ERRO_INCIRCLE 1.0e-20

#define MAX_BUFFER 255

#endif
