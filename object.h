/**
 * Defines commonly used types, such as Pointer, String, byte, File, Directory,
 * and Object, and the instanceof method.
 */

#ifndef OBJECT_H
#define OBJECT_H

#include <stdio.h>
#include <dirent.h>

typedef void *Pointer;
typedef char *String;
typedef signed char byte;
typedef FILE *File;
typedef DIR *Directory;

// all structs should keep track of their type, so that instanceof can work.
// All method structs should have a macro containing more function pointers;
// since Object has no methods, there are no FPs here.
#define OBJECT_METHODS	String type;
typedef struct object_methods {
	/**
	 * A pointer to the superclass's methods. Since Object has no
	 * superclass, this member will be NULL. This should be the only member
	 * in the struct that is not in the macro. The reason is that in
	 * subclasses, it might need to be a different type than ObjectMethods.
	 */
	struct object_methods *super;
	OBJECT_METHODS
} *ObjectMethods;

// Normally, a macro containing fields would be defined up here, but since
// Object has no fields, this is unnecessary.
typedef struct object {
	/**
	 * A pointer to Object's methods. Like the super pointer in the method
	 * struct, this should be the only member in the struct that is not in
	 * the macro for the same reason: in subclasses, it might need to be a
	 * different type than ObjectMethods.
	 */
	ObjectMethods this;
	// The macro would go here.
} *Object;

/**
 * Initializes an Object struct.
 *
 * @param space
 * 	a pointer to a struct of the correct size
 * @return the Object pointer
 */
Object init_object(Pointer space);

/**
 * Initializes an ObjectMethods struct.
 *
 * @param space
 * 	a pointer to a struct of the correct size
 * @return the ObjectMethods pointer
 */
ObjectMethods init_object_methods(ObjectMethods space);

/**
 * Returns a pointer to the methods of Object.
 *
 * @return a pointer to Object's methods.
 */
ObjectMethods get_object_methods();

/**
 * Returns whether the specified object is of the specified type. Returns false
 * (0) if object is NULL.
 *
 * @param object
 * 	the object to be checked
 * @param type
 * 	the type to be checked
 * @throws seg fault - if type is NULL and object is not NULL
 * @return whether the object is of the given type
 */
char instanceof(Object object, String type);

#endif // OBJECT_H
