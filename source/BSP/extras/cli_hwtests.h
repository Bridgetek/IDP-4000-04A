/*
 * cli_hwtests.h - hardware test commands
 */

#ifndef __CLI_HWTESTS_H__
#define __CLI_HWTESTS_H__

int cmd_rotsw(int argc, char *argv[]);
int cmd_sdcard(int argc, char* argv[]);
int cmd_evelogo(int argc, char* argv[]);
int cmd_buzzer(int argc, char* argv[]);
int cmd_temperature(int argc, char* argv[]);

#define CLI_HWTESTS_CMDLIST {"rot", cmd_rotsw},           \
                            {"sd", cmd_sdcard},           \
                            {"eve", cmd_evelogo},         \
                            {"buzzer", cmd_buzzer},       \
                            {"temp", cmd_temperature},

#endif /* __CLI_HWTESTS_H__ */
