#include <stdio.h>
#include <math.h>
#include <float.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json/json.h>
#include "psquared.h"

typedef struct VacBreakStats
{
	char BREAK_LEVEL_KEY[]="low_vac";
	char VAC_LEVEL_KEY[]="high_vac";
	char MAXIMA_1_KEY[]="maxima_1";
	char MAXIMA_2_KEY[]="maxima_2";
	char MAXIMA_3_KEY[]="maxima_3";
	char MAXIMA_4_KEY[]="maxima_4";
	char LB_PERCENTAGE_KEY[]="percent_lb_rejection";
	char UB_PERCENTAGE_KEY[]="percent_ub_rejection";
	char P_G[]="percent_green";
	char P_Y[]="percent_yellow";
	char P_R[]="percent_red";
	char P_VAC[]="percent_high_vac";
	char P_BREAK[]="percent_low_vac";
	char P_1[]="percent_1st_maxima";
	char P_2[]="percent_2nd_maxima";
	char P_3[]="percent_3rd_maxima";
	char P_4[]="percent_4th_maxima";
	char HIST_KEY[]="hist_values";
	json_object * algoResult;
	json_object * vacLevelsGaugeDoc = json_object_new_object("{\"gaugeRule\": {\"_id\": \"Vacuum Frequency (10 minutes)\",\"type\": \"gaugerule\",\"rank\": 99999990,\"barColor\": [\"green\",\"green\",\"green\",\"green\"],\"coloredBar\": false,\"display\": \"bar\",\"yUnit\": \"%\",   \"unitSystem\": {    \"mks\": {      \"x\": {        \"unit\": \"cmHg\",        \"func\": \" 2.54*_\"      },      \"y\": {        \"unit\": \"%\",        \"func\": \"_\"      }    },    \"fps\": {      \"x\": {        \"unit\": \"inHg\",        \"func\": \"_\"      },      \"y\": {        \"unit\": \"%\",        \"func\": \"_\"      }    }  } , \"xUnit\":\"inHg\",\"hasUnit\":\"true\"},\"pmfunction\": \"Blower:  Vacuum Frequency (10 minutes)\",\"subassembly\": \"Blower\",\"gaugeName\": [],\"gaugeValue\": [],\"display\": \"bar\",\"type\":\"gauge\"}");
	json_object * histogramGaugeDoc = json_object_new_object("{\"gaugeRule\": {\"_id\": \"Vacuum Distribution (10 minutes)\",\"type\": \"gaugerule\",\"rank\": 99999991,\"barColor\": [],\"coloredBar\": false,\"display\": \"bar\",\"hasUnit\":\"true\"  ,  \"yUnit\": \"%\" , \"xUnit\":\"inHg\" ,  \"unitSystem\": {    \"mks\": {      \"x\": {        \"unit\": \"cmHg\",        \"func\": \" 2.54*_\"      },      \"y\": {        \"unit\": \"%\",        \"func\": \"_\"      }    },    \"fps\": {      \"x\": {        \"unit\": \"inHg\",        \"func\": \"_\"      },      \"y\": {        \"unit\": \"%\",        \"func\": \"_\"      }    }  }},\"pmfunction\": \"Blower:  Vacuum Distribution (10 minutes)\",\"subassembly\": \"Blower\",\"gaugeName\": [],\"gaugeValue\": [],\"display\": \"bar\"  ,\"type\":\"gauge\"}");
	int MA_SIZE = 20;
	double THRESHOLD=0.3;
	double MIN=0;
	double MAX=100;
	double state=-1;
	double curr;
	double prev;
	double diff;
	long currTS;
	long prevTS=-1;
	char * company;
	char * machine;
	char * model;
	char * machineName;
	void (*setMachine)(char *,struct VacBreakStats *);
	void (*setCompany)(char *,struct VacBreakStats *);
	void (*setMachineName)(char *,struct VacBreakStats *);
	void (*setModel)(char *,struct VacBreakStats *);
	bool (*isCompanyAndMachineSet)(struct VacBreakStats *);
	void (*add)(char *, double,struct VacBreakStats * );
	double (*getState)(struct VacBreakStats *);
	
}VacBreakStats;
void setMachine(char * m,struct VacBreakStats * vc)
{
	vc->machine = m;
}

void setCompany(char * c,struct VacBreakStats * vc)
{
	vc->company=c;
}

void setMachineName(char * c1,struct VacBreakStats * vc)
{
	vc->machineName=c;
}

void setModel(char * md,struct VacBreakStats * vc)
{
	vc->model = md;
}

bool isCompanyAndMachineSet(struct VacBreakStats * vc)
{
	if((vc->machine=='\0')|| (vc->company=='\0'))
		return false;
	else
		return true;
}

void  add(char * t, double x)
{
	
}

double getState(struct VacBreakStats * vc)
{
	return vc->state;
}

