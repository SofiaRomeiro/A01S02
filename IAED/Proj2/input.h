#ifndef __INPUT_H__
#define __INPUT_H__

typedef struct input* input_s;

input_s inputConstructor();
void inputDestructor(input_s input);

#endif