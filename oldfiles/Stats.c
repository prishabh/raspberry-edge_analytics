#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <json/json.h>
#include "Dictionary.h"
#include "psquared.h"

typedef struct Stats
{
	double n;
	double m1;
	double m2;
	double m3;
	double m4;
	double min;
	double max;
	double count;
	double sumOfSquare;
	PSquared p2;
	PSquared p5;
	PSquared p20;
	PSquared p40;
	PSquared p60;
	PSquared p80;
	PSquared p90;
	PSquared p95;
	PSquared p98;
	void (*add) (double _x , struct Stats *);
	double (*getCount) (struct Stats *);
	double (*getSumOfSquare) (struct Stats *);
	double (*getMean) (struct Stats *);
	double (*getVariance) (struct Stats *);
	double (*getSkewness) (struct Stats *);
	double (*getKurtosis) (struct Stats *);
	double (*getRms) (struct Stats *);
	json_object getSummary(char * , struct Stats *);
}Stats;

void add(double _x , struct Stats * st){
	st->count = st->count + 1;
	if(st->count == 1){st->min = _x; st->max = _x;}
	if(_x < st->min)
    st->min = _x;
	if(_x > st->max )
    st->max = _x;
	double x = _x;
	if(!isnan(x)){
		st->sumOfSquare = st->sumOfSquare + x * x;
		double n1 , delta , delta_n, delta_n2, term1;
		n1 = st->n;
        st->n = st->n + 1;
        delta = x - st->m1;
        delta_n = delta / st->n;
        delta_n2 = delta_n * delta_n;
        term1 = delta * delta_n * n1;
        st->m1 += delta_n;
        st->m4 += term1 * delta_n2 * ( st->n * st->n - 3 * st->n + 3) + 6 * delta_n2 * st->m2 - 4 * delta_n * st->m3;
        st->m3 += term1 * delta_n * ( st->n - 2) - 3 * delta_n * st->m2;
        st->m2 += term1;
	}
}

double getCount(struct Stats * st){
	return st->count;
}

double getSumOfSquare(struct Stats * st){
	return st->sumOfSquare;
}

double getMean(struct Stats * st){
	return st->m1;
}

double getVariance(struct Stats * st){
	return st->m2 / ( st->n - 1);
}

double getSkewness(struct Stats * st){
	return sqrt(st->n) * st->m3 / pow(st->m2,1.5);
}

double getKurtosis(struct Stats * st){
	return (st->n * st->m4 / ( st->m2 * st->m2 )) - 3 ;
}

double getRms(struct Stats * st){
	return sqrt(st->sumOfSquare) / st->n;
}

json_object getSummary(char * Dictionary.Statistics, struct Stats * st){
	Dictionary.Statistics Statis;
	int l= sizeof(Statis)/sizeof(char*);
	int i;
	json_object * ret = json_object_new_object();
	for(i=0;i<l;i++)
	{
		switch(Statis[i])
		{
			case MIN:
				json_object_object_add(ret,Statis[i],st->min);
			break;
			case MAX:
				json_object_object_add(ret,Statis[i],st->max);
			break;
			case MEAN:
				st.getMean=getMean;
				json_object_object_add(ret,Statis[i],st.getMean(&st));
			break;
			case VARIANCE:
				st.getVariance=getVariance;
				json_object_object_add(ret,Statis[i],st.getVariance(&st));
			break;
			case SKEWNESS:
				st.getSkewness=getSkewness;
				json_object_object_add(ret,Statis[i],st.getSkewness(&st));
			break;
			case KURTOSOS:
				st.getKurtosis=getKurtosis;
				json_object_object_add(ret,Statis[i],st.getKurtosis(&st));
			break;
			case RMS:
				st.getRms=getRms;
				json_object_object_add(ret,Statis[i],st.getRms(&st));
			break;
		}
	}
	return json_object_to_json_string(ret);
}