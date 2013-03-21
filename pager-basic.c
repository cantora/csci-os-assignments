/*
 * File: pager-basic.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 4
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains a simple pageit
 *      implmentation at performs very poorly, but
 *      provided a basic idea of how to user the
 *      simulator interface. Your job is to improve
 *      upon this implmentation.
 */
#include <stdio.h>
#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) { 
    
    /* Local vars */
    int proc;
    int pc;
    int page;
    int oldpage; 
	int dummy;

    /* Trivial paging strategy */
    /* Select first active process */ 
    for(proc=0; proc<MAXPROCESSES; proc++) { 
	/* Is process active? */
		if(q[proc].active) {
		    /* Dedicate all work to first active process*/ 
		    pc = q[proc].pc; 		        // program counter for process
		    page = pc/PAGESIZE; 		// page the program counter needs
		    /* Is page swaped-out? */
		    if(!q[proc].pages[page]) {
				//printf("swapped in process %d:%d\n", proc, page);
				/* Try to swap in */
				if(!pagein(proc,page,&dummy)) {
					printf("failed to pagein\n");
				    /* If swapping fails, swap out another page */
				    for(oldpage=0; oldpage < q[proc].npages; oldpage++) {
			 			/* Make sure page isn't one I want */
						if(oldpage != page) {
						    /* Try to swap-out */
						    if(pageout(proc,oldpage)) {
								/* Break loop once swap-out starts*/
								break;
						    } 
						}
				    }
				}
			}
			
			//fflush(stdout);
		    /* Break loop after finding first active process */
		    break;
		}
    } 
} 
