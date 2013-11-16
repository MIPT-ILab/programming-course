//{-------------head----------------------------------
//
//! @file    node.h
//! @brief   First prototype of Node.
//!
//}-------------head---------------------------------

#ifndef NODEHEADER
#define NODEHEADER 1
#define NODEVERSION 100

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

//{-------------defines----------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define _CRT_SECURE_NO_WARNINGS

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

//{-------------node-consts-----------------------------------------------

typedef enum Childs Childs;

enum Childs {
	NODE_LEFT  = 0,
	NODE_RIGHT = 1,
};

typedef enum Node_exceptions Node_exceptions;

enum Node_exceptions {
	NEXC_OK                 = 800,
	NEXC_GOT                = 801,
	NEXC_LACK_OF_MEMORY     = 802,
	NEXC_TOKEN_NILL_POINTER = 803,
	NEXC_NODE_NILL_POINTER  = 804,
	NEXC_TOKEN_NOT_OK       = 805,
	NEXC_NODE_CHILD_FULL    = 806,
	NEXC_FILE_CORR_POINTER  = 807,
	NEXC_NODE_UB            = 808,
};

//}-------------node-consts-----------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

//{-------------debugging------------------------------

#define DEBUG

//}-------------debugging------------------------------

#ifdef DEBUG
#define ASSERT(cond)                           \
if (!(cond)) {                                 \
	fprintf (stderr, "# Assertion fail : %s. " \
	"File %s, line %d, function %s\n",         \
	#cond, __FILE__, __LINE__, __FUNCTION__);  \
	abort ();                                  \
}
#define CENSORED  printf
#else
#define ASSERT(cond)
#define CENSORED if (0) printf
#endif

//}-------------defines----------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

//{-------------structures-------------------------------------------------

//{-------------node_t-----------------------------------------------------

typedef int node_t; //node_t is int
#define NODE_T_FORMAT  "%d" //node_t format is "%d"
const node_t NODE_DEFAULT_VALUE = -12; // default value

//}-------------node_t------------------------------------------------------

typedef struct Node Node;

struct Node {
	Node *lt; // left child.
	Node *rt; // right one.
	node_t token;
};

//}-------------structures-------------------------------------------------

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

//{-------------declarations-----------------------------------------------

//==------------std_node_t-------------------------------------------------

Node_exceptions std_node_t_free (node_t *token);

Node_exceptions std_node_t_OK (node_t *token);

Node_exceptions std_node_t_dump (node_t *token, FILE *fo);

Node_exceptions std_node_t_print (node_t *token, FILE *fo);

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

//==------------Node_inner-------------------------------------------------

Node* Node_new (Node_exceptions *nexc, 
				node_t value = NODE_DEFAULT_VALUE,
				Node_exceptions (*node_t_OK) (node_t *token) = std_node_t_OK);

Node_exceptions Node_delete (Node *myNode, 
							 Node_exceptions (*node_t_free) (node_t *token) = std_node_t_free);

Node_exceptions Node_OK (Node *myNode, 
						 Node_exceptions (*node_t_OK) (node_t *token) = std_node_t_OK);

Node_exceptions Node_dump (Node *myNode, 
						   FILE *fo = stderr, 
						   Node_exceptions (*node_t_OK) (node_t *token) = std_node_t_OK, 
						   Node_exceptions (*node_t_dump) (node_t *token, FILE *fo) = std_node_t_dump);

Node_exceptions Node_print (Node *myNode, 
							FILE* fo, 
							int tabs = 0, 
							Node_exceptions (*node_t_print) (node_t *token, FILE *fo) = std_node_t_print);

Node_exceptions Node_add (Node *root, 
						  Childs dest, 
						  node_t value = NODE_DEFAULT_VALUE, 
						  Node_exceptions (*node_t_OK) (node_t *token) = std_node_t_OK);

//}-------------declarations-----------------------------------------------

#endif