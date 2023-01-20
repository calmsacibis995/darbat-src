/*
 * dynamic.c
 *
 */

/*
 * The purpose of this is simple, to build things that you want to get built,
 * but not linked in.  (note: you will probably want to link them in, just not
 * using the defaults in iguana-project.  This is useful for things like
 * device drivers where things might be dynamically instantiated and you want
 * to link EVERYTHING in instead fo selected bits, since you never know what
 * you need at runtime.
 *
 * Currently, this is only used by the xnu driver component (I/O Kit).
 *
 * To use you want to place the libraries you want to get built in the
 * LIBS= line.  They are not actually linked in, since they are not referenced
 * anywhere.  But they are built.  Which is what you want.
 */

