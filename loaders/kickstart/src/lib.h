static inline 
bool is_intersection(L4_Word_t start1, L4_Word_t end1, 
		     L4_Word_t start2, L4_Word_t end2)
{
	return ((start1 >= start2) && (start1 <= end2))
		|| ((end1 >= start2) && (end1 <= end2))
		|| ((start1 <= start2) && (end1 >= end2));
}
