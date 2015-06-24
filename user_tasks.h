#ifndef _USER_TASK_
#define _USER_TASK_

// pin for the lcd screen
#define RS (49)
#define E  (45)
#define D0 (44)
#define D1 (43)
#define D2 (42)
#define D3 (41)
#define D4 (40)
#define D5 (39)
#define D6 (38)
#define D7 (37)

void concurrent_increment (int t);

void process1 ();
void process2 ();
void process3 ();
void process4 ();

void setup_lcd();
void lcdMain(int cpt);
void lcdDebug(int val);
void lcd_crnb();

#endif
