/**
 * Implements object.h.
 */

#include <string.h>

#include "object.h"

/**
 * A struct containing Object's methods. This is declared globally so that it
 * does not need to be freed.
 */
static struct object_methods raw_methods;
/**
 * A pointer to Object's method struct. This is lazily initialized; it starts
 * out as NULL and only changes value when the client initializes a struct of
 * this type or a subtype.
 */
static ObjectMethods methods = NULL;

/*
 * Specified in object.h.
 */
ObjectMethods init_object_methods(const ObjectMethods space) {
	// normally, this method would get the superclass's methods first, but
	// since Object has no superclass, it does not happen in this case
	// set the type to Object
	space->type = "Object";
	space->super = NULL;
	return space;
}

/*
 * Specified in object.h.
 */
ObjectMethods get_object_methods() {
	if (methods == NULL) { // lazy initialization
		methods = init_object_methods(&raw_methods);
	}
	return methods;
}

/*
 * Specified in object.h.
 */
Object init_object(const Pointer space) {
	const Object result = (Object) space;
	// set the Object's this pointer
	result->this = get_object_methods();
	// normally, another method to initialize fields would be called here.
	// Since Object has no fields, this is unnecessary. Initialization of
	// fields should not be done in this method itself so that field
	// initialization for subclasses can call an init_fields method of the
	// superclass (like a super() call in Java) without resetting the this
	// pointer (note that this method sets the this pointer).
	return result;
}

/*
 * Specified in object.h.
 */
char instanceof(const Object object, const String type) {
	if (object == NULL) { // check for NULL object
		return 0; // false
	}
	if (type == NULL) {
		fprintf(stderr, "instanceof method; type should not be null\n");
		char c = *type; // throw seg fault
		c = c; // to prevent the compiler complaining that c is an
			// unused variable
	}
	// type is not NULL
	// iterate through the linked list of types
	for (ObjectMethods curr = object->this; curr != NULL;
	     curr = curr->super) {
		if (!strcmp(curr->type, type)) { // strings are equal
			return 1; // true
		}
	}
	// if the loop terminates, the Object is not an instance of the given
	// type
	return 0; // false
}
