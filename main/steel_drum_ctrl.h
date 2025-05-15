#include <inttypes.h>

void drum_parse_command(const char* command, uint32_t len);
void drum_setup();
void drum_play_note(int note);
void drum_play_multiple(int* notes, int count);