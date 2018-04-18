#include <czmq.h>
#include <stdlib.h>

//Reading config file
char* configFileName = "conf/emulator.config";
zhashx_t *_hashConfigured;
zloop_t *loop;
unsigned long long timestamp;
zsock_t *push;
FILE *writefile;

//This function is returning current timestamp in milli seconds
unsigned long long getTimestampInMillis(){
    struct timeval tv;
	gettimeofday(&tv, NULL);
    return (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
}

//
int generation(zloop_t *loop, int timer_id, void *arg)
{
    double r;
    char msg[300];
    zlistx_t *tmp = zlistx_new ();
    assert (tmp);
    assert (zlistx_size (tmp) == 0);
    tmp = arg;
    char *tp = zlistx_first (tmp);
    double *rng = zlistx_last (tmp);
    double min = rng[0];
    double max = rng[1];
    const double range = 1 + max - min;
    const double buckets = RAND_MAX / range;
    const double limit = buckets * range;
    //printf("\n======>>>>%f========%f<<<<<<<======",min,max);
    do
    {
        r = rand();
    } while (r >= limit);
    
    timestamp = getTimestampInMillis();

    double value = min + (r / buckets);
    sprintf(msg,"%s,%llu,%f",tp,timestamp,value);
    //printf("\n%s",msg);
    //FILE *dmp;
    //dmp = fopen("test.txt","a");
    fprintf(writefile,"%s\n", msg);
    zstr_send(push, msg);
}

main(){
	writefile = fopen("test.txt","a");
	_hashConfigured = zhashx_new ();
        assert (_hashConfigured);
        assert (zhashx_size (_hashConfigured) == 0);
        assert (zhashx_first (_hashConfigured) == NULL);
        assert (zhashx_cursor (_hashConfigured) == NULL);

	loop = zloop_new ();
        assert (loop);
	push = zsock_new_push ("tcp://127.0.0.1:9000");
	char* line;
        size_t len = 0;
        ssize_t read;
        FILE* file = fopen(configFileName, "r");
        while ((read = getline(&line, &len, file)) != -1){
                if(read != 1){
			zlistx_t *list = zlistx_new ();
        		assert (list);
        		assert (zlistx_size (list) == 0);

                        line[strlen(line)-1] = 0;
                        printf("%s\n", line);
			char* topic = strtok(strdup(line), "@");
                        char* var = strtok(NULL, "/");
			char* param = strtok(NULL,"/");
                        char* ofreq = strtok(NULL,"/");
                        char* omin = strtok(NULL,"/");
                        char* omax = strtok(NULL,"\0");
                        int freq = atoi(ofreq);
                        double min = atof(omin);
                        double max = atof(omax);
                        printf("%s\n", var);
                        printf("%d\n", freq);
                        printf("%f\n", min);
                        printf("%f\n", max);
                        int tmp = 1000/freq;
			
                        double *range = (double *)malloc(2 * sizeof(double));
                        *(range + 0) = min;
                        *(range + 1) = max;
			zlistx_add_end (list, topic);
			zlistx_add_end (list, range);
                        int tid = zloop_timer (loop, tmp, 0, generation, list);
		}
	}
	zloop_start (loop);
}
