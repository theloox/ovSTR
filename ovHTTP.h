#include <stdio.h>

#include <curl/curl.h>

#include <ovStr/ovStr.h>
#include <ovStr/ovStrArray.h>

#ifndef _OVHTTP_H
#define _OVHTTP_H

#define _HTTP_USER_AGENT "Mozilla/4.0 (compatible; ovHTTP; FreeBSD)"
#define _HTTP_TIMEOUT 60

/* write callback function */
size_t _http_callback(void *ptr, size_t size, size_t nmemb, void *data);

ovStr http_get(ovStr url, ovStr vars = "", ovStrArray header = "");

#endif
