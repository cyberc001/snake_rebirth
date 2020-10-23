#include "engine/base/obj.h"

static void __obj_destroy(obj *o){}

obj* new__obj(size_t sz)
{
	obj *n = malloc(sz);
	//memset(n, 0, sz);
	memset(n, 0, sizeof(obj));

	n->destroy = __obj_destroy;

	return n;
}
