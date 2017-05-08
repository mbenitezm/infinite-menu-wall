#include <stdio.h>
#include <stdlib.h>

// Node structure
struct node
{
  float red;
  float green;
  float blue;

  struct node *next;
}*top = NULL;

// Prototypes
void push();
void pop();
void peek();
void destroy();

// Insert elements in stack
void push(float r, float g, float b)
{
  struct node *temp;

  temp = (struct node*)malloc(sizeof(struct node));

  temp->red = r;
  temp->green = g;
  temp->blue = b;
  temp->next = top;
  top = temp;

  free(temp);
}

// Delete elements from stack
float * pop()
{
  static float rgb[3];
  int counter = 0;

  struct node *temp;
  if (top != NULL) {
    temp = top;
    //Red
    rgb[counter] = temp->red;
    counter ++;
    // Green
    rgb[counter] = temp->green;
    counter ++;
    // Blue
    rgb[counter] = temp->blue;
    top = top->next;
    free(temp);
  }
  else {
    rgb[0] = -1;
    rgb[1] = -1;
    rgb[2] = -1;
  }

  return rgb;
}

// Peek top
float * peek()
{
  static float rgb[3];
  int counter = 0;

  if (top != NULL) {
    //Red
    rgb[counter] = top->red;
    counter ++;
    // Green
    rgb[counter] = top->green;
    counter ++;
    // Blue
    rgb[counter] = top->blue;
  }
  else {
    rgb[0] = -1;
    rgb[1] = -1;
    rgb[2] = -1;
  }

  return rgb;
}

// Destroy Stack
void destroy() 
{
  struct node *temp;
  temp = top;

  while(temp != NULL)
  {
    pop();
    temp = temp->next;
  }
}