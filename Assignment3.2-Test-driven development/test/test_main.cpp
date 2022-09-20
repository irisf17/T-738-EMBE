#include <avr/delay.h>
#include <unity.h>

#include <fifo.h>

void test_normal_flow(void)
{
    // 1 Setup
    Fifo f;
    f.put(1); 
    f.put(2);
    // get() tekur alltaf fremsta stakið út
    f.get();  
    f.put(3);

    // 2-3 Execute and validate
    TEST_ASSERT_EQUAL(2, f.get());
    TEST_ASSERT_EQUAL(3, f.get());

    // 4 Cleanup
}

void test_underflow(void)
{
    // 1 Setup
    Fifo f;
    f.put(1);
    f.put(2);
    f.get();
    f.get();
    f.get();

    // 2-3 Execute and validate
    TEST_ASSERT_TRUE(f.is_empty());

    // 4 Cleanup
}

void test_reset(void)
{
    Fifo f;
    f.put(1);
    f.put(2);
    f.get();
    f.reset();

    TEST_ASSERT_TRUE(f.is_empty());
}

void test_overflow(void)
{
    Fifo f;
    f.put(1);
    f.put(2);
    f.put(3);
    f.put(4);
    f.put(5);
    f.put(6);

// 6 ætti að vera aftast, 2 fremst
    TEST_ASSERT_EQUAL(2, f.get());
}

void test_overwrite(void)
{
    Fifo f;
    f.put(1);
    f.put(2);
    f.put(3);
    f.put(4);
    f.put(5);
    f.put(6);
    f.put(7);

    TEST_ASSERT_EQUAL(3, f.get());
}

// ---- Circular TESTS ----

void circular_test_normal_flow(void)
{
    // 1 Setup
    Fifo f;
    f.circular_put(1); 
    f.circular_put(2);
    f.circular_get();  
    f.circular_put(3);

    // 2-3 Execute and validate
    TEST_ASSERT_EQUAL(2, f.circular_get());
    TEST_ASSERT_EQUAL(3, f.circular_get());

    // 4 Cleanup
}

void circular_test_underflow(void)
{
    // 1 Setup
    Fifo f;
    f.circular_put(1);
    f.circular_put(2);
    f.circular_get();
    f.circular_get();
    f.circular_get();

    // 2-3 Execute and validate
    TEST_ASSERT_TRUE(f.circular_is_empty());

    // 4 Cleanup
}

void circular_test_reset(void)
{
    Fifo f;
    f.circular_put(1);
    f.circular_put(2);
    f.circular_get();
    f.circular_reset();

    TEST_ASSERT_TRUE(f.circular_is_empty());
}

void circular_test_overflow(void)
{
    Fifo f;
    f.circular_put(1);
    f.circular_put(2);
    f.circular_put(3);
    f.circular_put(4);
    f.circular_put(5);
    f.circular_put(6);

// 6 ætti að vera aftast, 2 fremst
    TEST_ASSERT_EQUAL(2, f.circular_get());
}

void circular_test_overwrite(void)
{
    Fifo f;
    f.circular_put(1);
    f.circular_put(2);
    f.circular_put(3);
    f.circular_put(4);
    f.circular_put(5);
    f.circular_put(6);
    f.circular_put(7);

    TEST_ASSERT_EQUAL(3, f.circular_get());
}


int main()
{
    // NOTE!!! Wait for >2 secs
    // if board doesn't support software reset via Serial.DTR/RTS
    _delay_ms(2000);

    UNITY_BEGIN(); // IMPORTANT LINE!
    // ---- LIST TESTING ----
    RUN_TEST(test_normal_flow);
    RUN_TEST(test_underflow);
    RUN_TEST(test_reset);
    RUN_TEST(test_overflow);
    RUN_TEST(test_overwrite);
    // ---- CIRCULAR TESTING ----
    RUN_TEST(circular_test_normal_flow);
    RUN_TEST(circular_test_underflow);
    RUN_TEST(circular_test_reset);
    RUN_TEST(circular_test_overflow);
    RUN_TEST(circular_test_overwrite);
    UNITY_END(); // stop unit testing
}