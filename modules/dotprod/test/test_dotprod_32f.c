#include <string.h>
#include "unity.h"
#include "test_utils.h"
#include "freertos/FreeRTOS.h"
#include "freertos/portable.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_clk.h"
#include "soc/cpu.h"

#include "dsls_dotprod.h"
#include "esp_attr.h"


TEST_CASE("DSL check dsls_dotprod_32f_ae32 functionality", "[dsl]")
{
    float check_value = 1235;
    int max_N = 1024;
    float* x = (float*)malloc(max_N*sizeof(float));
    float* y = (float*)malloc(max_N*sizeof(float));
    float* z = (float*)malloc(max_N*sizeof(float));

    for (int i=0 ; i< max_N ; i++)
    {
        x[i] = 0;
        y[i] = 1000;
    }
    
    z[0] = check_value;
    z[2] = check_value + 1;

    for (int i=1 ; i< 1024 ; i++)
    {
        esp_err_t status = dsls_dotprod_32f_ae32(x,y,&z[1],i);
        TEST_ASSERT_EQUAL(status, ESP_OK);
        TEST_ASSERT_EQUAL(check_value, z[0]);
        TEST_ASSERT_EQUAL(check_value + 1, z[2]);
        TEST_ASSERT_EQUAL(0, z[1]);
    }
    for (int i=0 ; i< max_N ; i++)
    {
        x[i] = 1;
        y[i] = 3;
    }
    for (int i=1 ; i< 1024 ; i++)
    {
        esp_err_t status = dsls_dotprod_32f_ae32(x,y,&z[1],i);
        TEST_ASSERT_EQUAL(status, ESP_OK);
        TEST_ASSERT_EQUAL(check_value, z[0]);
        TEST_ASSERT_EQUAL(check_value + 1, z[2]);
        TEST_ASSERT_EQUAL(i*3, z[1]);
    }

    free(x);
    free(y);
    free(z);
}

TEST_CASE("DSL check dsls_dotprod_32f_ae32 benchmark", "[dsl]")
{
    int max_N = 1024;
    float* x = (float*)malloc(max_N*sizeof(float));
    float* y = (float*)malloc(max_N*sizeof(float));
    float* z = (float*)malloc(max_N*sizeof(float));

    for (int i=0 ; i< max_N ; i++)
    {
        x[i] = 0;
        y[i] = 1000;
    }
    
    unsigned int start_b = xthal_get_ccount();
    int repeat_count = 1024;
    for (int i=0 ; i< repeat_count ; i++)
    {
        dsls_dotprod_32f_ae32(x,y,&z[1],1024);
    }
    unsigned int end_b = xthal_get_ccount();

    float total_b = end_b - start_b;
    float cycles = total_b/(1024*repeat_count);
    printf("Benchmark dsls_dotprod_32f_ae32 - %f per sample + overhead.\n", cycles);
    float min_exec = 5;
    float max_exec = 6;
    if (cycles >= max_exec) { 
        TEST_ASSERT_MESSAGE (false, "Exec time takes more then expected!");
    }
    if (cycles < min_exec) { 
        TEST_ASSERT_MESSAGE (false, "Exec time takes less then expected!");
    }

    free(x);
    free(y);
    free(z);
}


TEST_CASE("DSL check dsls_dotprod_32f_ansi functionality", "[dsl]")
{
    float check_value = 1235;
    int max_N = 1024;
    float* x = (float*)malloc(max_N*sizeof(float));
    float* y = (float*)malloc(max_N*sizeof(float));
    float* z = (float*)malloc(max_N*sizeof(float));

    for (int i=0 ; i< max_N ; i++)
    {
        x[i] = 0;
        y[i] = 1000;
    }
    
    z[0] = check_value;
    z[2] = check_value + 1;

    for (int i=1 ; i< 1024 ; i++)
    {
        esp_err_t status = dsls_dotprod_32f_ansi(x,y,&z[1],i);
        TEST_ASSERT_EQUAL(status, ESP_OK);
        TEST_ASSERT_EQUAL(check_value, z[0]);
        TEST_ASSERT_EQUAL(check_value + 1, z[2]);
        TEST_ASSERT_EQUAL(0, z[1]);
    }
    for (int i=0 ; i< max_N ; i++)
    {
        x[i] = 1;
        y[i] = 3;
    }
    for (int i=1 ; i< 1024 ; i++)
    {
        esp_err_t status = dsls_dotprod_32f_ansi(x,y,&z[1],i);
        TEST_ASSERT_EQUAL(status, ESP_OK);
        TEST_ASSERT_EQUAL(check_value, z[0]);
        TEST_ASSERT_EQUAL(check_value + 1, z[2]);
        TEST_ASSERT_EQUAL(i*3, z[1]);
    }

    free(x);
    free(y);
    free(z);
}

TEST_CASE("DSL check dsls_dotprod_32f_ansi benchmark", "[dsl]")
{
    int max_N = 1024;
    float* x = (float*)malloc(max_N*sizeof(float));
    float* y = (float*)malloc(max_N*sizeof(float));
    float* z = (float*)malloc(max_N*sizeof(float));

    for (int i=0 ; i< max_N ; i++)
    {
        x[i] = 0;
        y[i] = 1000;
    }
    
    unsigned int start_b = xthal_get_ccount();
    int repeat_count = 1024;
    for (int i=0 ; i< repeat_count ; i++)
    {
        dsls_dotprod_32f_ansi(x,y,&z[1],1024);
    }
    unsigned int end_b = xthal_get_ccount();

    float total_b = end_b - start_b;
    float cycles = total_b/(1024*repeat_count);
    printf("Benchmark dsls_dotprod_32f_ansi - %f per sample + overhead.\n", cycles);
    float min_exec = 10;
    float max_exec = 20;
    if (cycles >= max_exec) { 
        TEST_ASSERT_MESSAGE (false, "Exec time takes more then expected!");
    }
    if (cycles < min_exec) { 
        TEST_ASSERT_MESSAGE (false, "Exec time takes less then expected!");
    }

    free(x);
    free(y);
    free(z);
}