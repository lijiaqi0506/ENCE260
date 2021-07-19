/* The main game file for assignment
 * Authors: JIAQI LI, HUNTER CRAIG
 * Date: 14 Oct 2019
 */

#include "system.h"
#include "pacer.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "tinygl.h"
#include "../fonts/font5x7_1.h"





#define PACER_RATE 500
#define MESSAGE_RATE 200


void display_character (char character)
{
    char buffer[2];
    buffer[0] = character;
    buffer[1] = '\0';
    tinygl_text (buffer);
}


int main (void)
{
    char character = 'R';
    char data[3] = {'R', 'P', 'S'};
    char character2 = 'A';
    int i = 0;

    system_init ();
    tinygl_init (PACER_RATE);
    tinygl_font_set (&font5x7_1);
    tinygl_text_speed_set (MESSAGE_RATE);
    navswitch_init ();

    /* TODO: Initialise IR driver.  */
    ir_uart_init ();

    pacer_init (PACER_RATE);

    while (1)
    {
        pacer_wait ();
        tinygl_update ();
        navswitch_update ();

        if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
            if (i < 2) {
                i++;
            } else {
                i = 0;
            }
            character = data[i];
        }

        if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
            if (i > 0) {
                i--;
            } else {
                i = 2;
            }
            character = data[i];
        }

        /* TODO: Transmit the character over IR on a NAVSWITCH_PUSH
           event.  */
        if (navswitch_push_event_p (NAVSWITCH_PUSH)) {
            ir_uart_putc(character);
        }

        display_character (character);

        if (ir_uart_read_ready_p ()) {
            character2 = ir_uart_getc ();
        }

        //AUTHOR JIAQI LI PANDING
        //PAPER VS ROCK
        if (character == 'P' && character2 == 'R') {
            display_character ('W');
            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                 main ();
            }

        }
        if (character == 'R' && character2 == 'P') {
            display_character ('L');
            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                 main ();
            }

        }

        //PAPER VS SCISSORS
        if (character == 'P' && character2 == 'S') {
            display_character ('L');
            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                 main ();
            }

        }
        if (character == 'S' && character2 == 'P') {
            display_character ('W');
            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                 main ();
            }

        }

        //ROCK VS SCISSORS
        if (character == 'R' && character2 == 'S') {
            display_character ('W');
            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                 main ();
            }

        }
        if (character == 'S' && character2 == 'R') {
            display_character ('L');
            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                 main ();
            }

        }

        if (character == character2) {
            display_character('D');
            if (navswitch_push_event_p (NAVSWITCH_EAST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_WEST)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_NORTH)) {
                 main ();
            }
            if (navswitch_push_event_p (NAVSWITCH_SOUTH)) {
                 main ();
            }

        }

    }

    return 0;
}
