#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// {} зона видимости
// первые 8 символов название сообщения (на него можно ссылаться)
// размер в символах (в шестнадцатеричной системе)
// название отправляющей программы
// название принимающей программы
// ! ошибка (код ошибки на той-же строке в шестнадцатеричной системе)
// * состояние программы F|E|W|R (fatal, error, wait, running) 
// 	*F-R можно на той-же строке написать действие (перезапустить программу)
// 	*R-notify (пример приминения)
// - действие (на той-же строке пишется действие)
//	-R перезапустить программу
//	-R=arg0;arg1;arg2 перезапустить программу с аргументами
//	-notify после исправления проблем записать сообщение мол всё исправлено
// [\] конец файла


void u8_to_hex( char *result, const uint8_t x );

char* encoder( const char const *program_name, const char const *recipient_program, const char const *state, const int return_code, const char const *action, char *encoded_str );

char* encode_msg( const char const *program_name, const char const *recipient_program, const char const *msg, char *encoded_str );
