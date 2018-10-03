#include "ovHTTP.h"

/* write callback function */
size_t _http_callback(void *ptr, size_t size, size_t nmemb, void *data)
{
    /* Declarations */
    ovStr *str;
    size_t realsize;

    /* Init */
    str = (ovStr *)data;
    realsize = size * nmemb;


    str->strcat((const char *)ptr, realsize);

    return(realsize);
}

ovStr http_get(ovStr url, ovStr vars, ovStrArray header)
{
    /* Declarations */
    CURL *curl;
    ovStr ret;

    /* Init */


    /* Init CURL */
    curl = curl_easy_init();


    /* Set CURL options */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _http_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ret);

    curl_easy_setopt(curl, CURLOPT_URL, (const char *)url);

    curl_easy_setopt(curl, CURLOPT_USERAGENT, _HTTP_USER_AGENT);

    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, _HTTP_TIMEOUT);


    /* Go for it! */
    curl_easy_perform(curl);

    /* Clean-up */
    curl_easy_cleanup(curl);

    return(ret);
}

