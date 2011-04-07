/*
 * Xournal++
 *
 * A scheduler for background jobs
 *
 * Some code from Evince project
 *
 * @author Xournal Team
 * http://xournal.sf.net
 *
 * @license GPL
 */

#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__

#include "Job.h"
#include <glib.h>

#include "../../util/XournalType.h"

typedef enum {
	JOB_PRIORITY_URGENT, // Rendering current page range
	JOB_PRIORITY_HIGH, // Rendering current thumbnail range
	JOB_PRIORITY_LOW, // Rendering pages not in current range
	JOB_PRIORITY_NONE, // Any other job: load, save, print, ...
	JOB_N_PRIORITIES
} JobPriority;

class Scheduler {
public:
	Scheduler();
	virtual ~Scheduler();

public:
	/**
	 * Adds a job
	 *
	 * The Job is now owned by the scheduler, and automatically freed if it is done
	 */
	void addJob(Job * job, JobPriority priority);

	void stop();

	/**
	 * Locks the complete scheduler
	 */
	void lock();

	/**
	 * Unlocks the complete scheduler
	 */
	void unlock();

private:
	static gpointer jobThreadCallback(Scheduler * scheduler);
	Job * getNextJobUnlocked();

protected:
	XOJ_TYPE_ATTRIB;

	bool threadRunning;

	GThread * thread;

	GCond * jobQueueCond;
	GMutex * jobQueueMutex;

	GMutex * schedulerMutex;

	// this is need to be sure there is no job running if we delete a page, else we may access delete memory...
	GMutex * jobRunningMutex;

	GQueue queueUrgent;
	GQueue queueHigh;
	GQueue queueLow;
	GQueue queueNone;

	GQueue * jobQueue[JOB_N_PRIORITIES];

};

#endif /* __SCHEDULER_H__ */