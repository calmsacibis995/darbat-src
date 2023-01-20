/*
  @LICENSE@
*/
/*
  Author: Tim Leslie
*/

#ifndef _IGUANA_QUOTA_H
#define _IGUANA_QUOTA_H

#define QUOTA_INF 0x7FFFFFFF

quota_ref_t get_pd_quota(pd_ref_t pd);
int transfer_quota(quota_ref_t q1, quota_ref_t q2, int amount);
int get_balance(quota_ref_t q);

#endif /* _IGUANA_QUOTA_H */
