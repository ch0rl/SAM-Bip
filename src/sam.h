#ifndef SAM_H
#define SAM_H

void SetInput(unsigned char *_input);
void EnableSingmode();

int SAMMain();

char* GetBuffer();
int GetBufferLength();

#endif
