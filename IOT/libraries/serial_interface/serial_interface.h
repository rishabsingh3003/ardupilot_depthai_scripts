#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstring>

#define ECHO_TEST_TXD 17
#define ECHO_TEST_RXD 16
#define ECHO_TEST_RTS (UART_PIN_NO_CHANGE)
#define ECHO_TEST_CTS (UART_PIN_NO_CHANGE)

#define ECHO_UART_PORT_NUM      (UART_NUM_2)
#define ECHO_UART_BAUD_RATE     (115200)
#define ECHO_TASK_STACK_SIZE    (CONFIG_EXAMPLE_TASK_STACK_SIZE)

#define BUF_SIZE (1024)


class Serial_Interface {

public:

    // To create the initial adjacency matrix
    Serial_Interface();

    uint32_t get_millis_ms();

    void send_heartbeat(uint8_t component_id = 93, uint32_t rate_ms = 1000);

    void send_message(uint16_t len, uint8_t* msg);

private:
    void setup_serial();
    uint32_t last_heartbeat_ms;

};