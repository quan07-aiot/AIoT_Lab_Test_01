#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef enum{
    TEMPERATURE= 0,
    HUMIDITY,
    PRESSURE
}SensorType;

typedef union{
    float temperature;
    float humidity;
    uint32_t pressure;
}SensorValue;

typedef struct{
    uint16_t sensor_id;
    SensorType type;
    SensorValue value;
    uint32_t timestamp;
    uint8_t status;
}SensorPacket;

SensorPacket *create_packets(size_t n){
    SensorPacket *arr = (SensorPacket*)malloc(n*sizeof(SensorPacket));
    if(arr == NULL){
        printf("Cấp Phát bộ nhớ thất bại \n");
        return NULL;
    }
    return arr;
}

// 
int update_packet(SensorPacket *packets, size_t n, uint16_t id, SensorType type, SensorValue value, uint8_t status, uint32_t times){
    for(int i = 0; i < n ; i++){
        if(packets[i].sensor_id == id){
            packets[i].type = type;
            packets[i].value = value;
            packets[i].status = status;
            packets[i].timestamp = times;
        }
    }
}

int compare_packets(const void *a , const void *b){
    const SensorPacket *packets_a = (const SensorPacket*)a;
    const SensorPacket *packets_b = (const SensorPacket*)b;
    if(packets_a->timestamp > packets_b->timestamp) return 1;
    else if (packets_a->timestamp < packets_b->timestamp) return -1;
    else return 0;
}
void sort_packets(SensorPacket *packets, size_t n){
    qsort(packets,n, sizeof(SensorPacket), compare_packets);
    
}

void print_packets(const SensorPacket *packets, size_t n){
    for(size_t i = 0 ; i < n ; i++ ){
        printf("id: %d \n ", packets[i].sensor_id);
        printf("time: %d \n ", packets[i].timestamp);
        printf("status : %d \n ", packets[i].status);
        switch (packets[i].type)
        {
        case HUMIDITY : printf("cảm biến độ ẩm humidity : %.1f \n", packets[i].value.humidity); break;
        case TEMPERATURE : printf("cảm biến nhiệt độ temperture : %.1f\n", packets[i].value.temperature); break;
        case PRESSURE : printf("cảm biến áp suất pressure : %d \n ", packets[i].value.pressure); break;
        }
    }
}

int main(){
    size_t n = 6;
    SensorPacket *my_packets = create_packets(n);
    for(int i = 0 ; i < n ; i++){
        my_packets[i].sensor_id = i;  
    }
    
    uint16_t id;
    SensorType type;
    SensorValue value;
    uint32_t times;
    uint8_t status;

    id =0;
    type =HUMIDITY;
    value.humidity =45.3;
    times = 10;
    status = 1;
    update_packet(my_packets, n, id, type, value, status, times);

    id =1;
    type =TEMPERATURE;
    value.temperature =6.7;
    times = 5;
    status = 0;
    update_packet(my_packets, n, id, type, value, status, times);

    id =2;
    type =PRESSURE;
    value.pressure =98;
    times = 100;
    status = 1;
    update_packet(my_packets, n, id, type, value, status, times);

    id =3;
    type =PRESSURE;
    value.pressure =20;
    times = 55;
    status = 0;
    update_packet(my_packets, n, id, type, value, status, times);

    id =4;
    type =HUMIDITY;
    value.humidity =32;
    times = 100;
    status = 0;
    update_packet(my_packets, n, id, type, value, status, times);

    id =5;
    type =TEMPERATURE;
    value.temperature =26.3;
    times = 500;
    status = 1;
    update_packet(my_packets, n, id, type, value, status, times);

    sort_packets(my_packets, n);

    print_packets(my_packets, n);

    free(my_packets);


    my_packets =NULL;
    return 0;
}