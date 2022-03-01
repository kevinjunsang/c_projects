#include "stack.h"
#include <stdbool.h>
#include <stdint.h>

struct Stack {
	uint32_t top;
	uint32_t capacity;
	Node **items;
};

Stack *stack_create(uint32_t capacity) {
	Stack *s = (Stack *)malloc(sizeof(Stack));
	if (s != NULL) {
		s->top = top;
		s->capacity = capacity;
		s->items = (Node **)malloc(s->capacity * sizeof(item *));
		if (s->items == NULL) {
			free(s);
			s = NULL;
		}
	}
	return s;
}

void stack_delete(Stack **s) {
	if (*s->items == NULL) {
		free(*s);
		*s = NULL;
	}
}

bool stack_empty(Stack *s) {
	if (s->top == 0) {
		return true;
	}
	else {
		return false;
	}
}

bool stack_full(Stack *s) {
	if (s->top == s->capacity) {
		return true;
	}
	else {
		return false;
	}
}

uint32_t stack_size(Stack *s) {
	return s->top;
}

bool stack_push(Stack *s, Node *n) {
	if (stack_full(s)) {
		s->capacity *= 2;
		s->items = (Node *)realloc(s->items, s->capacity * sizeof(Node));
	}
	s->items[s->top] = *n;
	s->top += 1;
	return true;
}

bool stack_pop(Stack *s, Node **n) {
	if (stack_empty(s)) {
		return false;
	}
	s->top -= 1;
	*n = s->items[s->top];
	return true;
}

void stack_print(Stack *s) {
	for (uint32_t

