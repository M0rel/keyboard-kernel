#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "key_buffers_manager.h"
#include "key_layout_provider.h"
#include "key_manager.h"
#include "key_scancodes.h"

#include "ll_adapter.h"

uint8_t pressed_keys[16] = {0};
keyboard_desc_st_t key_desc = {0};
usb_report_st_t usb_report = {0};

static
void usb_report_init(void)
{
        usb_report.id = 1;
}

void key_descriptor_init(void)
{
        key_desc.keys_layout = get_keys_layout(OS_MAC);
        key_desc.keys_row_cnt = get_keys_row_cnt();
        key_desc.keys_col_cnt = get_keys_col_cnt();
        key_desc.pressed_keys = pressed_keys;
}

int user_main(void)
{
        usb_report_init();
        key_descriptor_init();

        timer_init();

        delay_ms(3000);

        while (true) {
                get_pressed_keys(&key_desc);

                prepare_send_buffer(&key_desc, &usb_report);

                usb_send_report(&usb_report, sizeof(usb_report_st_t));
        };

        return 0;
}
