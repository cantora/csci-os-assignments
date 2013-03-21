#ifndef PHIST_H
#define PHIST_H

struct phist_record {
	int page;
	int fault;
};

//#define HSIZE (1 << 13)
#define HSIZE (1 << 14)

struct phist {
	struct phist_record records[HSIZE];
	int head;
	int tail;
};


void phist_init(struct phist *ph);
void phist_push(struct phist *ph, const struct phist_record *ph_r);
void phist_len(struct phist *ph, int *len);
/* phist_len(ph, &hlen);
 * t = 0 -> most recent access
 * t = 1 -> 2nd most recent access
 * ...
 * t = hlen-1 -> oldest access
 */
void phist_at(struct phist *ph, int t, struct phist_record *ph_r);
void phist_fault_sum(struct phist *ph, int *sum);


#endif /* PHIST_H */