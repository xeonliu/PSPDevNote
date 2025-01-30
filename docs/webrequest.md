# 进行网络请求

## PSP如何连接网络
### PSP支持的`Wi-Fi`协议
`802.11b`(1999): 工作频段为`2.4GHz`，最高速率半双工11 Mbit/s

> Wi-Fi标准提供向后兼容性，以便旧设备仍然可以与新的接入点和设备进行互操作。
>
> Wi-Fi 4 (802.11n)(2008)
>
> Wi-Fi 5 (802.11ac)(2014)
>
> Wi-Fi 6 (802.11ax)(2019)
### PSP支持的WiFi加密协议
+ WEP
+ WPA-PSK(TKIP)
+ WPA-PSK(AES)
> 不支持
>+ WPA2
>+ WPA2-PSK
>+ WPA3
### 在应用中连接网络
弹出弹窗，选择并连接

## 唤起网络连接弹窗 Network Dialog

## `socket&http lib` in PSPSDK
暂无研究计划

## `curl` & `mbedtls` in PSPDEV package (enable https)
[PSPHDC-23/Jokr at main · KorigamiK/PSPHDC-23](https://github.com/KorigamiK/PSPHDC-23/tree/main/Jokr)

main.c
```cpp
size_t writeCallback(char *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string *)userp)->append((char *)contents, size * nmemb);
    return size * nmemb;
}

CURLcode getRequest(const std::string &url, std::string &buffer, bool verbose = false)
{
    CURL *curl = curl_easy_init();
    if (!curl)
    {
        SDL_Log("Failed to initialize curl");
        return CURLE_FAILED_INIT;
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, verbose);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "curl/7.64.1");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, curl_slist_append(nullptr, "Accept: text/plain"));
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSLVERSION, CURL_SSLVERSION_TLSv1_2);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 20L);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, CURLUSESSL_TRY);

    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK)
        SDL_Log("Failed to perform curl request: %s", curl_easy_strerror(res));

    curl_easy_cleanup(curl);
    return res;
}
```

network.hpp
```cpp

int netDialog(SDL_Renderer *renderer)
{
    int done = 0;

    pspUtilityNetconfData data;

    memset(&data, 0, sizeof(data));
    data.base.size = sizeof(data);
    data.base.language = PSP_SYSTEMPARAM_LANGUAGE_ENGLISH;
    data.base.buttonSwap = PSP_UTILITY_ACCEPT_CROSS;
    data.base.graphicsThread = 17;
    data.base.accessThread = 19;
    data.base.fontThread = 18;
    data.base.soundThread = 16;
    data.action = PSP_NETCONF_ACTION_CONNECTAP;

    struct pspUtilityNetconfAdhoc adhocparam;
    memset(&adhocparam, 0, sizeof(adhocparam));
    data.adhocparam = &adhocparam;

    sceUtilityNetconfInitStart(&data);

    while (!done)
    {
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        switch (sceUtilityNetconfGetStatus())
        {
        case PSP_UTILITY_DIALOG_NONE:
            break;

        case PSP_UTILITY_DIALOG_VISIBLE:
            sceUtilityNetconfUpdate(1);
            break;

        case PSP_UTILITY_DIALOG_QUIT:
            printf("PSP_UTILITY_DIALOG_QUIT");
            sceUtilityNetconfShutdownStart();
            break;

        case PSP_UTILITY_DIALOG_FINISHED:
            done = 1;
            break;

        default:
            break;
        }

        SDL_Delay(10);
    }

    return 1;
}

void netInit(void)
{
    sceNetInit(128 * 1024, 42, 4 * 1024, 42, 4 * 1024);
    sceNetInetInit();
    sceNetApctlInit(0x8000, 48);
}

void startNetworking(SDL_Renderer *renderer)
{
    int rc = sceUtilityLoadNetModule(PSP_NET_MODULE_COMMON);
    if (rc < 0)
        printf("net common didn't load.\n");
    rc = sceUtilityLoadNetModule(PSP_NET_MODULE_INET);
    if (rc < 0)
        printf("inet didn't load.\n");

    netInit();
    netDialog(renderer);
}

void netTerm(void)
{
    sceNetApctlTerm();
    sceNetInetTerm();
    sceNetTerm();
}

void stopNetworking()
{
    sceUtilityUnloadNetModule(PSP_NET_MODULE_INET);
    sceUtilityUnloadNetModule(PSP_NET_MODULE_COMMON);
    netTerm();
}

```

链接`mbedtls mbedcrypto mbedx509`