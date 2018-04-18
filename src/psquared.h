#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

typedef struct Percentile
{
	// Percentile to find
	float p;
	// Last percentile value
	float pValue;
	// Initial observations
	float initial[5];
	int initialCount;
	bool initialized;
	// Marker heights
	float q[5];
	// Marker positions
	int n[5];
	// Desired marker positions
	float n_desired[5];
	// Precalculated desired marker increments
	float dn[5];
	// Last k value
	int lastK;
	void (*psq)(float, struct Percentile *);
	void (*init)(struct Percentile *);
	bool (*acceptInitial)(float, struct Percentile *);
	float (*initialSetPercentile)(struct Percentile *);
	float (*accept_value)(float, struct Percentile *);
	float (*getPValue)(struct Percentile *);
	float (*linear)(int , int , struct Percentile *);
	float (*parabolic)(int , int , struct Percentile *);
	void (*dump)(struct Percentile *);
}Percentile;

void psq(float f, struct Percentile * pq)
{
	// Set percentile
	int i;
	for(i=0;i<5;i++)
	{
		pq->q[i]=0.0;
		pq->n[i]=0;
		pq->n_desired[i]=0.0;
		pq->dn[i]=0.0;
		pq->initial[i]=0.0;
	}
	pq->lastK=0;
	pq->p=f;
	pq->initialized = false;
	pq->initialCount=0;
	
}

void init(struct Percentile * pq)
{
	// Set initialized flag
	pq->initialized=true;
	int i;
	// Process initial observations
	for (i = 0; i < 5; i++)
	{
		//printf("Inside...................");
		// Set initial marker heights
		pq->q[i] = pq->initial[i];

		// Initial marker positions
		pq->n[i] = i;
	}

	// Desired marker positions
	pq->n_desired[0] = 0;
	pq->n_desired[1] = 2 * pq->p;
	pq->n_desired[2] = 4 * pq->p;
	pq->n_desired[3] = 2 + 2 * pq->p;
	pq->n_desired[4] = 4;

	// Precalculated desired marker increments
	pq->dn[0] = 0;
	pq->dn[1] = (float) pq->p / 2.0;
	pq->dn[2] = pq->p;
	pq->dn[3] = (1.0 + (float) pq->p) / 2.0;
	pq->dn[4] = 1;
}

bool acceptInitial(float x, struct Percentile * pq)
{
	int u,v;
	float a;
	if (pq->initialCount < 5)
	{
		int u,v;
		float a;
		pq->initial[pq->initialCount++] = x;
		for (u = 0; u < pq->initialCount; ++u)
		{
			for (v = u + 1; v < pq->initialCount; ++v)
			{
				if (pq->initial[u] > pq->initial[v])
				{
					a =  pq->initial[u];
					pq->initial[u] = pq->initial[v];
					pq->initial[v] = a;
				}
			}
		}
		return false;
	}

	// Enough values available
	//Arrays.sort(initial);
	for (u = 0; u < 5; ++u)
	{
		for (v = u + 1; v < 5; ++v)
		{
			if (pq->initial[u] > pq->initial[v])
			{
				a =  pq->initial[u];
				pq->initial[u] = pq->initial[v];
				pq->initial[v] = a;
			}
		}
	}
	init(pq);
	return true;
}

float initialSetPercentile(struct Percentile * pq)
{
	//printf("INITIALSETPERCENTILE");
	int n = (int) ((pq->p) * (float) (pq->initialCount));
	return pq->initial[n];
}

