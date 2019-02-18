#include "node.h"
#include <CUnit/Basic.h>
#include <CUnit/Console.h>
#include <CUnit/CUCurses.h>
#include <CUnit/TestRun.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_NODES 10

Node* test_head;
Node* forward[NUM_NODES] = {0};
Node* reverse[NUM_NODES] = {0};

/*
 * Nodes have pointers to the next pointer field, not the head of the next node.
 * This function returns a pointer to the next node's head given a void pointer
 * to the next node's next pointer.
 */
Node *get_head(void *p) {
  return p == NULL
             ? NULL
             : ((Node *)((char *)(p) - (unsigned long)(&((Node *)0)->ptr)));
}

/*
 * Generate a linked list of length @count with randomized contents
 */
Node *gen_rand_list(unsigned int count) {
  Node *head, *tail, *curr;
  //void *p;
  unsigned int i;

  head = tail = curr = NULL;
  srand(time(NULL));
  for (i = 0; i < count; i++) {
    curr = (Node *)malloc(sizeof(Node));
    memset(curr, 0, sizeof(Node));
    curr->var = curr->val.n = rand() % 1000;
    if (head == NULL) {
      head = tail = curr;
    } else {
      tail->ptr = &(curr->ptr);
      tail = curr;
    }
  }
  return head;
}

/*
 *  Test correctness of a linked list.
 *  Return one on correct, zero on non-correct.
 */
unsigned int verify_correctness(Node *h1, Node *h2) {
  while (h1 != NULL) {
    if (h2 == NULL)
      return 0;
    if (h1->var != h2->var)
      return 0;
    h1 = get_head(h1->ptr);
    h2 = get_head(h2->ptr);
  }
  if (h2 != NULL)
    return 0;
  return 1;
}

/*
 * Print the address and contents of a Node.
 */
void _printNode(Node* n){
  if (n != NULL){
    printf("Node [%p] = {.val=%d, .ptr=%p, .var=%d}\n", n, n->val.n,n->ptr, n->var);
  }
  else{
    printf("(nil)\n");
  }
}

/*
 * Print each Node in a linked list of Nodes beginning with n (n may be a node * in middle of list).
 */
void _printNodeList(Node* n){
  while (n != NULL){
    _printNode(n);
    n = get_head(n->ptr);
  }
}

/* The suite initialization function.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite(void) {

  // Generate a linked list for Testing
  test_head = gen_rand_list(NUM_NODES);

  // Print the generated linked list
  _printNodeList(test_head);

  return 0;
}

/* The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite(void) {

  // Traverse the linked list, freeing nodes as we go
  for (size_t i = 0; i < NUM_NODES; i++) {
    free(forward[i]);
  }
  return 0;
}

/* Test student's function */
void testMY_REVERSE(void) {

  // Populate the forward array
  Node* n = test_head;
  for (size_t i = 0; i < NUM_NODES; i++) {
    forward[i] = n;
    if (n != NULL)
      n = get_head(n->ptr);
    else
      n = NULL;
  }

  // Reverse the array, assert finishing the function
  n = my_reverse(test_head);
  CU_PASS("Completed reversal function");

  // Populate the reverse array
  for (size_t i = 0; i < NUM_NODES; i++) {
    reverse[i] = n;
    if (n != NULL)
      n = get_head(n->ptr);
    else
      n = NULL;
  }

  // Traverse the arrays, checking for equality, asserting each time.
  for (size_t i = 0; i < NUM_NODES; i++) {
    if (forward[i] != reverse[NUM_NODES - i - 1])
      CU_FAIL_FATAL("my_reverse() did not reverse correctly.")
  }
  CU_PASS("my_reverse() reversed correctly.");
}

int main(int argc, char const *argv[]) {

  // Argparse to find curses or console mode
  char curses = 0;
  char console = 0;
  size_t i;
  for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "--curses") == 0) {
      curses = 1;
      console = 0;
    }
    if (strcmp(argv[i], "--console") == 0) {
      curses = 0;
      console = 1;
    }
  }

  CU_pSuite pSuite = NULL;

  /* initialize the CUnit test registry */
  if (CUE_SUCCESS != CU_initialize_registry())
    return CU_get_error();

  /* add a suite to the registry */
  pSuite = CU_add_suite("Suite_A5", init_suite, clean_suite);
  if (NULL == pSuite) {
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* add the tests to the suite */
  if ((NULL == CU_add_test(pSuite, "Testing my_reverse function ...",
                           testMY_REVERSE))) {
    // Adding one or more tests failed. Cleanup!
    CU_cleanup_registry();
    return CU_get_error();
  }

  /* Run tests */
  CU_basic_set_mode(CU_BRM_VERBOSE);
  if (curses == 1) {
    CU_curses_run_tests();
  } else if (console == 1) {
    CU_console_run_tests();
  } else {
    CU_basic_run_tests();
  }
  CU_cleanup_registry();
  return CU_get_error();
}
