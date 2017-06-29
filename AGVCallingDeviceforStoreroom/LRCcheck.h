#ifndef LRCCHECK_H
#define LRCCHECK_H

char LRC(const char* src, int len)
{
    char lrc = 0;
    for(int i = 0;i<len;i++)
    {
        lrc += src[i];
    }
    lrc = (~lrc)+1;
    return lrc;
}

#endif // LRCCHECK_H
