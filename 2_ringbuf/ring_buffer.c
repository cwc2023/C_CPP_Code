#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define min(a,b) ((a < b)?(a):(b))
#define MAX_RING_BUFFER_LEN 4

typedef struct Ring_buffer{
    unsigned char * buffer ;
    int buffer_size ;  
    int write_p ; 
    int read_p ; 
    int data_len ; 
}Ring_buffer, *Ring_buffer_p ;

// init the ring buffer 
int init_ring_buffer(Ring_buffer_p ring_buffer , int max_size)
{
    if(ring_buffer == NULL || max_size == 0)
    {
        return -1; 
    }
    memset(ring_buffer , 0 , sizeof(*ring_buffer)) ; 
    ring_buffer->buffer =(unsigned char *) malloc(max_size*sizeof(unsigned char)) ; 
    if(ring_buffer->buffer == NULL)
    { 
        printf("malloc the buffer fault\n") ; 
        return -1 ; 
    }
    ring_buffer->buffer_size = max_size ; 
    ring_buffer->write_p = 0 ; 
    ring_buffer->read_p = 0 ; 
    ring_buffer->data_len = 0 ;
    
    printf("init the ring buffer succesfull!\n") ; 
    return 0 ; 
}

//write the ring buffer 
int write_ring_buffer(Ring_buffer_p ring_buffer , unsigned char* in_buf , int in_data_len)
{
    if(ring_buffer->data_len == ring_buffer->buffer_size)
    {
        printf("the ring buffer have been full\n") ; 
        return -1 ; 
    }
    else if(in_data_len == 0)
    {
        printf("no data need to write to the ring buffer\n") ; 
        return -1; 
    }

    // 1.计算剩余的空间
    int free_space  = 0 ; 
    if(ring_buffer->write_p >= ring_buffer->read_p)
    {//如果写指针在读指针的前面， 则剩余的空间分为两部分
        free_space =( ring_buffer->buffer_size - ring_buffer->write_p ) + (ring_buffer->read_p - 1); 
    }
    else
    {
        free_space = ring_buffer->read_p -1  - ring_buffer->write_p;
    }
    //2.计算实际写入的数据长度
    int need_write_len = in_data_len>free_space?free_space:in_data_len ; 
    printf("the auctual write data len is %d\n",need_write_len);

    int first_write_len = 0 ;
    int second_write_len = 0 ;
    if(ring_buffer->write_p >= ring_buffer->read_p) //分为两部分可以写入
    {
        /*1.先判断第一部分剩余的空间是否可以写完需要写的数据*/   
        first_write_len = min(ring_buffer->buffer_size - ring_buffer->write_p,need_write_len) ; 
        memcpy(ring_buffer->buffer+ring_buffer->write_p, in_buf,first_write_len);
        ring_buffer->write_p = (ring_buffer->write_p+first_write_len)%ring_buffer->buffer_size;
        ring_buffer->data_len += first_write_len;
        /*2.如果第一次写不完那么第二次进行写入*/
        if(need_write_len>first_write_len)
            {
                int second_write_len = need_write_len - first_write_len ; 
                memcpy(ring_buffer->buffer,in_buf+first_write_len,second_write_len );
                ring_buffer->write_p = (ring_buffer->write_p+first_write_len)%ring_buffer->buffer_size;
                ring_buffer->data_len += first_write_len;
            }
        }
    else
    {
        first_write_len = min(ring_buffer->read_p - ring_buffer->write_p -1 ,need_write_len); 
        memcpy(ring_buffer->buffer + ring_buffer->write_p,in_buf,first_write_len) ; 
        ring_buffer->write_p = (ring_buffer->write_p+first_write_len)%ring_buffer->buffer_size;
        ring_buffer->data_len += first_write_len;
    }
}


//read the ring buffer 
int read_ring_buffer(Ring_buffer_p ring_buffer , unsigned char* out_buf , int out_data_len)
{
    if(out_data_len == 0 || ring_buffer->data_len==0)
    {
        printf("read data length is 0\n");
        return -1 ; 
    }
    
    int read_data_len ;
    read_data_len = out_data_len >ring_buffer->data_len ? ring_buffer->data_len:out_data_len;
    printf("coule read data length is %d\n",read_data_len);
    int first_read_len  = 0 ;
    int second_read_len  =0 ;

    if(ring_buffer->read_p >= ring_buffer->write_p)
    { //分为两部分进行读取
        first_read_len = ring_buffer->buffer_size - ring_buffer->read_p ; 
        memcpy(out_buf,ring_buffer->buffer + ring_buffer->read_p,first_read_len);
        ring_buffer->read_p = (ring_buffer->read_p+first_read_len)% ring_buffer->buffer_size ;
        ring_buffer->data_len = ring_buffer->data_len - first_read_len ; 
        printf("第一部分读取成功\n");
 
        if(read_data_len >  first_read_len)
        {
            second_read_len = read_data_len - first_read_len ; 
            memcpy(out_buf+first_read_len, ring_buffer->buffer,second_read_len);
            ring_buffer->read_p = second_read_len ;
            ring_buffer->data_len = ring_buffer->data_len - second_read_len ;
            printf("第二部分读取成功\n");
        }
    }
    else
    {//一次性全部读取
        memcpy(out_buf,ring_buffer->buffer+ring_buffer->read_p,read_data_len);
        ring_buffer->read_p = (ring_buffer->read_p+read_data_len)% ring_buffer->buffer_size ;
        ring_buffer->data_len = ring_buffer->data_len - read_data_len ; 
        printf("一次性读取成功\n");
    }
    return read_data_len ; 
}



void printf_ring_buffer(Ring_buffer_p ring_buffer) 
{
    for(int i = ring_buffer->read_p ; i <= ring_buffer->data_len;++i)
    {
        printf("the ring_buffer[%d] data is : %d\n", i ,ring_buffer->buffer[i]);
    }
}


int main()
{
    int ret = 0 ; 
    Ring_buffer ring_buffer ; 
    init_ring_buffer(&ring_buffer , MAX_RING_BUFFER_LEN);
    unsigned  char in_buf[] = {2,5,3,4};
    for(int i = 0 ; i < sizeof(in_buf)/sizeof(in_buf[0]) ; ++i)
    {
	    printf("the in_buf[%d] data is: %d\n", i , in_buf[i]) ; 
    }
    ret = write_ring_buffer(&ring_buffer ,&in_buf,sizeof(in_buf)) ; 
    printf_ring_buffer(&ring_buffer) ; 

    unsigned char out_buf[2] ; 
    ret = read_ring_buffer(&ring_buffer,&out_buf,2);
    for(int i = 0 ; i < sizeof(out_buf)/sizeof(out_buf[0]);++i)
    {
        printf("the out_buf [%d] data is %d\n",i,out_buf[i]);
    }
    printf_ring_buffer(&ring_buffer) ; 
    return 0;
}
