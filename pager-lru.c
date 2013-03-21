/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */
#include <errno.h>
#include "lru.h"

static uint32_t tick = 0; // artificial time
	
static void lru_pageit(Pentry q[MAXPROCESSES], uint32_t tick) {
	int proc, page, state, evicted;
	
	for(proc = 0; proc < MAXPROCESSES; proc++) {
		if(!q[proc].active) /* done if its not active */
			continue;

		page = q[proc].pc/PAGESIZE;
		/* note this time for future eviction decisions */
		timestamps[proc][page] = tick; 
		
		/* done if the page is already in memory */
		if(q[proc].pages[page]) 
			continue;

		/* the page is not in memory.
		 * if pagein give 1 the page is either 
		 * on its way already or we just got it
		 * started, so we are done with this process
		 */
		if(pagein(proc, page, &state) )
			continue;

		/* either the page is swapping out or 
		 * there are no free physical pages
		 */
		if(state == SWAPOUT) 
			continue; /* just have to wait... */

		/* there are no free physical pages */
		if(pages_alloc(q, proc) < 1) 
			continue; /* must have at least one page to evict */

		lru_page(q, proc, tick, &evicted);

		if(!pageout(proc, evicted) ) {
			endit();
		}
	}
}

void exit_fn() {
	printf("final tick value was %d\n", tick);	
}

void pageit(Pentry q[MAXPROCESSES]) { 
	/* tick starts at 1, so 0 means this is the first run
	 * or an overflow. either way, reset timestamps.
	 */	
	if(tick < 1) {
		timestamps_init();		
		tick = 1;
		if(atexit(exit_fn) != 0) {
			perror(NULL);
			exit(1);
		}
	}	
	
	lru_pageit(q, tick);
	
	/* advance time for next pageit iteration */
	tick++;
} 


