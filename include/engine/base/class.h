#ifndef CLASS_H
#define CLASS_H

/*
	Use #ifdef __CLASS_INIT_CALL_MODE
	To call class initialization function instead of providing class definition.
	Then simply use #define __CLASS_INIT_CALL_MODE inside main() function
	or it's subfunctions, and include all the headers you need again.
*/

typedef struct cls cls;
struct cls
{
	const char *name;
	struct cls *parent;
};

#endif
