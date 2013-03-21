#ifndef PHIST_H
#define PHIST_H
#include <string.h>

struct phist_record {
	int page;
	int fault;
};

#define HSIZE (1 << 11)

struct phist {
	struct phist_record records[HSIZE];
	int head;
	int tail;
};


void phist_init(struct phist *ph);
void phist_push(struct phist *ph, const struct phist_record *ph_r);
void phist_len(const struct phist *ph, int *len);
/* phist_len(ph, &hlen);
 * t = 0 -> most recent access
 * t = 1 -> 2nd most recent access
 * ...
 * t = hlen-1 -> oldest access
 */
void phist_at(const struct phist *ph, int t, struct phist_record *ph_r);
void phist_fault_sum(const struct phist *ph, int *sum);
void phist_working_set(const struct phist *ph, int *pset, size_t psize);
void phist_working_set_and_fault_sum(const struct phist *ph, int *pset, size_t psize, int *sum);
void phist_print_records(const struct phist *ph);

#endif /* PHIST_H */