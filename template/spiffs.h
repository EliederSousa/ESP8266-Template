#ifndef _SPIFFS_H_
#define _SPIFFS_H_

void writeFile(String content, String file);
String readFile(String file);
void openFS();

#endif