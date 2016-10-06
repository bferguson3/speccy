void drawstring_pascal(unsigned char *aS, unsigned char aX, unsigned char aY)
{
    unsigned char i, *s, *d, sx, x, c;
    unsigned char *datap = (unsigned char*)(int*)propfont_data - 32 * FONTHEIGHT;
    unsigned char *widthp = (unsigned char*)(int*)propfont_width - 32;
    for (i = 0; i < FONTHEIGHT; i++)
    {
        s = aS+1;
        c = *aS;
        sx = 0;
        x = aX;
        d = (unsigned char*)yofs[aY];
        while (c)
        {
            unsigned char ch = *s;
            unsigned char data = datap[ch * FONTHEIGHT];
            unsigned char width = widthp[ch];
            if (data)
            {
                *d |= data >> sx;
            }
            
            sx += width;
            if (sx > 8)
            {
                d++;
                sx -= 8;
                if (data)
                {
                    *d = data << (width - sx);
                }
            }
            s++;
            c--;
        }
        aY++;
        datap++;
    }
}

void drawstring(unsigned char *s, unsigned char x, unsigned char y)
{
    unsigned char temp[128];
    unsigned char *p;
    temp[0] = 0;
    p = temp + 1;
    while (*s)
    {
        *p = *s;
        p++;
        s++;
        temp[0]++;
    }
    drawstring_pascal(temp, x, y);
}

void drawstring_lr_pascal(unsigned char *s, unsigned char x, unsigned char y)
{
    unsigned char i;
    unsigned char c;
    char sx = 0;
    unsigned char *yp[8];
    unsigned char *datap = (unsigned char*)(int*)propfont_data - 32 * FONTHEIGHT;
    unsigned char *widthp = (unsigned char*)(int*)propfont_width - 32;
    for (i = 0; i < 8; i++)
    {
        yp[i] = (unsigned char*)yofs[y + i] + x;
    }
    c = *s;
    s++;
    while (c)
    {
        unsigned char ch = *s;
        unsigned char wd = widthp[ch];
        unsigned char *chp = datap + ch * FONTHEIGHT;
        if (*s != 32)
        {
            for (i = 0; i < 8; i++, chp++)
            {
                unsigned char data = *chp;
                if (data)
                {
                    *(yp[i]) |= data >> sx;                        
                }
            }
        }
        else
        {
            chp += 8;
        }
        
        sx += wd;
        if (sx > 8)
        {
            sx -= 8;
            chp -= 8;            
            for (i = 0; i < 8; i++, chp++)
            {
                unsigned char data = *chp;
                yp[i]++;
                if (data)
                {
                    *(yp[i]) = data << (wd - sx);
                }
            }            
        }
        s++;
        c--;
    }
}

void drawstring_lr(unsigned char *s, unsigned char x, unsigned char y)
{
    unsigned char temp[128];
    unsigned char *p;
    temp[0] = 0;
    p = temp + 1;
    while (*s)
    {
        *p = *s;
        p++;
        s++;
        temp[0]++;
    }
    drawstring_lr_pascal(temp, x, y);
}