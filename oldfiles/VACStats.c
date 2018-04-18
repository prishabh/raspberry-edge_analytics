#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json/json.h>
#include "json_tokener.h"
#include "Dictionary.h"
#include "psquared.h"

typedef struct VACStats
{
	const double M=-2.036;
	const double C=34.136;
	VacBreakStats vbStats;
	Stats xStats;
	json_object * raw = json_object_new_array();
	json_object * meta;
	char * machine;
	char * machineName;
	char * company;
	char * model;
	PSquared p2;
	PSquared p5;
	PSquared p20;
	PSquared p40;
	PSquared p60;
	PSquared p80;
	PSquared p90;
	PSquared p95;
	PSquared p98;
	//void (*VACStats)(char *, struct VACStats *);
	void (*push)(json_object *);
	json_object (*getSummary)();
}VACStats;

/*void VACStats(char * jo, struct VACStats * va)
{
	va->meta = json_tokener_parse (jo);
	va->vbStats.setCompany(json_object_get_string(json_object_object_get(meta, "companyName")));
	va->vbStats.setMachine(json_object_get_string(json_object_object_get(meta, "machineId")));
	va->vbStats.setModel(json_object_get_string(json_object_object_get(meta, "modelName")));
	va->vbStats.setMachineName(json_object_get_string(json_object_object_get(meta, "machineName")));
	
}*/

/*void push(json_object * all)
{
	char * datatype;
	datatype = json_object_get_type(json_object_object_get(all, "data"));
}*/

json_object getSummary()
{
	printf("summary vacstats start");
	json_object * ret = json_object_new_object();
	json_object * tmp;
	json_object_object_add(ret,"VAC", xStats.getSummary(Dictionary.Statistics[]{
				Dictionary.Statistics[1],
                Dictionary.Statistics[2],
                Dictionary.Statistics[4],
                Dictionary.Statistics[3],        	
				}));
	json_object_object_add(all,"stats",ret);
	return all;
}