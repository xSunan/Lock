typedef struct {
    int count;
} counter_t;

void Counter_Init(counter_t *c, int value);
void Counter_Increment(counter_t *c);
void Counter_Decrement(counter_t *c);
int Counter_GetValue(counter_t *c);