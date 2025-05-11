#include "smoods.h"
CREATE_SMOODS(int);
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
void test_circular_buffer() {
    printf("Starting comprehensive circular buffer tests (front-before-back)...\n");

    // Initialize buffer
    int_smoods buffer;
    BUILD_SMOODS(buffer, int);
    buffer._initialize(&buffer);
    assert(buffer._empty(&buffer) == 1);
    assert(buffer._size(&buffer) == 0);

    // Test 1: Basic push/pop operations with front-before-back ordering
    printf("\nTest 1: Basic push/pop operations\n");
    buffer._push_front(&buffer, 10);  // Buffer: [10]
    assert(buffer._at(&buffer, 0) == 10);
    assert(buffer._size(&buffer) == 1);

    buffer._push_back(&buffer, 20);   // Buffer: [10, 20]
    assert(buffer._at(&buffer, 0) == 10);
    assert(buffer._at(&buffer, 1) == 20);

    buffer._push_front(&buffer, 5);   // Buffer: [5, 10, 20]
    assert(buffer._at(&buffer, 0) == 5);
    assert(buffer._at(&buffer, 1) == 10);
    assert(buffer._at(&buffer, 2) == 20);

    // Test pop_front removes first element (5)
    buffer._pop_front(&buffer);       // Buffer: [10, 20]
    assert(buffer._size(&buffer) == 2);
    assert(buffer._at(&buffer, 0) == 10);
    assert(buffer._at(&buffer, 1) == 20);

    // Test pop_back removes last element (20)
    buffer._pop_back(&buffer);        // Buffer: [10]
    assert(buffer._size(&buffer) == 1);
    assert(buffer._at(&buffer, 0) == 10);

    buffer._clear(&buffer);
    // Test 2: Indexing and circular behavior
    printf("\nTest 2: Indexing and circular behavior\n");
    const uint32_t test_size = 5;
    for (int i = 0; i < test_size; i++) {
        buffer._push_back(&buffer, i*10);  // Buffer: [0, 10, 20, 30, 40]
    }
    // Verify front is at index 0 (value 0)
    assert(buffer._at(&buffer, 0) == 0);

    // Verify back is at index size-1 (value 40)
    assert(buffer._at(&buffer, test_size-1) == 40);

    // Test index calculations with capacity
    uint32_t cap = buffer._capacity(&buffer);
    printf("Current capacity: %u\n", cap);

    // Test front_index (should return physical index of logical front)
    int64_t front_idx = buffer._front_index(&buffer, 0, cap);
    assert(front_idx >= 0 && front_idx < cap);

    // Test back_index (should return physical index of logical back)
    int64_t back_idx = buffer._back_index(&buffer, test_size-1, cap);
    assert(back_idx >= 0 && back_idx < cap);

    // Test next_index wraps around correctly
    int64_t next_idx = buffer._next_index(&buffer, back_idx, cap);
    printf("Next index after back (%ld): %ld\n", back_idx, next_idx);

    // Test prev_index wraps around correctly
    int64_t prev_idx = buffer._prev_index(&buffer, front_idx, cap);
    printf("Previous index before front (%ld): %ld\n", front_idx, prev_idx);

    // Test 3: Insert/erase operations maintain ordering
    printf("\nTest 3: Insert/erase operations\n");
    buffer._insert(&buffer, 2, 25);  // Buffer: [0, 10, 25, 20, 30, 40]
    assert(buffer._size(&buffer) == 6);
    assert(buffer._at(&buffer, 2) == 25);
    assert(buffer._at(&buffer, 3) == 20);

    buffer._erase(&buffer, 1);       // Buffer: [0, 25, 20, 30, 40]
    assert(buffer._size(&buffer) == 5);
    assert(buffer._at(&buffer, 1) == 25);

    // Test 4: Find operations respect ordering
    printf("\nTest 4: Find operations\n");
    assert(buffer._find(&buffer, 0, 0) == 0);    // Find first element
    assert(buffer._find(&buffer, 0, 25) == 1);   // Find middle element
    assert(buffer._find(&buffer, 0, 40) == 4);   // Find last element
    assert(buffer._find(&buffer, 0, 99) == -1);  // Not found

    // Test 5: Resizing and capacity
    printf("\nTest 5: Resizing and capacity\n");
    uint32_t old_cap = buffer._capacity(&buffer);
    buffer._reserve(&buffer, old_cap * 2);
    assert(buffer._capacity(&buffer) >= old_cap * 2);
    // Verify data integrity after resize
    assert(buffer._at(&buffer, 0) == 0);
    assert(buffer._at(&buffer, 1) == 25);
    assert(buffer._at(&buffer, 4) == 40);

    // Test 6: Edge cases
    printf("\nTest 6: Edge cases\n");
    buffer._clear(&buffer);

    // Single element operations
    buffer._push_front(&buffer, 100);
    assert(buffer._at(&buffer, 0) == 100);
    buffer._pop_back(&buffer);
    assert(buffer._empty(&buffer));

    buffer._push_back(&buffer, 200);
    assert(buffer._at(&buffer, 0) == 200);
    buffer._pop_front(&buffer);
    assert(buffer._empty(&buffer));

    // Test 7: Reverse operation maintains ordering
    printf("\nTest 7: Reverse operation\n");
    for (int i = 0; i < 5; i++) {
        buffer._push_back(&buffer, i);
    }
    buffer._reverse(&buffer);  // Should become [4, 3, 2, 1, 0]
    assert(buffer._at(&buffer, 0) == 4);
    assert(buffer._at(&buffer, 4) == 0);

    // Test 8: Change sizing factor
    printf("\nTest 8: Sizing factor\n");
    buffer._change_sizing_factor(&buffer, 1.5f);
    // Verify by checking growth behavior
    uint32_t current_cap = buffer._capacity(&buffer);
    while (buffer._size(&buffer) < current_cap) {
        buffer._push_back(&buffer, 0);
    }
    buffer._push_back(&buffer, 0);  // Should trigger growth
    // Cleanup
    buffer._dispose(&buffer);
    printf("\nAll front-before-back circular buffer tests passed successfully!\n");
}

int main() {
    test_circular_buffer();
    return 0;
}

