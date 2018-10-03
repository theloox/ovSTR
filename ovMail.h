
#include <stdio.h>

#include <ovStr/ovStr.h>

#ifndef _OVMAIL_H
#define _OVMAIL_H

#ifndef _SENDMAIL

#warning No _SENDMAIL defined, defaulting to "/usr/sbin/sendmail"
#define _SENDMAIL "/usr/sbin/sendmail"

#endif


#ifndef _SENDMAIL_FLAGS

#warning No _SENDMAIL_FLAGS defined, defaulting to "-t -i"
#define _SENDMAIL_FLAGS "-t -i"

#endif


bool mail(ovStr to, ovStr subject, ovStr message, ovStr additional_headers = "", ovStr additional_parameters = "");

#endif
