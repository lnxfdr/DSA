#include "ploods.h"
CREATE_PLOODS(int);
#include <stdio.h>
#include <assert.h>
int main() {
    printf("Starting PLOODS test suite...\n");    
    int_ploods list;
    BUILD_PLOODS(list, int);
    list._initialize(&list); 
    // Test basic insertion
    list._insert(&list, 0, 10);
    assert(list._size(&list) == 1);
    assert(list._empty(&list) == 0);
    assert(list.root->value == 10);
    // Test insertion at beginning
    list._insert(&list, 0, 5);
    assert(list._size(&list) == 2);
    assert(list.root->value == 5);
    assert(list.root->next->value == 10);
    // Test insertion at end
    list._insert(&list, 2, 20);
    assert(list._size(&list) == 3);
    assert(list.root->next->next->value == 20);
    // Test insertion in middle 
    list._insert(&list, 1, 15);
    assert(list._size(&list) == 4);
    for (int i = 0; i < list._size(&list); i++){
      printf("%d ", list._node_value(&list, list._get_node(&list, i)));
    } 
    
    assert(list.root->next->value == 15);
    assert(list.root->next->next->value == 10);
    // Test removal from beginning
    list._erase(&list, 0);
    assert(list._size(&list) == 3);
    assert(list.root->value == 15);
    // Test removal from end
    list._erase(&list, 2);
    assert(list._size(&list) == 2);
    assert(list.root->next->value == 10);
    assert(list.root->next->next == NULL);
    // Test removal from middle
    list._insert(&list, 2, 25);
    list._erase(&list, 1);
    assert(list._size(&list) == 2);
    assert(list.root->value == 15);
    assert(list.root->next->value == 25);
    list._dispose(&list);
    printf("Insertion and removal tests passed.\n");
    return 0;
}

