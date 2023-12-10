#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#define quad(x) (x*x)
#define max(a, b) (a>b?a:b)

#include "dequef.h"


/**
   Create an empty deque of floats.

   capacity is both the initial and minimum capacity.
   factor is the resizing factor, larger than 1.0.

   On success it returns the address of a new dequef.
   On failure it returns NULL.
**/

dequef* df_alloc(long capacity, double factor) {
	dequef *vector = malloc(sizeof(dequef));
    vector->data = malloc(capacity * sizeof(float));
	vector->size = 0;
	vector->mincap = vector->cap = capacity;
	vector->first = 0;
	vector->factor = factor;
	return vector;
}



/**
  Release a dequef and its data.
**/
void df_free(dequef* D) {
	free(D->data);
	free(D);
}

/**
   The size of the deque.
**/
long df_size(dequef* D) {
	return D->size;
}



/**
   Add x to the end of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_push(dequef* D, float x) {
	if (D->size == D->cap)
	{
		float *cp = malloc(sizeof(float) * (D->cap*D->factor));
		if (!cp) return 0;
		int pos = D->first;
		for (int i = 0; i < D->size; i++)
		{
			cp[i] = D->data[pos];
			pos = (pos + 1) % D->cap;
		}

		free(D->data);
		D->data = cp;
		D->first = 0;
		D->cap *= D->factor;
	}
	int idx = (D->first + D->size) % D->cap;
 	D->data[idx] = x;
	D->size++;	
	return 1;
}




/**
   Remove a float from the end of D.

   If the deque has capacity/(factor^2) it tries to reduce the array size to
   capacity/factor.  If capacity/factor is smaller than the minimum capacity,
   the minimum capacity is used instead.  If it is not possible to resize, then
   the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_pop(dequef* D) {
	if (D->size == 0) return 0;
	D->size--;
	float val = D->data[(D->first + D->size) % D->cap];
	if (D->size == (D->cap/(quad(D->factor))))
	{
		float *cp = malloc(sizeof(float) * max(D->mincap, (D->cap/D->factor)));
		if (!cp) return val;
		int pos = D->first;
		for (int i = 0; i < D->size; i++)
		{
			cp[i] = D->data[pos];
			pos = (pos + 1) % D->cap;
		}

		free(D->data);
		D->data = cp;
		D->first = 0;
		D->cap = max(D->mincap, (D->cap/D->factor));
	}

	return val;
}




/**
   Add x to the beginning of D.

   If the array is full, it first tries to increase the array size to
   capacity*factor.

   On success it returns 1.
   If attempting to resize the array fails then it returns 0 and D remains unchanged.
**/
int df_inject(dequef* D, float x) {
	if (D->size == D->cap)
	{
		float *cp = malloc(sizeof(float) * (D->cap*D->factor));
		if (!cp) return 0;
		int pos = D->first;
		for (int i = 0; i < D->size; i++)
		{
			cp[i] = D->data[pos];
			pos = (pos + 1) % D->cap;
		}

		free(D->data);
		D->data = cp;
		D->first = 0;
		D->cap *= D->factor;
	}
	D->first = (D->first - 1 + D->cap) % D->cap;
	D->data[D->first] = x;
	D->size++;
	return 1;
}




/**
   Remove a float from the beginning of D.

   If the deque has capacity/(factor^2) elements, this function tries to reduce
   the array size to capacity/factor.  If capacity/factor is smaller than the
   minimum capacity, the minimum capacity is used instead.

   If it is not possible to resize, then the array size remains unchanged.

   This function returns the float removed from D.
   If D was empty prior to invocation, it returns 0.0 and D remains unchanged.
**/
float df_eject(dequef* D) {
	if (D->size == 0) return 0;
	float val = D->data[D->first];
	D->first = (D->first + 1) % D->cap, D->size--;
	if (D->size == (D->cap/(quad(D->factor))))
	{
		float *cp = malloc(sizeof(float) * max(D->mincap, (D->cap/D->factor)));
		if (!cp) return val;
		int pos = D->first;
		for (int i = 0; i < D->size; i++)
		{
			cp[i] = D->data[pos];
			pos = (pos + 1) % D->cap;
		}

		free(D->data);
		D->data = cp;
		D->first = 0;
		D->cap = max(D->mincap, (D->cap/D->factor));
	}

	return val;

}



/**
   Set D[i] to x.

   If i is not in [0,|D|-1]] then D remains unchanged.
**/
void df_set(dequef* D, long i, float x) {
	if (i < 0 || i >= D->size) return;
	D->data[(i + D->first) % D->cap] = x;
}



/**
   Return D[i].

   If i is not in [0,|D|-1]] it returns 0.0.
**/
float df_get(dequef* D, long i) {
	if (i < 0 || i >= D->size) return 0;
	return D->data[(i + D->first) % D->cap];
}



/**
   Print the elements of D in a line.
**/
void df_print(dequef* D) {
	printf("deque (%d): ", D->size);
	for (int i = D->first, q = 0; q < D->size; q++, i = (i + 1) % D->cap)
	{
		printf("%.1f ", D->data[i]);
	}

	printf("\n");
}
