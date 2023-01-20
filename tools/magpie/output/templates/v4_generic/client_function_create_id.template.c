/* the *_CALL_ID is defined as 64 * the interface ID, plus the function number.
 * This restricts us to 64 functions per interface.
*/
#define /*-?function.get_defable_name()-*/_CALL_ID (64 * (/*-?interface.get_uuid()-*/) + /*-?function.get_number()-*/u)
