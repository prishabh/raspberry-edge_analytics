#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <json/json.h>
#include "json_tokener.h"
#include "Dictionary.h"
#include "psquared.h"
typedef struct ACStats
{
	Stats rStats;
	Stats thetaStats;
	Stats phiStats;
	Stats xStats;
	Stats yStats;
	Stats zStats;
	PSquared p2;
	PSquared p5;
	PSquared p20;
	PSquared p40;
	PSquared p60;
	PSquared p80;
	PSquared p90;
	PSquared p95;
	PSquared p98;
	json_object * raw = json_object_new_array();
	char machine[100];
	char machineName[100];
	char company[100];
	char model[100];
	int VARIANCE_WINDOW = 50;
	void (*ACStats)(char *);
	void (*push)(json_object);
	json_object (*getSummary)();
}
void ACStats(char * jo)
{
	meta = json_tokener_parse (jo);
	Stats rStats;
	Stats thetaStats;
	Stats phiStats;
}
void push(json_object all)
{
	double x, y, z, s, r, theta, phi;
	char t[1000];
	x=
	y=
	z=
	json_object * _xyz = json_object_new_array();
	json_object_array_add(_xyz,x);
	json_object_array_add(_xyz,y);
	json_object_array_add(_xyz,z);
	json_object_array_add(raw,_xyz);
	r = sqrt(x * x + y * y + z * z);
	if (!isnan(x) && !isnan(y))
	{
		theta = atan(y / x);
		if (theta > (M_PI / 4))
		theta = theta - (M_PI / 2);
		else if (theta < (-1) * (M_PI / 4))
		theta = theta + (M_PI / 2);
		thetaStats.add(theta);
	}
	if (!isnan(r))
	{
		phi = acos(z / r);
		phiStats.add(phi);
	}
	rStats.add(r);
}
json_object getSummary()
{
	printf("summary ac start");
	json_object * ret = json_object_new_object();
	//json_object * gof = json_object_new_object();
	printf("ac1 start");
	if (isProperBatch())
	{
		json_object_object_add(ret,"R",rStats.getSummary(Dictionary.Statistics[] {Dictionary.Statistics[0], Dictionary.Statistics[4], Dictionary.Statistics[2], Dictionary.Statistics[3], Dictionary.Statistics[1]}));
		json_object_object_add(ret,"THETA",thetaStats.getSummary(Dictionary.Statistics[] {Dictionary.Statistics[0], Dictionary.Statistics[4], Dictionary.Statistics[2], Dictionary.Statistics[3], Dictionary.Statistics[1]}));
		json_object_object_add(ret,"PHI",phiStats.getSummary(Dictionary.Statistics[] {Dictionary.Statistics[0], Dictionary.Statistics[4], Dictionary.Statistics[2], Dictionary.Statistics[3], Dictionary.Statistics[1]}));
		printf("ac1 R theta phi");
	}
	return ret;
	
	
}