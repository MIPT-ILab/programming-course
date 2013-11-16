//{-------------head----------------------------------
//
//! @file    node.cpp
//! @brief   Node structure functions here.
//!
//}-------------head----------------------------------

//{-------------defines-------------------------------

#include "node.h"

//}-------------defines-------------------------------

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

/*
//{-------------declarations-----------------------------------------------

//==------------std_node_t-------------------------------------------------

Node_exceptions std_node_t_free (node_t *token);

Node_exceptions std_node_t_OK (node_t *token);

Node_exceptions std_node_t_dump (node_t *token, FILE *fo);

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

Node_exceptions Node_add (Node *root, 
						  Childs dest, 
						  node_t value = NODE_DEFAULT_VALUE, 
						  Node_exceptions (*node_t_OK) (node_t *token) = std_node_t_OK);

//}-------------declarations-----------------------------------------------
*/

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

//{-------------Node-functions-----------------------------------
//! @brief		Creates new Node
//!
//! @param		nexc        variable for exceptions catched.
//! @param		value       new Node token value.
//! @param		node_t_OK   function that checks if Node token is OK.
//!
//! @return		pointer on the new Node.
//!
//! @see     Node_delete(), std_node_t_OK() 
//}-------------Node-functions-------------------------------------

Node* Node_new (Node_exceptions *nexc,
				node_t value, 
				Node_exceptions (*node_t_OK) (node_t *token))
{
	Node *temp = (Node *)malloc (sizeof (*temp));

	if (!temp) {
		*nexc = NEXC_LACK_OF_MEMORY;
		return NULL;
	}

	temp->lt = NULL;
	temp->rt = NULL;
	temp->token = value;

	Node_exceptions ok = Node_OK (temp, node_t_OK);
	if (ok != NEXC_OK) {
		*nexc = ok;
		return NULL; 
	}

	*nexc = NEXC_OK;
	return temp;
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

Node_exceptions std_node_t_free (node_t *token)
{
	if (!token)
		return NEXC_TOKEN_NILL_POINTER;
	//nothing to free yet.
	return NEXC_OK;
}

//{-------------Node-functions-----------------------------------
//! @brief		Recursively deletes a Node and all it's childs, grandchilds etc.
//!
//! @param		myNode        Node to delete.
//! @param		node_t_free   function that frees token if it is required.
//!
//! @return		exception, if it was catched.
//!
//! @see     Node_new(), std_node_t_free() 
//}-------------Node-functions-------------------------------------

Node_exceptions Node_delete (Node *myNode, 
							 Node_exceptions (*node_t_free) (node_t *token))
{
	if (!myNode)
		return NEXC_NODE_NILL_POINTER;

	if (myNode->lt)
		Node_delete (myNode->lt, node_t_free);

	if (myNode->rt)
		Node_delete (myNode->rt, node_t_free);

	node_t_free (&myNode->token);
	free (myNode);
	myNode = NULL;
	return NEXC_OK;
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

Node_exceptions std_node_t_OK (node_t *token)
{
	if (!token)
		return NEXC_TOKEN_NILL_POINTER;
	// nothing to check.
	return NEXC_OK;
}

//{-------------Node-functions-----------------------------------
//! @brief		Checks if Node and it's token are OK.
//!
//! @param		myNode      Node to check.
//! @param		node_t_OK   function that checks if Node token is OK.
//!
//! @return		exception, if it was catched.
//!
//! @see     Node_new(), std_node_t_OK(), Node_dump(), Node_add() 
//}-------------Node-functions-------------------------------------

Node_exceptions Node_OK (Node *myNode, 
						 Node_exceptions (*node_t_OK) (node_t *token))
{
	if (!myNode)
		return NEXC_NODE_NILL_POINTER;

	if (node_t_OK (&myNode->token) != NEXC_OK)
		return NEXC_TOKEN_NOT_OK;

	return NEXC_OK;
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

Node_exceptions std_node_t_dump (node_t *token, FILE *fo)
{
	if (!token)
		return NEXC_TOKEN_NILL_POINTER;
	int ok = std_node_t_OK (token);
	if (!NODE_T_FORMAT)
		return NEXC_OK;

	Node_exceptions ok = NEXC_OK;

	fprintf (fo, "Hello @, I'm token. %.8X. // %s\n", token, ok ? "ok" : "I'M NOT OK!!!!1!!!1!!1! NOT OK!!!!$@#!!1!");
	fprintf (fo, "I'm equal to__ " NODE_T_FORMAT " __.\n", *token);

	fprintf (fo, "token: That's all.\n\n");
	return NEXC_OK; // Check printfs, man.
}

//{-------------Node-functions-----------------------------------
//! @brief		Dumps Node and it's tokeninto a stream given.
//!
//! @param		myNode      Node to dump.
//! @param		fo          stream to dump into.
//! @param		node_t_OK   function that checks if Node token is OK.
//! @param		node_t_dump function that dumps Node token.
//!
//! @return		exception, if it was catched.
//!
//! @par		It prints:
//!				- That it's Node;
//!				- Adress of this Node;
//!				- If Node is ok or not;
//!				- Node left Child adress;
//!				- Node right Child adress;
//!				- Node token dump (std function can be replaced by another one.);
//!
//! @see     std_node_t_OK(), std_node_t_dump(), Node_OK() 
//}-------------Node-functions-------------------------------------

Node_exceptions Node_dump (Node *myNode, 
						   FILE *fo, 
						   Node_exceptions (*node_t_OK) (node_t *token), 
						   Node_exceptions (*node_t_dump) (node_t *token, FILE *fo))
{
	Node_exceptions ok = Node_OK (myNode, node_t_OK);

	fprintf (fo, "Hello @, I'm Node. %.8X. // %s\n", myNode, (ok == NEXC_OK) ? "ok" : "I'M NOT OK!!!!1!!!1!!1! NOT OK!!!!$@#!!1!");

	fprintf (fo, "\t" "lt = %.8X\n", myNode->lt);
	fprintf (fo, "\t" "rt = %.8X\n", myNode->rt);
	fprintf (fo, "\t" "I have got a token.\n");

	ok = node_t_dump (&myNode->token, fo);
	if (ok != NEXC_OK)
		return ok;

	fprintf (fo, "Node: That's all.\n\n");
	return NEXC_OK; // Check printfs, man.
}

// -------------------------------------------------------------------------------------------------------------------------
// /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
// -------------------------------------------------------------------------------------------------------------------------

//{-------------Node-functions-----------------------------------
//! @brief		Adds a Node to the root if it's possible.
//!
//! @param		root      Node to add new Node to.
//! @param		dest      Const that defines left or right Child of root.
//! @param		value     new Node token value.
//! @param		node_t_OK function that checks if Node token is OK.
//!
//! @return		exception, if it was catched.
//!
//! @see     Node_new(), Node_OK()
//}-------------Node-functions-------------------------------------

Node_exceptions Node_add (Node *root, 
						  Childs dest, 
						  node_t value, 
						  Node_exceptions (*node_t_OK) (node_t *token))
{
	Node_exceptions ok = Node_OK (root, node_t_OK);
	
	if (ok != NEXC_OK)
		return ok;

	Node_exceptions nexc = NEXC_OK;
	if (dest == NODE_LEFT) 
		if (root->lt == NULL) {
			root->lt = Node_new (&nexc, value, node_t_OK);
			return nexc;
		}
		else
			return NEXC_NODE_CHILD_FULL;
	if (dest == NODE_RIGHT) 
		if (root->rt == NULL) {
			root->rt = Node_new (&nexc, value, node_t_OK);
			return nexc;
		}
		else
			return NEXC_NODE_CHILD_FULL;
	return NEXC_NODE_UB;
}