#include <stdlib.h>
#include <stdio.h>


/* compile:
gcc list_all.c
run:
./a.out
 *
 */

struct node {
    int data;
    struct node * next;
};

struct node * build_list_of_ints();
struct node * array_2_list(int arr[], int sz);

/* Creates a new node, that contains the value specified in the argument,
 * and that points to next_in.
 */
struct node * new_node(int value_in, struct node * next_in);

/*  Note that these functions may not have all the security checks.
E.g. not all the functions reading and setting members of a node pointer,
check that the node is not NULL  */


/*  --------  LIST  */
// List implementation uses a DUMMY NODE

// Creates and returns an empty list.
struct node * new_list();

void destroy_list(struct node * Ld);

// Iterates through list and counts nodes.
int compute_length(struct node * Ld);

// Inserts new_node to the specified list, at the position right after
// the node called "previous".
void insert_node(struct node * previous, struct node * new_node);

void print_list_vert(struct node * my_list);

void print_list_horiz(struct node * my_list);

void print_list_pointer(struct node * my_list);

//-------------------------------------------------------------

// ------------- Node functions

/* Creates a new link, that contains the value specified in the argument,
 * and that points to next_in.
 */
struct node * new_node(int value_in,  struct node * next_in) {
    struct node * result = (struct node *) malloc(sizeof (struct node));
    result->data = value_in;
    result->next = next_in;
    return result;
}

/*    --------  LIST functions    */
// List implementation uses a DUMMY NODE

/* Creates and returns an empty list with a dummy node. */
struct node * new_list() {
	struct node * dummy = new_node(0,NULL);
    return dummy;
}

/* Deallocates memory for all nodes in the list and the list object itself. */
void destroy_list(struct node * Ld) {
    struct node * next;
	struct node * current = Ld;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
}

// Inserts new_node after the node called "previous".
void insert_node(struct node * previous, struct node * new_node) {
    if (previous == NULL) {
        printf("\n Cannot insert after a NULL node. No action taken.");
    } else {
        new_node->next = previous->next;
        previous->next = new_node;
    }
}

// Returns 0 for empty lists (that have just one dummy node) and NULL lists
int compute_length(struct node * Ld) {
    if (Ld == NULL) {
        return 0;
    }

    int counter = 0;
    struct node * curr;
    for (curr = Ld->next; curr != NULL; curr = curr->next) {
        counter++;
    }
    return counter;
}


// does not print the dummy node
void print_list_vert(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list> : list is NULL\n");
        return;
    }
    int i = 0;
    struct node * curr;
    printf("\n List items:\n");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("item %d: %d\n", i, curr->data);
        i++;
    }
	printf(" Length of above list = %d\n", i);
}


// does not print the dummy node
void print_list_horiz(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_horiz> : List is NULL\n");
        return;
    }
    int i = 0;
    struct node * curr;

    printf("\n List items: ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%5d    ", curr->data);
        i++;
    }
	printf("\n Length of above list = %d\n", i);
}

// does not print the dummy node
void print_list_pointer(struct node * my_list) {
    if (my_list == NULL) {
		printf("\n<print_list_pointer> : List is NULL\n");
        return;
    }

    int i = 0;
    struct node * curr;
    printf("\n List items:    ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%-11d ", curr->data);
        i++;
    }
    printf("\n List pointers: ");
    for (i = 0, curr = my_list->next; (curr != NULL); curr = curr->next) {
        printf("%p ", curr);
        i++;
    }
	printf("\n Length of above list = %d\n", i);
}

// Builds and returns a list with integers read from standard input.
 struct node * build_list_of_ints() {
   struct node * Ld = new_list();
   struct node * last_node = Ld; // the last (and only) node in the list is the dummy node.
   while(1)
   {
      int number;
      printf("please enter an integer: ");
      int items_read = scanf("%d", &number);
      if (items_read != 1)  // There are no more integers in the read buffer => STOP
      {
         break;
      }

      // allocate memory for the next node
      struct node * new_node_ptr = new_node(number, NULL);
      insert_node(last_node, new_node_ptr);
      last_node = new_node_ptr;
   }
   return Ld;
}


struct node * array_2_list(int arr[], int sz)  {
	int i;
	struct node * last_node, *new_node_ptr;
	struct node * A = new_list();

	last_node = A;  // the last (and only) node of A is the dummy node.
	for (i = 0; i < sz; i++) 	{
		new_node_ptr = new_node(arr[i], NULL);
		insert_node(last_node, new_node_ptr);
		last_node = new_node_ptr;
	}
	return A;
}


//-------------------------------------------------------------


int main()
{
    int option = 999;
    struct node *one;
    struct node *two;
    while(option!=0)
    {
        printf("1. Load from a File 2 Linked List\n2. Check if L1 is sorted\n3. Merge L1 and L2 into L1.\n4. Removes Duplicates from L1 and print again.\n5. Print L1 and L2\n6. Destroy L1 and L2.\n0. Exit\nOption: ");
        scanf("%d",&option);
        switch(option)
        {
            case 1:
                printf("Please enter a list of integers for List 1. Stops when a non-integer character is entered.\n");
                one = build_list_of_ints();
                printf("Please enter a list of integers for List 2. Stops when a non-integer character is entered.\n");
                two = build_list_of_ints();
                break;
            case 2:
                printf("Option 2 - CHECK IF L1 SORTED\n");
                break;
            case 3:
                printf("Option 3 - MERGE L1 AND L2 TO L1\n");
                break;
            case 4:
                printf("Option 4 - REMOVE DUPLICATES IN L1 AND PRINT AGAIN\n");
                break;
            case 5:
                printf("List 1 - ");
                print_list_horiz(one);
                printf("List 2 - ");
                print_list_horiz(two);
                break;
            case 6:
                destroy_list(one);
                destroy_list(two);
                printf("Lists 1 and 2 have been destroyed\n");
                break;
            case 0:
                printf("Exiting...");
                break;
            default:
                printf("Invalid Option. Please try again.\n");
        }
    }
}
