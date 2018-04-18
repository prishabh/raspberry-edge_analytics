#include <czmq.h>
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <json/json.h>
#include "ACStats.c"

//#include "MQTTClient.h"

#define ADDRESS     "tcp://54.144.127.33:8883"
#define CLIENTID    "edge_rpi"
#define TOPIC       "edge"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

struct json_object *o;
char* sensorId;
char* sensorType;
json_object* content;
double* point;
ACStats acs;
double* contentToArray(char* sensorType, json_object *content){
	if(streq(sensorType,"AC")){
		point = malloc(3*sizeof(double));
		point[0] =  json_object_get_double( json_object_object_get(content, "x"  )); 
		point[1] =  json_object_get_double( json_object_object_get(content, "y"  ));
		point[2] =  json_object_get_double( json_object_object_get(content, "z"  ));
		return point;
	}
}

int recieve(zloop_t *loop, zsock_t *reader, void *arg){
o = json_tokener_parse(zstr_recv(reader));
sensorId =  json_object_get_string(json_object_object_get(o, "sensor_id"));
sensorType = json_object_get_string(  json_object_object_get( json_object_object_get(o, "data"  ), "type"  )  );
content =   json_object_object_get( json_object_object_get(o, "data"  ), "content"  )  ;
//printf("%s  %s\n",sensorId,sensorType);
//parse json string


double* point = contentToArray(sensorType, content);
printf("%f %f %f\n", point[0], point[1], point[2]);
//if AC
if(streq(sensorType,"AC")){
	acs->push(point);
}
//else if VAC


return 0;
}

int scheduler( zloop_t *loop, int timer_id, void *arg){
printf("ping\n");
char* ret = acs->getSummary();
printf("%s\n",ret);
zclock_sleep (5000);
return 0;

}


int main (void)
{

acs->ACStats();

zsock_t *reader = zsock_new_pair (">tcp://127.0.0.1:8876" );
assert (reader);
assert (zsock_resolve (reader) != reader);
assert (streq (zsock_type_str (reader), "PAIR"));
printf("blocking read......\n");
//   printf("%s",zstr_recv(reader));
/*
while(true){
zmsg_t *msg = zmsg_recv (reader);
assert (msg);
char *string = zmsg_popstr (msg);
printf("%s", string);
free (string);
zmsg_destroy (&msg);
printf("...........................\n");
}*/
zloop_t *loop = zloop_new ();
assert (loop);

int rc = zloop_reader (loop, reader, recieve, NULL);
assert (rc == 0);
zloop_timer (loop, 60000, 0, scheduler, NULL);
zloop_reader_set_tolerant (loop, reader);
zloop_start (loop);


zsock_destroy(&reader);
}


