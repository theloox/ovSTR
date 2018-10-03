
#include "ovMail.h"

bool mail(ovStr to, ovStr subject, ovStr message, ovStr additional_headers, ovStr additional_parameters)
{

    ovStr cmd, str;

    FILE *f;


    to.replace("\n", "");
    to.replace("\r", "");

    subject.replace("\n", "");
    subject.replace("\r", "");


    cmd.printf("%s %s %s", _SENDMAIL, _SENDMAIL_FLAGS, (const char *)additional_parameters);

    f = popen(cmd, "r+");


    str = "To: ";
    str.strcat(to);
    str.strcat("\n");

    str.strcat("Subject: ");
    str.strcat(subject);
    str.strcat("\n");

    str.strcat(additional_headers);
    str.strcat("\n\n");


    str.strcat(message);


    fwrite((const char *)str, str.Len(), 1, f);


    pclose(f);

}
