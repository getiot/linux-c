#include <stdio.h>
#include <stdbool.h>
#include <curl/curl.h>


size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);	
    return written;
}

//显示文件传输进度，dltotal代表文件大小，dlnow代表传输已经完成部分
//clientp是CURLOPT_PROGRESSDATA传入的值
int progress_callback(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{	
    if (dltotal != 0)
    {
        printf("%lf / %lf (%lf %%)\n", dlnow, dltotal, dlnow*100.0 / dltotal);
    }	
    return 0;
}

int main()
{
    const char *netlink = "https://static.getiot.tech/flag-of-china.png";
    const char *output = "test.png";

    curl_global_init(CURL_GLOBAL_ALL);		//初始化全局资源

    CURL *curl = curl_easy_init();		//初始化句柄

    //需要的话，可以设置代理
    //curl_easy_setopt(curl, CURLOPT_PROXY, "127.0.0.1:1080");

    //访问网址
    curl_easy_setopt(curl, CURLOPT_URL, netlink);

    //设置用户代理
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.121 Safari/537.36");

    //注意以二进制打开
    FILE *fp = fopen(output, "wb");
    if (fp == NULL)
    {
        perror("fopen");
        curl_easy_cleanup(curl);
        return 0;
    }

    //写出数据
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    
    //实现下载进度
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
    curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_callback);
    curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, NULL);

    //运行
    curl_easy_perform(curl);

    curl_easy_cleanup(curl);			//释放句柄

    fclose(fp);

    curl_global_cleanup(); //释放全局资源

    return 1;
}