float accept_value(float x, struct Percentile * pq)
{
	int i;
	// Still recording initial values
	if (!(pq->initialized))
	{
		//printf("IFFFFFFFFFFFFFFFFF");
		if (!(pq->acceptInitial(x,pq)))
		{
			pq->pValue = pq->initialSetPercentile(pq);
			return pq->pValue;
			//printf("LLLLLLLLLLLLL");
		}
	}
	//printf("111111");
	int k = -1;
	if (x < pq->q[0])
	{
		// Update minimum value
		pq->q[0] = x;
		k = 0;
	}
	else if (pq->q[0] <= x && x < pq->q[1])
		k = 0;
	else if (pq->q[1] <= x && x < pq->q[2])
		k = 1;
	else if (pq->q[2] <= x && x < pq->q[3])
		k = 2;
	else if (pq->q[3] <= x && x <= pq->q[4])
		k = 3;
	else if (pq->q[4] < x)
	{
		// Update maximum value
		pq->q[4] = x;
		k = 3;
	}
	//printf("222222");
	// Check if k is set properly
	assert(k >= 0);
	pq->lastK = k;

	// Increment all positions starting at marker k+1
	for (i = k + 1; i < 5; i++)
		pq->n[i]++;
	//printf("333333");
	// Update desired marker positions
	for (i = 0; i < 5; i++)
		pq->n_desired[i] += pq->dn[i];
	//printf("4444444");
	// Adjust marker heights 2-4 if necessary
	for (i = 1; i < (5 - 1); i++)
	{
		float d = pq->n_desired[i] - pq->n[i];

		if ((d >= 1 && (pq->n[i + 1] - pq->n[i]) > 1) || (d <= -1 && (pq->n[i - 1] - pq->n[i]) < -1))
		{
			int ds;
			if (d >= 0)
			ds= 1;
			else
			ds= -1;
			

			// Try adjusting q using P-squared formula
			float tmp = pq->parabolic(ds, i, pq);
			if (pq->q[i - 1] < tmp && tmp < pq->q[i + 1])
			{
				pq->q[i] = tmp;
			}
			else
			{
				pq->q[i] = pq->linear(ds, i, pq);
			}

			pq->n[i] += ds;
		}

	}
	//printf("555555");
	// Set current percentile value for later retrieval
	pq->pValue = pq->q[2];
	return pq->q[2];
}

float getPValue(struct Percentile * pq)
{
	return pq->pValue;
}

float linear(int d, int i, struct Percentile * pq)
{
	return pq->q[i] + (float)d * (pq->q[i + d] - pq->q[i]) / (float)(pq->n[i + d] - pq->n[i]);
}

float parabolic(int d, int i, struct Percentile * pq)
{
	float a = (float) d / (float) (pq->n[i + 1] - pq->n[i - 1]);
	float b = (float) (pq->n[i] - pq->n[i - 1] + d) * (pq->q[i + 1] - pq->q[i]) / (float) (pq->n[i + 1] - pq->n[i]) + (float) (pq->n[i + 1] - pq->n[i] - d) * (pq->q[i] - pq->q[i - 1]) / (float) (pq->n[i] - pq->n[i - 1]);
	return (float) pq->q[i] + a * b;
}

void dump(struct Percentile * pq)
{
	int i;
	printf("\nInitials: ");
	for (i=0;i < (sizeof (pq->initial) /sizeof (pq->initial[0]));i++)
	{
		printf("%f  ",pq->initial[i]);
	}
	printf("\n");
	printf("k: %d",pq->lastK);
	printf("\nq:  ");
	for (i=0;i < (sizeof (pq->q) /sizeof (pq->q[0]));i++)
	{
		printf("%f  ",pq->q[i]);
	}
	printf("\nn:  ");
	for (i=0;i < (sizeof (pq->n) /sizeof (pq->n[0]));i++)
	{
		printf("%d  ",pq->n[i]);
	}
	printf("\nn':  ");
	for (i=0;i < (sizeof (pq->n_desired) /sizeof (pq->n_desired[0]));i++)
	{
		printf("%f  ",pq->n_desired[i]);
	}
}

Percentile* makeInstance(){
	Percentile *pq = malloc(sizeof(Percentile));
	pq->psq = psq;
	pq->init = init;
	pq->acceptInitial = acceptInitial;
	pq->initialSetPercentile = initialSetPercentile;
	pq->accept_value = accept_value;
	pq->getPValue = getPValue;
	pq->linear = linear;
	pq->parabolic = parabolic;
	pq->dump = dump;
	return pq;
}
